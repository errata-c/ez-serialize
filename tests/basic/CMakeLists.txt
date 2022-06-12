
add_executable(basic_test "main.cpp")
target_link_libraries(basic_test PRIVATE ez::serialize fmt::fmt Catch2::Catch2WithMain)