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

#define mMASK(x)					( ( 0x1ULL << ( x ) ) )

static inline eByteOrder_t GetSystemByteOrder( void );

/**
 * Pulls out a 64-bit unsigned integer from an array of bytes with a given byte
 * order. The result is copied into the passed 64 bit pointer.
 *
 * @return		Error code.
 */
int UnpackUint64( const uint8_t * const pabyData,
				  const size_t iOffsetBits,
				  const size_t iWidthBits,
				  const eByteOrder_t eByteOrder,
				  uint64_t * qwDest )
{
	uint64_t qwTemp = 0;
	int iIdx;

	/* Cant do anything more than a uint64 */
	if ( iWidthBits > ( 8 * sizeof( uint64_t ) ) )
		return -1;

	/* Independent of the host architecture we will copy out the array into a uint64.
	 * For this we shall treat the first byte in the array (index [0]) as the
	 * least significant part of the int.
	 * This means that a right shift equates to shifting towards the start of
	 * the array.
	 * TODO this will not work for non byte boundaries.
	 */
	for ( iIdx = 0; iIdx < iWidthBits/8; iIdx++ )
	{
		//qwTemp |= ( (uint64_t)pabyData[ ( iWidthBits / 8 - 1) - iIdx] ) << ( 8 * iIdx );
		qwTemp |= ( (uint64_t)pabyData[ iIdx ] ) << ( 8 * iIdx );
	}

	if ( eByteOrder == GetSystemByteOrder() )
	{
		/* Same byte order - shift and mask verbatim */
		qwTemp >>= iOffsetBits;
		qwTemp &= mMASK( iWidthBits );

		printf("%d, %llx\n", iWidthBits, mMASK( iWidthBits + 1 ));

		*qwDest = qwTemp;
	}
	else
	{
		/* Different byte order - need to byte swap */
		*qwDest = qwTemp;

		/* TODO can't do different byte order */
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

	if ( eByteOrder == GetSystemByteOrder() )
	{
		/* Same byte order - copy out verbatim */
		qwTemp = *((const uint64_t*)pabyData);

		/* Clear the existing bits we are about to copy in */
		qwTemp &= ~mMASK( iWidthBits );
		qwTemp |= ( qwSrc & mMASK( iWidthBits ) ) << iOffsetBits;
	}
	else
	{
		/* Different byte order - need to byte swap */
		return -1;
	}

	return 0;
}

/* ************************************************************************** */
static inline eByteOrder_t GetSystemByteOrder( void )
{
	union test testval;

	testval.val = 0x1;

	if ( testval.bytes[0] == 0x1 )
	{
		return eByteOrder_MSBLast;
	}
	else
	{
		return eByteOrder_MSBFirst;
	}
}
