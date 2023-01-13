#include <catch2/catch_all.hpp>

#include <type_traits>

#include <ez/serialize/ranges.hpp>

#include <ez/intern/Convert.hpp>
#include <ez/intern/TypeSupport.hpp>

#include <iostream>
#include <vector>
#include <deque>

TEST_CASE("char ranges") {
	std::string source = "test";
	std::string dest;
	std::string regen;

	SECTION("pointer to pointer") {
		dest.resize(source.size(), 0);
		regen.resize(source.size(), 0);

		const char* read = source.c_str();
		read = ez::serialize::range(read, read + source.size(), dest.data(), dest.data() + dest.size());

		REQUIRE(read == (dest.data() + dest.size()));
		REQUIRE(source == dest);

		read = dest.data();
		read = ez::deserialize::range(read, read + dest.size(), regen.data(), regen.data() + regen.size());

		REQUIRE(read == (dest.c_str() + dest.size()));
		REQUIRE(source == regen);
	}
	SECTION("pointer to string") {
		regen.resize(source.size(), 0);
		
		const char* read = source.c_str();
		ez::serialize::range(read, read + source.size(), dest);

		REQUIRE(source == dest);

		read = dest.data();
		read = ez::deserialize::range(read, read + dest.size(), regen.data(), regen.data() + regen.size());

		REQUIRE(read == (dest.data() + dest.size()));
		REQUIRE(source == regen);
	}

	SECTION("pointer to pointer range_n") {
		dest.resize(source.size(), 0);
		regen.resize(source.size(), 0);

		const char* read = source.c_str();
		read = ez::serialize::range_n(read, source.size(), dest.data(), dest.data() + dest.size());

		REQUIRE(read == (dest.data() + dest.size()));
		REQUIRE(source == dest);

		read = dest.data();
		read = ez::deserialize::range_n(read, read + dest.size(), regen.data(), regen.size());

		REQUIRE(read == (dest.c_str() + dest.size()));
		REQUIRE(source == regen);
	}
	SECTION("pointer to string range_n") {
		regen.resize(source.size(), 0);

		const char* read = source.c_str();
		ez::serialize::range_n(read, source.size(), dest);

		REQUIRE(source == dest);

		read = dest.data();
		read = ez::deserialize::range_n(read, read + dest.size(), regen.data(), regen.size());

		REQUIRE(read == (dest.data() + dest.size()));
		REQUIRE(source == regen);
	}
}

TEST_CASE("vector ranges") {
	SECTION("int") {
		std::vector<int> source{0, 1, 2, 3, 4, 5};
		std::string d0, d1;

		ez::serialize::range(source.begin(), source.end(), d0);
		d1.resize(d0.size(), 0);

		char * write = ez::serialize::range(source.begin(), source.end(), d1.data(), d1.data() + d1.size());
		REQUIRE(d0 == d1);
		REQUIRE(write == (d1.data() + d1.size()));

		std::vector<int> regen;
		regen.resize(source.size(), 0);

		const char * read = ez::deserialize::range(d0.data(), d0.data() + d0.size(), regen.begin(), regen.end());
		
		for (size_t i = 0; i < source.size(); ++i) {
			CAPTURE(i);
			REQUIRE(source[i] == regen[i]);
		}
		REQUIRE(read == (d0.data() + d0.size()));
	}
	SECTION("float") {
		std::vector<float> source{ 0, 1, 2, 3, 4, 5 };
		std::string d0, d1;

		ez::serialize::range(source.begin(), source.end(), d0);
		d1.resize(d0.size(), 0);

		char* write = ez::serialize::range(source.begin(), source.end(), d1.data(), d1.data() + d1.size());
		REQUIRE(d0 == d1);
		REQUIRE(write == (d1.data() + d1.size()));

		std::vector<float> regen;
		regen.resize(source.size(), 0);

		const char* read = ez::deserialize::range(d0.data(), d0.data() + d0.size(), regen.begin(), regen.end());

		for (size_t i = 0; i < source.size(); ++i) {
			CAPTURE(i);
			REQUIRE(source[i] == regen[i]);
		}
		REQUIRE(read == (d0.data() + d0.size()));
	}
}

TEST_CASE("range_n") {
	SECTION("back_inserter") {
		std::vector<float> source{ 0, 1, 2, 3, 4, 5 };
		std::vector<float> regen;
		std::string buffer;

		ez::serialize::range(source.begin(), source.end(), buffer);

		ez::deserialize::range_n(buffer.data(), buffer.data() + buffer.size(), std::back_inserter(regen), source.size());

		REQUIRE(regen.size() == source.size());

		for (size_t i = 0; i < source.size(); ++i) {
			CAPTURE(i);
			REQUIRE(source[i] == regen[i]);
		}
	}
	SECTION("back_inserter with elements already present") {
		std::vector<float> source{ 0, 1, 2, 3, 4, 5 };
		std::vector<float> regen{ 6, 7 };
		std::string buffer;

		ez::serialize::range(source.begin(), source.end(), buffer);

		size_t prior = regen.size();
		const char * write = ez::deserialize::range_n(buffer.data(), buffer.data() + buffer.size(), std::back_inserter(regen), source.size());

		REQUIRE(write == (buffer.data() + buffer.size()));
		REQUIRE(regen.size() == (source.size() + prior));

		for (size_t i = 0; i < source.size(); ++i) {
			CAPTURE(i);
			REQUIRE(source[i] == regen[i + prior]);
		}
	}
	SECTION("front_inserter") {
		std::deque<float> source{ 0, 1, 2, 3, 4, 5 };
		std::deque<float> regen{ 6, 7 };
		std::string buffer;

		ez::serialize::range(source.begin(), source.end(), buffer);

		size_t prior = regen.size();
		const char* write = ez::deserialize::range_n(buffer.data(), buffer.data() + buffer.size(), std::front_inserter(regen), source.size());

		REQUIRE(write == (buffer.data() + buffer.size()));
		REQUIRE(regen.size() == (source.size() + prior));

		for (ptrdiff_t i = 0; i < source.size(); ++i) {
			CAPTURE(i);
			REQUIRE(source[i] == regen[source.size() - (i + 1)]);
		}
	}

	SECTION("serialize range_n") {
		std::vector<float> source{ 0, 1, 2, 3, 4, 5 };
		std::string d0, d1;

		ez::serialize::range_n(source.begin(), source.size(), d0);
		d1.resize(d0.size(), 0);

		char* write = ez::serialize::range_n(source.begin(), source.size(), d1.data(), d1.data() + d1.size());
		REQUIRE(d0 == d1);
		REQUIRE(write == (d1.data() + d1.size()));

		std::vector<float> regen;
		regen.resize(source.size(), 0);

		const char* read = ez::deserialize::range(d0.data(), d0.data() + d0.size(), regen.begin(), regen.end());

		for (size_t i = 0; i < source.size(); ++i) {
			CAPTURE(i);
			REQUIRE(source[i] == regen[i]);
		}
		REQUIRE(read == (d0.data() + d0.size()));
	}
}