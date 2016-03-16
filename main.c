#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "bit_pack.h"

void print_array_raw( const uint8_t *bytes, int len );
static void test_unpack_uint64_be_aligned( void **state );
static void test_unpack_uint64_le_aligned( void **state );
static void test_unpack_uint64_be_unaligned( void **state );
static void test_unpack_uint64_le_unaligned( void **state );

struct test
{
	uint64_t padding  : 3;
	uint64_t element1 : 32;
};

int main(void)
{
	struct test teststruct = { 0, 0xBEEFFACE };
	printf( "Printing a example of how a 32 bit field is packed using a C bit packed structure on your system:\n" );
	print_array_raw( (uint8_t*)&teststruct, 8 );

	const struct UnitTest tests[] =
	{
		unit_test( test_unpack_uint64_be_aligned ),
		unit_test( test_unpack_uint64_le_aligned ),
		unit_test( test_unpack_uint64_be_unaligned ),
		unit_test( test_unpack_uint64_le_unaligned ),
	};
	return run_tests(tests);
}

static void test_unpack_uint64_be_aligned( void **state )
{
	const uint8_t input[8] = { 0x00,
							   0xBE,
							   0xEF,
							   0xFA,
							   0xCE,
							   0x00,
							   0x00,
							   0x00 };
	const uint64_t expected = 0xBEEFFACE;
	uint64_t result;

	(void) state; /* unused */

	print_array_raw( input, 8 );

	/* Unpack that big word we just wrote in */
	int err = unpack_uint64_be( input, sizeof( input ), 24, 32, &result );

	assert_int_equal( 0, err );
	assert_int_equal( expected, result );
}

static void test_unpack_uint64_le_aligned( void **state )
{
	const uint8_t input[8] = { 0x00,
							   0xCE,
							   0xFA,
							   0xEF,
							   0xBE,
							   0x00,
							   0x00,
							   0x00 };
	const uint64_t expected = 0xBEEFFACE;
	uint64_t result;

	(void) state; /* unused */

	print_array_raw( input, 8 );

	/* Unpack that big word we just wrote in */
	int err = unpack_uint64_le( input, sizeof( input ), 8, 32, &result );

	assert_int_equal( 0, err );
	assert_int_equal( expected, result );
}

static void test_unpack_uint64_be_unaligned( void **state )
{
	const uint8_t input[8] = { 0x00,
							   0x0B,
							   0xEE,
							   0xFF,
							   0xAC,
							   0xE0,
							   0x00,
							   0x00 };
	const uint64_t expected = 0xBEEFFACE;
	uint64_t result;
	int err;

	(void) state; /* unused */

	print_array_raw( input, 8 );

	/* Unpack that big word we just wrote in */
	err = unpack_uint64_be( input, sizeof( input ), 20, 32, &result );

	assert_int_equal( 0, err );
	assert_int_equal( expected, result );

	/* Unpack that big word we just wrote in */
	err = unpack_uint64_be_rev( input, sizeof( input ), 12, 32, &result );

	assert_int_equal( 0, err );
	assert_int_equal( expected, result );
}

static void test_unpack_uint64_le_unaligned( void **state )
{
	const uint8_t input[8] = { 0x70,
							   0xd6,
							   0x7f,
							   0xf7,
							   0xfd,
							   0x7f,
							   0x00,
							   0x00 };
	const uint64_t expected = 0xBEEFFACE;
	uint64_t result;

	(void) state; /* unused */

	print_array_raw( input, 8 );

	/* Unpack that big word we just wrote in */
	int err = unpack_uint64_le( input, sizeof( input ), 3, 32, &result );

	assert_int_equal( 0, err );
	assert_int_equal( expected, result );
}

void print_array_raw( const uint8_t *bytes, const int len )
{
	int idx;
	int bitoffset;

	//printf( "Raw test array:\n" );

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
