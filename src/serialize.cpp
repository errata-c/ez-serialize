#include <ez/serialize.hpp>
#include <ez/intern/Convert.hpp>

#include <cassert>

// Benchmarks show that just writing directly is much faster.
// Small boost to performance when using assertions instead of exceptions as well.
// (Obviously just for the release builds)

// Going to have to check the specs to see if this is a valid implementation, don't want any undefined
// behaviour.

namespace ez::serialize {
	using namespace ez::intern;

	char* i8(int8_t val, char* write, char const* const end) {
		assert((end - write) >= sizeof(val));

		return writeConvert(write, val);
	}
	char* i16(int16_t val, char* write, char const* const end) {
		assert((end - write) >= sizeof(val));

		return writeConvert(write, val);
	}
	char* i32(int32_t val, char* write, char const* const end) {
		assert((end - write) >= sizeof(val));

		return writeConvert(write, val);
	}
	char* i64(int64_t val, char* write, char const* const end) {
		assert((end - write) >= sizeof(val));

		return writeConvert(write, val);
	}
	char* u8(uint8_t val, char* write, char const* const end) {
		assert((end - write) >= sizeof(val));

		return writeConvert(write, val);
	}
	char* u16(uint16_t val, char* write, char const* const end) {
		assert((end - write) >= sizeof(val));

		return writeConvert(write, val);
	}
	char* u32(uint32_t val, char* write, char const* const end) {
		assert((end - write) >= sizeof(val));

		return writeConvert(write, val);
	}
	char* u64(uint64_t val, char* write, char const* const end) {
		assert((end - write) >= sizeof(val));

		return writeConvert(write, val);
	}
	char* f32(float val, char* write, char const* const end) {
		assert((end - write) >= sizeof(val));

		Converter32 convert;
		convert.floatVal = val;
		writeConvert(write, convert.uintVal);

		return write + sizeof(convert);
	}
	char* f64(double val, char* write, char const* const end) {
		assert((end - write) >= sizeof(val));

		Converter64 convert;
		convert.floatVal = val;
		writeConvert(write, convert.uintVal);

		return write + sizeof(convert);
	}
	char* ptr(const void* val, char* write, char const* const end) {
		assert((end - write) >= sizeof(val));

		ConverterPtr convert;
		convert.cptr = val;
		writeConvert(write, convert.uintVal);

		return write + sizeof(convert);
	}

	char* string(const std::string& val, char* write, char const* const end) {
		assert((end - write) >= val.size());

		uint64_t length = val.size();
		write = u64(length, write, end);

		for (char elem : val) {
			*write++ = elem;
		}

		return write;
	}
	char* string_u8(const std::basic_string<uint8_t>& val, char* write, char const* const end) {
		uint64_t bytes = val.size();

		assert((end - write) >= bytes);
			
		write = u64(bytes, write, end);

		for (char elem : val) {
			write = u8(elem, write, end);
		}

		return write;
	}
	char* string_u16(const std::basic_string<uint16_t>& val, char* write, char const* const end) {
		uint64_t bytes = val.size() * 2;

		assert((end - write) >= val.size());

		write = u64(bytes, write, end);

		for (uint16_t elem : val) {
			write = u16(elem, write, end);
		}

		return write;
	}
	char* string_u32(const std::basic_string<uint32_t>& val, char* write, char const* const end) {
		uint64_t bytes = val.size() * 4;

		assert((end - write) >= bytes);
			
		write = u64(bytes, write, end);

		for (uint32_t elem : val) {
			write = u32(elem, write, end);
		}

		return write;
	}
	char* string_u64(const std::basic_string<uint64_t>& val, char* write, char const* const end) {
		uint64_t bytes = val.size() * 8;

		assert((end - write) >= val.size());

		write = u64(bytes, write, end);

		for (uint64_t elem : val) {
			write = u64(elem, write, end);
		}

		return write;
	}
	char* string_i8(const std::basic_string<int8_t>& val, char* write, char const* const end) {
		uint64_t bytes = val.size();

		assert((end - write) >= val.size());

		write = u64(bytes, write, end);

		for (int8_t elem : val) {
			write = i8(elem, write, end);
		}

		return write;
	}
	char* string_i16(const std::basic_string<int16_t>& val, char* write, char const* const end) {
		uint64_t bytes = val.size() * 2;

		assert((end - write) >= val.size());

		write = u64(bytes, write, end);

		for (int16_t elem : val) {
			write = i16(elem, write, end);
		}

		return write;
	}
	char* string_i32(const std::basic_string<int32_t>& val, char* write, char const* const end) {
		uint64_t bytes = val.size() * 4;

		assert((end - write) >= val.size());

		write = u64(bytes, write, end);

		for (int32_t elem : val) {
			write = i32(elem, write, end);
		}

		return write;
	}
	char* string_i64(const std::basic_string<int64_t>& val, char* write, char const* const end) {
		uint64_t bytes = val.size() * 8;

		assert((end - write) >= val.size());

		write = u64(bytes, write, end);

		for (int64_t elem : val) {
			write = i64(elem, write, end);
		}

		return write;
	}


