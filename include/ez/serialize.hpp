#pragma once
#include <stdexcept>
#include <vector>
#include <string>
#include <cinttypes>
#include <type_traits>

namespace ez {
	namespace serialize {
		uint8_t* i8(int8_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* i16(int16_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* i32(int32_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* i64(int64_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* u8(uint8_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* u16(uint16_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* u32(uint32_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* u64(uint64_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* f32(float val, uint8_t* write, uint8_t const* const end);
		uint8_t* f64(double val, uint8_t* write, uint8_t const* const end);
		uint8_t* ptr(const void* val, uint8_t* write, uint8_t const* const end);

		void i8(int8_t val, std::vector<uint8_t>& buffer);
		void i16(int16_t val, std::vector<uint8_t>& buffer);
		void i32(int32_t val, std::vector<uint8_t>& buffer);
		void i64(int64_t val, std::vector<uint8_t>& buffer);
		void u8(uint8_t val, std::vector<uint8_t>& buffer);
		void u16(uint16_t val, std::vector<uint8_t>& buffer);
		void u32(uint32_t val, std::vector<uint8_t>& buffer);
		void u64(uint64_t val, std::vector<uint8_t>& buffer);
		void f32(float val, std::vector<uint8_t>& buffer);
		void f64(double val, std::vector<uint8_t>& buffer);
		void ptr(const void* val, std::vector<uint8_t>& buffer);


		uint8_t* value(int8_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(int16_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(int32_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(int64_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(uint8_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(uint16_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(uint32_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(uint64_t val, uint8_t* write, uint8_t const* const end);
		uint8_t* value(float val, uint8_t* write, uint8_t* end);
		uint8_t* value(double val, uint8_t* write, uint8_t* end);
		uint8_t* value(const void* val, uint8_t* write, uint8_t* end);

		void value(int8_t val, std::vector<uint8_t>& buffer);
		void value(int16_t val, std::vector<uint8_t>& buffer);
		void value(int32_t val, std::vector<uint8_t>& buffer);
		void value(int64_t val, std::vector<uint8_t>& buffer);
		void value(uint8_t val, std::vector<uint8_t>& buffer);
		void value(uint16_t val, std::vector<uint8_t>& buffer);
		void value(uint32_t val, std::vector<uint8_t>& buffer);
		void value(uint64_t val, std::vector<uint8_t>& buffer);
		void value(float val, std::vector<uint8_t>& buffer);
		void value(double val, std::vector<uint8_t>& buffer);
		void value(const void* val, std::vector<uint8_t>& buffer);


		template<typename T>
		void string(const std::basic_string<T>& str, std::vector<uint8_t>& buffer) {
			static_assert(std::is_integral_v<T>, "ez::serialize::string requires a string type with integral value_type!");

			uint64_t bytes = str.size() * sizeof(T);
			serialize::u64(bytes, buffer);

			for (const T & val: str) {
				serialize::value(val, buffer);
			}
		}

		template<typename T>
		void string(const std::basic_string<T>& str, uint8_t* write, uint8_t const* const end) {
			static_assert(std::is_integral_v<T>, "ez::serialize::string requires a string type with integral value_type!");

			uint64_t bytes = str.size() * sizeof(T);

			if ((bytes + sizeof(uint64_t)) > (end - write)) {
				throw std::out_of_range("ez::serialize::string called with write range smaller than the string being written!");
			}
			
			write = serialize::u64(bytes, write, end);
			for (const T& val : str) {
				write = serialize::value(val, write, end);
			}
		}
	};
};