#pragma once
#include <iterator>

#include <ez/serialize/core.hpp>

namespace ez::intern {
	template<typename Iter, typename Traits>
	struct generic_serialize_func {
		static inline char* apply(Iter first, Iter last, char* write, char const* const end) {
			using value_type = typename Traits::value_type;

			while (first != last) {
				write = ez::serialize::value<value_type>(*first, write, end);
				++first;
			}

			return write;
		}
		static inline void apply(Iter first, Iter last, std::string& buffer) {
			using value_type = typename Traits::value_type;

			while (first != last) {
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
		//static_assert(std::is_lvalue_reference_v<reference>, "The reference returned from the iterator must be an lvalue reference!");

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
	struct serialize_func: generic_serialize_func<Iter, std::iterator_traits<Iter>> {};

	template<>
	struct serialize_func<char*>: memcpy_serialize_func<const char*, std::iterator_traits<const char*>> {};
	template<>
	struct serialize_func<const char*> : memcpy_serialize_func<const char*, std::iterator_traits<const char*>> {};



	template<typename Iter>
	struct deserialize_func: generic_deserialize_func<Iter, std::iterator_traits<Iter>> {};

	template<>
	struct deserialize_func<char*>: memcpy_deserialize_func<char*, std::iterator_traits<char*>> {};
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
}

namespace ez::deserialize {
	template<typename Iter>
	const char* range(const char* read, char const* const end, Iter first, Iter last) {
		return ez::intern::deserialize_func<Iter>::apply(read, end, first, last);
	}
}