# ez-serialize
Simple safe serialization utilities for modern c++.

This small static library implements serialization primitives in a safe, defined manner.
It deals with all conversions by using unions, and avoids endianess issues by using bitshifting for reading bytes of data.