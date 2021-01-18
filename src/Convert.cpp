#include "ez/intern/Convert.hpp"

namespace ez {
	namespace intern {
		std::uint8_t readByte16(std::int16_t value, int index) {
			index <<= 3;
			return static_cast<std::uint8_t>((value & (0xFF << index)) >> index);
		}
		std::uint8_t readByte32(std::int32_t value, int index) {
			index <<= 3;
			return static_cast<std::uint8_t>((value & (0xFF << index)) >> index);
		}
		std::uint8_t readByte64(std::int64_t value, int index) {
			index <<= 3;
			return static_cast<std::uint8_t>((value & (static_cast<std::int64_t>(0xFF) << index)) >> index);
		}

		std::uint8_t readByte16(std::uint16_t value, int index) {
			index <<= 3;
			return static_cast<std::uint8_t>((value & (0xFF << index)) >> index);
		}
		std::uint8_t readByte32(std::uint32_t value, int index) {
			index <<= 3;
			return static_cast<std::uint8_t>((value & (0xFF << index)) >> index);
		}
		std::uint8_t readByte64(std::uint64_t value, int index) {
			index <<= 3;
			return static_cast<std::uint8_t>((value & (static_cast<std::int64_t>(0xFF) << index)) >> index);
		}

		std::uint16_t writeByte16(int byte, int index) {
			index <<= 3;
			return byte << index;
		}
		std::uint32_t writeByte32(int byte, int index) {
			index <<= 3;
			return byte << index;
		}
		std::uint64_t writeByte64(std::int64_t byte, int index) {
			index <<= 3;
			return byte << index;
		}
	}
}