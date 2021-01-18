#pragma once
#include <vector>
#include <string>
#include <cinttypes>
#include <type_traits>

namespace ez {
	namespace serialize {
		void string(const std::string & val, std::vector<std::uint8_t> & buffer);

		void string_u8(const std::basic_string<std::uint8_t>& val, std::vector<std::uint8_t>& buffer);
		void string_u16(const std::basic_string<std::uint16_t>& val, std::vector<std::uint8_t>& buffer);
		void string_u32(const std::basic_string<std::uint32_t>& val, std::vector<std::uint8_t>& buffer);
		void string_u64(const std::basic_string<std::uint64_t>& val, std::vector<std::uint8_t>& buffer);

		void string_i8(const std::basic_string<std::int8_t>& val, std::vector<std::uint8_t>& buffer);
		void string_i16(const std::basic_string<std::int16_t>& val, std::vector<std::uint8_t>& buffer);
		void string_i32(const std::basic_string<std::int32_t>& val, std::vector<std::uint8_t>& buffer);
		void string_i64(const std::basic_string<std::int64_t>& val, std::vector<std::uint8_t>& buffer);

		std::uint8_t* i8(std::int8_t val, std::uint8_t* write);
		std::uint8_t* i16(std::int16_t val, std::uint8_t* write);
		std::uint8_t* i32(std::int32_t val, std::uint8_t* write);
		std::uint8_t* i64(std::int64_t val, std::uint8_t* write);

		std::uint8_t* u8(std::uint8_t val, std::uint8_t* write);
		std::uint8_t* u16(std::uint16_t val, std::uint8_t* write);
		std::uint8_t* u32(std::uint32_t val, std::uint8_t* write);
		std::uint8_t* u64(std::uint64_t val, std::uint8_t* write);

		std::uint8_t* f32(float val, std::uint8_t* write);
		std::uint8_t* f64(double val, std::uint8_t* write);

		void i8(int8_t val, std::vector<std::uint8_t>& buffer);
		void i16(int16_t val, std::vector<std::uint8_t>& buffer);
		void i32(int32_t val, std::vector<std::uint8_t>& buffer);
		void i64(int64_t val, std::vector<std::uint8_t>& buffer);

		void u8(uint8_t val, std::vector<std::uint8_t>& buffer);
		void u16(uint16_t val, std::vector<std::uint8_t>& buffer);
		void u32(uint32_t val, std::vector<std::uint8_t>& buffer);
		void u64(uint64_t val, std::vector<std::uint8_t>& buffer);

		void f32(float val, std::vector<std::uint8_t>& buffer);
		void f64(double val, std::vector<std::uint8_t>& buffer);

		std::uint8_t* ptr(const void* val, std::uint8_t* write);
		void ptr(const void* val, std::vector<std::uint8_t>& buffer);
	};
};