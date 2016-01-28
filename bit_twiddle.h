#ifndef BIT_TWIDDLE_H
#define BIT_TWIDDLE_H

typedef enum
{
	eByteOrder_MSBFirst,	/* Motorola */
	eByteOrder_LSBFirst		/* Intel */

} eByteOrder_t;

int UnpackUint64( const uint8_t * const pabyData,
					   const size_t iOffsetBits,
					   const size_t iWidthBits,
					   const eByteOrder_t eByteOrder,
					   uint64_t * qwDest );

int PackUint64( const uint8_t * const pabyData,
				const size_t iOffsetBits,
				const size_t iWidthBits,
				const eByteOrder_t eByteOrder,
				const uint64_t qwSrc );



#endif
