#pragma once
#include <cassert>
#include <string>
#include <cinttypes>
#include <type_traits>
#include <complex>

#include <ez/intern/TypeSupport.hpp>
#include <ez/intern/Convert.hpp>

namespace ez::serialize {
	template<typename T, std::enable_if_t<std::is_fundamental_v<T>, int> = 0>
	char* value(const T& val, char* write, char const* const end) {
		static_assert(ez::intern::type_supported<T>::value, "ez::serialize::value does not support the input type T!");

		assert((end - write) >= sizeof(T));
		return ez::intern::write_convert<T>(write, val);
	}

	template<typename T, std::enable_if_t<std::is_fundamental_v<T>, int> = 0>
	void value(const T& val, std::string& buffer) {
		static_assert(ez::intern::type_supported<T>::value, "ez::serialize::value does not support the input type T!");

		return ez::intern::write_convert<T>(buffer, val);
	}

	template<typename T, std::enable_if_t<ez::intern::is_complex<T>::value, int> = 0>
	char* value(const T& val, char* write, char const* const end) {
		assert((end - write) >= sizeof(T));
		write = ez::intern::write_convert<T>(write, val.real());
		return ez::intern::write_convert<T>(write, val.imag());
	}
	template<typename T, std::enable_if_t<ez::intern::is_complex<T>::value, int> = 0>
	void value(const T& val, std::string& buffer) {
		ez::intern::write_convert<T>(buffer, val.real());
		ez::intern::write_convert<T>(buffer, val.imag());
	}


	template<typename E>
	void enumerator(const E& val, std::string& buffer) {
		static_assert(std::is_enum_v<E>, "Type E passed into ez::serialize::enumerator must be an enum!");
		using utype = std::underlying_type_t<E>;

		value<utype>(static_cast<utype>(val), buffer);
	}

	template<typename E>
	char* enumerator(const E& val, char* write, char const* const end) {
		static_assert(std::is_enum_v<E>, "Type E passed into ez::serialize::enumerator must be an enum!");
		using utype = std::underlying_type_t<E>;

		return value<utype>(static_cast<utype>(val), write, end);
	}



#define NAMED_FUNCTION(NAME, TYPE) \
inline char* NAME(const TYPE& val, char* write, char const * const end) { return value<TYPE>(val, write, end); } \
inline void NAME(const TYPE& val, std::string& buffer) { return value<TYPE>(val, buffer); }

	NAMED_FUNCTION(i8, int8_t);
	NAMED_FUNCTION(i16, int16_t);
	NAMED_FUNCTION(i32, int32_t);
	NAMED_FUNCTION(i64, int64_t);

	NAMED_FUNCTION(u8, uint8_t);
	NAMED_FUNCTION(u16, uint16_t);
	NAMED_FUNCTION(u32, uint32_t);
	NAMED_FUNCTION(u64, uint64_t);

	NAMED_FUNCTION(f32, float);
	NAMED_FUNCTION(f64, double);

	NAMED_FUNCTION(c32, std::complex<float>);
	NAMED_FUNCTION(c64, std::complex<double>);

#undef NAMED_FUNCTION
}



namespace ez::deserialize {
	template<typename T, std::enable_if_t<std::is_fundamental_v<T>, int> = 0>
	const char* value(const char* read, char const* const end, T& ret) {
		static_assert(ez::intern::type_supported<T>::value, "Type is not supported by ez::deserialize!");

		assert((end - read) >= sizeof(T));
		return ez::intern::read_convert<T>(read, ret);
	}
	template<typename T, std::enable_if_t<ez::intern::is_complex<T>::value, int> = 0>
	const char* value(const char* read, char const* const end, T& ret) {
		using value_type = typename T::value_type;

		assert((end - read) >= sizeof(T));
		value_type tmp;

		read = ez::intern::read_convert<value_type>(read, tmp);
		ret.real(tmp);

		read = ez::intern::read_convert<value_type>(read, tmp);
		ret.imag(tmp);

		return read;
	}


	template<typename E>
	const char* enumerator(const char* read, char const* const end, E& ret) {
		static_assert(std::is_enum_v<E>, "Type E passed into ez::deserialize::enumerator must be an enum!");
		using utype = std::underlying_type_t<E>;

		utype tmp;
		read = value<utype>(read, end, tmp);
		ret = static_cast<E>(tmp);

		return read;
	}


#define NAMED_FUNCTION(NAME, TYPE) inline const char* NAME(const char* read, char const* const end, TYPE& ret) { return value<TYPE>(read, end, ret); }

	NAMED_FUNCTION(i8, int8_t);
	NAMED_FUNCTION(i16, int16_t);
	NAMED_FUNCTION(i32, int32_t);
	NAMED_FUNCTION(i64, int64_t);

	NAMED_FUNCTION(u8, uint8_t);
	NAMED_FUNCTION(u16, uint16_t);
	NAMED_FUNCTION(u32, uint32_t);
	NAMED_FUNCTION(u64, uint64_t);

	NAMED_FUNCTION(f32, float);
	NAMED_FUNCTION(f64, double);

	NAMED_FUNCTION(c32, std::complex<float>);
	NAMED_FUNCTION(c64, std::complex<double>);

#undef NAMED_FUNCTION
};