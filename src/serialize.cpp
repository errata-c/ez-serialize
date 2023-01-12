#include <ez/serialize.hpp>
#include <ez/intern/Convert.hpp>

#include <cassert>

namespace ez::serialize {
	using namespace ez::intern;

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
