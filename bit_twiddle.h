#ifndef BIT_TWIDDLE_H
#define BIT_TWIDDLE_H

typedef enum
{
	eByteOrder_MSBFirst,	/* Motorola */
	eByteOrder_LSBFirst		/* Intel */

} byte_order_t;

int UnpackUint64( const uint8_t * const buf,
					   const size_t offset_bits,
					   const size_t width_bits,
					   const byte_order_t byte_order,
					   uint64_t * dest );

int PackUint64( const uint8_t * const buf,
				const size_t offset_bits,
				const size_t width_bits,
				const byte_order_t byte_order,
				const uint64_t src );



#endif
