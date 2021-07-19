#include <ez/serialize.hpp>
#include "Convert.hpp"

namespace ez {
	namespace serialize {
		uint8_t* i8(int8_t val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < sizeof(val)) {
				throw std::out_of_range("ez::serialize::i8 called with write range smaller than the object being written!");
			}

			Converter8 convert;
			convert.intVal = val;
			*write++ = convert.uintVal;
			return write;
		}
		uint8_t* i16(int16_t val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < sizeof(val)) {
				throw std::out_of_range("ez::serialize::i16 called with write range smaller than the object being written!");
			}

			Converter16 convert;
			convert.intVal = val;
			writeConvert(write, convert);

			return write + sizeof(convert);
		}
		uint8_t* i32(int32_t val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < sizeof(val)) {
				throw std::out_of_range("ez::serialize::i32 called with write range smaller than the object being written!");
			}

			Converter32 convert;
			convert.intVal = val;
			writeConvert(write, convert);

			return write + sizeof(convert);
		}
		uint8_t* i64(int64_t val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < sizeof(val)) {
				throw std::out_of_range("ez::serialize::i64 called with write range smaller than the object being written!");
			}

			Converter64 convert;
			convert.intVal = val;
			writeConvert(write, convert);

			return write + sizeof(convert);
		}
		uint8_t* u8(uint8_t val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < sizeof(val)) {
				throw std::out_of_range("ez::serialize::u8 called with write range smaller than the object being written!");
			}

			*write++ = val;
			return write;
		}
		uint8_t* u16(uint16_t val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < sizeof(val)) {
				throw std::out_of_range("ez::serialize::u16 called with write range smaller than the object being written!");
			}

			Converter16 convert;
			convert.uintVal = val;
			writeConvert(write, convert);

			return write + sizeof(convert);
		}
		uint8_t* u32(uint32_t val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < sizeof(val)) {
				throw std::out_of_range("ez::serialize::u32 called with write range smaller than the object being written!");
			}

			Converter32 convert;
			convert.uintVal = val;
			writeConvert(write, convert);

			return write + sizeof(convert);
		}
		uint8_t* u64(uint64_t val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < sizeof(val)) {
				throw std::out_of_range("ez::serialize::u64 called with write range smaller than the object being written!");
			}

			Converter64 convert;
			convert.uintVal = val;
			writeConvert(write, convert);

			return write + sizeof(convert);
		}
		uint8_t* f32(float val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < sizeof(val)) {
				throw std::out_of_range("ez::serialize::ptr called with write range smaller than the object being written!");
			}

			Converter32 convert;
			convert.floatVal = val;
			writeConvert(write, convert);

			return write + sizeof(convert);
		}
		uint8_t* f64(double val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < sizeof(val)) {
				throw std::out_of_range("ez::serialize::f64 called with write range smaller than the object being written!");
			}

			Converter64 convert;
			convert.floatVal = val;
			writeConvert(write, convert);

			return write + sizeof(convert);
		}
		uint8_t* ptr(const void* val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < sizeof(val)) {
				throw std::out_of_range("ez::serialize::f32 called with write range smaller than the object being written!");
			}

			ConverterPtr convert;
			convert.cptr = val;
			writeConvert(write, convert);

			return write + sizeof(convert);
		}

		uint8_t* string(const std::string& val, uint8_t* write, uint8_t const* const end) {
			if ((end - write) < val.size()) {
				throw std::out_of_range("ez::serialize::string called with write range smaller than the object being written!");
			}

			uint64_t length = val.size();
			write = u64(length, write, end);

			Converter8 convert;
			for (char elem : val) {
				convert.charVal = elem;
				write = i8(convert.intVal, write, end);
			}

			return write;
		}
		uint8_t* string_u8(const std::basic_string<uint8_t>& val, uint8_t* write, uint8_t const* const end) {
			uint64_t bytes = val.size();

			if ((end - write) < bytes) {
				throw std::out_of_range("ez::serialize::string_u8 called with write range smaller than the object being written!");
			}
			
			write = u64(bytes, write, end);

			for (uint8_t elem : val) {
				write = u8(elem, write, end);
			}

			return write;
		}
		uint8_t* string_u16(const std::basic_string<uint16_t>& val, uint8_t* write, uint8_t const* const end) {
			uint64_t bytes = val.size() * 2;

			if ((end - write) < val.size()) {
				throw std::out_of_range("ez::serialize::string_u16 called with write range smaller than the object being written!");
			}

			write = u64(bytes, write, end);

			for (uint16_t elem : val) {
				write = u16(elem, write, end);
			}

			return write;
		}
		uint8_t* string_u32(const std::basic_string<uint32_t>& val, uint8_t* write, uint8_t const* const end) {
			uint64_t bytes = val.size() * 4;

			if ((end - write) < bytes) {
				throw std::out_of_range("ez::serialize::string_u32 called with write range smaller than the object being written!");
			}
			
			write = u64(bytes, write, end);

			for (uint32_t elem : val) {
				write = u32(elem, write, end);
			}

			return write;
		}
		uint8_t* string_u64(const std::basic_string<uint64_t>& val, uint8_t* write, uint8_t const* const end) {
			uint64_t bytes = val.size() * 8;

			if ((end - write) < val.size()) {
				throw std::out_of_range("ez::serialize::string_u64 called with write range smaller than the object being written!");
			}

			write = u64(bytes, write, end);

			for (uint64_t elem : val) {
				write = u64(elem, write, end);
			}

			return write;
		}
		uint8_t* string_i8(const std::basic_string<int8_t>& val, uint8_t* write, uint8_t const* const end) {
			uint64_t bytes = val.size();

			if ((end - write) < val.size()) {
				throw std::out_of_range("ez::serialize::string_i8 called with write range smaller than the object being written!");
			}

			write = u64(bytes, write, end);

			for (int8_t elem : val) {
				write = i8(elem, write, end);
			}

			return write;
		}
		uint8_t* string_i16(const std::basic_string<int16_t>& val, uint8_t* write, uint8_t const* const end) {
			uint64_t bytes = val.size() * 2;

			if ((end - write) < val.size()) {
				throw std::out_of_range("ez::serialize::string_i16 called with write range smaller than the object being written!");
			}

			write = u64(bytes, write, end);

			for (int16_t elem : val) {
				write = i16(elem, write, end);
			}

			return write;
		}
		uint8_t* string_i32(const std::basic_string<int32_t>& val, uint8_t* write, uint8_t const* const end) {
			uint64_t bytes = val.size() * 4;

			if ((end - write) < val.size()) {
				throw std::out_of_range("ez::serialize::string_i32 called with write range smaller than the object being written!");
			}

			write = u64(bytes, write, end);

			for (int32_t elem : val) {
				write = i32(elem, write, end);
			}

			return write;
		}
		uint8_t* string_i64(const std::basic_string<int64_t>& val, uint8_t* write, uint8_t const* const end) {
			uint64_t bytes = val.size() * 8;

			if ((end - write) < val.size()) {
				throw std::out_of_range("ez::serialize::string_i64 called with write range smaller than the object being written!");
			}

			write = u64(bytes, write, end);

			for (int64_t elem : val) {
				write = i64(elem, write, end);
			}

			return write;
		}


		void i8(int8_t val, std::vector<uint8_t>& buffer) {
			Converter8 convert;
			convert.intVal = val;
			buffer.push_back(convert.uintVal);
		}
		void i16(int16_t val, std::vector<uint8_t>& buffer) {
			Converter16 convert;
			convert.intVal = val;
			
			writeConvert(buffer, convert);
		}
		void i32(int32_t val, std::vector<uint8_t>& buffer) {
			Converter32 convert;
			convert.intVal = val;
			
			writeConvert(buffer, convert);
		}
		void i64(int64_t val, std::vector<uint8_t>& buffer) {
			Converter64 convert;
			convert.intVal = val;
			
			writeConvert(buffer, convert);
		}
		void u8(uint8_t val, std::vector<uint8_t>& buffer) {
			buffer.push_back(val);
		}
		void u16(uint16_t val, std::vector<uint8_t>& buffer) {
			Converter16 convert;
			convert.uintVal = val;

			writeConvert(buffer, convert);
		}
		void u32(uint32_t val, std::vector<uint8_t>& buffer) {
			Converter32 convert;
			convert.uintVal = val;

			writeConvert(buffer, convert);
		}
		void u64(uint64_t val, std::vector<uint8_t>& buffer) {
			Converter64 convert;
			convert.uintVal = val;

			writeConvert(buffer, convert);
		}

		void f32(float val, std::vector<uint8_t>& buffer) {
			Converter32 convert;
			convert.floatVal = val;

			writeConvert(buffer, convert);
		}
		void f64(double val, std::vector<uint8_t>& buffer) {
			Converter64 convert;
			convert.floatVal = val;

			writeConvert(buffer, convert);
		}
		void ptr(const void* val, std::vector<uint8_t>& buffer) {
			ConverterPtr convert;
			convert.cptr = val;

			writeConvert(buffer, convert);
		}

		void string(const std::string& val, std::vector<uint8_t>& buffer) {
			uint64_t length = val.size();
			u64(length, buffer);

			Converter8 convert;
			for (char elem : val) {
				convert.charVal = elem;
				i8(convert.intVal, buffer);
			}
		}
		void string_u8(const std::basic_string<uint8_t>& val, std::vector<uint8_t>& buffer) {
			uint64_t bytes = val.size();

			u64(bytes, buffer);

			for (uint8_t elem : val) {
				u8(elem, buffer);
			}
		}
		void string_u16(const std::basic_string<uint16_t>& val, std::vector<uint8_t>& buffer) {
			uint64_t bytes = val.size();

			u64(bytes, buffer);

			for (uint16_t elem : val) {
				u16(elem, buffer);
			}
		}
		void string_u32(const std::basic_string<uint32_t>& val, std::vector<uint8_t>& buffer) {
			uint64_t bytes = val.size();

			u64(bytes, buffer);

			for (uint32_t elem : val) {
				u32(elem, buffer);
			}
		}
		void string_u64(const std::basic_string<uint64_t>& val, std::vector<uint8_t>& buffer) {
			uint64_t bytes = val.size();

			u64(bytes, buffer);

			for (uint64_t elem : val) {
				u64(elem, buffer);
			}
		}
		void string_i8(const std::basic_string<int8_t>& val, std::vector<uint8_t>& buffer) {
			uint64_t bytes = val.size();

			u64(bytes, buffer);

			for (int8_t elem : val) {
				i8(elem, buffer);
			}
		}
		void string_i16(const std::basic_string<int16_t>& val, std::vector<uint8_t>& buffer) {
			uint64_t bytes = val.size();

			u64(bytes, buffer);

			for (int16_t elem : val) {
				i16(elem, buffer);
			}
		}
		void string_i32(const std::basic_string<int32_t>& val, std::vector<uint8_t>& buffer) {
			uint64_t bytes = val.size();

			u64(bytes, buffer);

			for (int32_t elem : val) {
				i32(elem, buffer);
			}
		}
		void string_i64(const std::basic_string<int64_t>& val, std::vector<uint8_t>& buffer) {
			uint64_t bytes = val.size();

			u64(bytes, buffer);

			for (int64_t elem : val) {
				i64(elem, buffer);
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
		uint8_t* value(float val, uint8_t* write, uint8_t const* const end) {
			return serialize::f32(val, write, end);
		}
		uint8_t* value(double val, uint8_t* write, uint8_t const* const end) {
			return serialize::f64(val, write, end);
		}
		uint8_t* value(const void* val, uint8_t* write, uint8_t const* const end) {
			return serialize::ptr(val, write, end);
		}
		uint8_t* value(const std::string& val, uint8_t* write, uint8_t const* const end) {
			return serialize::string(val, write, end);
		}
		uint8_t* value(const std::basic_string<uint8_t>& val, uint8_t* write, uint8_t const* const end) {
			return serialize::string_u8(val, write, end);
		}
		uint8_t* value(const std::basic_string<uint16_t>& val, uint8_t* write, uint8_t const* const end) {
			return serialize::string_u16(val, write, end);
		}
		uint8_t* value(const std::basic_string<uint32_t>& val, uint8_t* write, uint8_t const* const end) {
			return serialize::string_u32(val, write, end);
		}
		uint8_t* value(const std::basic_string<uint64_t>& val, uint8_t* write, uint8_t const* const end) {
			return serialize::string_u64(val, write, end);
		}
		uint8_t* value(const std::basic_string<int8_t>& val, uint8_t* write, uint8_t const* const end) {
			return serialize::string_i8(val, write, end);
		}
		uint8_t* value(const std::basic_string<int16_t>& val, uint8_t* write, uint8_t const* const end) {
			return serialize::string_i16(val, write, end);
		}
		uint8_t* value(const std::basic_string<int32_t>& val, uint8_t* write, uint8_t const* const end) {
			return serialize::string_i32(val, write, end);
		}
		uint8_t* value(const std::basic_string<int64_t>& val, uint8_t* write, uint8_t const* const end) {
			return serialize::string_i64(val, write, end);
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
		void value(const std::string& val, std::vector<uint8_t>& buffer) {
			return serialize::string(val, buffer);
		}
		void value(const std::basic_string<uint8_t>& val, std::vector<uint8_t>& buffer) {
			return serialize::string_u8(val, buffer);
		}
		void value(const std::basic_string<uint16_t>& val, std::vector<uint8_t>& buffer) {
			return serialize::string_u16(val, buffer);
		}
		void value(const std::basic_string<uint32_t>& val, std::vector<uint8_t>& buffer) {
			return serialize::string_u32(val, buffer);
		}
		void value(const std::basic_string<uint64_t>& val, std::vector<uint8_t>& buffer) {
			return serialize::string_u64(val, buffer);
		}
		void value(const std::basic_string<int8_t>& val, std::vector<uint8_t>& buffer) {
			return serialize::string_i8(val, buffer);
		}
		void value(const std::basic_string<int16_t>& val, std::vector<uint8_t>& buffer) {
			return serialize::string_i16(val, buffer);
		}
		void value(const std::basic_string<int32_t>& val, std::vector<uint8_t>& buffer) {
			return serialize::string_i32(val, buffer);
		}
		void value(const std::basic_string<int64_t>& val, std::vector<uint8_t>& buffer) {
			return serialize::string_i64(val, buffer);
		}
	}
}
