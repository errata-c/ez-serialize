#pragma once
#include <cinttypes>

union Converter8 {
	int8_t intVal;
	uint8_t uintVal;
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


inline uint8_t readByte16(int16_t value, int index) {
	index <<= 3;
	return static_cast<uint8_t>((value & (0xFF << index)) >> index);
}
inline uint8_t readByte32(int32_t value, int index) {
	index <<= 3;
	return static_cast<uint8_t>((value & (0xFF << index)) >> index);
}
inline uint8_t readByte64(int64_t value, int index) {
	index <<= 3;
	return static_cast<uint8_t>((value & (static_cast<int64_t>(0xFF) << index)) >> index);
}

inline uint8_t readByte16(uint16_t value, int index) {
	index <<= 3;
	return static_cast<uint8_t>((value & (0xFF << index)) >> index);
}
inline uint8_t readByte32(uint32_t value, int index) {
	index <<= 3;
	return static_cast<uint8_t>((value & (0xFF << index)) >> index);
}
inline uint8_t readByte64(uint64_t value, int index) {
	index <<= 3;
	return static_cast<uint8_t>((value & (static_cast<int64_t>(0xFF) << index)) >> index);
}

inline uint16_t writeByte16(int byte, int index) {
	index <<= 3;
	return byte << index;
}
inline uint32_t writeByte32(int byte, int index) {
	index <<= 3;
	return byte << index;
}
inline uint64_t writeByte64(int64_t byte, int index) {
	index <<= 3;
	return byte << index;
}
