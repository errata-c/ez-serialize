#include <ez/deserialize.hpp>
#include <ez/intern/Convert.hpp>

#include <cassert>
#include <stdexcept>
#include <limits.h>

static_assert(CHAR_BIT == 8, "Your system has a non-standard bitwidth for character types!");

static_assert(std::is_same_v<std::uint8_t, char> ||
	std::is_same_v<std::uint8_t, unsigned char>,
	"This library requires std::uint8_t to be implemented as char or unsigned char.");

namespace ez::deserialize {
	using namespace ez::intern;

	const char* string(const char* read, char const* const end, std::string& ret) {
		uint64_t length;
		read = u64(read, end, length);

		assert((end - read) >= length);
		
		ret.reserve(ret.size() + length);

		const char* last = read + length;
		while (read < last) {
			ret.push_back(*read++);
		}

		return read;
	}
	const char* string_u8(const char* read, char const* const end, std::basic_string<uint8_t>& ret) {
		uint64_t length;
		read = u64(read, end, length);

		assert((end - read) >= length);

		ret.reserve(ret.size() + length);

		const char* last = read + length;
		while (read < last) {
			ret.push_back(*read++);
		}

		return read;
	}
	const char* string_u16(const char* read, char const* const end, std::basic_string<uint16_t>& ret) {
		uint64_t bytes;
		read = u64(read, end, bytes);
		uint64_t length = bytes / sizeof(uint16_t);

		assert((end - read) >= bytes);

		ret.reserve(ret.size() + length);

		const char* last = read + length;
		while (read < last) {
			uint16_t val;
			read = u16(read, end, val);
			ret.push_back(val);
		}

		return read;
	}
	const char* string_u32(const char* read, char const* const end, std::basic_string<uint32_t>& ret) {
		uint64_t bytes;
		read = u64(read, end, bytes);
		uint64_t length = bytes / sizeof(uint32_t);

		assert((end - read) >= bytes);

		ret.reserve(ret.size() + length);

		const char* last = read + length;
		while (read < last) {
			uint32_t val;
			read = u32(read, end, val);
			ret.push_back(val);
		}

		return read;
	}
	const char* string_u64(const char* read, char const* const end, std::basic_string<uint64_t>& ret) {
		uint64_t bytes;
		read = u64(read, end, bytes);
		uint64_t length = bytes / sizeof(uint64_t);

		assert((end - read) >= bytes);

		ret.reserve(ret.size() + length);

		const char* last = read + length;
		while (read < last) {
			uint64_t val;
			read = u64(read, end, val);
			ret.push_back(val);
		}

		return read;
	}

	const char* string_i8(const char* read, char const* const end, std::basic_string<int8_t>& ret) {
		uint64_t bytes;
		read = u64(read, end, bytes);
		uint64_t length = bytes / sizeof(int8_t);

		assert((end - read) >= bytes);

		ret.reserve(ret.size() + length);

		const char* last = read + length;
		while (read < last) {
			int8_t val;
			read = i8(read, end, val);
			ret.push_back(val);
		}

		return read;
	}
	const char* string_i16(const char* read, char const* const end, std::basic_string<int16_t>& ret) {
		uint64_t bytes;
		read = u64(read, end, bytes);
		uint64_t length = bytes / sizeof(int16_t);

		assert((end - read) >= bytes);

		ret.reserve(ret.size() + length / 2);

		const char* last = read + length;
		while (read < last) {
			int16_t val;
			read = i16(read, end, val);
			ret.push_back(val);
		}

		return read;
	}
	const char* string_i32(const char* read, char const* const end, std::basic_string<int32_t>& ret) {
		uint64_t bytes;
		read = u64(read, end, bytes);
		uint64_t length = bytes / sizeof(int32_t);

		assert((end - read) >= bytes);

		ret.reserve(ret.size() + length);

		const char* last = read + length;
		while (read < last) {
			int32_t val;
			read = i32(read, end, val);
			ret.push_back(val);
		}

		return read;
	}
	const char* string_i64(const char* read, char const* const end, std::basic_string<int64_t>& ret) {
		uint64_t bytes;
		read = u64(read, end, bytes);
		uint64_t length = bytes / sizeof(int64_t);

		assert((end - read) >= bytes);

		ret.reserve(ret.size() + length / 8);

		const char* last = read + length;
		while (read < last) {
			int64_t val;
			read = i64(read, end, val);
			ret.push_back(val);
		}
		
		return read;
	}

	const char* f32(const char* read, char const* const end, float & ret) {
		assert((end - read) >= sizeof(float));

		Converter32 convert;
		read = readConvert(read, convert.uintVal);
		ret = convert.floatVal;

		return read;
	}
	const char* f64(const char* read, char const* const end, double & ret) {
		assert((end - read) >= sizeof(double));

		uint64_t ival;
		read = readConvert(read, ival);

		Converter64 convert;
		convert.uintVal = ival;
		ret = convert.floatVal;

		return read;
	}

	const char* i8(const char* read, char const* const end, int8_t & ret) {
		assert((end - read) >= sizeof(int8_t));

		ret = *read++;
		return read;
	}
	const char* i16(const char* read, char const* const end, int16_t & ret) {
		assert((end - read) >= sizeof(int16_t));

		return readConvert(read, ret);
	}
	const char* i32(const char* read, char const* const end, int32_t & ret) {
		assert((end - read) >= sizeof(int32_t));

		return readConvert(read, ret);
	}
	const char* i64(const char* read, char const* const end, int64_t & ret) {
		assert((end - read) >= sizeof(int64_t));

		return readConvert(read, ret);
	}

	const char* u8(const char* read, char const* const end, uint8_t & ret) {
		assert((end - read) >= sizeof(uint8_t));

		return readConvert(read, ret);
	}
	const char* u16(const char* read, char const* const end, uint16_t & ret) {
		assert((end - read) >= sizeof(uint16_t));

		return readConvert(read, ret);
	}
	const char* u32(const char* read, char const* const end, uint32_t & ret) {
		assert((end - read) >= sizeof(uint32_t));

		return readConvert(read, ret);
	}
	const char* u64(const char* read, char const* const end, uint64_t & ret) {
		assert((end - read) >= sizeof(uint64_t));

		return readConvert(read, ret);
	}

	const char* ptr(const char* read, char const* const end, void * & ret) {
		assert((end - read) < sizeof(void*));

		ConverterPtr convert;
		read = readConvert(read, convert.uintVal);

		ret = convert.ptr;
		return read;
	}
	
}