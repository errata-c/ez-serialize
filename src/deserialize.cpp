#include <ez/deserialize.hpp>
#include "Convert.hpp"
#include <cassert>
#include <stdexcept>
#include <limits.h>

static_assert(CHAR_BIT == 8, "Your system has a non-standard bitwidth for character types!");

namespace ez {
	namespace deserialize {
		const uint8_t* string(const uint8_t* read, uint8_t const* const end, std::string& ret) {
			uint64_t length;
			read = u64(read, end, length);

			if ((end - read) < length) {
				throw std::out_of_range("Read range passed into ez::deserialize::string is too small!");
			}
			
			ret.reserve(ret.size() + length);

			const uint8_t* last = read + length;
			Converter8 convert;
			while (read < last) {
				convert.uintVal = *read++;
				ret.push_back(convert.charVal);
			}

			return read;
		}
		const uint8_t* string_u8(const uint8_t* read, uint8_t const* const end, std::basic_string<uint8_t>& ret) {
			uint64_t length;
			read = u64(read, end, length);

			if ((end - read) < length) {
				throw std::out_of_range("Read range passed into ez::deserialize::string_u8 is too small!");
			}

			ret.reserve(ret.size() + length);

			const uint8_t* last = read + length;
			while (read < last) {
				uint8_t val;
				read = u8(read, end, val);
				ret.push_back(val);
			}

			return read;
		}
		const uint8_t* string_u16(const uint8_t* read, uint8_t const* const end, std::basic_string<uint16_t>& ret) {
			uint64_t bytes;
			read = u64(read, end, bytes);
			uint64_t length = bytes / sizeof(uint16_t);

			if ((end - read) < bytes) {
				throw std::out_of_range("Read range passed into ez::deserialize::string_u16 is too small!");
			}

			ret.reserve(ret.size() + length);

			const uint8_t* last = read + length;
			while (read < last) {
				uint16_t val;
				read = u16(read, end, val);
				ret.push_back(val);
			}

			return read;
		}
		const uint8_t* string_u32(const uint8_t* read, uint8_t const* const end, std::basic_string<uint32_t>& ret) {
			uint64_t bytes;
			read = u64(read, end, bytes);
			uint64_t length = bytes / sizeof(uint32_t);

			if ((end - read) < bytes) {
				throw std::out_of_range("Read range passed into ez::deserialize::string_u32 is too small!");
			}

			ret.reserve(ret.size() + length);

			const uint8_t* last = read + length;
			while (read < last) {
				uint32_t val;
				read = u32(read, end, val);
				ret.push_back(val);
			}

			return read;
		}
		const uint8_t* string_u64(const uint8_t* read, uint8_t const* const end, std::basic_string<uint64_t>& ret) {
			uint64_t bytes;
			read = u64(read, end, bytes);
			uint64_t length = bytes / sizeof(uint64_t);

			if ((end - read) < bytes) {
				throw std::out_of_range("Read range passed into ez::deserialize::string_u64 is too small!");
			}

			ret.reserve(ret.size() + length);

			const uint8_t* last = read + length;
			while (read < last) {
				uint64_t val;
				read = u64(read, end, val);
				ret.push_back(val);
			}

			return read;
		}

		const uint8_t* string_i8(const uint8_t* read, uint8_t const* const end, std::basic_string<int8_t>& ret) {
			uint64_t bytes;
			read = u64(read, end, bytes);
			uint64_t length = bytes / sizeof(int8_t);

			if ((end - read) < bytes) {
				throw std::out_of_range("Read range passed into ez::deserialize::string_i8 is too small!");
			}

			ret.reserve(ret.size() + length);

			const uint8_t* last = read + length;
			while (read < last) {
				int8_t val;
				read = i8(read, end, val);
				ret.push_back(val);
			}

			return read;
		}
		const uint8_t* string_i16(const uint8_t* read, uint8_t const* const end, std::basic_string<int16_t>& ret) {
			uint64_t bytes;
			read = u64(read, end, bytes);
			uint64_t length = bytes / sizeof(int16_t);

			if ((end - read) < bytes) {
				throw std::out_of_range("Read range passed into ez::deserialize::string_i16 is too small!");
			}

			ret.reserve(ret.size() + length / 2);

			const uint8_t* last = read + length;
			while (read < last) {
				int16_t val;
				read = i16(read, end, val);
				ret.push_back(val);
			}

			return read;
		}
		const uint8_t* string_i32(const uint8_t* read, uint8_t const* const end, std::basic_string<int32_t>& ret) {
			uint64_t bytes;
			read = u64(read, end, bytes);
			uint64_t length = bytes / sizeof(int32_t);

			if ((end - read) < bytes) {
				throw std::out_of_range("Read range passed into ez::deserialize::string_i32 is too small!");
			}

			ret.reserve(ret.size() + length);

			const uint8_t* last = read + length;
			while (read < last) {
				int32_t val;
				read = i32(read, end, val);
				ret.push_back(val);
			}

			return read;
		}
		const uint8_t* string_i64(const uint8_t* read, uint8_t const* const end, std::basic_string<int64_t>& ret) {
			uint64_t bytes;
			read = u64(read, end, bytes);
			uint64_t length = bytes / sizeof(int64_t);

			if ((end - read) < bytes) {
				throw std::out_of_range("Read range passed into ez::deserialize::string_i64 is too small!");
			}

			ret.reserve(ret.size() + length / 8);

			const uint8_t* last = read + length;
			while (read < last) {
				int64_t val;
				read = i64(read, end, val);
				ret.push_back(val);
			}
			
			return read;
		}

