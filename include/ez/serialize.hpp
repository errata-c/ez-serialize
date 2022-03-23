#pragma once
#include <stdexcept>
#include <vector>
#include <string>
#include <cinttypes>
#include <type_traits>

namespace ez {
	namespace serialize {
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

		char* value(int8_t val, char* write, char const* const end);
		char* value(int16_t val, char* write, char const* const end);
		char* value(int32_t val, char* write, char const* const end);
		char* value(int64_t val, char* write, char const* const end);
		char* value(uint8_t val, char* write, char const* const end);
		char* value(uint16_t val, char* write, char const* const end);
		char* value(uint32_t val, char* write, char const* const end);
		char* value(uint64_t val, char* write, char const* const end);
		char* value(float val, char* write, char const* const end);
		char* value(double val, char* write, char const* const end);
		char* value(const void* val, char* write, char const* const end);
		char* value(const std::string& val, char* write, char const* const end);
		char* value(const std::basic_string<uint8_t>& val, char* write, char const* const end);
		char* value(const std::basic_string<uint16_t>& val, char* write, char const* const end);
		char* value(const std::basic_string<uint32_t>& val, char* write, char const* const end);
		char* value(const std::basic_string<uint64_t>& val, char* write, char const* const end);
		char* value(const std::basic_string<int8_t>& val, char* write, char const* const end);
		char* value(const std::basic_string<int16_t>& val, char* write, char const* const end);
		char* value(const std::basic_string<int32_t>& val, char* write, char const* const end);
		char* value(const std::basic_string<int64_t>& val, char* write, char const* const end);

		void value(int8_t val, std::string& buffer);
		void value(int16_t val, std::string& buffer);
		void value(int32_t val, std::string& buffer);
		void value(int64_t val, std::string& buffer);
		void value(uint8_t val, std::string& buffer);
		void value(uint16_t val, std::string& buffer);
		void value(uint32_t val, std::string& buffer);
		void value(uint64_t val, std::string& buffer);
		void value(float val, std::string& buffer);
		void value(double val, std::string& buffer);
		void value(const void* val, std::string& buffer);
		void value(const std::string& val, std::string& buffer);
		void value(const std::basic_string<uint8_t>& val, std::string& buffer);
		void value(const std::basic_string<uint16_t>& val, std::string& buffer);
		void value(const std::basic_string<uint32_t>& val, std::string& buffer);
		void value(const std::basic_string<uint64_t>& val, std::string& buffer);
		void value(const std::basic_string<int8_t>& val, std::string& buffer);
		void value(const std::basic_string<int16_t>& val, std::string& buffer);
		void value(const std::basic_string<int32_t>& val, std::string& buffer);
		void value(const std::basic_string<int64_t>& val, std::string& buffer);

	};
};