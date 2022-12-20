#include <catch2/catch_all.hpp>

#include <type_traits>

#include <ez/serialize.hpp>
#include <ez/deserialize.hpp>

#include <ez/intern/Convert.hpp>

using namespace ez::intern;

TEST_CASE("conversion") {
	// Simple conversion test to make sure the compiler is conformant
	char val = -86;
	uint32_t res = val;

	uint32_t c = 86;
	c = ~c;
	c += 1;

	// Sign extension should take place
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

		Converter32 convert;
		convert.floatVal = val;
		bool isLittleEndian = convert.data[0] == char(convert.uintVal & 0xFF);

		char* write_end = ez::serialize::f32(val, data, end);
		REQUIRE((write_end - data) == sizeof(val));

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
		const char* read_end = ez::deserialize::f32(data, end, regen);
		REQUIRE((read_end - data) == sizeof(val));

		REQUIRE(val == regen);
	}
	SECTION("double") {
		double val = 1.234567890123456789;
		Converter64 convert;
		convert.floatVal = val;
		bool isLittleEndian = convert.data[0] == char(convert.uintVal & 0xFF);

		char* write_end = ez::serialize::f64(val, data, end);
		REQUIRE((write_end - data) == sizeof(val));

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
		const char* read_end = ez::deserialize::f64(data, end, regen);
		REQUIRE((read_end - data) == sizeof(val));

		REQUIRE(val == regen);
	}
}