		const uint8_t* f32(const uint8_t* read, uint8_t const* const end, float & ret) {
			if ((end - read) < sizeof(float)) {
				throw std::out_of_range("Read range passed into ez::deserialize::f32 is too small!");
			}

			Converter32 convert;
			readConvert(read, convert);

			ret = convert.floatVal;
			return read + sizeof(convert);
		}
		const uint8_t* f64(const uint8_t* read, uint8_t const* const end, double & ret) {
			if ((end - read) < sizeof(double)) {
				throw std::out_of_range("Read range passed into ez::deserialize::f64 is too small!");
			}

			Converter64 convert;
			readConvert(read, convert);

			ret = convert.floatVal;
			return read + sizeof(convert);
		}

		const uint8_t* i8(const uint8_t* read, uint8_t const* const end, int8_t & ret) {
			if ((end - read) < sizeof(int8_t)) {
				throw std::out_of_range("Read range passed into ez::deserialize::i8 is too small!");
			}

			Converter8 convert;
			readConvert(read, convert);

			ret = convert.intVal;
			return read + sizeof(convert);
		}
		const uint8_t* i16(const uint8_t* read, uint8_t const* const end, int16_t & ret) {
			if ((end - read) < sizeof(int16_t)) {
				throw std::out_of_range("Read range passed into ez::deserialize::i16 is too small!");
			}

			Converter16 convert;
			readConvert(read, convert);

			ret = convert.intVal;
			return read + sizeof(convert);
		}
		const uint8_t* i32(const uint8_t* read, uint8_t const* const end, int32_t & ret) {
			if ((end - read) < sizeof(int32_t)) {
				throw std::out_of_range("Read range passed into ez::deserialize::i32 is too small!");
			}

			Converter32 convert;
			readConvert(read, convert);

			ret = convert.intVal;
			return read + sizeof(convert);
		}
		const uint8_t* i64(const uint8_t* read, uint8_t const* const end, int64_t & ret) {
			if ((end - read) < sizeof(int64_t)) {
				throw std::out_of_range("Read range passed into ez::deserialize::i64 is too small!");
			}

			Converter64 convert;
			readConvert(read, convert);

			ret = convert.intVal;
			return read + sizeof(convert);
		}

		const uint8_t* u8(const uint8_t* read, uint8_t const* const end, uint8_t & ret) {
			if ((end - read) < sizeof(uint8_t)) {
				throw std::out_of_range("Read range passed into ez::deserialize::u8 is too small!");
			}

			ret = *read;
			return read + 1;
		}
		const uint8_t* u16(const uint8_t* read, uint8_t const* const end, uint16_t & ret) {
			if ((end - read) < sizeof(uint16_t)) {
				throw std::out_of_range("Read range passed into ez::deserialize::u16 is too small!");
			}

			Converter16 convert;
			readConvert(read, convert);

			ret = convert.uintVal;
			return read + sizeof(convert);
		}
		const uint8_t* u32(const uint8_t* read, uint8_t const* const end, uint32_t & ret) {
			if ((end - read) < sizeof(uint32_t)) {
				throw std::out_of_range("Read range passed into ez::deserialize::u32 is too small!");
			}

			Converter32 convert;
			readConvert(read, convert);

			ret = convert.uintVal;
			return read + sizeof(convert);
		}
		const uint8_t* u64(const uint8_t* read, uint8_t const* const end, uint64_t & ret) {
			if ((end - read) < sizeof(uint64_t)) {
				throw std::out_of_range("Read range passed into ez::deserialize::u64 is too small!");
			}

			Converter64 convert;
			readConvert(read, convert);

			ret = convert.uintVal;
			return read + sizeof(convert);
		}

		const uint8_t* ptr(const uint8_t* read, uint8_t const* const end, void * & ret) {
			if ((end - read) < sizeof(void*)) {
				throw std::out_of_range("Read range passed into ez::deserialize::ptr is too small!");
			}

			ConverterPtr convert;
			readConvert(read, convert);

			ret = convert.ptr;
			return read + sizeof(convert);
		}
	}
}