find_package(benchmark CONFIG REQUIRED)

add_executable(ez_serialize_benchmarks 
	"serialize.cpp"
)
target_link_libraries(ez_serialize_benchmarks PRIVATE
	benchmark::benchmark_main
	ez::serialize
)