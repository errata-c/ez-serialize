#include <ez/deserialize.hpp>
#include <ez/intern/Convert.hpp>
#include <cassert>

namespace ez {
	using namespace intern;
	namespace deserialize {
		void string(const std::uint8_t*& read, std::string& ret) {
			std::uint64_t length = u64(read);
			ret.reserve(ret.size() + length);

			const std::uint8_t* end = read + length;
			while (read < end) {
				ret.push_back(i8(read));
			}
		}

		void string_u8(const std::uint8_t*& read, std::basic_string<std::uint8_t>& ret) {
			std::uint64_t length = u64(read);
			ret.reserve(ret.size() + length);

			const std::uint8_t* end = read + length;
			while (read < end) {
				ret.push_back(u8(read));
			}
		}
		void string_u16(const std::uint8_t*& read, std::basic_string<std::uint16_t>& ret) {
			std::uint64_t length = u64(read);
			assert(length % 2 == 0);

			ret.reserve(ret.size() + length / 2);

			const std::uint8_t* end = read + length;
			while (read < end) {
				ret.push_back(u16(read));
			}
		}
		void string_u32(const std::uint8_t*& read, std::basic_string<std::uint32_t>& ret) {
			std::uint64_t length = u64(read);
			assert(length % 4 == 0);

			ret.reserve(ret.size() + length / 4);

			const std::uint8_t* end = read + length;
			while (read < end) {
				ret.push_back(u32(read));
			}
		}
		void string_u64(const std::uint8_t*& read, std::basic_string<std::uint64_t>& ret) {
			std::uint64_t length = u64(read);
			assert(length % 8 == 0);

			ret.reserve(ret.size() + length / 8);

			const std::uint8_t* end = read + length;
			while (read < end) {
				ret.push_back(u64(read));
			}
		}

		void string_i8(const std::uint8_t*& read, std::basic_string<std::int8_t>& ret) {
			std::uint64_t length = u64(read);
			ret.reserve(ret.size() + length);

			const std::uint8_t* end = read + length;
			while (read < end) {
				ret.push_back(i8(read));
			}
		}
		void string_i16(const std::uint8_t*& read, std::basic_string<std::int16_t>& ret) {
			std::uint64_t length = u64(read);
			assert(length % 2 == 0);

			ret.reserve(ret.size() + length / 2);

			const std::uint8_t* end = read + length;
			while (read < end) {
				ret.push_back(i16(read));
			}
		}
		void string_i32(const std::uint8_t*& read, std::basic_string<std::int32_t>& ret) {
			std::uint64_t length = u64(read);
			assert(length % 4 == 0);

			ret.reserve(ret.size() + length / 4);

			const std::uint8_t* end = read + length;
			while (read < end) {
				ret.push_back(i32(read));
			}
		}
		void string_i64(const std::uint8_t*& read, std::basic_string<std::int64_t>& ret) {
			std::uint64_t length = u64(read);
			assert(length % 8 == 0);

			ret.reserve(ret.size() + length / 8);

			const std::uint8_t* end = read + length;
			while (read < end) {
				ret.push_back(i64(read));
			}
		}

		std::string string(const std::uint8_t*& read) {
			std::uint64_t length = u64(read);
			std::string ret(length, 0);

			for (auto && val : ret) {
				val = i8(read);
			}

			return ret;
		}

		std::basic_string<std::uint8_t> string_u8(const std::uint8_t*& read) {
			std::uint64_t length = u64(read);
			std::basic_string<std::uint8_t> ret(length, 0);

			for (auto&& val : ret) {
				val = u8(read);
			}

			return ret;
		}
		std::basic_string<std::uint16_t> string_u16(const std::uint8_t*& read) {
			std::uint64_t length = u64(read);
			assert(length % 2 == 0);

			std::basic_string<std::uint16_t> ret(length / 2, 0);
			
			for (auto&& val : ret) {
				val = u16(read);
			}

			return ret;
		}
		std::basic_string<std::uint32_t> string_u32(const std::uint8_t*& read) {
			std::uint64_t length = u64(read);
			assert(length % 4 == 0);

			std::basic_string<std::uint32_t> ret(length / 4, 0);

			for (auto&& val : ret) {
				val = u32(read);
			}

			return ret;
		}
		std::basic_string<std::uint64_t> string_u64(const std::uint8_t*& read) {
			std::uint64_t length = u64(read);
			assert(length % 8 == 0);

			std::basic_string<std::uint64_t> ret(length / 8, 0);

			for (auto&& val : ret) {
				val = u64(read);
			}

			return ret;
		}

