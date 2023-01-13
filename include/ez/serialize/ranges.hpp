#pragma once
#include <iterator>
#include <utility>

#include <ez/serialize/core.hpp>

namespace ez::intern {
	template<typename Iter, typename = int>
	struct is_iterator_adaptor: std::false_type {};

	template<typename Iter>
	struct is_iterator_adaptor<
		Iter, 
		std::enable_if_t<
			std::is_same_v<typename std::iterator_traits<Iter>::value_type, void>, // Check that value_type is void
			decltype(std::declval<typename Iter::container_type>(), 0) // Make sure iterator has container_type defined
			>
		>: std::true_type {};

	template<typename Iter>
	static constexpr bool is_iterator_adaptor_v = is_iterator_adaptor<Iter>::value;


	template<typename Iter, typename Traits>
	struct generic_serialize_func {
		using value_type = typename Traits::value_type;

		static inline char* apply(Iter first, Iter last, char* write, char const* const end) {
			while (first != last) {
				write = ez::serialize::value<value_type>(*first, write, end);
				++first;
			}

			return write;
		}
		static inline void apply(Iter first, Iter last, std::string& buffer) {
			while (first != last) {
				ez::serialize::value<value_type>(*first, buffer);
				++first;
			}
		}

		static inline char* apply_n(Iter first, size_t count, char* write, char const* const end) {
			for(size_t i = 0; i < count; ++i) {
				write = ez::serialize::value<value_type>(*first, write, end);
				++first;
			}

			return write;
		}
		static inline void apply_n(Iter first, size_t count, std::string& buffer) {
			for (size_t i = 0; i < count; ++i) {
				ez::serialize::value<value_type>(*first, buffer);
				++first;
			}
		}
	};

	template<typename Iter, typename Traits>
	struct generic_deserialize_func {
		using value_type = typename Traits::value_type;
		using reference = typename Traits::reference;

		static_assert(!std::is_const_v<value_type>, "Cannot deserialize to a const_iterator!");
		static_assert(!std::is_same_v<typename Traits::value_type, void>, "Iterator with void value_type must have a container_type defined!");

		static inline const char* apply(const char* read, char const* const end, Iter first, Iter last) {
			while (first != last) {
				
				if constexpr (std::is_lvalue_reference_v<reference>) {
					read = ez::deserialize::value<value_type>(read, end, *first);
				}
				else {
					// If the type returned from dereferencing the iterator is not lvalue, 
					// then we can't rely on passing it directly to the deserialize function.
					// Instead we create a value_type instance and then assign that to the dereferenced iterator.
					value_type tmp;
					read = ez::deserialize::value<value_type>(read, end, tmp);
					*first = tmp;
				}

				++first;
			}

			return read;
		}
		static inline const char* apply_n(const char* read, char const* const end, Iter first, size_t N) {
			assert((N * sizeof(value_type)) <= (end - read));

			for (size_t i = 0; i < N; ++i) {
				value_type tmp;
				read = ez::deserialize::value<value_type>(read, end, tmp);
				*first = tmp;
				++first;
			}
			return read;
		}
	};

	// Special handling for void type iterator adaptors
	template<typename Iter, typename Traits>
	struct adaptor_deserialize_func {
		using container = typename Iter::container_type;
		using value_type = typename container::value_type;
		using reference = typename container::reference;

		static_assert(!std::is_const_v<value_type>, "Cannot deserialize to a const_iterator!");

		static inline const char* apply(const char* read, char const* const end, Iter first, Iter last) {
			while (first != last) {
				value_type tmp;
				read = ez::deserialize::value<value_type>(read, end, tmp);
				*first = tmp;
				++first;
			}

			return read;
		}
		static inline const char* apply_n(const char* read, char const* const end, Iter first, size_t N) {
			assert((N * sizeof(value_type)) <= (end - read));

			for (size_t i = 0; i < N; ++i) {
				value_type tmp;
				read = ez::deserialize::value<value_type>(read, end, tmp);
				*first = tmp;
				++first;
			}
			return read;
		}
	};

