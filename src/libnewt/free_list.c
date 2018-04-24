#include <stdlib.h>
#include "newt_priv.h"

NewtResult newtpInitFreeList(NewtpFreeList* freeList)
{
	static const int defaultCapacity = 8;

	if (!(freeList->data = malloc(sizeof(uint32_t) * defaultCapacity)))
		return NEWT_ERROR_OUT_OF_MEMORY;
	freeList->capacity = defaultCapacity;
	freeList->size = 0;
	return NEWT_OK;
}

void newtpDestroyFreeList(NewtpFreeList* freeList)
{
	free(freeList->data);
}

int newtpPopFreeList(NewtpFreeList* freeList, uint32_t* value)
{
	if (freeList->size == 0)
		return 0;
	*value = freeList->data[--freeList->size];
	return 1;
}

NewtResult newtpPushFreeList(NewtpFreeList* freeList, uint32_t value)
{
	uint32_t newCapacity;
	uint32_t* newData;

	if (freeList->capacity == freeList->size)
	{
		newCapacity = freeList->capacity + freeList->capacity / 2;
		newData = realloc(freeList->data, sizeof(uint32_t) * newCapacity);
		if (!newData)
			return NEWT_ERROR_OUT_OF_MEMORY;
		freeList->capacity = newCapacity;
		freeList->data = newData;
	}
	freeList->data[freeList->size++] = value;
	return NEWT_OK;
}