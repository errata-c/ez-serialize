#pragma once
#include <cinttypes>
#include <string>

namespace ez {
	namespace deserialize {
		void string(const std::uint8_t*& read, std::string& ret);

		void string_u8(const std::uint8_t*& read, std::basic_string<std::uint8_t>& ret);
		void string_u16(const std::uint8_t*& read, std::basic_string<std::uint16_t>& ret);
		void string_u32(const std::uint8_t*& read, std::basic_string<std::uint32_t>& ret);
		void string_u64(const std::uint8_t*& read, std::basic_string<std::uint64_t>& ret);

		void string_i8(const std::uint8_t*& read, std::basic_string<std::int8_t>& ret);
		void string_i16(const std::uint8_t*& read, std::basic_string<std::int16_t>& ret);
		void string_i32(const std::uint8_t*& read, std::basic_string<std::int32_t>& ret);
		void string_i64(const std::uint8_t*& read, std::basic_string<std::int64_t>& ret);

		std::string string(const std::uint8_t*& read);

		std::basic_string<std::uint8_t> string_u8(const std::uint8_t*& read);
		std::basic_string<std::uint16_t> string_u16(const std::uint8_t*& read);
		std::basic_string<std::uint32_t> string_u32(const std::uint8_t*& read);
		std::basic_string<std::uint64_t> string_u64(const std::uint8_t*& read);

		std::basic_string<std::int8_t> string_i8(const std::uint8_t*& read);
		std::basic_string<std::int16_t> string_i16(const std::uint8_t*& read);
		std::basic_string<std::int32_t> string_i32(const std::uint8_t*& read);
		std::basic_string<std::int64_t> string_i64(const std::uint8_t*& read);

		float f32(const std::uint8_t*& read);
		double f64(const std::uint8_t*& read);

		std::int8_t i8(const std::uint8_t*& read);
		std::int16_t i16(const std::uint8_t*& read);
		std::int32_t i32(const std::uint8_t*& read);
		std::int64_t i64(const std::uint8_t*& read);

		std::uint8_t u8(const std::uint8_t*& read);
		std::uint16_t u16(const std::uint8_t*& read);
		std::uint32_t u32(const std::uint8_t*& read);
		std::uint64_t u64(const std::uint8_t*& read);

		void* ptr(const std::uint8_t*& read);
	};
};