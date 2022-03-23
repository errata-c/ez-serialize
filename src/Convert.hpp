#pragma once
#include <cinttypes>
#include <vector>

union Converter32 {
	int32_t intVal;
	uint32_t uintVal;
	float floatVal;
	uint8_t bytes[sizeof(intVal)];
};

union Converter64 {
	int64_t intVal;
	uint64_t uintVal;
	double floatVal;
	uint8_t bytes[sizeof(intVal)];
};

union ConverterPtr {
	uintptr_t uintVal;
	void* ptr;
	const void* cptr;
};

template<typename itype>
const char* readConvert(const char* read, itype & ret) {
	ret = 0;
	for (int i = 0; i < sizeof(itype) * 8; i += 8) {
		ret |= itype(*read++) << i;
	}
	return read;
}
template<typename itype>
void writeConvert(char* write, itype value) {
	for (int i = 0; i < sizeof(itype) * 8; i += 8) {
		*write++ = (value & (itype(0xFF) << i)) >> i;
	}
}
template<typename itype>
void writeConvert(std::string& write, itype value) {
	for (int i = 0; i < sizeof(itype) * 8; i += 8) {
		write.push_back((value & (itype(0xFF) << i)) >> i);
	}
}