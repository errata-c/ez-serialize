cmake_minimum_required(VERSION 3.15)

project(EZ_SERIALIZE
	VERSION 0.3.1
	LANGUAGES CXX
)

option(EZ_SERIALIZE_BUILD_TESTS "Build the test executables" OFF)
set(EZ_SERIALIZE_CONFIG_DIR "share/ez-serialize" CACHE STRING "The relative directory to install package config files.")


include(FetchContent)

FetchContent_Declare(
	ez-cmake
	GIT_REPOSITORY "https://github.com/errata-c/ez-cmake.git"
	GIT_TAG "main"
)
FetchContent_MakeAvailable(ez-cmake)


add_library(ez-serialize STATIC 
	"src/serialize.cpp" 
	"src/deserialize.cpp"
)
target_include_directories(ez-serialize PUBLIC 
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>" 
	"$<INSTALL_INTERFACE:include>"
)
target_compile_features(ez-serialize PUBLIC cxx_std_17)
target_compile_options(ez-serialize PRIVATE "$<BUILD_INTERFACE:$<$<CXX_COMPILER_ID:MSVC>:/permissive->>")

set_target_properties(ez-serialize PROPERTIES EXPORT_NAME "serialize")

add_library(ez::serialize ALIAS ez-serialize)


if(EZ_SERIALIZE_BUILD_TESTS)
	add_subdirectory("tests")
endif()


install(
	DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
	DESTINATION "include"
)

install(TARGETS ez-serialize
	EXPORT ez-serialize-targets
	LIBRARY DESTINATION "lib/$<CONFIG>"
	ARCHIVE DESTINATION "lib/$<CONFIG>"
	RUNTIME DESTINATION "bin/$<CONFIG>"
)

install_package(
	NAME "ez-serialize"
	NAMESPACE "ez::"
	EXPORT "ez-serialize-targets"
	DESTINATION "${EZ_SERIALIZE_CONFIG_DIR}"
	COMPATIBILITY "SameMajorVersion"
	VERSION "${EZ_SERIALIZE_VERSION}"
)