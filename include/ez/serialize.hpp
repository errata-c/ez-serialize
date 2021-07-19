#pragma once
#include <stdexcept>
#include <vector>
#include <string>
#include <cinttypes>
#include <type_traits>

namespace ez {
	namespace serialize {
		uint8_t* i8(int8_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* i16(int16_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* i32(int32_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* i64(int64_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* u8(uint8_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* u16(uint16_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* u32(uint32_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* u64(uint64_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* f32(float val, uint8_t* write, uint8_t const* const end);
		uint8_t* f64(double val, uint8_t* write, uint8_t const* const end);
		uint8_t* ptr(const void* val, uint8_t* write, uint8_t const* const end);

		uint8_t* string(const std::string& val, uint8_t* write, uint8_t const* const end);
		uint8_t* string_u8(const std::basic_string<uint8_t>& val, uint8_t* write, uint8_t const* const end);
		uint8_t* string_u16(const std::basic_string<uint16_t>& val, uint8_t* write, uint8_t const* const end);
		uint8_t* string_u32(const std::basic_string<uint32_t>& val, uint8_t* write, uint8_t const* const end);
		uint8_t* string_u64(const std::basic_string<uint64_t>& val, uint8_t* write, uint8_t const* const end);
		uint8_t* string_i8(const std::basic_string<int8_t>& val, uint8_t* write, uint8_t const* const end);
		uint8_t* string_i16(const std::basic_string<int16_t>& val, uint8_t* write, uint8_t const* const end);
		uint8_t* string_i32(const std::basic_string<int32_t>& val, uint8_t* write, uint8_t const* const end);
		uint8_t* string_i64(const std::basic_string<int64_t>& val, uint8_t* write, uint8_t const* const end);

		void i8(int8_t val, std::vector<uint8_t>& buffer);
		void i16(int16_t val, std::vector<uint8_t>& buffer);
		void i32(int32_t val, std::vector<uint8_t>& buffer);
		void i64(int64_t val, std::vector<uint8_t>& buffer);
		void u8(uint8_t val, std::vector<uint8_t>& buffer);
		void u16(uint16_t val, std::vector<uint8_t>& buffer);
		void u32(uint32_t val, std::vector<uint8_t>& buffer);
		void u64(uint64_t val, std::vector<uint8_t>& buffer);
		void f32(float val, std::vector<uint8_t>& buffer);
		void f64(double val, std::vector<uint8_t>& buffer);
		void ptr(const void* val, std::vector<uint8_t>& buffer);

		void string(const std::string& val, std::vector<uint8_t>& buffer);
		void string_u8(const std::basic_string<uint8_t>& val, std::vector<uint8_t>& buffer);
		void string_u16(const std::basic_string<uint16_t>& val, std::vector<uint8_t>& buffer);
		void string_u32(const std::basic_string<uint32_t>& val, std::vector<uint8_t>& buffer);
		void string_u64(const std::basic_string<uint64_t>& val, std::vector<uint8_t>& buffer);
		void string_i8(const std::basic_string<int8_t>& val, std::vector<uint8_t>& buffer);
		void string_i16(const std::basic_string<int16_t>& val, std::vector<uint8_t>& buffer);
		void string_i32(const std::basic_string<int32_t>& val, std::vector<uint8_t>& buffer);
		void string_i64(const std::basic_string<int64_t>& val, std::vector<uint8_t>& buffer);

		uint8_t* value(int8_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(int16_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(int32_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(int64_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(uint8_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(uint16_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(uint32_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(uint64_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(float val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(double val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(const void* val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(const std::string& val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(const std::basic_string<uint8_t>& val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(const std::basic_string<uint16_t>& val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(const std::basic_string<uint32_t>& val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(const std::basic_string<uint64_t>& val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(const std::basic_string<int8_t>& val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(const std::basic_string<int16_t>& val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(const std::basic_string<int32_t>& val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(const std::basic_string<int64_t>& val, uint8_t* write, uint8_t const* const end);

		void value(int8_t val, std::vector<uint8_t>& buffer);
		void value(int16_t val, std::vector<uint8_t>& buffer);
		void value(int32_t val, std::vector<uint8_t>& buffer);
		void value(int64_t val, std::vector<uint8_t>& buffer);
		void value(uint8_t val, std::vector<uint8_t>& buffer);
		void value(uint16_t val, std::vector<uint8_t>& buffer);
		void value(uint32_t val, std::vector<uint8_t>& buffer);
		void value(uint64_t val, std::vector<uint8_t>& buffer);
		void value(float val, std::vector<uint8_t>& buffer);
		void value(double val, std::vector<uint8_t>& buffer);
		void value(const void* val, std::vector<uint8_t>& buffer);
		void value(const std::string& val, std::vector<uint8_t>& buffer);
		void value(const std::basic_string<uint8_t>& val, std::vector<uint8_t>& buffer);
		void value(const std::basic_string<uint16_t>& val, std::vector<uint8_t>& buffer);
		void value(const std::basic_string<uint32_t>& val, std::vector<uint8_t>& buffer);
		void value(const std::basic_string<uint64_t>& val, std::vector<uint8_t>& buffer);
		void value(const std::basic_string<int8_t>& val, std::vector<uint8_t>& buffer);
		void value(const std::basic_string<int16_t>& val, std::vector<uint8_t>& buffer);
		void value(const std::basic_string<int32_t>& val, std::vector<uint8_t>& buffer);
		void value(const std::basic_string<int64_t>& val, std::vector<uint8_t>& buffer);

	};
};