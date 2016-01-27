#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "bit_twiddle.h"

void print_array_raw( const uint8_t *bytes, int len );
static void test_unpack_uint64_bigendian_aligned( void **state );
static void test_unpack_uint64_littleendian_aligned( void **state );

int main(void)
{
	const struct CMUnitTest tests[] =
	{
		cmocka_unit_test( test_unpack_uint64_bigendian_aligned ),
		cmocka_unit_test( test_unpack_uint64_littleendian_aligned ),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}

static void test_unpack_uint64_bigendian_aligned( void **state )
{
	const uint8_t input[8] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };
	const uint64_t expected = 0x0123456789ABCDEF;
	uint64_t result;

	(void) state; /* unused */

	print_array_raw( input, 8 );

	/* Unpack that big word we just wrote in */
	int err = UnpackUint64( input, 0, 64, eByteOrder_MSBFirst, &result );

	assert_int_equal( 0, err );
	assert_int_equal( result, expected );
}

static void test_unpack_uint64_littleendian_aligned( void **state )
{
	const uint8_t input[8] = { 0xEF, 0xCD, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01 };
	const uint64_t expected = 0x0123456789ABCDEF;
	uint64_t result;

	(void) state; /* unused */

	print_array_raw( input, 8 );

	/* Unpack that big word we just wrote in */
	int err = UnpackUint64( input, 0, 64, eByteOrder_MSBLast, &result );

	assert_int_equal( 0, err );
	assert_int_equal( result, expected );
}

void print_array_raw( const uint8_t *bytes, const int len )
{
	int idx;

	printf( "Raw test array = " );

	for ( idx = 0; idx < len; idx++ )
	{
		printf("[%02x]", bytes[idx]);
	}

	printf("\n");
}






