#include <stdlib.h>
#include <string.h>
#include "newt_priv.h"

NEWT_EXPORTED NewtResult newtCreateString(NewtVirtualMachine* vm, const char* str, NewtValue* value)
{
	size_t len;
	char* copiedStr;
	uint32_t strSlot;
	uint32_t newCapacity;
	char** newData;
	uint8_t* newRefcount;

	if (str == NULL)
	{
		memset(value, 0, sizeof(*value));
		return NEWT_OK;
	}

	len = strlen(str);
	copiedStr = malloc(len + 1);
	if (copiedStr == NULL)
		goto oom_copy;
	memcpy(copiedStr, str, len);
	copiedStr[len] = 0;

	if (newtpPopFreeList(&vm->strings.freeList, &strSlot))
	{
		vm->strings.data[strSlot] = copiedStr;
		memset(value, 0, sizeof(*value));
		value->string = strSlot;
		return NEWT_OK;
	}

	if (vm->strings.size == vm->strings.capacity)
	{
		newCapacity = vm->strings.capacity + vm->strings.capacity / 2;
		newData = realloc(vm->strings.data, sizeof(char*) * newCapacity);
		if (newData == NULL)
			goto oom_resize;
		vm->strings.data = newData;
		newRefcount = realloc(vm->strings.refcount, sizeof(uint8_t) * newCapacity);
		if (newRefcount == NULL)
			goto oom_resize;
		vm->strings.refcount = newRefcount;
		vm->strings.capacity = newCapacity;
	}

	strSlot = vm->strings.size++;
	vm->strings.data[strSlot] = copiedStr;
	vm->strings.refcount[strSlot] = 0;
	memset(value, 0, sizeof(*value));
	value->string = strSlot;
	return NEWT_OK;

oom_resize:
	free(copiedStr);
oom_copy:
	return NEWT_ERROR_OUT_OF_MEMORY;
}

NEWT_EXPORTED NewtResult newtAcquireString(NewtVirtualMachine* vm, NewtValue value)
{
	if (value.string == 0)
		return NEWT_OK;
	if (value.string >= vm->strings.size)
		return NEWT_ERROR_INVALID_VALUE;
	if (vm->strings.data[value.string] == NULL)
		return NEWT_ERROR_INVALID_VALUE;
	if (vm->strings.refcount[value.string] == 255)
		return NEWT_ERROR_INVALID_OPERATION;
	vm->strings.refcount[value.string]++;
	return NEWT_OK;
}

NEWT_EXPORTED NewtResult newtReleaseString(NewtVirtualMachine* vm, NewtValue value)
{
	NewtResult ret;

	if (value.string == 0)
		return NEWT_OK;
	if (value.string >= vm->strings.size)
		return NEWT_ERROR_INVALID_VALUE;
	if (vm->strings.data[value.string] == NULL)
		return NEWT_ERROR_INVALID_VALUE;
	if (vm->strings.refcount[value.string] == 0)
	{
		ret = newtpPushFreeList(&vm->strings.freeList, value.string);
		if (ret != NEWT_OK)
			return ret;
		free(vm->strings.data[value.string]);
		vm->strings.data[value.string] = NULL;
	}
	else
		vm->strings.refcount[value.string]--;
	return NEWT_OK;
}

NEWT_EXPORTED NewtResult newtGetString(NewtVirtualMachine* vm, NewtValue value, const char** dst)
{
	char* str;

	if (value.string == 0)
	{
		*dst = NULL;
		return NEWT_OK;
	}
	if (value.string >= vm->strings.size)
		return NEWT_ERROR_INVALID_VALUE;
	str = vm->strings.data[value.string];
	if (!str)
		return NEWT_ERROR_INVALID_VALUE;
	*dst = str;
	return NEWT_OK;
}

NewtResult newtpInitVirtualMachineStrings(NewtpStrings* strings)
{
	if (!(strings->data = malloc(sizeof(char*) * NEWTP_ARRAY_DEFAULT_CAPACITY)))
		goto oom_data;
	if (!(strings->refcount = malloc(sizeof(uint8_t) * NEWTP_ARRAY_DEFAULT_CAPACITY)))
		goto oom_refcount;
	if (newtpInitFreeList(&strings->freeList) != NEWT_OK)
		goto oom_free_list;

	strings->capacity = NEWTP_ARRAY_DEFAULT_CAPACITY;
	strings->size = 1;
	strings->data[0] = NULL;
	strings->refcount[0] = 0;
	return NEWT_OK;

oom_free_list:
	free(strings->refcount);
oom_refcount:
	free(strings->data);
oom_data:
	return NEWT_ERROR_OUT_OF_MEMORY;
}

void newtpDestroyVirtualMachineStrings(NewtpStrings* strings)
{
	for (uint32_t i = 0; i < strings->size; ++i)
		free(strings->data[i]);
	free(strings->data);
	free(strings->refcount);
	newtpDestroyFreeList(&strings->freeList);
}
