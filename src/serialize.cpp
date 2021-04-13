#include <ez/serialize.hpp>
#include "Convert.hpp"

namespace ez {
	namespace serialize {

		uint8_t* i8(int8_t val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < sizeof(val)) {
				throw std::out_of_range("ez::serialize::string called with write range smaller than the string being written!");
			}

			Converter8 convert;
			convert.intVal = val;
			(*write) = convert.uintVal;
			return ++write;
		}
		uint8_t* i16(int16_t val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < sizeof(val)) {
				throw std::out_of_range("ez::serialize::string called with write range smaller than the string being written!");
			}

			Converter16 convert;
			convert.intVal = val;
			for (int i = 0; i < sizeof(val); ++i) {
				(*write) = readByte16(convert.uintVal, i);
				++write;
			}
			return write;
		}
		uint8_t* i32(int32_t val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < sizeof(val)) {
				throw std::out_of_range("ez::serialize::string called with write range smaller than the string being written!");
			}

			Converter32 convert;
			convert.intVal = val;
			for (int i = 0; i < sizeof(val); ++i) {
				(*write) = readByte32(convert.uintVal, i);
				++write;
			}
			return write;
		}
		uint8_t* i64(int64_t val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < sizeof(val)) {
				throw std::out_of_range("ez::serialize::string called with write range smaller than the string being written!");
			}

			Converter64 convert;
			convert.intVal = val;
			for (int i = 0; i < sizeof(val); ++i) {
				(*write) = readByte64(convert.uintVal, i);
				++write;
			}
			return write;
		}
		uint8_t* u8(uint8_t val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < sizeof(val)) {
				throw std::out_of_range("ez::serialize::string called with write range smaller than the string being written!");
			}

			(*write) = val;
			return ++write;
		}
		uint8_t* u16(uint16_t val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < sizeof(val)) {
				throw std::out_of_range("ez::serialize::string called with write range smaller than the string being written!");
			}

			for (int i = 0; i < sizeof(val); ++i) {
				(*write) = readByte16(val, i);
				++write;
			}
			return write;
		}
		uint8_t* u32(uint32_t val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < sizeof(val)) {
				throw std::out_of_range("ez::serialize::string called with write range smaller than the string being written!");
			}

			for (int i = 0; i < sizeof(val); ++i) {
				(*write) = readByte32(val, i);
				++write;
			}
			return write;
		}
		uint8_t* u64(uint64_t val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < sizeof(val)) {
				throw std::out_of_range("ez::serialize::string called with write range smaller than the string being written!");
			}

			for (int i = 0; i < sizeof(val); ++i) {
				(*write) = readByte64(val, i);
				++write;
			}
			return write;
		}
		uint8_t* f32(float val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < sizeof(val)) {
				throw std::out_of_range("ez::serialize::string called with write range smaller than the string being written!");
			}

			Converter32 convert;
			convert.floatVal = val;
			for (int i = 0; i < sizeof(convert.uintVal); ++i) {
				(*write) = readByte32(convert.uintVal, i);
				++write;
			}
			return write;
		}
		uint8_t* f64(double val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < sizeof(val)) {
				throw std::out_of_range("ez::serialize::string called with write range smaller than the string being written!");
			}

			Converter64 convert;
			convert.floatVal = val;
			for (int i = 0; i < sizeof(convert.uintVal); ++i) {
				(*write) = readByte64(convert.uintVal, i);
				++write;
			}
			return write;
		}
		uint8_t* ptr(const void* val, uint8_t* write, uint8_t const* const end) {
			ConverterPtr convert;
			convert.cptr = val;
			if constexpr (sizeof(val) == 8) {
				return serialize::u64(convert.uintVal, write, end);
			}
			else {
				return serialize::u32(static_cast<std::uint32_t>(convert.uintVal), write, end);
			}
		}


		void i8(int8_t val, std::vector<uint8_t>& buffer) {
			Converter8 convert;
			convert.intVal = val;
			buffer.push_back(convert.uintVal);
		}
		void i16(int16_t val, std::vector<uint8_t>& buffer) {
			Converter16 convert;
			convert.intVal = val;
			for (int u = 0; u < sizeof(val); ++u) {
				buffer.push_back(readByte16(convert.uintVal, u));
			}
		}
		void i32(int32_t val, std::vector<uint8_t>& buffer) {
			Converter32 convert;
			convert.intVal = val;
			for (int u = 0; u < sizeof(val); ++u) {
				buffer.push_back(readByte32(convert.uintVal, u));
			}
		}
		void i64(int64_t val, std::vector<uint8_t>& buffer) {
			Converter64 convert;
			convert.intVal = val;
			for (int u = 0; u < sizeof(val); ++u) {
				buffer.push_back(readByte64(convert.uintVal, u));
			}
		}
		void u8(uint8_t val, std::vector<uint8_t>& buffer) {
			buffer.push_back(val);
		}
		void u16(uint16_t val, std::vector<uint8_t>& buffer) {
			for (int u = 0; u < sizeof(val); ++u) {
				buffer.push_back(readByte16(val, u));
			}
		}
		void u32(uint32_t val, std::vector<uint8_t>& buffer) {
			for (int u = 0; u < sizeof(val); ++u) {
				buffer.push_back(readByte32(val, u));
			}
		}
		void u64(uint64_t val, std::vector<uint8_t>& buffer) {
			for (int u = 0; u < sizeof(val); ++u) {
				buffer.push_back(readByte64(val, u));
			}
		}

		void f32(float val, std::vector<uint8_t>& buffer) {
			Converter32 convert;
			convert.floatVal = val;
			for (int u = 0; u < sizeof(convert.uintVal); ++u) {
				buffer.push_back(readByte32(convert.uintVal, u));
			}
		}
		void f64(double val, std::vector<uint8_t>& buffer) {
			Converter64 convert;
			convert.floatVal = val;
			for (int u = 0; u < sizeof(convert.uintVal); ++u) {
				buffer.push_back(readByte64(convert.uintVal, u));
			}
		}
		void ptr(const void* val, std::vector<uint8_t>& buffer) {
			ConverterPtr convert;
			convert.cptr = val;
			if constexpr (sizeof(void*) == 8) {
				serialize::u64(convert.uintVal, buffer);
			}
			else {
				serialize::u32(static_cast<std::uint32_t>(convert.uintVal), buffer);
			}
		}


		uint8_t* value(int8_t val, uint8_t* write, uint8_t const* const end) {
			return serialize::i8(val, write, end);
		}
		uint8_t* value(int16_t val, uint8_t* write, uint8_t const* const end) {
			return serialize::i16(val, write, end);
		}
		uint8_t* value(int32_t val, uint8_t* write, uint8_t const* const end) {
			return serialize::i32(val, write, end);
		}
		uint8_t* value(int64_t val, uint8_t* write, uint8_t const* const end) {
			return serialize::i64(val, write, end);
		}
		uint8_t* value(uint8_t val, uint8_t* write, uint8_t const* const end) {
			return serialize::u8(val, write, end);
		}
		uint8_t* value(uint16_t val, uint8_t* write, uint8_t const* const end) {
			return serialize::u16(val, write, end);
		}
		uint8_t* value(uint32_t val, uint8_t* write, uint8_t const* const end) {
			return serialize::u32(val, write, end);
		}
		uint8_t* value(uint64_t val, uint8_t* write, uint8_t const* const end) {
			return serialize::u64(val, write, end);
		}
		uint8_t* value(float val, uint8_t* write, uint8_t* end) {
			return serialize::f32(val, write, end);
		}
		uint8_t* value(double val, uint8_t* write, uint8_t* end) {
			return serialize::f64(val, write, end);
		}
		uint8_t* value(const void* val, uint8_t* write, uint8_t* end) {
			return serialize::ptr(val, write, end);
		}

		void value(int8_t val, std::vector<uint8_t>& buffer) {
			return serialize::i8(val, buffer);
		}
		void value(int16_t val, std::vector<uint8_t>& buffer) {
			return serialize::i16(val, buffer);
		}
		void value(int32_t val, std::vector<uint8_t>& buffer) {
			return serialize::i32(val, buffer);
		}
		void value(int64_t val, std::vector<uint8_t>& buffer) {
			return serialize::i64(val, buffer);
		}
		void value(uint8_t val, std::vector<uint8_t>& buffer) {
			return serialize::u8(val, buffer);
		}
		void value(uint16_t val, std::vector<uint8_t>& buffer) {
			return serialize::u16(val, buffer);
		}
		void value(uint32_t val, std::vector<uint8_t>& buffer) {
			return serialize::u32(val, buffer);
		}
		void value(uint64_t val, std::vector<uint8_t>& buffer) {
			return serialize::u64(val, buffer);
		}
		void value(float val, std::vector<uint8_t>& buffer) {
			return serialize::f32(val, buffer);
		}
		void value(double val, std::vector<uint8_t>& buffer) {
			return serialize::f64(val, buffer);
		}
		void value(const void* val, std::vector<uint8_t>& buffer) {
			return serialize::ptr(val, buffer);
		}
	}
}
