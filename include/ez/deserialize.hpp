#pragma once
#include <cinttypes>
#include <string>

namespace ez {
	namespace deserialize {
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
		
		// Only use this function if you know what your doing!
		// Its a really bad idea to actually save a pointer to file.
		const char* ptr(const char* read, char const* const end, void*& ptr);
	};
};