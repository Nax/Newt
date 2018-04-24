#include <stdlib.h>
#include <string.h>
#include "newt_priv.h"

NEWT_begin_

NEWT_EXPORTED NewtValue newtNull()
{
	NewtValue value;

	memset(&value, 0, sizeof(value));
	return value;
}

NEWT_EXPORTED NewtValue newtBoolean(int boolean)
{
	NewtValue value;

	memset(&value, 0, sizeof(value));
	value.boolean = boolean ? 1 : 0;
	return value;
}

NEWT_EXPORTED NewtValue newtInteger(uint64_t integer)
{
	NewtValue value;

	/* No need to memset because the integer is 64 bits */
	value.integer = integer;
	return value;
}

NEWT_EXPORTED NewtValue newtReal(float real)
{
	NewtValue value;

	memset(&value, 0, sizeof(value));
	value.real = real;
	return value;
}

NEWT_end_