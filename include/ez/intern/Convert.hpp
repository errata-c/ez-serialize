#pragma once
#include <cinttypes>

namespace ez {
	namespace intern {
		union Converter8 {
			std::int8_t intVal;
			std::uint8_t uintVal;
		};

		union Converter16 {
			std::int16_t intVal;
			std::uint16_t uintVal;
			std::uint8_t bytes[sizeof(intVal)];
		};

		union Converter32 {
			std::int32_t intVal;
			std::uint32_t uintVal;
			float floatVal;
			std::uint8_t bytes[sizeof(intVal)];
		};

		union Converter64 {
			std::int64_t intVal;
			std::uint64_t uintVal;
			double floatVal;
			std::uint8_t bytes[sizeof(intVal)];
		};

		union ConverterPtr {
			std::uintptr_t uintVal;
			void* ptr;
			const void* cptr;
		};

		std::uint8_t readByte16(std::int16_t value, int index);
		std::uint8_t readByte32(std::int32_t value, int index);
		std::uint8_t readByte64(std::int64_t value, int index);

		std::uint8_t readByte16(std::uint16_t value, int index);
		std::uint8_t readByte32(std::uint32_t value, int index);
		std::uint8_t readByte64(std::uint64_t value, int index);

		std::uint16_t writeByte16(int byte, int index);
		std::uint32_t writeByte32(int byte, int index);
		std::uint64_t writeByte64(std::int64_t byte, int index);
	}
}