project(EZ_SERIALIZE_TESTS)

find_package(fmt CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

include(Catch)

add_executable(basic_test "basic/basic.cpp")
target_link_libraries(basic_test 
PRIVATE 
	ez::serialize 
	fmt::fmt 
	Catch2::Catch2WithMain
)

catch_discover_tests(basic_test)