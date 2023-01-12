#pragma once
#include <string>
#include <ez/serialize/ranges.hpp>

namespace ez::serialize {
	template<typename T, typename Traits, typename Alloc>
	char* string(const std::basic_string<T, Traits, Alloc>& val, char* write, char const* const end) {
		static_assert(ez::intern::type_supported<T>::value, "ez::serialize::string does not support the value type!");

		uint64_t count = val.size();
		write = ez::serialize::u64(count, write, end);
		
		return ez::serialize::range(val.data(), val.data() + count, write, end);
	}

	template<typename T, typename Traits, typename Alloc>
	void string(const std::basic_string<T, Traits, Alloc>& val, std::string & buffer) {
		static_assert(ez::intern::type_supported<T>::value, "ez::serialize::string does not support the value type!");

		uint64_t count = val.size();
		ez::serialize::u64(count, buffer);
		ez::serialize::range(val.data(), val.data() + count, buffer);
	}
}

namespace ez::deserialize {
	template<typename T, typename Traits, typename Alloc>
	const char* string(const char* read, char const* const end, std::basic_string<T, Traits, Alloc>& ret) {
		static_assert(ez::intern::type_supported<T>::value, "ez::serialize::string does not support the value type!");

		uint64_t count;
		read = ez::deserialize::u64(read, end, count);

		ret.resize(count);
		return ez::deserialize::range(read, end, ret.begin(), ret.end());
	}
}