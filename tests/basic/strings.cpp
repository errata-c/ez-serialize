#include <catch2/catch_all.hpp>

#include <type_traits>

#include <ez/serialize/ranges.hpp>
#include <ez/serialize/strings.hpp>

#include <iostream>
#include <vector>
#include <deque>
#include <string>

TEST_CASE("basic strings") {
	std::string val = "Hello, world!";
	std::string d0, d1;
	std::string regen;

	ez::serialize::string(val, d0);

	d1.resize(d0.size());
	char * write = ez::serialize::string(val, d1.data(), d1.data() + d1.size());

	REQUIRE(write == (d1.data() + d1.size()));
	REQUIRE(d0 == d1);
	
	ez::deserialize::string(d0.data(), d0.data() + d0.size(), regen);

	REQUIRE(regen == val);
}