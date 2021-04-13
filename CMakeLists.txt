cmake_minimum_required(VERSION 3.15)

project(EZ_SERIALIZE
VERSION 0.1.0
LANGUAGES CXX)

find_package(ez-cmake CONFIG REQUIRED)

option(BUILD_TESTS "Build the test executables" ON)
option(SEPARATE_DIRECTORY "Install the package into its own directory" ON)

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

if(BUILD_TESTS)
	add_subdirectory("tests")
endif()

if(SEPARATE_DIRECTORY)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/ez-serialize")
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
	NAME ez-serialize
	NAMESPACE "ez::"
	EXPORT ez-serialize-targets
	DESTINATION DEFAULT
	COMPATIBILITY SameMajorVersion
	VERSION ${EZ_SERIALIZE_VERSION}
)