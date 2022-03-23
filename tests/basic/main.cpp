#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <type_traits>

#include <ez/serialize.hpp>
#include <ez/deserialize.hpp>

#include <ez/intern/Convert.hpp>



TEST_CASE("conversion") {
	// Simple conversion test to make sure the compiler is conformant
	char val = -86;
	uint32_t res = val;

	uint32_t c = 86;
	c = ~c;
	c += 1;

	// Sign extention should take place
	REQUIRE(res == c);


	res = uint8_t(val);
	c = c & 0xFF;
	REQUIRE(res == c);
}

TEST_CASE("basic") {
	std::string buffer;
	buffer.resize(32, 0);

	char * data = buffer.data();
	const char* const end = data + buffer.size();

	SECTION("uint8_t") {
		uint8_t val = 0x12;
		ez::serialize::u8(val, data, end);
		uint8_t regen;
		ez::deserialize::u8(data, end, regen);

		REQUIRE(val == regen);
	}
	SECTION("uint16_t") {
		uint16_t val = 0x1234;
		ez::serialize::u16(val, data, end);
		uint16_t regen;
		ez::deserialize::u16(data, end, regen);

		REQUIRE(val == regen);
	}
	SECTION("uint32_t") {
		uint32_t val = 0x1111'2222;
		ez::serialize::u32(val, data, end);
		uint32_t regen;
		ez::deserialize::u32(data, end, regen);

		REQUIRE(val == regen);
	}
	SECTION("uint64_t") {
		uint64_t val = 0x1111'2222'3333'4444;
		ez::serialize::u64(val, data, end);
		uint64_t regen;
		ez::deserialize::u64(data, end, regen);

		REQUIRE(val == regen);
	}

	SECTION("int8_t") {
		int8_t val = 0x12;
		ez::serialize::i8(val, data, end);
		int8_t regen;
		ez::deserialize::i8(data, end, regen);

		REQUIRE(val == regen);
	}
	SECTION("int16_t") {
		int16_t val = 0x1234;
		ez::serialize::i16(val, data, end);
		int16_t regen;
		ez::deserialize::i16(data, end, regen);

		REQUIRE(val == regen);
	}
	SECTION("int32_t") {
		int32_t val = 0x1111'2222;
		ez::serialize::i32(val, data, end);
		int32_t regen;
		ez::deserialize::i32(data, end, regen);

		REQUIRE(val == regen);
	}
	SECTION("int64_t") {
		int64_t val = 0x1111'2222'3333'4444;
		ez::serialize::i64(val, data, end);
		int64_t regen;
		ez::deserialize::i64(data, end, regen);

		REQUIRE(val == regen);
	}

	SECTION("float") {
		float val = 1.234567890123456789;

		Converter32 convert;
		convert.floatVal = val;
		bool isLittleEndian = convert.data[0] == char(convert.uintVal & 0xFF);

		ez::serialize::f32(val, data, end);

		if (isLittleEndian) {
			for (int i = 0; i < 4; ++i) {
				REQUIRE(convert.data[i] == data[i]);
			}
		}
		else {
			for (int i = 0; i < 4; ++i) {
				REQUIRE(convert.data[3-i] == data[i]);
			}
		}

		float regen;
		ez::deserialize::f32(data, end, regen);

		REQUIRE(val == regen);
	}
	SECTION("double") {
		double val = 1.234567890123456789;
		Converter64 convert;
		convert.floatVal = val;
		bool isLittleEndian = convert.data[0] == char(convert.uintVal & 0xFF);

		ez::serialize::f64(val, data, end);
		if (isLittleEndian) {
			for (int i = 0; i < 8; ++i) {
				REQUIRE(convert.data[i] == data[i]);
			}
		}
		else {
			for (int i = 0; i < 8; ++i) {
				REQUIRE(convert.data[3 - i] == data[i]);
			}
		}

		double regen;
		ez::deserialize::f64(data, end, regen);

		REQUIRE(val == regen);
	}

	SECTION("string") {
		std::string val = "test";
		ez::serialize::string(val, data, end);
		std::string regen;
		ez::deserialize::string(data, end, regen);

		REQUIRE(val == regen);
	}
}