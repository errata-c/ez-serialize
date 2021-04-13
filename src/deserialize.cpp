#include <ez/deserialize.hpp>
#include "Convert.hpp"
#include <cassert>
#include <stdexcept>

namespace ez {
	namespace deserialize {
		void string(const uint8_t*& read, uint8_t const* const end, std::string& ret) {
			static_assert(sizeof(std::string::value_type) == 1, "Unexpected character size for std::string!");

			uint64_t length = u64(read, end);

			if ((end - read) < length) {
				throw std::out_of_range("Read range passed into ez::deserialize::string is too small!");
			}

			uint64_t start = ret.size();
			ret.resize(ret.size() + length, '\0');
			uint8_t* write = (uint8_t*)(ret.data() + start);

			const uint8_t* last = read + length;
			while (read < last) {
				*write = u8(read, write);
				++write;
			}
		}
		void string_u8(const uint8_t*& read, uint8_t const* const end, std::basic_string<uint8_t>& ret) {
			uint64_t bytes = u64(read, end);
			uint64_t length = bytes / sizeof(uint8_t);

			if ((end - read) < bytes) {
				throw std::out_of_range("Read range passed into ez::deserialize::string_u8 is too small!");
			}

			ret.reserve(ret.size() + length);

			const uint8_t* last = read + length;
			while (read < last) {
				ret.push_back(u8(read, end));
			}
		}
		void string_u16(const uint8_t*& read, uint8_t const* const end, std::basic_string<uint16_t>& ret) {
			uint64_t bytes = u64(read, end);
			uint64_t length = bytes / sizeof(uint16_t);

			if ((end - read) < bytes) {
				throw std::out_of_range("Read range passed into ez::deserialize::string_u16 is too small!");
			}

			ret.reserve(ret.size() + length);

			const uint8_t* last = read + length;
			while (read < last) {
				ret.push_back(u16(read, end));
			}
		}
		void string_u32(const uint8_t*& read, uint8_t const* const end, std::basic_string<uint32_t>& ret) {
			uint64_t bytes = u64(read, end);
			uint64_t length = bytes / sizeof(uint32_t);

			if ((end - read) < bytes) {
				throw std::out_of_range("Read range passed into ez::deserialize::string_u32 is too small!");
			}

			ret.reserve(ret.size() + length);

			const uint8_t* last = read + length;
			while (read < last) {
				ret.push_back(u32(read, end));
			}
		}
		void string_u64(const uint8_t*& read, uint8_t const* const end, std::basic_string<uint64_t>& ret) {
			uint64_t bytes = u64(read, end);
			uint64_t length = bytes / sizeof(uint64_t);

			if ((end - read) < bytes) {
				throw std::out_of_range("Read range passed into ez::deserialize::string_u64 is too small!");
			}

			ret.reserve(ret.size() + length);

			const uint8_t* last = read + length;
			while (read < last) {
				ret.push_back(u64(read, end));
			}
		}

		void string_i8(const uint8_t*& read, uint8_t const* const end, std::basic_string<int8_t>& ret) {
			uint64_t bytes = u64(read, end);
			uint64_t length = bytes / sizeof(int8_t);

			if ((end - read) < bytes) {
				throw std::out_of_range("Read range passed into ez::deserialize::string_i8 is too small!");
			}

			ret.reserve(ret.size() + length);

			const uint8_t* last = read + length;
			while (read < last) {
				ret.push_back(i8(read, end));
			}
		}
		void string_i16(const uint8_t*& read, uint8_t const* const end, std::basic_string<int16_t>& ret) {
			uint64_t bytes = u64(read, end);
			uint64_t length = bytes / sizeof(int16_t);

			if ((end - read) < bytes) {
				throw std::out_of_range("Read range passed into ez::deserialize::string_i16 is too small!");
			}

			ret.reserve(ret.size() + length / 2);

			const uint8_t* last = read + length;
			while (read < last) {
				ret.push_back(i16(read, end));
			}
		}
		void string_i32(const uint8_t*& read, uint8_t const* const end, std::basic_string<int32_t>& ret) {
			uint64_t bytes = u64(read, end);
			uint64_t length = bytes / sizeof(int32_t);

			if ((end - read) < bytes) {
				throw std::out_of_range("Read range passed into ez::deserialize::string_i32 is too small!");
			}

			ret.reserve(ret.size() + length);

			const uint8_t* last = read + length;
			while (read < last) {
				ret.push_back(i32(read, end));
			}
		}
		void string_i64(const uint8_t*& read, uint8_t const* const end, std::basic_string<int64_t>& ret) {
			uint64_t bytes = u64(read, end);
			uint64_t length = bytes / sizeof(int64_t);

			if ((end - read) < bytes) {
				throw std::out_of_range("Read range passed into ez::deserialize::string_i64 is too small!");
			}

			ret.reserve(ret.size() + length / 8);

			const uint8_t* last = read + length;
			while (read < last) {
				ret.push_back(i64(read, end));
			}
		}

		std::basic_string<uint8_t> string_u8(const uint8_t*& read, uint8_t const* const end) {
			std::basic_string<uint8_t> ret;
			deserialize::string_u8(read, end, ret);

			return ret;
		}
		std::basic_string<uint16_t> string_u16(const uint8_t*& read, uint8_t const* const end) {
			std::basic_string<uint16_t> ret;
			deserialize::string_u16(read, end, ret);

			return ret;
		}
		std::basic_string<uint32_t> string_u32(const uint8_t*& read, uint8_t const* const end) {
			std::basic_string<uint32_t> ret;
			string_u32(read, end, ret);

			return ret;
		}
		std::basic_string<uint64_t> string_u64(const uint8_t*& read, uint8_t const* const end) {
			std::basic_string<uint64_t> ret;
			deserialize::string_u64(read, end, ret);

			return ret;
		}

