#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <ez/serialize.hpp>
#include <ez/deserialize.hpp>

TEST_CASE("basic") {
	
	int v0 = 0xF0F0'F0F0;

	uint8_t mem[4];

	ez::serialize::i32(v0, mem, mem + 4);
}