#pragma once
#include <cinttypes>
#include <string>

union Converter32 {
	int32_t intVal;
	uint32_t uintVal;
	float floatVal;
	char data[4];
};

union Converter64 {
	int64_t intVal;
	uint64_t uintVal;
	double floatVal;
	char data[8];
};

union ConverterPtr {
	uintptr_t uintVal;
	void* ptr;
	const void* cptr;
	char data[sizeof(void*)];
};

template<typename itype>
const char* readConvert(const char* read, itype & ret) {
	ret = 0;
	for (itype i = 0; i < (sizeof(itype) * 8); i += 8) {
		// two convversions here are NECESSARY
		// The first conversion prevents sign extension
		// The second conversion stops integer promotion from happening
		ret |= itype(uint8_t(*read++)) << i;
	}
	return read;
}
template<typename itype>
char* writeConvert(char* write, itype value) {
	// For some reason manually unrolling like this gets 2x speed improvement on benchmarks.
	if constexpr (sizeof(itype) == 1) {
		*write++ = value;
	}
	else if constexpr (sizeof(itype) == 2) {
		*write++ = (value & 0xFF);
		*write++ = ((value & 0xFF00) >> 8);
	}
	else if constexpr (sizeof(itype) == 4) {
		*write++ = (value & 0xFF);
		*write++ = ((value & 0xFF00) >> 8);
		*write++ = ((value & 0xFF0000) >> 16);
		*write++ = ((value & 0xFF000000) >> 24);
	}
	else {
		*write++ = (value & 0xFF);
		*write++ = ((value & 0xFF00) >> 8);
		*write++ = ((value & 0xFF0000) >> 16);
		*write++ = ((value & 0xFF000000) >> 24);

		*write++ = ((value & 0xFF000000'00) >> 32);
		*write++ = ((value & 0xFF000000'0000) >> 40);
		*write++ = ((value & 0xFF000000'000000) >> 48);
		*write++ = ((value & 0xFF000000'00000000) >> 56);
	}
	return write;
}
template<typename itype>
void writeConvert(std::string& write, itype value) {
	if constexpr (sizeof(itype) == 1) {
		write.push_back(value);
	}
	else if constexpr (sizeof(itype) == 2) {
		write.push_back(value & 0xFF);
		write.push_back((value & 0xFF00) >> 8);
	}
	else if constexpr (sizeof(itype) == 4) {
		write.push_back(value & 0xFF);
		write.push_back((value & 0xFF00) >> 8);
		write.push_back((value & 0xFF0000) >> 16);
		write.push_back((value & 0xFF000000) >> 24);
	}
	else {
		write.push_back(value & 0xFF);
		write.push_back((value & 0xFF00) >> 8);
		write.push_back((value & 0xFF0000) >> 16);
		write.push_back((value & 0xFF000000) >> 24);

		write.push_back((value & 0xFF000000'00) >> 32);
		write.push_back((value & 0xFF000000'0000) >> 40);
		write.push_back((value & 0xFF000000'000000) >> 48);
		write.push_back((value & 0xFF000000'00000000) >> 56);
	}
}