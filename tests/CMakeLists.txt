cmake_minimum_required(VERSION 3.24)
project(EZ_SERIALIZE_TESTS)

FetchContent_Declare(
	Catch2
	GIT_REPOSITORY "https://github.com/catchorg/Catch2.git"
	GIT_TAG "v3.2.1"
	FIND_PACKAGE_ARGS CONFIG
)
FetchContent_Declare(
	fmt
	GIT_REPOSITORY "https://github.com/fmtlib/fmt.git"
	GIT_TAG "9.1.0"
	FIND_PACKAGE_ARGS CONFIG
)
FetchContent_MakeAvailable(Catch2 fmt)

include(Catch)

add_executable(basic_test 
	"basic/basic.cpp"
	"basic/enumerators.cpp"
	"basic/ranges.cpp"
	"basic/strings.cpp"
	"basic/types.cpp"
)
target_link_libraries(basic_test 
PRIVATE 
	ez::serialize 
	fmt::fmt 
	Catch2::Catch2WithMain
)

catch_discover_tests(basic_test)