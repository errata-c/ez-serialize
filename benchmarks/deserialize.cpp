#include <benchmark/benchmark.h>

#include <ez/serialize/core.hpp>

static void BM_DeserializeI32(benchmark::State& state) {
    std::size_t byteCount = state.range(0) * sizeof(int32_t);
    std::size_t count = state.range(0);

    char* buffer = new char[byteCount];
    { // Initialize the buffer to a set of ones.
        ez::intern::Converter32 convert;
        convert.uintVal = 1;

        char* write = buffer;
        int oi = 3;
        if (convert.data[0] == char(convert.uintVal & 0xFF)) {
            oi = 0;
        }

        for (std::size_t i = 0; i < byteCount; ++i) {
            if ((i % 4) == oi) {
                *write++ = 1;
            }
            else {
                *write++ = 0;
            }
        }
    }


    for (auto _ : state) {
        const char* read = buffer;
        const char* end = buffer + byteCount;
        int32_t total = 0;
        int32_t val = 0;

        for (std::size_t i = 0; i < count; ++i) {
            read = ez::deserialize::i32(read, end, val);
            total += val;
        }
    }

    delete[] buffer;
}

// Register the function as a benchmark
BENCHMARK(BM_DeserializeI32)->Range(8, 8 << 10);


static void BM_DeserializeI64(benchmark::State& state) {
    std::size_t byteCount = state.range(0) * sizeof(int64_t);
    std::size_t count = state.range(0);

    char* buffer = new char[byteCount];
    { // Initialize the buffer to a set of ones.
        ez::intern::Converter64 convert;
        convert.uintVal = 1;

        char* write = buffer;
        int oi = 7;
        if (convert.data[0] == char(convert.uintVal & 0xFF)) {
            oi = 0;
        }

        for (std::size_t i = 0; i < byteCount; ++i) {
            if ((i % 8) == oi) {
                *write++ = 1;
            }
            else {
                *write++ = 0;
            }
        }
    }

    for (auto _ : state) {
        const char* read = buffer;
        const char* end = buffer + byteCount;
        int64_t total = 0;
        int64_t val = 0;

        for (std::size_t i = 0; i < count; ++i) {
            read = ez::deserialize::i64(read, end, val);
            total += val;
        }
    }

    delete[] buffer;
}

BENCHMARK(BM_DeserializeI64)->Range(8, 8 << 10);