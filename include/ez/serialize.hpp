#pragma once
#include <stdexcept>
#include <vector>
#include <string>
#include <cinttypes>
#include <type_traits>

namespace ez::serialize {
	char* i8(int8_t val, char* write, char const* const end);
	char* i16(int16_t val, char* write, char const* const end);
	char* i32(int32_t val, char* write, char const* const end);
	char* i64(int64_t val, char* write, char const* const end);
	char* u8(uint8_t val, char* write, char const* const end);
	char* u16(uint16_t val, char* write, char const* const end);
	char* u32(uint32_t val, char* write, char const* const end);
	char* u64(uint64_t val, char* write, char const* const end);
	char* f32(float val, char* write, char const* const end);
	char* f64(double val, char* write, char const* const end);
	char* ptr(const void* val, char* write, char const* const end);

	char* string(const std::string& val, char* write, char const* const end);
	char* string_u8(const std::basic_string<uint8_t>& val, char* write, char const* const end);
	char* string_u16(const std::basic_string<uint16_t>& val, char* write, char const* const end);
	char* string_u32(const std::basic_string<uint32_t>& val, char* write, char const* const end);
	char* string_u64(const std::basic_string<uint64_t>& val, char* write, char const* const end);
	char* string_i8(const std::basic_string<int8_t>& val, char* write, char const* const end);
	char* string_i16(const std::basic_string<int16_t>& val, char* write, char const* const end);
	char* string_i32(const std::basic_string<int32_t>& val, char* write, char const* const end);
	char* string_i64(const std::basic_string<int64_t>& val, char* write, char const* const end);

	void i8(int8_t val, std::string& buffer);
	void i16(int16_t val, std::string& buffer);
	void i32(int32_t val, std::string& buffer);
	void i64(int64_t val, std::string& buffer);
	void u8(uint8_t val, std::string& buffer);
	void u16(uint16_t val, std::string& buffer);
	void u32(uint32_t val, std::string& buffer);
	void u64(uint64_t val, std::string& buffer);
	void f32(float val, std::string& buffer);
	void f64(double val, std::string& buffer);
	void ptr(const void* val, std::string& buffer);

	void string(const std::string& val, std::string& buffer);
	void string_u8(const std::basic_string<uint8_t>& val, std::string& buffer);
	void string_u16(const std::basic_string<uint16_t>& val, std::string& buffer);
	void string_u32(const std::basic_string<uint32_t>& val, std::string& buffer);
	void string_u64(const std::basic_string<uint64_t>& val, std::string& buffer);
	void string_i8(const std::basic_string<int8_t>& val, std::string& buffer);
	void string_i16(const std::basic_string<int16_t>& val, std::string& buffer);
	void string_i32(const std::basic_string<int32_t>& val, std::string& buffer);
	void string_i64(const std::basic_string<int64_t>& val, std::string& buffer);
};


namespace ez::serialize::intern {
	template<typename T>
	struct meta : std::false_type {};

#define META_STRUCT(INPUT_TYPE, FUNC_NAME) \
template<>\
struct meta<INPUT_TYPE>: std::true_type {\
	static void func(const INPUT_TYPE& val, std::string & buffer) { ez::serialize::FUNC_NAME(val, buffer); }; \
	static char* func(const INPUT_TYPE& val, char* write, char const* const end) { return ez::serialize::FUNC_NAME(val, write, end); }; \
}

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

#undef META_STRUCT
}

namespace ez::serialize {
	template<typename T>
	void value(const T& val, std::string& buffer) {
		using meta_t = intern::meta<T>;
		static_assert(meta_t::value, "ez::serialize::value does not support the input type T!");

		meta_t::func(val, buffer);
	}

	template<typename T>
	char* value(const T& val, char* write, char const* const end) {
		using meta_t = intern::meta<T>;
		static_assert(meta_t::value, "ez::serialize::value does not support the input type T!");

		return meta_t::func(val, write, end);
	}
	
	template<typename E>
	void enumerator(const E& val, std::string& buffer) {
		static_assert(std::is_enum_v<E>, "Type E passed into ez::serialize::enumerator must be an enum!");
		using utype = std::underlying_type_t<E>;

		value<utype>(reinterpret_cast<const utype&>(val), buffer);
	}

	template<typename E>
	char* enumerator(const E& val, char* write, char const* const end) {
		static_assert(std::is_enum_v<E>, "Type E passed into ez::serialize::enumerator must be an enum!");
		using utype = std::underlying_type_t<E>;

		return value<utype>(reinterpret_cast<const utype&>(val), write, end);
	}
}