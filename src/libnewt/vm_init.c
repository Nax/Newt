#include <stdlib.h>
#include <newt/newt.h>

NEWT_EXPORTED NewtResult newtCreateVirtualMachine(NewtVirtualMachine** vm)
{
	NewtVirtualMachine* newVm;

	newVm = malloc(sizeof(*newVm));
	if (!newVm)
		return NEWT_ERROR_MEMORY;
	memset(newVm, 0, sizeof(*newVm));
	*vm = newVm;

	return NEWT_OK;
}

NEWT_EXPORTED NewtResult newtDestroyVirtualMachine(NewtVirtualMachine* vm)
{
	if (vm)
		free(vm);
	return NEWT_OK;
}