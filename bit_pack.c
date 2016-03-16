#include "bit_pack.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

int unpack_uint64_le( const uint8_t * const src,
					  const size_t len,
					  const size_t offset_bits,
					  const size_t width_bits,
					  uint64_t * dest )
{
	uint64_t temp = 0;
	int bit_index;
	int bitoffset = 0;
	int byteoffset = 0;
	int width_bytes = ( ( width_bits - 1 ) / 8 ) + 1;	/* Width in bytes rounded up */
	int targetByte = bit_index / 8;
	int targetBit = bit_index % 8;
	uint8_t byte = 0;

	/* Can't return anything wider than a 64 bit int */
	if ( width_bits > ( 8 * sizeof( uint64_t ) ) )
	{
		return -1;
	}

	/* Little endian */
	for ( bit_index = offset_bits; bit_index < ( offset_bits + width_bits ); bit_index++ )
	{
		targetByte = bit_index / 8;
		targetBit = bit_index % 8;

		/* Work out which byte we want */
		temp |= ( (uint64_t)( src[targetByte] >> targetBit ) & 0x1 ) << bitoffset++;
	}

	*dest = temp;

	return 0;
}

int unpack_uint64_be( const uint8_t * const src,
					  const size_t len,
					  const size_t offset_bits,
					  const size_t width_bits,
					  uint64_t * dest )
{
	uint64_t temp = 0;
	int bit_index;
	int bitoffset = 0;
	int byteoffset = 0;
	int width_bytes = ( ( width_bits - 1 ) / 8 ) + 1;	/* Width in bytes rounded up */
	int targetByte = bit_index / 8;
	int targetBit = bit_index % 8;
	uint8_t byte = 0;

	/* Can't return anything wider than a 64 bit int */
	if ( width_bits > ( 8 * sizeof( uint64_t ) ) )
	{
		return -1;
	}

	/* Big endian */
	for ( bit_index = offset_bits; bit_index < ( offset_bits + width_bits ); bit_index++ )
	{
		targetByte = bit_index / 8;
		targetBit = bit_index % 8;

		/* Work out which byte we want */
		byte |= ( ( src[targetByte] >> targetBit ) & 0x1 ) << bitoffset++;

		if ( 8 == bitoffset )
		{
			/* We have completed a byte to move it up into place */
			temp |= ((uint64_t)byte) << (8*(width_bytes - (++byteoffset)));

			bitoffset = 0;
			byte = 0;
		}
	}

	*dest = temp;

	return 0;
}
