#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "bit_twiddle.h"

void print_array_raw( const uint8_t *bytes, int len );
static void test_unpack_uint64_be_aligned( void **state );
static void test_unpack_uint64_le_aligned( void **state );
static void test_unpack_uint32_be_byaligned( void **state );
static void test_unpack_uint32_le_byaligned( void **state );
static void test_unpack_uint32_be_unaligned( void **state );
static void test_unpack_uint32_le_unaligned( void **state );


int main(void)
{
	const struct UnitTest tests[] =
	{
		unit_test( test_unpack_uint64_be_aligned ),
		unit_test( test_unpack_uint64_le_aligned ),
		unit_test( test_unpack_uint32_be_byaligned ),
		unit_test( test_unpack_uint32_le_byaligned ),
		unit_test( test_unpack_uint32_be_unaligned ),
		unit_test( test_unpack_uint32_le_unaligned ),
	};
	return run_tests(tests);
}

static void test_unpack_uint64_be_aligned( void **state )
{
	const uint8_t input[8] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };
	const uint64_t expected = 0x0123456789ABCDEF;
	uint64_t result;

	(void) state; /* unused */

	print_array_raw( input, 8 );

	/* Unpack that big word we just wrote in */
	int err = UnpackUint64( input, 0, 64, eByteOrder_MSBFirst, &result );

	assert_int_equal( 0, err );
	assert_int_equal( expected, result );
}

static void test_unpack_uint64_le_aligned( void **state )
{
	const uint8_t input[8] = { 0xEF, 0xCD, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01 };
	const uint64_t expected = 0x0123456789ABCDEF;
	uint64_t result;

	(void) state; /* unused */

	print_array_raw( input, 8 );

	/* Unpack that big word we just wrote in */
	int err = UnpackUint64( input, 0, 64, eByteOrder_LSBFirst, &result );

	assert_int_equal( 0, err );
	assert_int_equal( expected, result );
}

static void test_unpack_uint32_be_byaligned( void **state )
{
	const uint8_t input[8] = { 0xFF, 0x01, 0x23, 0x45, 0x67, 0xFF, 0xFF, 0xFF };
	const uint64_t expected = 0x01234567;
	uint64_t result;

	(void) state; /* unused */

	print_array_raw( input, 8 );

	/* Unpack that big word we just wrote in */
	int err = UnpackUint64( input, 8, 32, eByteOrder_MSBFirst, &result );

	assert_int_equal( 0, err );
	assert_int_equal( expected, result );
}

static void test_unpack_uint32_le_byaligned( void **state )
{
	const uint8_t input[8] = { 0xFF, 0x67, 0x45, 0x23, 0x01, 0xFF, 0xFF, 0xFF };
	const uint64_t expected = 0x01234567;
	uint64_t result;

	(void) state; /* unused */

	print_array_raw( input, 8 );

	/* Unpack that big word we just wrote in */
	int err = UnpackUint64( input, 8, 32, eByteOrder_LSBFirst, &result );

	assert_int_equal( 0, err );
	assert_int_equal( expected, result );
}

static void test_unpack_uint32_be_unaligned( void **state )
{
	const uint8_t input[8] = { 0x00,
							   0x02,
							   0x46,
							   0x8A,
							   0xCE,
							   0x10,
							   0x00,
							   0x00 };
	const uint64_t expected = 0x01234567;
	uint64_t result;

	(void) state; /* unused */

	print_array_raw( input, 8 );

	/* Unpack that big word we just wrote in */
	int err = UnpackUint64( input, 9, 32, eByteOrder_MSBFirst, &result );

	assert_int_equal( 0, err );
	assert_int_equal( expected, result );
}

static void test_unpack_uint32_le_unaligned( void **state )
{
	const uint8_t input[8] = { 0x00,
							   0x00,
							   0x00,
							   0x00,
							   0x00,
							   0x00,
							   0xEF,
							   0xBE };
	const uint64_t expected = 0xBEEF;
	uint64_t result;

	(void) state; /* unused */

	print_array_raw( input, 8 );

	/* Unpack that big word we just wrote in */
	int err = UnpackUint64( input, 12, 32, eByteOrder_LSBFirst, &result );

	assert_int_equal( 0, err );
	assert_int_equal( expected, result );
}

void print_array_raw( const uint8_t *bytes, const int len )
{
	int idx;
	int bitoffset;

	printf( "Raw test array = " );

	for ( idx = 0; idx < len; idx++ )
	{
		printf("[");
		for ( bitoffset = 7; bitoffset >= 0; bitoffset-- )
		{
			printf( "%01u", 0x1 & (bytes[idx] >> bitoffset ) );
		}
		printf("]");

		printf("[%02x]", bytes[idx]);
		printf("\n");
	}


}






