#pragma once
#include "TypeSupport.hpp"

#include <cinttypes>
#include <cstring>
#include <string>

namespace ez::intern {
	template<size_t N>
	struct sized_uint {
		using type = uint8_t;
	};

	template<>
	struct sized_uint<1> {
		using type = uint8_t;
	};

	template<>
	struct sized_uint<2> {
		using type = uint16_t;
	};

	template<>
	struct sized_uint<4> {
		using type = uint32_t;
	};

	template<>
	struct sized_uint<8> {
		using type = uint64_t;
	};

	template<size_t N>
	using sized_uint_t = typename sized_uint<N>::type;


	template<typename T>
	const char* read_convert(const char* read, T& ret) {
		using utype = sized_uint_t<sizeof(T)>;
		static constexpr utype offset = 8 * (sizeof(T) - 1);

		utype val;
		if constexpr (sizeof(T) == 1) {
			val = utype(uint8_t(*read++));
		}
		else {
			val = (utype(uint8_t(*read++)) << offset);
			for (unsigned i = 1; i < sizeof(T); ++i) {
				val = (val >> 8) | (utype(uint8_t(*read++)) << offset);
			}
		}
		
		// Safe type punning
		std::memcpy(&ret, &val, sizeof(T));

		return read;
	}

	template<typename T>
	char* write_convert(char* write, const T& value) {
		using utype = sized_uint_t<sizeof(T)>;

		utype val;

		// Safe type punning
		std::memcpy(&val, &value, sizeof(T));

		*write++ = val;
		if constexpr (sizeof(T) > 1) {
			for (unsigned i = 1; i < sizeof(T); ++i) {
				val = val >> 8;
				*write++ = val;
			}
		}

		return write;
	}

	template<typename T>
	void write_convert(std::string& write, const T & value) {
		using utype = sized_uint_t<sizeof(T)>;

		utype val;

		// Safe type punning
		std::memcpy(&val, &value, sizeof(T));

		write.push_back(val);
		if constexpr (sizeof(T) > 1) {
			for (unsigned i = 1; i < sizeof(T); ++i) {
				val = val >> 8;
				write.push_back(val);
			}
		}
	}
}