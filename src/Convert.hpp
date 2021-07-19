#pragma once
#include <cinttypes>
#include <vector>

union Converter8 {
	int8_t intVal;
	uint8_t uintVal;

	// signed and unsigned char are not the same as char itself
	char charVal;
};

union Converter16 {
	int16_t intVal;
	uint16_t uintVal;
	uint8_t bytes[sizeof(intVal)];
};

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

template<typename Converter>
void readConvert(const uint8_t* read, Converter & convert) {
	convert.uintVal = 0;
	for (int i = 0; i < sizeof(Converter) * 8; i += 8) {
		convert.uintVal |= static_cast<decltype(convert.uintVal)>(*read++) << i;
	}
}
template<typename Converter>
void writeConvert(uint8_t* write, const Converter& convert) {
	for (int i = 0; i < sizeof(Converter) * 8; i += 8) {
		*write++ = (convert.uintVal & (static_cast<decltype(convert.uintVal)>(0xFF) << i)) >> i;
	}
}
template<typename Converter>
void writeConvert(std::vector<uint8_t>& write, const Converter& convert) {
	for (int i = 0; i < sizeof(Converter) * 8; i += 8) {
		write.push_back((convert.uintVal & (static_cast<decltype(convert.uintVal)>(0xFF) << i)) >> i);
	}
}