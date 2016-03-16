# libbitpack
C library for packing and unpacking various number types of arbitrary bit lengths to and from arbitrary bit positions within byte arrays. Supports various byte orders. Useful for binary protocols.
The idea is that these functions will be able to pack and unpack bit fields to and from a message regardless of what architecture machine it is running on. It can also be used to pack or unpack legacy binary protocols such as CAN messages being sent to or being received from devices architecture.

How it works:
 - Each function is passed a pointer to a byte array, an bit offset and a bit length.
 - The buffer is treated as a large number of arbitrary precision.
 - For big endian byte order, the bit offset is counted starting at the LSb of the first byte in the array.
 - For little endian byte order, the bit offset is counted starting at the LSb of the last byte in the array.

## Reasoning
Originally designed for packing and parsing CAN messages. Not meant to be fast or efficient, just flexible.

## Build & test instructions
(Requires cmocka libraries to be installed) - make && make test

## TODO
 - Write pretty much all the code!
 - Continuous integration
