#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "bit_twiddle.h"

/**
 * Pulls a 64-bit unsigned integer out of an array of bytes with a given byte
 * order. The result is copied into the passed 64 bit pointer.
 *
 * @param[in]	buf				Byte array to use.
 * @param[in]	offset_bits		Offset from the START of the array i.e. the
 * 								least significant bit of element [0] of the
 * 								byte array.
 * @param[in]	width_bits		Width if the parameter in bits.
 * @param[in]	byte_order		The byte order LSB or MSB first.
 * @param[out]	dst				Destination int.
 *
 * @return		Error code.
 */
int UnpackUint64( const uint8_t * const buf,
				  const size_t offset_bits,
				  const size_t width_bits,
				  const byte_order_t byte_order,
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

	if ( byte_order == eByteOrder_LSBFirst )
	{
		/* Little endian */
		for ( bit_index = offset_bits; bit_index < ( offset_bits + width_bits ); bit_index++ )
		{
			targetByte = bit_index / 8;
			targetBit = bit_index % 8;

			/* Work out which byte we want */
			temp |= ( (uint64_t)( buf[targetByte] >> targetBit ) & 0x1 ) << bitoffset++;
		}
	}
	else
	{
		/* Big endian */
		for ( bit_index = offset_bits; bit_index < ( offset_bits + width_bits ); bit_index++ )
		{
			targetByte = bit_index / 8;
			targetBit = bit_index % 8;

			/* Work out which byte we want */
			byte |= ( ( buf[targetByte] >> targetBit ) & 0x1 ) << bitoffset++;

			if ( 8 == bitoffset )
			{
				/* We have completed a byte to move it up into place */
				temp |= ((uint64_t)byte) << (8*(width_bytes - (++byteoffset)));

				bitoffset = 0;
				byte = 0;
			}
		}
	}

	*dest = temp;

	return 0;
}

/**
 * Pulls out a 64-bit unsigned integer from an array of bytes with a given byte
 * order. The result is copied into the passed 64 bit pointer.
 */
int PackUint64( const uint8_t * const buf,
				const size_t offset_bits,
				const size_t width_bits,
				const byte_order_t byte_order,
				const uint64_t src )
{
	/* Not implemented yet */
	return -1;
}
