#include <catch2/catch_all.hpp>

#include <type_traits>

#include <ez/serialize.hpp>
#include <ez/deserialize.hpp>

#include <ez/intern/Convert.hpp>

using namespace ez::intern;

TEST_CASE("Enumerator int32_t") {
	enum class Test: int32_t {
		A,
		B,
		C,
		D
	};

	std::string buffer;
	buffer.resize(32, 0);

	char* data = buffer.data();
	const char* const end = data + buffer.size();

	
	Test val = GENERATE(Test::A, Test::B, Test::C, Test::D);
	char * next = ez::serialize::enumerator(val, data, end);

	REQUIRE((next - data) == sizeof(Test));
	REQUIRE((next - data) == sizeof(int32_t));

	Test regen;
	ez::deserialize::enumerator(data, end, regen);

	REQUIRE(val == regen);
}

TEST_CASE("Enumerator int8_t") {
	enum class Test : int8_t {
		A,
		B,
		C,
		D
	};

	std::string buffer;
	buffer.resize(32, 0);

	char* data = buffer.data();
	const char* const end = data + buffer.size();

	Test val = GENERATE(Test::A, Test::B, Test::C, Test::D);
	char* next = ez::serialize::enumerator(val, data, end);

	REQUIRE((next - data) == sizeof(Test));
	REQUIRE((next - data) == sizeof(int8_t));

	Test regen;
	ez::deserialize::enumerator(data, end, regen);

	REQUIRE(val == regen);
}


TEST_CASE("Enumerator uint32_t") {
	enum class Test : uint32_t {
		A,
		B,
		C,
		D
	};

	std::string buffer;
	buffer.resize(32, 0);

	char* data = buffer.data();
	const char* const end = data + buffer.size();

	Test val = GENERATE(Test::A, Test::B, Test::C, Test::D);
	char* next = ez::serialize::enumerator(val, data, end);

	REQUIRE((next - data) == sizeof(Test));
	REQUIRE((next - data) == sizeof(uint32_t));

	Test regen;
	ez::deserialize::enumerator(data, end, regen);

	REQUIRE(val == regen);
}

TEST_CASE("Enumerator uint8_t") {
	enum class Test : uint8_t {
		A,
		B,
		C,
		D
	};

	std::string buffer;
	buffer.resize(32, 0);

	char* data = buffer.data();
	const char* const end = data + buffer.size();

	Test val = GENERATE(Test::A, Test::B, Test::C, Test::D);
	char* next = ez::serialize::enumerator(val, data, end);

	REQUIRE((next - data) == sizeof(Test));
	REQUIRE((next - data) == sizeof(uint8_t));

	Test regen;
	ez::deserialize::enumerator(data, end, regen);

	REQUIRE(val == regen);
}