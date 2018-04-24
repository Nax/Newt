#include <stdlib.h>
#include <string.h>
#include "newt_priv.h"

NEWT_EXPORTED NewtResult newtCreateVirtualMachine(NewtVirtualMachine** vm)
{
	NewtVirtualMachine* newVm;
	NewtResult ret;

	newVm = malloc(sizeof(*newVm));
	if (!newVm)
		return NEWT_ERROR_OUT_OF_MEMORY;
	memset(newVm, 0, sizeof(*newVm));
	ret = newtpInitVirtualMachineStrings(&newVm->strings);
	if (ret != NEWT_OK)
		goto err_string_init;
	*vm = newVm;

	return NEWT_OK;

err_string_init:
	free(newVm);
	return ret;
}

NEWT_EXPORTED NewtResult newtDestroyVirtualMachine(NewtVirtualMachine* vm)
{
	if (vm)
	{
		newtpDestroyVirtualMachineStrings(&vm->strings);
		free(vm);
	}
	return NEWT_OK;
}