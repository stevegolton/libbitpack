#ifndef BIT_PACK_H
#define BIT_PACK_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * Pulls a 64-bit unsigned integer out of an array of bytes stored in a little
 * endian byte order. The result is copied into the passed 64 bit pointer.
 *
 * @param[in]	src				Source array.
 * @param[in]	len				Length of the source array in bytes.
 * @param[in]	offset_bits		Offset in bits to the start value to be parsed if counting up from the least significant bit of the LAST byte of the source array.
 * @param[in]	width_bits		Width of the parameter in bits.
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
 * @param[in]	offset_bits		Offset in bits to the start value to be parsed if counting up from the least significant bit of the FIRST byte of the source array.
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

// Not supported
#if 0
int pack_uint64_le( const uint8_t * const src,
					const size_t len,
					const size_t offset_bits,
					const size_t width_bits,
					const uint64_t src );

int pack_uint64_be( const uint8_t * const src,
					const size_t len,
					const size_t offset_bits,
					const size_t width_bits,
					const uint64_t src );
#endif

#endif
