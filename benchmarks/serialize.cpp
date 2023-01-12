#include <benchmark/benchmark.h>

#include <ez/serialize/core.hpp>

static void BM_SerializeI32(benchmark::State& state) {
    std::size_t byteCount = state.range(0) * sizeof(int32_t);
    std::size_t count = state.range(0);

    char* dest = new char[byteCount];

    for (auto _ : state) {
        char* write = dest;
        char* end = dest + byteCount;
        int32_t val = 0;

        for (std::size_t i = 0; i < count; ++i) {
            write = ez::serialize::i32(val, write, end);
            ++val;
        }
    }

    delete[] dest;
}

// Register the function as a benchmark
BENCHMARK(BM_SerializeI32)->Range(8, 8<<10);


static void BM_SerializeI64(benchmark::State& state) {
    std::size_t byteCount = state.range(0) * sizeof(int64_t);
    std::size_t count = state.range(0);

    char* dest = new char[byteCount];

    for (auto _ : state) {
        char* write = dest;
        char* end = dest + byteCount;
        int64_t val = 0;

        for (std::size_t i = 0; i < count; ++i) {
            write = ez::serialize::i64(val, write, end);
            ++val;
        }
    }

    delete[] dest;
}

BENCHMARK(BM_SerializeI64)->Range(8, 8 << 10);