# ez-serialize
Simple safe serialization utilities for modern c++

This small static library implements serialization primitives in a safe, defined manner.
It deals with all conversions by using unions, and avoids endianess issues by using bit shifting for reading bytes of data.

This is not meant as a replacement for higher level serialization libraries like google flatbuffers, but instead as a simpler solution for use in scenarios where a high level library is overkill.

The serialization has two signatures:

```c++
// The pointer based signature accepts a writable range of data,
// and returns the pointer one past the end of the written data.
uint8_t* ez::serialize::i32(int32_t val, uint8_t* write, uint8_t const* const end);

// The vector based signature accepts a std::vector<uint8_t> buffer to write into
void ez::serialize::i32(int32_t val, std::vector<uint8_t>& buffer);
```

 The deserialization has only one signature:

```c++
// Takes a range of data and deserializes a value from it, returning the pointer one past the end of the read data.
// The value deserialized is returned via the reference argument, which is always the last argument.
const uint8_t* ez::deserialize::i32(const uint8_t* read, uint8_t const* const end, int32_t & ret);
```

Note that when serializing strings, the data in the string is written as is, encoding agnostic. This means that an external library is required to handle encodings if you need them.