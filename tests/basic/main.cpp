#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <ez/serialize.hpp>
#include <ez/deserialize.hpp>

TEST_CASE("basic") {
	std::vector<uint8_t> buffer;
	buffer.resize(32, 0);

	uint8_t * data = buffer.data();
	const uint8_t* const end = data + buffer.size();

	SECTION("uint8_t") {
		uint8_t val = 0x55;
		ez::serialize::u8(val, data, end);
		uint8_t regen;
		ez::deserialize::u8(data, end, regen);

		REQUIRE(val == regen);
	}
	SECTION("uint16_t") {
		uint16_t val = 0x5555;
		ez::serialize::u16(val, data, end);
		uint16_t regen;
		ez::deserialize::u16(data, end, regen);

		REQUIRE(val == regen);
	}
	SECTION("uint32_t") {
		uint32_t val = 0x5555'5555;
		ez::serialize::u32(val, data, end);
		uint32_t regen;
		ez::deserialize::u32(data, end, regen);

		REQUIRE(val == regen);
	}
	SECTION("uint64_t") {
		uint64_t val = 0x5555'5555'5555'5555;
		ez::serialize::u64(val, data, end);
		uint64_t regen;
		ez::deserialize::u64(data, end, regen);

		REQUIRE(val == regen);
	}

	SECTION("int8_t") {
		int8_t val = 0x55;
		ez::serialize::i8(val, data, end);
		int8_t regen;
		ez::deserialize::i8(data, end, regen);

		REQUIRE(val == regen);
	}
	SECTION("int16_t") {
		int16_t val = 0x5555;
		ez::serialize::i16(val, data, end);
		int16_t regen;
		ez::deserialize::i16(data, end, regen);

		REQUIRE(val == regen);
	}
	SECTION("int32_t") {
		int32_t val = 0x5555'5555;
		ez::serialize::i32(val, data, end);
		int32_t regen;
		ez::deserialize::i32(data, end, regen);

		REQUIRE(val == regen);
	}
	SECTION("int64_t") {
		int64_t val = 0x5555'5555'5555'5555;
		ez::serialize::i64(val, data, end);
		int64_t regen;
		ez::deserialize::i64(data, end, regen);

		REQUIRE(val == regen);
	}

	SECTION("float") {
		float val = 1.234567890123456789;
		ez::serialize::f32(val, data, end);
		float regen;
		ez::deserialize::f32(data, end, regen);

		REQUIRE(val == regen);
	}
	SECTION("double") {
		double val = 1.234567890123456789;
		ez::serialize::f64(val, data, end);
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