#include <catch2/catch_all.hpp>

#include <type_traits>
#include <limits>

#include <ez/serialize.hpp>
#include <ez/deserialize.hpp>

#include <ez/intern/Convert.hpp>

using namespace ez::intern;
using namespace Catch::Generators;

TEST_CASE("strings") {
	std::string buffer;
	buffer.resize(16 * 8, 0);
	
	char* data = buffer.data();
	const char* const end = data + buffer.size();

	SECTION("default string") {
		using type = char;
		using string = std::basic_string<type>;

		static constexpr int64_t
			minv = std::numeric_limits<type>::min(),
			maxv = std::numeric_limits<type>::max();

		auto init = GENERATE(chunk(16, take(16 * 4, random(minv, maxv))));

		string val(init.begin(), init.end());
		char * write_end = ez::serialize::string(val, data, end);

		REQUIRE(((write_end - data) - 8) == val.size() * sizeof(type));

		string regen;
		const char * read_end = ez::deserialize::string(data, end, regen);

		REQUIRE(((read_end - data) - 8) == val.size() * sizeof(type));

		REQUIRE(val == regen);
	}

	SECTION("basic_string int8_t") {
		using type = int8_t;
		using string = std::basic_string<type>;

		static constexpr int64_t
			minv = std::numeric_limits<type>::min(),
			maxv = std::numeric_limits<type>::max();

		auto init = GENERATE(chunk(16, take(16 * 4, random(minv, maxv))));

		string val(init.begin(), init.end());
		char* write_end = ez::serialize::string_i8(val, data, end);

		REQUIRE(((write_end - data) - 8) == val.size() * sizeof(type));

		string regen;
		const char* read_end = ez::deserialize::string_i8(data, end, regen);

		REQUIRE(((read_end - data) - 8) == val.size() * sizeof(type));

		REQUIRE(val == regen);
	}
	
	SECTION("basic_string int32_t") {
		using type = int32_t;
		using string = std::basic_string<type>;

		static constexpr int64_t
			minv = std::numeric_limits<type>::min(),
			maxv = std::numeric_limits<type>::max();

		auto init = GENERATE(chunk(16, take(16 * 4, random(minv, maxv))));

		string val(init.begin(), init.end());
		char* write_end = ez::serialize::string_i32(val, data, end);

		REQUIRE(((write_end - data) - 8) == val.size() * sizeof(type));

		string regen;
		const char* read_end = ez::deserialize::string_i32(data, end, regen);

		REQUIRE(((read_end - data) - 8) == val.size() * sizeof(type));

		REQUIRE(val == regen);
	}

	SECTION("basic_string uint8_t") {
		using type = uint8_t;
		using string = std::basic_string<type>;

		static constexpr int64_t
			minv = std::numeric_limits<type>::min(),
			maxv = std::numeric_limits<type>::max();

		auto init = GENERATE(chunk(16, take(16 * 4, random(minv, maxv))));

		string val(init.begin(), init.end());
		char* write_end = ez::serialize::string_u8(val, data, end);

		REQUIRE(((write_end - data) - 8) == val.size() * sizeof(type));

		string regen;
		const char* read_end = ez::deserialize::string_u8(data, end, regen);

		REQUIRE(((read_end - data) - 8) == val.size() * sizeof(type));

		REQUIRE(val == regen);
	}

	SECTION("basic_string uint32_t") {
		using type = uint32_t;
		using string = std::basic_string<type>;

		static constexpr int64_t
			minv = std::numeric_limits<type>::min(),
			maxv = std::numeric_limits<type>::max();

		auto init = GENERATE(chunk(16, take(16 * 4, random(minv, maxv))));

		string val(init.begin(), init.end());
		char* write_end = ez::serialize::string_u32(val, data, end);

		REQUIRE(((write_end - data) - 8) == val.size() * sizeof(type));

		string regen;
		const char* read_end = ez::deserialize::string_u32(data, end, regen);

		REQUIRE(((read_end - data) - 8) == val.size() * sizeof(type));

		REQUIRE(val == regen);
	}
}