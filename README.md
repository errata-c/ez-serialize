# ez-serialize
This library is meant to provide standards compliant, low level serialization functions. These functions do not take into account the structure of the data at a high level, this must be done by the programmer. In order to avoid undefined behavior, the serialization is done by converting all the primitive types to unsigned integers first (via `std::memcpy`) and then each byte is written away by shift operations.

This is not meant as a replacement for higher level serialization libraries (see: [cereal](https://github.com/USCiLab/cereal), [protobuf](https://github.com/protocolbuffers/protobuf), [FlatBuffers](https://github.com/google/flatbuffers), etc...), but instead as a simpler solution for use in scenarios where a high level library is overkill.

The core library header provides functions to serialize/deserialize primitive types (provided by header `ez/serialize/core.hpp`):

```c++
int32_t val = 33;
// pointers to a range of writable characters:
char * writable, *end;
// Or a simple string:
std::string buffer;

// The pointer based signature accepts a writable range of data,
// and returns the pointer one past the end of the written data.
char* one_past_end = ez::serialize::i32(val, writable, end);

// The string based signature accepts a std::string buffer to write into
ez::serialize::i32(val, buffer);

// Alternatively, you can use the generic 'value' function, 
// which can infer the type (or given the type via template parameter)
one_past_end = ez::serialize::value(val, writable, end);
one_past_end = ez::serialize::value<int32_t>(val, writable, end);
```

```c++
// Takes a range of data and deserializes a value from it, returning the pointer one past the end of the read data.
// The value deserialized is returned via the reference argument, which is always the last argument.
const uint8_t* ez::deserialize::i32(const uint8_t* read, uint8_t const* const end, int32_t & ret);
```

