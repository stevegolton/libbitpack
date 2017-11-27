#include "bit_pack.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

int unpack_uint64_le( const uint8_t * const src,
					  const size_t offset_bits,
					  const size_t width_bits,
					  uint64_t * dest )
{
	uint64_t temp = 0;
	size_t bit_index;
	size_t targetByte;
	uint8_t targetBit;

	/* Can't return anything wider than a 64 bit int */
	if ( width_bits > ( 8 * sizeof( uint64_t ) ) )
	{
		return -1;
	}

	for ( bit_index = ( offset_bits + width_bits ); bit_index > offset_bits; )
	{
		--bit_index;
		targetByte = bit_index / 8;
		targetBit = bit_index % 8;

		temp = (temp << 1) | ( ( src[targetByte] >> targetBit ) & 0x1 );
	}

	*dest = temp;

	return 0;
}

int unpack_uint64_be( const uint8_t * const src,
					  const size_t offset_bits,
					  const size_t width_bits,
					  uint64_t * dest )
{
	uint64_t temp = 0;
	size_t bit_index;
	size_t targetByte;
	uint8_t targetBit;

	/* Can't return anything wider than a 64 bit int */
	if ( width_bits > ( 8 * sizeof( uint64_t ) ) )
	{
		return -1;
	}

	for ( bit_index = offset_bits; bit_index < ( offset_bits + width_bits ); bit_index++ )
	{
		targetByte = bit_index / 8;
		targetBit = 7 - (bit_index % 8);

		temp = (temp << 1) | ( ( src[targetByte] >> targetBit ) & 0x1 );
	}

	*dest = temp;

	return 0;
}

int pack_uint64_le( uint8_t * const dest,
					const size_t offset_bits,
					const size_t width_bits,
					const uint64_t src )
{
	size_t bit_index;
	uint8_t bitoffset = width_bits;
	size_t targetByte;
	uint8_t targetBit;

	/* Can't return anything wider than a 64 bit int */
	if ( width_bits > ( 8 * sizeof( uint64_t ) ) )
	{
		return -1;
	}

	for ( bit_index = ( offset_bits + width_bits ); bit_index > offset_bits; )
	{
		--bit_index;
		targetByte = bit_index / 8;
		targetBit = bit_index % 8;

		--bitoffset;
		dest[targetByte] &= ~(1 << targetBit); /* Clearing a bit */
		dest[targetByte] |= ( ( src >> bitoffset ) & 0x1 ) << targetBit;
	}

	return 0;
}

int pack_uint64_be( uint8_t * const dest,
					const size_t offset_bits,
					const size_t width_bits,
					const uint64_t src )
{
	size_t bit_index;
	uint8_t bitoffset = width_bits;
	size_t targetByte;
	uint8_t targetBit;

	/* Can't return anything wider than a 64 bit int */
	if ( width_bits > ( 8 * sizeof( uint64_t ) ) )
	{
		return -1;
	}

	for ( bit_index = offset_bits; bit_index < ( offset_bits + width_bits ); bit_index++ )
	{
		targetByte = bit_index / 8;
		targetBit = 7 - (bit_index % 8);

		--bitoffset;
		dest[targetByte] &= ~(1 << targetBit); /* Clearing a bit */
		dest[targetByte] |= ( ( src >> bitoffset ) & 0x1 ) << targetBit;
	}

	return 0;
}
