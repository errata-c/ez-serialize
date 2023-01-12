#include <catch2/catch_all.hpp>

#include <type_traits>

#include <ez/serialize/core.hpp>

#include <ez/intern/Convert.hpp>
#include <ez/intern/TypeSupport.hpp>

using namespace ez::intern;

template<typename T>
auto force_unsigned(T val) {
	using utype = std::make_unsigned_t<T>;
	
	utype cvt = 0;
	std::memcpy(&cvt, &val, sizeof(val));
	return cvt;
}
template<typename T>
auto force_signed(T val) {
	using utype = std::make_signed_t<T>;

	utype cvt = 0;
	std::memcpy(&cvt, &val, sizeof(val));
	return cvt;
}

TEST_CASE("conversion") {
	SECTION("signed extension") {
		int8_t v0 = 0xF0;
		int16_t v1 = v0;
		int32_t v2 = v0;
		int64_t v3 = v0;

		REQUIRE(force_unsigned(v1) == uint64_t(0xFFF0));
		REQUIRE(force_unsigned(v2) == uint64_t(0xFFFF'FFF0));
		REQUIRE(force_unsigned(v3) == uint64_t(0xFFFF'FFFF'FFFF'FFF0));

		int16_t v4 = 0xF000;
		int32_t v5 = 0xF000'0000;
		int64_t v6 = 0xF000'0000'0000'0000;

		REQUIRE(force_unsigned(v4 >> 8) == uint64_t(0xFFFF'FFF0)); // Automatically converted to int, 32 bits.
		REQUIRE(force_unsigned(v5 >> 24) == uint64_t(0xFFFF'FFF0));
		REQUIRE(force_unsigned(v6 >> 56) == uint64_t(0xFFFF'FFFF'FFFF'FFF0));
	}
	SECTION("unsigned extension") {
		uint8_t v0 = 0xF0u;
		uint16_t v1 = v0;
		uint32_t v2 = v0;
		uint64_t v3 = v0;

		REQUIRE(force_unsigned(v1) == uint64_t(0x00F0));
		REQUIRE(force_unsigned(v2) == uint64_t(0x0000'00F0));
		REQUIRE(force_unsigned(v3) == uint64_t(0x0000'0000'0000'00F0));
	}
	SECTION("signed conversion") {
		int8_t v0 = 0xF0;
		int16_t v1 = 0xF0;
		int32_t v2 = 0xF0;
		int64_t v3 = 0xF0;

		REQUIRE(uint8_t(v0) == 0xF0u);
		REQUIRE(uint16_t(v1) == 0xF0u);
		REQUIRE(uint32_t(v2) == 0xF0u);
		REQUIRE(uint64_t(v3) == 0xF0u);

		REQUIRE(uint16_t(uint8_t(v0)) == 0xF0u);
		REQUIRE(uint32_t(uint8_t(v0)) == 0xF0u);
		REQUIRE(uint64_t(uint8_t(v0)) == 0xF0u);
	}

	auto char_cast = [](char val) -> uint32_t {
		auto tmp = force_unsigned(val);
		return uint32_t(tmp);
	};

	SECTION("char conversion") {
		uint64_t v0(0x1234'5678'9ABC'DEFFu);

		uint32_t expected[] = { 0xFFu, 0xDEu, 0xBCu, 0x9Au, 0x78u, 0x56u, 0x34u, 0x12u };

		for (int i = 0; i < 8; ++i) {
			CAPTURE(i);
			REQUIRE(char_cast(v0 >> (i * 8)) == expected[i]);
		}

		for (int i = 0; i < 8; ++i) {
			CAPTURE(i);
			REQUIRE(char_cast(v0) == expected[i]);
			if (i != 7) {
				v0 = v0 >> 8;
			}
		}
	}

	SECTION("char regeneration") {
		uint64_t v0(0x1234'5678'9ABC'DEFFu);

		char buffer[8];
		std::memset(buffer, 0, 8);
		uint64_t regen = 0;

		char *write = buffer;
		for (int i = 0; i < 8; ++i) {
			CAPTURE(i);
			*write++ = v0;
			if (i != 7) {
				v0 = v0 >> 8;
			}
		}

		REQUIRE((write-8) == buffer);

		uint64_t expected[] = { 
			uint64_t(0xFFu) << 56,
			uint64_t(0xDEFFu) << 48,
			uint64_t(0xBC'DEFFu) << 40,
			uint64_t(0x9ABC'DEFFu) << 32,
			uint64_t(0x78'9ABC'DEFFu) << 24,
			uint64_t(0x5678'9ABC'DEFFu) << 16,
			uint64_t(0x34'5678'9ABC'DEFFu) << 8,
			uint64_t(0x1234'5678'9ABC'DEFFu)
		};

		const char* read = buffer;
		for (int i = 0; i < 8; ++i) {
			if (i == 0) {
				regen = (uint64_t(uint8_t(*read++)) << 56);
			}
			else {
				regen = (regen >> 8) | (uint64_t(uint8_t(*read++)) << 56);
			}

			CAPTURE(i);
			REQUIRE(regen == expected[i]);
		}
	}
}

TEST_CASE("basic") {
	std::string buffer;
	buffer.resize(32, 0);

	char * data = buffer.data();
	const char* const end = data + buffer.size();

	SECTION("uint8_t") {
		uint8_t val = 0x12;
		char * write_end = ez::serialize::u8(val, data, end);
		REQUIRE((write_end - data) == sizeof(val));

		uint8_t regen;
		const char * read_end = ez::deserialize::u8(data, end, regen);
		REQUIRE((read_end - data) == sizeof(val));

		REQUIRE(val == regen);
	}
	SECTION("uint16_t") {
		uint16_t val = 0x1234;
		char* write_end = ez::serialize::u16(val, data, end);
		REQUIRE((write_end - data) == sizeof(val));

		uint16_t regen;
		const char* read_end = ez::deserialize::u16(data, end, regen);
		REQUIRE((read_end - data) == sizeof(val));

		REQUIRE(val == regen);
	}
	SECTION("uint32_t") {
		uint32_t val = 0x1111'2222;
		char* write_end = ez::serialize::u32(val, data, end);
		REQUIRE((write_end - data) == sizeof(val));

		uint32_t regen;
		const char* read_end = ez::deserialize::u32(data, end, regen);
		REQUIRE((read_end - data) == sizeof(val));

		REQUIRE(val == regen);
	}
	SECTION("uint64_t") {
		uint64_t val = 0x1111'2222'3333'4444;
		char* write_end = ez::serialize::u64(val, data, end);
		REQUIRE((write_end - data) == sizeof(val));

		uint64_t regen;
		const char* read_end = ez::deserialize::u64(data, end, regen);
		REQUIRE((read_end - data) == sizeof(val));

		REQUIRE(val == regen);
	}

	SECTION("int8_t") {
		int8_t val = 0x12;
		char* write_end = ez::serialize::i8(val, data, end);
		REQUIRE((write_end - data) == sizeof(val));

		int8_t regen;
		const char* read_end = ez::deserialize::i8(data, end, regen);
		REQUIRE((read_end - data) == sizeof(val));

		REQUIRE(val == regen);
	}
	SECTION("int16_t") {
		int16_t val = 0x1234;
		char* write_end = ez::serialize::i16(val, data, end);
		REQUIRE((write_end - data) == sizeof(val));

		int16_t regen;
		const char* read_end = ez::deserialize::i16(data, end, regen);
		REQUIRE((read_end - data) == sizeof(val));

		REQUIRE(val == regen);
	}
	SECTION("int32_t") {
		int32_t val = 0x1111'2222;
		char* write_end = ez::serialize::i32(val, data, end);
		REQUIRE((write_end - data) == sizeof(val));

		int32_t regen;
		const char* read_end = ez::deserialize::i32(data, end, regen);
		REQUIRE((read_end - data) == sizeof(val));

		REQUIRE(val == regen);
	}
	SECTION("int64_t") {
		int64_t val = 0x1111'2222'3333'4444;
		char* write_end = ez::serialize::i64(val, data, end);
		REQUIRE((write_end - data) == sizeof(val));

		int64_t regen;
		const char* read_end = ez::deserialize::i64(data, end, regen);
		REQUIRE((read_end - data) == sizeof(val));

		REQUIRE(val == regen);
	}

	SECTION("float") {
		float val = 1.234567890123456789;

		char* write_end = ez::serialize::f32(val, data, end);
		REQUIRE((write_end - data) == sizeof(val));


		float regen;
		const char* read_end = ez::deserialize::f32(data, end, regen);
		REQUIRE((read_end - data) == sizeof(val));

		REQUIRE(val == regen);
	}
	SECTION("double") {
		double val = 1.234567890123456789;

		char* write_end = ez::serialize::f64(val, data, end);
		REQUIRE((write_end - data) == sizeof(val));

		double regen;
		const char* read_end = ez::deserialize::f64(data, end, regen);
		REQUIRE((read_end - data) == sizeof(val));

		REQUIRE(val == regen);
	}
}