	void i8(int8_t val, std::string& buffer) {
		buffer.push_back((char)val);
	}
	void i16(int16_t val, std::string& buffer) {
		buffer.push_back((val & 0xFF));
		buffer.push_back((val & 0xFF00) >> 8);
	}
	void i32(int32_t val, std::string& buffer) {
		buffer.push_back((val & 0xFF));
		buffer.push_back((val & 0xFF00) >> 8);
		buffer.push_back((val & 0xFF0000) >> 16);
		buffer.push_back((val & 0xFF000000) >> 24);
	}
	void i64(int64_t val, std::string& buffer) {
		buffer.push_back((val & 0xFF));
		buffer.push_back((val & 0xFF00) >> 8);
		buffer.push_back((val & 0xFF0000) >> 16);
		buffer.push_back((val & 0xFF000000) >> 24);

		buffer.push_back((val & 0xFF000000'00) >> 32);
		buffer.push_back((val & 0xFF000000'0000) >> 40);
		buffer.push_back((val & 0xFF000000'000000) >> 48);
		buffer.push_back((val & 0xFF000000'00000000) >> 56);
	}
	void u8(uint8_t val, std::string& buffer) {
		buffer.push_back(val);
	}
	void u16(uint16_t val, std::string& buffer) {
		buffer.push_back((val & 0xFF));
		buffer.push_back((val & 0xFF00) >> 8);
	}
	void u32(uint32_t val, std::string& buffer) {
		buffer.push_back((val & 0xFF));
		buffer.push_back((val & 0xFF00) >> 8);
		buffer.push_back((val & 0xFF0000) >> 16);
		buffer.push_back((val & 0xFF000000) >> 24);
	}
	void u64(uint64_t val, std::string& buffer) {
		buffer.push_back((val & 0xFF));
		buffer.push_back((val & 0xFF00) >> 8);
		buffer.push_back((val & 0xFF0000) >> 16);
		buffer.push_back((val & 0xFF000000) >> 24);

		buffer.push_back((val & 0xFF000000'00) >> 32);
		buffer.push_back((val & 0xFF000000'0000) >> 40);
		buffer.push_back((val & 0xFF000000'000000) >> 48);
		buffer.push_back((val & 0xFF000000'00000000) >> 56);
	}

	void f32(float val, std::string& buffer) {
		Converter32 convert;
		convert.floatVal = val;
		u32(convert.uintVal, buffer);
	}
	void f64(double val, std::string& buffer) {
		Converter64 convert;
		convert.floatVal = val;
		u64(convert.uintVal, buffer);
	}
	void ptr(const void* val, std::string& buffer) {
		ConverterPtr convert;
		convert.cptr = val;

		writeConvert(buffer, convert.uintVal);
	}

	void string(const std::string& val, std::string& buffer) {
		uint64_t length = val.size();
		u64(length, buffer);

		buffer.append(val);
	}
	void string_u8(const std::basic_string<uint8_t>& val, std::string& buffer) {
		uint64_t bytes = val.size();

		u64(bytes, buffer);

		for (uint8_t elem : val) {
			u8(elem, buffer);
		}
	}
	void string_u16(const std::basic_string<uint16_t>& val, std::string& buffer) {
		uint64_t bytes = val.size();

		u64(bytes, buffer);

		for (uint16_t elem : val) {
			u16(elem, buffer);
		}
	}
	void string_u32(const std::basic_string<uint32_t>& val, std::string& buffer) {
		uint64_t bytes = val.size();

		u64(bytes, buffer);

		for (uint32_t elem : val) {
			u32(elem, buffer);
		}
	}
	void string_u64(const std::basic_string<uint64_t>& val, std::string& buffer) {
		uint64_t bytes = val.size();

		u64(bytes, buffer);

		for (uint64_t elem : val) {
			u64(elem, buffer);
		}
	}
	void string_i8(const std::basic_string<int8_t>& val, std::string& buffer) {
		uint64_t bytes = val.size();

		u64(bytes, buffer);

		for (int8_t elem : val) {
			i8(elem, buffer);
		}
	}
	void string_i16(const std::basic_string<int16_t>& val, std::string& buffer) {
		uint64_t bytes = val.size();

		u64(bytes, buffer);

		for (int16_t elem : val) {
			i16(elem, buffer);
		}
	}
	void string_i32(const std::basic_string<int32_t>& val, std::string& buffer) {
		uint64_t bytes = val.size();

		u64(bytes, buffer);

		for (int32_t elem : val) {
			i32(elem, buffer);
		}
	}
	void string_i64(const std::basic_string<int64_t>& val, std::string& buffer) {
		uint64_t bytes = val.size();

		u64(bytes, buffer);

		for (int64_t elem : val) {
			i64(elem, buffer);
		}
	}
}