		std::basic_string<int8_t> string_i8(const uint8_t*& read, uint8_t const* const end) {
			std::basic_string<int8_t> ret;
			deserialize::string_i8(read, end, ret);

			return ret;
		}
		std::basic_string<int16_t> string_i16(const uint8_t*& read, uint8_t const* const end) {
			std::basic_string<int16_t> ret;
			deserialize::string_i16(read, end, ret);

			return ret;
		}
		std::basic_string<int32_t> string_i32(const uint8_t*& read, uint8_t const* const end) {
			std::basic_string<int32_t> ret;
			deserialize::string_i32(read, end, ret);

			return ret;
		}
		std::basic_string<int64_t> string_i64(const uint8_t*& read, uint8_t const* const end) {
			std::basic_string<int64_t> ret;
			deserialize::string_i64(read, end, ret);

			return ret;
		}
		std::string string(const uint8_t*& read, uint8_t const* const end) {
			std::string ret;
			deserialize::string(read, end, ret);

			return ret;
		}

		float f32(const uint8_t*& read, uint8_t const* const end) {
			if ((end - read) < sizeof(float)) {
				throw std::out_of_range("Read range passed into ez::deserialize::f32 is too small!");
			}

			Converter32 convert;
			convert.uintVal = 0;
			for (int i = 0; i < sizeof(convert.uintVal); ++i) {
				convert.uintVal |= writeByte32(*read, i);
				++read;
			}
			return convert.floatVal;
		}
		double f64(const uint8_t*& read, uint8_t const* const end) {
			if ((end - read) < sizeof(double)) {
				throw std::out_of_range("Read range passed into ez::deserialize::f64 is too small!");
			}

			Converter64 convert;
			convert.uintVal = 0;
			for (int i = 0; i < sizeof(convert.uintVal); ++i) {
				convert.uintVal |= writeByte64(*read, i);
				++read;
			}
			return convert.floatVal;
		}

		int8_t i8(const uint8_t*& read, uint8_t const* const end) {
			if ((end - read) < sizeof(int8_t)) {
				throw std::out_of_range("Read range passed into ez::deserialize::i8 is too small!");
			}

			Converter8 convert;
			convert.uintVal = *read;
			++read;
			return convert.intVal;
		}
		int16_t i16(const uint8_t*& read, uint8_t const* const end) {
			if ((end - read) < sizeof(int16_t)) {
				throw std::out_of_range("Read range passed into ez::deserialize::i16 is too small!");
			}

			Converter16 convert;
			convert.uintVal = 0;
			for (int i = 0; i < sizeof(convert.uintVal); ++i) {
				convert.uintVal |= writeByte16(*read, i);
				++read;
			}
			return convert.intVal;
		}
		int32_t i32(const uint8_t*& read, uint8_t const* const end) {
			if ((end - read) < sizeof(int32_t)) {
				throw std::out_of_range("Read range passed into ez::deserialize::i32 is too small!");
			}

			Converter32 convert;
			convert.uintVal = 0;
			for (int i = 0; i < sizeof(convert.uintVal); ++i) {
				convert.uintVal |= writeByte32(*read, i);
				++read;
			}
			return convert.intVal;
		}
		int64_t i64(const uint8_t*& read, uint8_t const* const end) {
			if ((end - read) < sizeof(int64_t)) {
				throw std::out_of_range("Read range passed into ez::deserialize::i64 is too small!");
			}

			Converter64 convert;
			convert.uintVal = 0;
			for (int i = 0; i < sizeof(convert.uintVal); ++i) {
				convert.uintVal |= writeByte64(*read, i);
				++read;
			}
			return convert.intVal;
		}

		uint8_t u8(const uint8_t*& read, uint8_t const* const end) {
			if ((end - read) < sizeof(uint8_t)) {
				throw std::out_of_range("Read range passed into ez::deserialize::u8 is too small!");
			}

			uint8_t val = *read;
			++read;
			return val;
		}
		uint16_t u16(const uint8_t*& read, uint8_t const* const end) {
			if ((end - read) < sizeof(uint16_t)) {
				throw std::out_of_range("Read range passed into ez::deserialize::u16 is too small!");
			}

			uint16_t val = 0;
			for (int i = 0; i < sizeof(val); ++i) {
				val |= writeByte16(*read, i);
				++read;
			}
			return val;
		}
		uint32_t u32(const uint8_t*& read, uint8_t const* const end) {
			if ((end - read) < sizeof(uint32_t)) {
				throw std::out_of_range("Read range passed into ez::deserialize::u32 is too small!");
			}

			uint32_t val = 0;
			for (int i = 0; i < sizeof(val); ++i) {
				val |= writeByte32(*read, i);
				++read;
			}
			return val;
		}
		uint64_t u64(const uint8_t*& read, uint8_t const* const end) {
			if ((end - read) < sizeof(uint64_t)) {
				throw std::out_of_range("Read range passed into ez::deserialize::u64 is too small!");
			}

			uint64_t val = 0;
			for (int i = 0; i < sizeof(val); ++i) {
				val |= writeByte64(*read, i);
				++read;
			}
			return val;
		}

		void* ptr(const uint8_t*& read, uint8_t const* const end) {
			if ((end - read) < sizeof(void*)) {
				throw std::out_of_range("Read range passed into ez::deserialize::ptr is too small!");
			}

			if constexpr (sizeof(void*) == 8) {
				return reinterpret_cast<void*>(u64(read, end));
			}
			else {
				return reinterpret_cast<void*>(static_cast<std::uintptr_t>(u32(read, end)));
			}
		}
	}
}