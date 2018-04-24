#include <stdlib.h>  
#include <stdio.h>
#include <newt/newt.h>

int main()
{
	NewtVirtualMachine* vm;
	NewtValue str[3];
	char* tmp;

	if (newtCreateVirtualMachine(&vm) != NEWT_OK)
	{
		puts("Error creating virtual machine");
		return 1;
	}
	if (newtCreateString(vm, "foo", &str[0]) != NEWT_OK)
	{
		puts("Error creating str0");
		return 1;
	}
	if (newtCreateString(vm, "bar", &str[1]) != NEWT_OK)
	{
		puts("Error creating str1");
		return 1;
	}
	newtReleaseString(vm, str[1]);
	if (newtCreateString(vm, "baz", &str[2]) != NEWT_OK)
	{
		puts("Error creating str2");
		return 1;
	}
	if (newtGetString(vm, str[0], &tmp) != NEWT_OK)
	{
		puts("Error fetching str0");
		return 1;
	}
	puts(tmp);
	if (newtGetString(vm, str[2], &tmp) != NEWT_OK)
	{
		puts("Error fetching str2");
		return 1;
	}
	puts(tmp);
	newtDestroyVirtualMachine(vm);
	return 0;
}