	// Optimization for simple pointer types
	template<typename Iter, typename Traits>
	struct memcpy_serialize_func
	{
		static inline char* apply(Iter first, Iter last, char* write, char const* const end) {
			assert((last - first) <= (end - write));

			std::memcpy(write, first, last - first);
			return write + (last - first);
		}
		static inline void apply(Iter first, Iter last, std::string & buffer) {
			size_t offset = buffer.size();
			buffer.resize(offset + (last - first));

			std::memcpy(buffer.data() + offset, first, last - first);
		}

		static inline char* apply_n(Iter first, size_t count, char* write, char const* const end) {
			assert(count <= (end - write));

			std::memcpy(write, first, count);
			return write + count;
		}
		static inline void apply_n(Iter first, size_t count, std::string& buffer) {
			size_t offset = buffer.size();
			buffer.resize(offset + count);

			std::memcpy(buffer.data() + offset, first, count);
		}
	};

	// Optimization for simple pointer types
	template<typename Iter, typename Traits>
	struct memcpy_deserialize_func
	{
		static inline const char* apply(const char* read, char const* const end, Iter first, Iter last) {
			assert((last - first) <= (end - read));

			std::memcpy(first, read, last - first);
			return read + (last - first);
		}
		static inline const char* apply_n(const char* read, char const* const end, Iter first, size_t N) {
			assert(N <= (end - read));

			std::memcpy(first, read, N);
			return read + (N);
		}
	};

	template<typename Iter>
	struct serialize_func: generic_serialize_func<Iter, std::iterator_traits<Iter>> {
		static_assert(!std::is_same_v<typename std::iterator_traits<Iter>::value_type, void>, "Cannot serialize void type! The iterator passed in is invalid.");
	};

	template<>
	struct serialize_func<char*>: memcpy_serialize_func<const char*, std::iterator_traits<const char*>> {};
	template<>
	struct serialize_func<const char*> : memcpy_serialize_func<const char*, std::iterator_traits<const char*>> {};



	template<typename Iter, typename = int>
	struct deserialize_func: generic_deserialize_func<Iter, std::iterator_traits<Iter>> {
		using traits = std::iterator_traits<Iter>;
	};

	template<>
	struct deserialize_func<char*, int>: memcpy_deserialize_func<char*, std::iterator_traits<char*>> {};

	template<typename Iter>
	struct deserialize_func<Iter, std::enable_if_t<is_iterator_adaptor_v<Iter>, int>> : adaptor_deserialize_func<Iter, std::iterator_traits<Iter>> {};
}

namespace ez::serialize {
	template<typename Iter>
	inline char* range(Iter first, Iter last, char* write, char const* const end) {
		return ez::intern::serialize_func<Iter>::apply(first, last, write, end);
	}
	template<typename Iter>
	inline void range(Iter first, Iter last, std::string& buffer) {
		return ez::intern::serialize_func<Iter>::apply(first, last, buffer);
	}

	template<typename Iter>
	inline char* range_n(Iter first, size_t count, char* write, char const* const end) {
		return ez::intern::serialize_func<Iter>::apply_n(first, count, write, end);
	}
	template<typename Iter>
	inline void range_n(Iter first, size_t count, std::string& buffer) {
		return ez::intern::serialize_func<Iter>::apply_n(first, count, buffer);
	}
}

namespace ez::deserialize {
	template<typename Iter>
	const char* range(const char* read, char const* const end, Iter first, Iter last) {
		return ez::intern::deserialize_func<Iter>::apply(read, end, first, last);
	}

	template<typename Iter>
	const char* range_n(const char* read, char const* const end, Iter first, size_t count) {
		return ez::intern::deserialize_func<Iter>::apply_n(read, end, first, count);
	}
}