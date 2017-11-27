#ifndef BIT_PACK_H
#define BIT_PACK_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/*
Example 1
-------------------------
Bit offset =  3
Bit width  = 13
Endanness  = le
MSB            LSB
 7 6 5 4 3 2 1 0
+---------------+ Address
|e|d|c|b|a| | | |  0x1000
+---------------+
| | |k|j|i|h|g|f|  0x1001
+---------------+
| | | | | | | | |  0x1002
+---------------+
| | | | | | | | |  0x1003
+---------------+

Example 2
-------------------------
Bit offset =  3
Bit width  = 13
Endanness  = be
MSB            LSB
 0 1 2 3 4 5 6 7
+---------------+ Address
| | | |k|j|i|h|g|  0x1000
+---------------+
|f|e|d|c|b|a| | |  0x1001
+---------------+
| | | | | | | | |  0x1002
+---------------+
| | | | | | | | |  0x1003
+---------------+
*/

/**
 * Pulls a 64-bit unsigned integer out of an array of bytes stored in a little
 * endian byte order. The result is copied into the passed 64 bit pointer.
 *
 * @param[in]	src				Source array.
 * @param[in]	offset_bits		Offset in bits to the start of the value counting up from the LEAST significant bit of the FIRST byte of the source array.
 * @param[in]	width_bits		Width of the value in bits.
 * @param[out]	dest			Pointer to where to store the obtained value.
 *
 * @return		0 if successful, -1 on error.
 */
int unpack_uint64_le( const uint8_t * const src,
					  const size_t offset_bits,
					  const size_t width_bits,
					  uint64_t * dest );

/**
 * Pulls a 64-bit unsigned integer out of an array of bytes stored in a big
 * endian byte order. The result is copied into the passed 64 bit pointer.
 *
 * @param[in]	src				Source array.
 * @param[in]	len				Length of the source array in bytes.
 * @param[in]	offset_bits		Offset in bits to the start of the value counting up from the LEAST significant bit of the LAST byte of the source array.
 * @param[in]	width_bits		Width of the parameter in bits.
 * @param[out]	dest			Pointer to where to store the obtained value.
 *
 * @return		0 if successful, -1 on error.
 */
int unpack_uint64_be( const uint8_t * const src,
					  const size_t offset_bits,
					  const size_t width_bits,
					  uint64_t * dest );

/**
 * Packs a 64-bit unsigned integer into of an array of bytes stored in a big
 * endian byte order.
 *
 * @param[in]	dest			Destination array.
 * @param[in]	offset_bits		Offset in bits to the start of the value counting up from the LEAST significant bit of the FIRST byte of the source array.
 * @param[in]	width_bits		Width of the value in bits.
 * @param[in]	src				The value to pack.
 *
 * @return		0 if successful, -1 on error.
 */
int pack_uint64_le( uint8_t * const dest,
					const size_t offset_bits,
					const size_t width_bits,
					const uint64_t src );

/**
 * Packs a 64-bit unsigned integer into of an array of bytes stored in a big
 * endian byte order.
 *
 * @param[in]	dest			Destination array.
 * @param[in]	offset_bits		Offset in bits to the start of the value counting up from the LEAST significant bit of the LAST byte of the source array.
 * @param[in]	width_bits		Width of the value in bits.
 * @param[in]	src				The value to pack.most
 *
 * @return		0 if successful, -1 on error.
 */
int pack_uint64_be( uint8_t * const dest,
					const size_t offset_bits,
					const size_t width_bits,
					const uint64_t src );

#endif
