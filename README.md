# libbitpack
Architecture independent C library for packing and unpacking integers and floats of varying precision into and from arbitrary bit-wise locations within a byte array, supporting various types of byte and bit ordering.

Note: This library is in no way finished, the description here is more of a wishlist.

Example use case: you have been given a device which talks in a weird binary protocol where values are packed tightly into bit fields in big endian byte order. After successfully connecting to the device you are receiving messages which end up in a byte array on your Intel (little endian) machine and you want to pluck out the values in a logical manner.

How it works:
 - The library contains a set of functions which can be used to pick out various size integers and floats from a given byte array.
 - Each function notably takes a pointer to a byte array, a bit offset and a bit length of the value in question as well as byte ordering information.
 - The passed buffer is treated as a large arbitrary precision integer which means bit offsets larger than 64 can be used.
 - For Motorola (big endian) byte order, the bit offset is counted starting at the LSbit of the first byte in the array, counting forward through the bytes.
 - For Intel (little endian) byte order, the bit offset is counted starting at the LSbit of the last byte in the array, counting backward through the bytes.

## Reasoning
This library was originally designed for packing and parsing CAN messages to and from weird automotive devices. It's not meant to be fast or efficient, just flexible.

## Build & test instructions
 - install cmocka `# apt-get install libcmocka-dev` (tested on Ubuntu 14.04)
 - make && make test

## TODO
 - Write pretty much all the code!
 - Continuous integration
