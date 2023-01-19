cmake_minimum_required(VERSION 3.24)

project(EZ_SERIALIZE
	VERSION 0.6.1
	LANGUAGES CXX
)

option(EZ_SERIALIZE_BUILD_BENCHMARKS "Build the benchmarks" OFF)
set(EZ_SERIALIZE_CONFIG_DIR "share/ez-serialize" CACHE STRING "The relative directory to install package config files.")

include(FetchContent)
FetchContent_Declare(
	ez-cmake
	GIT_REPOSITORY "https://github.com/errata-c/ez-cmake.git"
	GIT_TAG "main"
)
FetchContent_MakeAvailable(ez-cmake)

add_library(ez-serialize INTERFACE)
target_include_directories(ez-serialize INTERFACE 
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>" 
	"$<INSTALL_INTERFACE:include>"
)
target_compile_features(ez-serialize INTERFACE cxx_std_17)

set_target_properties(ez-serialize PROPERTIES EXPORT_NAME "serialize")

add_library(ez::serialize ALIAS ez-serialize)

if(PROJECT_IS_TOP_LEVEL)
	if(EZ_SERIALIZE_BUILD_BENCHMARKS)
		add_subdirectory("benchmarks")
	endif()

	include(CTest)
	if(BUILD_TESTING)
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
		ARCH_INDEPENDENT
	)
endif()