		std::basic_string<std::int8_t> string_i8(const std::uint8_t*& read) {
			std::uint64_t length = u64(read);
			std::basic_string<std::int8_t> ret(length, 0);

			for (auto&& val : ret) {
				val = i8(read);
			}

			return ret;
		}
		std::basic_string<std::int16_t> string_i16(const std::uint8_t*& read) {
			std::uint64_t length = u64(read);
			assert(length % 2 == 0);

			std::basic_string<std::int16_t> ret(length / 2, 0);

			for (auto&& val : ret) {
				val = i16(read);
			}

			return ret;
		}
		std::basic_string<std::int32_t> string_i32(const std::uint8_t*& read) {
			std::uint64_t length = u64(read);
			assert(length % 4 == 0);

			std::basic_string<std::int32_t> ret(length / 4, 0);

			for (auto&& val : ret) {
				val = i32(read);
			}

			return ret;
		}
		std::basic_string<std::int64_t> string_i64(const std::uint8_t*& read) {
			std::uint64_t length = u64(read);
			assert(length % 8 == 0);

			std::basic_string<std::int64_t> ret(length / 8, 0);

			for (auto&& val : ret) {
				val = i64(read);
			}

			return ret;
		}

		float f32(const std::uint8_t*& read) {
			Converter32 convert;
			convert.uintVal = 0;
			for (int i = 0; i < sizeof(convert.uintVal); ++i) {
				convert.uintVal |= writeByte32(*read, i);
				++read;
			}
			return convert.floatVal;
		}
		double f64(const std::uint8_t*& read) {
			Converter64 convert;
			convert.uintVal = 0;
			for (int i = 0; i < sizeof(convert.uintVal); ++i) {
				convert.uintVal |= writeByte64(*read, i);
				++read;
			}
			return convert.floatVal;
		}

		std::int8_t i8(const std::uint8_t*& read) {
			Converter8 convert;
			convert.uintVal = *read;
			++read;
			return convert.intVal;
		}
		std::int16_t i16(const std::uint8_t*& read) {
			Converter16 convert;
			convert.uintVal = 0;
			for (int i = 0; i < sizeof(convert.uintVal); ++i) {
				convert.uintVal |= writeByte16(*read, i);
				++read;
			}
			return convert.intVal;
		}
		std::int32_t i32(const std::uint8_t*& read) {
			Converter32 convert;
			convert.uintVal = 0;
			for (int i = 0; i < sizeof(convert.uintVal); ++i) {
				convert.uintVal |= writeByte32(*read, i);
				++read;
			}
			return convert.intVal;
		}
		std::int64_t i64(const std::uint8_t*& read) {
			Converter64 convert;
			convert.uintVal = 0;
			for (int i = 0; i < sizeof(convert.uintVal); ++i) {
				convert.uintVal |= writeByte64(*read, i);
				++read;
			}
			return convert.intVal;
		}

		std::uint8_t u8(const std::uint8_t*& read) {
			std::uint8_t val = *read;
			++read;
			return val;
		}
		std::uint16_t u16(const std::uint8_t*& read) {
			std::uint16_t val = 0;
			for (int i = 0; i < sizeof(val); ++i) {
				val |= writeByte16(*read, i);
				++read;
			}
			return val;
		}
		std::uint32_t u32(const std::uint8_t*& read) {
			std::uint32_t val = 0;
			for (int i = 0; i < sizeof(val); ++i) {
				val |= writeByte32(*read, i);
				++read;
			}
			return val;
		}
		std::uint64_t u64(const std::uint8_t*& read) {
			std::uint64_t val = 0;
			for (int i = 0; i < sizeof(val); ++i) {
				val |= writeByte64(*read, i);
				++read;
			}
			return val;
		}

		void* ptr(const std::uint8_t*& read) {
			if constexpr (sizeof(void*) == 8) {
				return reinterpret_cast<void*>(u64(read));
			}
			else {
				return reinterpret_cast<void*>(static_cast<std::uintptr_t>(u32(read)));
			}
		}
	}
}