#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "bit_twiddle.h"

// TODO pack...?
union test
{
	uint32_t val;
	uint8_t bytes[4];
};

#define mMASK(x)					( ( x < 64 )?( ( 0x1ULL << x ) - 1 ):0xFFFFFFFFFFFFFFFFULL )

static inline eByteOrder_t GetSystemByteOrder( void );

/**
 * Pulls out a 64-bit unsigned integer from an array of bytes with a given byte
 * order. The result is copied into the passed 64 bit pointer.
 *
 * @param[in]	Byte array to use.
 * @param[in]	offset_bits		Offset from the START of the array i.e. the
 * 								least significant bit of element [0] of the
 * 								byte array.
 * @param[in]	width_bits		Width if the parameter in bits.
 * @param[in]	byte_order		The byte order LSB or MSB first.
 * @param[out]	qwDest			Destination int.
 *
 * @return		Error code.
 */
int UnpackUint64( const uint8_t * const pabyData,
				  const size_t offset_bits,
				  const size_t width_bits,
				  const eByteOrder_t eByteOrder,
				  uint64_t * qwDest )
{
	uint64_t qwTemp = 0;
	int iIdx;
	int offset = 0;
	int bitoffset = 0;
	int byteoffset = 0;
	int widthinbytes = ( ( width_bits - 1 ) / 8 ) + 1;

	/* Cant do anything more than a uint64 */
	if ( width_bits > ( 8 * sizeof( uint64_t ) ) )
		return -1;

	if ( eByteOrder == eByteOrder_LSBFirst )
	{
		/* Little endian */
		for ( iIdx = offset_bits; iIdx < ( offset_bits + width_bits ); iIdx++ )
		{
			int targetByte = iIdx / 8;
			int targetBit = iIdx % 8;

			/* Work out which byte we want */
			qwTemp |= ( (uint64_t)( pabyData[targetByte] >> targetBit ) & 0x1 ) << offset++;
		}

		*qwDest = qwTemp;
	}
	else
	{
		/* Big endian */
		for ( iIdx = offset_bits; iIdx < ( offset_bits + width_bits ); iIdx++ )
		{
			int targetByte = iIdx / 8;
			int targetBit = iIdx % 8;
			uint8_t byte;

			/* Work out which byte we want */
			byte |= ( ( pabyData[targetByte] >> targetBit ) & 0x1 ) << bitoffset++;

			if ( 8 == bitoffset )
			{
				/* We have completed a byte to move it up into place */
				qwTemp |= ((uint64_t)byte) << (8*(widthinbytes - (++byteoffset)));

				bitoffset = 0;
				byte = 0;
			}
		}

		*qwDest = qwTemp;
	}

	return 0;
}

/**
 * Pulls out a 64-bit unsigned integer from an array of bytes with a given byte
 * order. The result is copied into the passed 64 bit pointer.
 */
int PackUint64( const uint8_t * const pabyData,
				const size_t iOffsetBits,
				const size_t iWidthBits,
				const eByteOrder_t eByteOrder,
				const uint64_t qwSrc )
{
	uint64_t qwTemp = qwSrc;

	/* TODO cant do anything more than 64 bits yet as we cast to a uint64 */
	if ( ( iOffsetBits + iWidthBits ) > 64 )
		return -1;

	return -1;
}

/* ************************************************************************** */
static inline eByteOrder_t GetSystemByteOrder( void )
{
	union test testval;

	testval.val = 0x1;

	if ( testval.bytes[0] == 0x1 )
	{
		return eByteOrder_LSBFirst;
	}
	else
	{
		return eByteOrder_MSBFirst;
	}
}
