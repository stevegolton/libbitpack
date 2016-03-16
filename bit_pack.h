#ifndef BIT_PACK_H
#define BIT_PACK_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/*
Example 1
-------------------------
Bit offset =  3
Bit width  = 13
Endanness  = le

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

 7 6 5 4 3 2 1 0
+---------------+ Address
| | | | | | | | |  0x1000
+---------------+
| | | | | | | | |  0x1001
+---------------+
| | |k|j|i|h|g|f|  0x1002
+---------------+
|e|d|c|b|a| | | |  0x1003
+---------------+
*/

/**
 * Pulls a 64-bit unsigned integer out of an array of bytes stored in a little
 * endian byte order. The result is copied into the passed 64 bit pointer.
 *
 * @param[in]	src				Source array.
 * @param[in]	len				Length of the source array in bytes.
 * @param[in]	offset_bits		Offset in bits to the start of the value counting up from the least significant bit of the FIRST byte of the source array.
 * @param[in]	width_bits		Width of the value in bits.
 * @param[out]	dest			Pointer to where to store the obtained value.
 *
 * @return		0 if successful, -1 on error.
 */
int unpack_uint64_le( const uint8_t * const src,
					  const size_t len,
					  const size_t offset_bits,
					  const size_t width_bits,
					  uint64_t * dest );

/**
 * Pulls a 64-bit unsigned integer out of an array of bytes stored in a big
 * endian byte order. The result is copied into the passed 64 bit pointer.
 *
 * @param[in]	src				Source array.
 * @param[in]	len				Length of the source array in bytes.
 * @param[in]	offset_bits		Offset in bits to the start of the value counting up from the least significant bit of the LAST byte of the source array.
 * @param[in]	width_bits		Width of the parameter in bits.
 * @param[out]	dest			Pointer to where to store the obtained value.
 *
 * @return		0 if successful, -1 on error.
 */
int unpack_uint64_be( const uint8_t * const src,
					  const size_t len,
					  const size_t offset_bits,
					  const size_t width_bits,
					  uint64_t * dest );

/**
 * Exactly the same as unpack_uint64_be() except the offset is expected from the
 * most significat byte of the first byte of the source array.
 *
 * @param[in]	src				Source array.
 * @param[in]	len				Length of the source array in bytes.
 * @param[in]	offset_bits		Offset in bits to the start of the value counting up from the most significant bit of the FIRST byte of the source array.
 * @param[in]	width_bits		Width of the parameter in bits.
 * @param[out]	dest			Pointer to where to store the obtained value.
 *
 * @return		0 if successful, -1 on error.
 */
int unpack_uint64_be_rev( const uint8_t * const src,
						  const size_t len,
						  const size_t offset_bits,
						  const size_t width_bits,
						  uint64_t * dest );

// Not supported
/*
int pack_uint64_le( const uint8_t * const dest,
					const size_t len,
					const size_t offset_bits,
					const size_t width_bits,
					const uint64_t src );

int pack_uint64_be( const uint8_t * const dest,
					const size_t len,
					const size_t offset_bits,
					const size_t width_bits,
					const uint64_t src );
*/

#endif
