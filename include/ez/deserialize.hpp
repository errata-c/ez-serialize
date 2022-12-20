#pragma once
#include <cinttypes>
#include <string>
#include <complex>

namespace ez::deserialize {
	const char* string(const char* read, char const* const end, std::string& ret);
	const char* string_u8(const char* read, char const* const end, std::basic_string<uint8_t>& ret);
	const char* string_u16(const char* read, char const* const end, std::basic_string<std::uint16_t>& ret);
	const char* string_u32(const char* read, char const* const end, std::basic_string<std::uint32_t>& ret);
	const char* string_u64(const char* read, char const* const end, std::basic_string<std::uint64_t>& ret);
	const char* string_i8(const char* read, char const* const end, std::basic_string<std::int8_t>& ret);
	const char* string_i16(const char* read, char const* const end, std::basic_string<std::int16_t>& ret);
	const char* string_i32(const char* read, char const* const end, std::basic_string<std::int32_t>& ret);
	const char* string_i64(const char* read, char const* const end, std::basic_string<std::int64_t>& ret);

	const char* f32(const char* read, char const* const end, float & ret);
	const char* f64(const char* read, char const* const end, double & ret);
	const char* i8(const char* read, char const* const end, int8_t & ret);
	const char* i16(const char* read, char const* const end, int16_t & ret);
	const char* i32(const char* read, char const* const end, int32_t & ret);
	const char* i64(const char* read, char const* const end, int64_t & ret);
	const char* u8(const char* read, char const* const end, uint8_t & ret);
	const char* u16(const char* read, char const* const end, uint16_t & ret);
	const char* u32(const char* read, char const* const end, uint32_t & ret);
	const char* u64(const char* read, char const* const end, uint64_t & ret);

	const char* c32(const char* read, char const* const end, std::complex<float>& ret);
	const char* c64(const char* read, char const* const end, std::complex<double>& ret);
	
	// Only use this function if you know what your doing!
	// Its a really bad idea to actually save a pointer to file.
	const char* ptr(const char* read, char const* const end, void*& ptr);
};

namespace ez::deserialize::intern {
	template<typename T>
	struct meta: std::false_type {};

	#define META_STRUCT(INPUT_TYPE, FUNC_NAME) template<> struct meta<INPUT_TYPE>: std::true_type {\
static const char* func(const char* read, char const* const end, INPUT_TYPE& ret) { return ez::deserialize::FUNC_NAME(read, end, ret); }; }

	META_STRUCT(std::string, string);
	META_STRUCT(std::basic_string<uint8_t>, string_u8);
	META_STRUCT(std::basic_string<uint16_t>, string_u16);
	META_STRUCT(std::basic_string<uint32_t>, string_u32);
	META_STRUCT(std::basic_string<uint64_t>, string_u64);

	META_STRUCT(std::basic_string<int8_t>, string_i8);
	META_STRUCT(std::basic_string<int16_t>, string_i16);
	META_STRUCT(std::basic_string<int32_t>, string_i32);
	META_STRUCT(std::basic_string<int64_t>, string_i64);

	META_STRUCT(uint8_t, u8);
	META_STRUCT(uint16_t, u16);
	META_STRUCT(uint32_t, u32);
	META_STRUCT(uint64_t, u64);

	META_STRUCT(int8_t, i8);
	META_STRUCT(int16_t, i16);
	META_STRUCT(int32_t, i32);
	META_STRUCT(int64_t, i64);

	META_STRUCT(float, f32);
	META_STRUCT(double, f64);

	META_STRUCT(std::complex<float>, c32);
	META_STRUCT(std::complex<double>, c64);

#undef META_STRUCT
}

namespace ez::deserialize {
	template<typename T>
	const char* value(const char* read, char const* const end, T& ret) {
		using meta_t = ez::deserialize::intern::meta<T>;
		static_assert(meta_t::value, "Type is not supported by ez::deserialize!");

		return meta_t::func(read, end, ret);
	}

	template<typename E>
	const char* enumerator(const char* read, char const* const end, E& ret) {
		static_assert(std::is_enum_v<E>, "Type E passed into ez::deserialize::enumerator must be an enum!");
		using utype = std::underlying_type_t<E>;

		return value<utype>(read, end, reinterpret_cast<utype&>(ret));
	}
}