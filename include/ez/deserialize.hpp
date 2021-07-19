#pragma once
#include <cinttypes>
#include <string>

namespace ez {
	namespace deserialize {
		const uint8_t* string(const uint8_t* read, uint8_t const* const end, std::string& ret);
		const uint8_t* string_u8(const uint8_t* read, uint8_t const* const end, std::basic_string<uint8_t>& ret);
		const uint8_t* string_u16(const uint8_t* read, uint8_t const* const end, std::basic_string<std::uint16_t>& ret);
		const uint8_t* string_u32(const uint8_t* read, uint8_t const* const end, std::basic_string<std::uint32_t>& ret);
		const uint8_t* string_u64(const uint8_t* read, uint8_t const* const end, std::basic_string<std::uint64_t>& ret);
		const uint8_t* string_i8(const uint8_t* read, uint8_t const* const end, std::basic_string<std::int8_t>& ret);
		const uint8_t* string_i16(const uint8_t* read, uint8_t const* const end, std::basic_string<std::int16_t>& ret);
		const uint8_t* string_i32(const uint8_t* read, uint8_t const* const end, std::basic_string<std::int32_t>& ret);
		const uint8_t* string_i64(const uint8_t* read, uint8_t const* const end, std::basic_string<std::int64_t>& ret);

		const uint8_t* f32(const uint8_t* read, uint8_t const* const end, float & ret);
		const uint8_t* f64(const uint8_t* read, uint8_t const* const end, double & ret);
		const uint8_t* i8(const uint8_t* read, uint8_t const* const end, int8_t & ret);
		const uint8_t* i16(const uint8_t* read, uint8_t const* const end, int16_t & ret);
		const uint8_t* i32(const uint8_t* read, uint8_t const* const end, int32_t & ret);
		const uint8_t* i64(const uint8_t* read, uint8_t const* const end, int64_t & ret);
		const uint8_t* u8(const uint8_t* read, uint8_t const* const end, uint8_t & ret);
		const uint8_t* u16(const uint8_t* read, uint8_t const* const end, uint16_t & ret);
		const uint8_t* u32(const uint8_t* read, uint8_t const* const end, uint32_t & ret);
		const uint8_t* u64(const uint8_t* read, uint8_t const* const end, uint64_t & ret);
		
		// Only use this function for interprocess or interthread communication.
		// Its a really bad idea to actually save a pointer to file.
		const uint8_t* ptr(const uint8_t* read, uint8_t const* const end, void*& ptr);
	};
};