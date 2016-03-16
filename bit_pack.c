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
	int targetByte;
	int targetBit;

	/* Can't return anything wider than a 64 bit int */
	if ( width_bits > ( 8 * sizeof( uint64_t ) ) )
	{
		return -1;
	}

	for ( bit_index = offset_bits; bit_index < ( offset_bits + width_bits ); bit_index++ )
	{
		targetByte = bit_index / 8;
		targetBit = bit_index % 8;

		temp |= ( (uint64_t)( src[targetByte] >> targetBit ) & 0x1 ) << ( bitoffset++ );
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
	int targetByte;
	int targetBit;

	/* Can't return anything wider than a 64 bit int */
	if ( width_bits > ( 8 * sizeof( uint64_t ) ) )
	{
		return -1;
	}

	for ( bit_index = offset_bits; bit_index < ( offset_bits + width_bits ); bit_index++ )
	{
		targetByte = ( len - 1 ) - ( bit_index / 8 );
		targetBit = bit_index % 8;

		temp |= ( (uint64_t)( src[targetByte] >> targetBit ) & 0x1 ) << ( bitoffset++ );
	}

	*dest = temp;

	return 0;
}

int unpack_uint64_be_rev( const uint8_t * const src,
						  const size_t len,
						  const size_t offset_bits,
						  const size_t width_bits,
						  uint64_t * dest )
{
	size_t offset_bits_from_start = ( ( len * 8 ) - offset_bits ) - width_bits;

	return unpack_uint64_be( src, len, offset_bits_from_start, width_bits, dest );
}

int pack_uint64_le( uint8_t * const dest,
					const size_t len,
					const size_t offset_bits,
					const size_t width_bits,
					const uint64_t src )
{
	uint64_t temp = 0;
	int bit_index;
	int bitoffset = 0;
	int targetByte;
	int targetBit;

	/* Can't return anything wider than a 64 bit int */
	if ( width_bits > ( 8 * sizeof( uint64_t ) ) )
	{
		return -1;
	}

	for ( bit_index = offset_bits; bit_index < ( offset_bits + width_bits ); bit_index++ )
	{
		targetByte = bit_index / 8;
		targetBit = bit_index % 8;

		dest[targetByte] |= ( (uint64_t)( src >> bitoffset++ ) & 0x1 ) << ( targetBit++ );
	}

	return 0;
}

int pack_uint64_be( uint8_t * const dest,
					const size_t len,
					const size_t offset_bits,
					const size_t width_bits,
					const uint64_t src )
{
	uint64_t temp = 0;
	int bit_index;
	int bitoffset = 0;
	int targetByte;
	int targetBit;

	/* Can't return anything wider than a 64 bit int */
	if ( width_bits > ( 8 * sizeof( uint64_t ) ) )
	{
		return -1;
	}

	for ( bit_index = offset_bits; bit_index < ( offset_bits + width_bits ); bit_index++ )
	{
		targetByte = ( len - 1 ) - ( bit_index / 8 );
		targetBit = bit_index % 8;

		dest[targetByte] |= ( (uint64_t)( src >> bitoffset++ ) & 0x1 ) << ( targetBit++ );
	}

	return 0;
}

int pack_uint64_be_rev( uint8_t * const dest,
					const size_t len,
					const size_t offset_bits,
					const size_t width_bits,
					const uint64_t src )
{
	size_t offset_bits_from_start = ( ( len * 8 ) - offset_bits ) - width_bits;

	return pack_uint64_be( src, len, offset_bits_from_start, width_bits, dest );
}
