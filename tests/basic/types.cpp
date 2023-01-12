#include <catch2/catch_all.hpp>

#include <type_traits>

#include <ez/serialize/core.hpp>

#include <ez/intern/Convert.hpp>
#include <ez/intern/TypeSupport.hpp>

using namespace ez::intern;

static_assert(type_supported<short>::value, "");
static_assert(type_supported<int>::value, "");
static_assert(type_supported<char>::value, "");
static_assert(type_supported<long>::value, "");
static_assert(type_supported<long long>::value, "");
static_assert(type_supported<bool>::value, "");

static_assert(type_supported<float>::value, "");
static_assert(type_supported<double>::value, "");

static_assert(type_supported<signed>::value, "");
static_assert(type_supported<unsigned>::value, "");

static_assert(type_supported<unsigned char>::value, "");
static_assert(type_supported<unsigned int>::value, "");
static_assert(type_supported<unsigned short>::value, "");
static_assert(type_supported<unsigned long>::value, "");
static_assert(type_supported<unsigned long long>::value, "");

static_assert(type_supported<signed char>::value, "");
static_assert(type_supported<signed int>::value, "");
static_assert(type_supported<signed short>::value, "");
static_assert(type_supported<signed long>::value, "");
static_assert(type_supported<signed long long>::value, "");


static_assert(type_supported<int8_t>::value, "");
static_assert(type_supported<int16_t>::value, "");
static_assert(type_supported<int32_t>::value, "");
static_assert(type_supported<int64_t>::value, "");

static_assert(type_supported<uint8_t>::value, "");
static_assert(type_supported<uint16_t>::value, "");
static_assert(type_supported<uint32_t>::value, "");
static_assert(type_supported<uint64_t>::value, "");

static_assert(type_supported<std::pair<bool, bool>>::value, "");
static_assert(type_supported<std::tuple<int, short, long, long long>>::value, "");
static_assert(type_supported<std::set<int>>::value, "");