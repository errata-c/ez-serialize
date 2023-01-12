#include <catch2/catch_all.hpp>

#include <type_traits>

#include <ez/serialize/ranges.hpp>

#include <ez/intern/Convert.hpp>
#include <ez/intern/TypeSupport.hpp>

#include <iostream>

TEST_CASE("simple char ranges") {
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
}

TEST_CASE("vector iterators") {
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