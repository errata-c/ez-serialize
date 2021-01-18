#include <ez/serialize.hpp>
#include <ez/intern/Convert.hpp>

namespace ez {
	using namespace intern;
	namespace serialize {
		void string(const std::string& val, std::vector<std::uint8_t>& buffer) {
			u64(val.length(), buffer);
			for (auto elem : val) {
				i8(elem, buffer);
			}
		}

		void string_u8(const std::basic_string<std::uint8_t>& val, std::vector<std::uint8_t>& buffer) {
			u64(val.length(), buffer);
			for (std::uint8_t elem : val) {
				buffer.push_back(elem);
			}
		}
		void string_u16(const std::basic_string<std::uint16_t>& val, std::vector<std::uint8_t>& buffer) {
			u64(val.length(), buffer);
			for (auto elem : val) {
				u16(elem, buffer);
			}
		}
		void string_u32(const std::basic_string<std::uint32_t>& val, std::vector<std::uint8_t>& buffer) {
			u64(val.length(), buffer);
			for (auto elem : val) {
				u32(elem, buffer);
			}
		}
		void string_u64(const std::basic_string<std::uint64_t>& val, std::vector<std::uint8_t>& buffer) {
			u64(val.length(), buffer);
			for (auto elem : val) {
				u64(elem, buffer);
			}
		}

		void string_i8(const std::basic_string<std::int8_t>& val, std::vector<std::uint8_t>& buffer) {
			u64(val.length(), buffer);
			for (auto elem : val) {
				i8(elem, buffer);
			}
		}
		void string_i16(const std::basic_string<std::int16_t>& val, std::vector<std::uint8_t>& buffer) {
			u64(val.length(), buffer);
			for (auto elem : val) {
				i16(elem, buffer);
			}
		}
		void string_i32(const std::basic_string<std::int32_t>& val, std::vector<std::uint8_t>& buffer) {
			u64(val.length(), buffer);
			for (auto elem : val) {
				i32(elem, buffer);
			}
		}
		void string_i64(const std::basic_string<std::int64_t>& val, std::vector<std::uint8_t>& buffer) {
			u64(val.length(), buffer);
			for (auto elem : val) {
				i64(elem, buffer);
			}
		}

		std::uint8_t* i8(std::int8_t val, std::uint8_t* write) {
			Converter8 convert;
			convert.intVal = val;
			(*write) = convert.uintVal;
			return ++write;
		}
		std::uint8_t* i16(std::int16_t val, std::uint8_t* write) {
			Converter16 convert;
			convert.intVal = val;
			for (int i = 0; i < sizeof(val); ++i) {
				(*write) = readByte16(convert.uintVal, i);
				++write;
			}
			return write;
		}
		std::uint8_t* i32(std::int32_t val, std::uint8_t* write) {
			Converter32 convert;
			convert.intVal = val;
			for (int i = 0; i < sizeof(val); ++i) {
				(*write) = readByte32(convert.uintVal, i);
				++write;
			}
			return write;
		}
		std::uint8_t* i64(std::int64_t val, std::uint8_t* write) {
			Converter64 convert;
			convert.intVal = val;
			for (int i = 0; i < sizeof(val); ++i) {
				(*write) = readByte64(convert.uintVal, i);
				++write;
			}
			return write;
		}

		std::uint8_t* u8(std::uint8_t val, std::uint8_t* write) {
			(*write) = val;
			return ++write;
		}
		std::uint8_t* u16(std::uint16_t val, std::uint8_t* write) {
			for (int i = 0; i < sizeof(val); ++i) {
				(*write) = readByte16(val, i);
				++write;
			}
			return write;
		}
		std::uint8_t* u32(std::uint32_t val, std::uint8_t* write) {
			for (int i = 0; i < sizeof(val); ++i) {
				(*write) = readByte32(val, i);
				++write;
			}
			return write;
		}
		std::uint8_t* u64(std::uint64_t val, std::uint8_t* write) {
			for (int i = 0; i < sizeof(val); ++i) {
				(*write) = readByte64(val, i);
				++write;
			}
			return write;
		}

		std::uint8_t* f32(float val, std::uint8_t* write) {
			Converter32 convert;
			convert.floatVal = val;
			for (int i = 0; i < sizeof(convert.uintVal); ++i) {
				(*write) = readByte32(convert.uintVal, i);
				++write;
			}
			return write;
		}
		std::uint8_t* f64(double val, std::uint8_t* write) {
			Converter64 convert;
			convert.floatVal = val;
			for (int i = 0; i < sizeof(convert.uintVal); ++i) {
				(*write) = readByte64(convert.uintVal, i);
				++write;
			}
			return write;
		}

		void i8(int8_t val, std::vector<std::uint8_t>& buffer) {
			Converter8 convert;
			convert.intVal = val;
			buffer.push_back(convert.uintVal);
		}
		void i16(int16_t val, std::vector<std::uint8_t>& buffer) {
			Converter16 convert;
			convert.intVal = val;
			for (int u = 0; u < sizeof(val); ++u) {
				buffer.push_back(readByte16(convert.uintVal, u));
			}
		}
		void i32(int32_t val, std::vector<std::uint8_t>& buffer) {
			Converter32 convert;
			convert.intVal = val;
			for (int u = 0; u < sizeof(val); ++u) {
				buffer.push_back(readByte32(convert.uintVal, u));
			}
		}
		void i64(int64_t val, std::vector<std::uint8_t>& buffer) {
			Converter64 convert;
			convert.intVal = val;
			for (int u = 0; u < sizeof(val); ++u) {
				buffer.push_back(readByte64(convert.uintVal, u));
			}
		}

		void u8(uint8_t val, std::vector<std::uint8_t>& buffer) {
			buffer.push_back(val);
		}
		void u16(uint16_t val, std::vector<std::uint8_t>& buffer) {
			for (int u = 0; u < sizeof(val); ++u) {
				buffer.push_back(readByte16(val, u));
			}
		}
		void u32(uint32_t val, std::vector<std::uint8_t>& buffer) {
			for (int u = 0; u < sizeof(val); ++u) {
				buffer.push_back(readByte32(val, u));
			}
		}
		void u64(uint64_t val, std::vector<std::uint8_t>& buffer) {
			for (int u = 0; u < sizeof(val); ++u) {
				buffer.push_back(readByte64(val, u));
			}
		}

		void f32(float val, std::vector<std::uint8_t>& buffer) {
			Converter32 convert;
			convert.floatVal = val;
			for (int u = 0; u < sizeof(convert.uintVal); ++u) {
				buffer.push_back(readByte32(convert.uintVal, u));
			}
		}
		void f64(double val, std::vector<std::uint8_t>& buffer) {
			Converter64 convert;
			convert.floatVal = val;
			for (int u = 0; u < sizeof(convert.uintVal); ++u) {
				buffer.push_back(readByte64(convert.uintVal, u));
			}
		}

		std::uint8_t* ptr(const void* val, std::uint8_t* write) {
			ConverterPtr convert;
			convert.cptr = val;
			if constexpr (sizeof(void*) == 8) {
				return serialize::u64(convert.uintVal, write);
			}
			else {
				return serialize::u32(static_cast<std::uint32_t>(convert.uintVal), write);
			}
		}

		void ptr(const void* val, std::vector<std::uint8_t>& buffer) {
			ConverterPtr convert;
			convert.cptr = val;
			if constexpr (sizeof(void*) == 8) {
				serialize::u64(convert.uintVal, buffer);
			}
			else {
				serialize::u32(static_cast<std::uint32_t>(convert.uintVal), buffer);
			}
		}
	}
}
