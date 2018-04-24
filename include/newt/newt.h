#ifndef INCLUDED_NEWT_NEWT_H
#define INCLUDED_NEWT_NEWT_H

#include <stdint.h>
#include <newt/config.h>

#if NEWT_CONFIG_POINTER_SIZE > 8
# error "Newt does not support address spaces larger than 64 bits"
#endif

#if defined(__x86_64__) || defined(WIN64) || defined(_WIN64)
# define NEWT_BITS		64
# define NEWT_64_BITS	1
#elif defined(__i386__) || defined(WIN32) || defined(_WIN32)
# define NEWT_BITS		32
# define NEWT_32_BITS	1
#else
# error "Newt is not supported on your platform"
#endif

#define NEWT_VERSION_MAJOR			0
#define NEWT_VERSION_MINOR			1
#define NEWT_VERSION_PATCH			0
#define	NEWT_VERSION_PRERELEASE		"alpha1"

#if defined(__cplusplus)
# define NEWT_begin_	extern "C" {
# define NEWT_end_		}
#else
# define NEWT_begin_
# define NEWT_end_
#endif

#if (defined(WIN32) || defined(_WIN32)) && (!defined(NEWT_STATIC) || NEWT_STATIC==0)
# define NEWT_EXPORTED	__declspec(dllexport)
# if defined(NEWT_EXPORT_DLL) && NEWT_EXPORT_DLL > 0
#  define NEWT_IMPORTED	__declspec(dllexport)
# else
#  define NEWT_IMPORTED	__declspec(dllimport)
# endif
#else
# define NEWT_EXPORTED
# define NEWT_IMPORTED
#endif

enum NewtResult_ {
	NEWT_OK							= 0,
	NEWT_ERROR_OUT_OF_MEMORY		= 1,
	NEWT_ERROR_INVALID_OPERATION	= 2,
	NEWT_ERROR_INVALID_VALUE		= 3
};
typedef enum NewtResult_ NewtResult;

#define	NEWT_TYPE_NONE		0
#define NEWT_TYPE_BOOLEAN	1
#define NEWT_TYPE_INTEGER	2
#define NEWT_TYPE_REAL      3
#define NEWT_TYPE_STRING	4
#define NEWT_TYPE_ARRAY		5
#define NEWT_TYPE_TABLE		6
#define NEWT_TYPE_FUNCTION	7
#define NEWT_TYPE_HANDLE	8

typedef uint32_t NewtType;

union NewtValue_ {
	int			boolean;
	uint64_t	integer;
	float		real;
	uint32_t	handle;
	uint32_t	string;
};
typedef union NewtValue_ NewtValue;

struct NewtVirtualMachine_;
typedef struct NewtVirtualMachine_ NewtVirtualMachine;

typedef void (*NewtHandleCallback)(void*);

NEWT_begin_

/* handle.c */
NEWT_IMPORTED NewtResult	newtRegisterHandleType(NewtVirtualMachine* vm, const char* name, NewtType parentType, NewtHandleCallback callback, NewtType* type);
NEWT_IMPORTED NewtResult	newtRegisterEnumType(NewtVirtualMachine* vm, const char* name, NewtType* type);
NEWT_IMPORTED NewtResult	newtRegisterEnumValue(NewtVirtualMachine* vm, NewtType type, uint64_t value);

/* string.c */
NEWT_IMPORTED NewtResult	newtCreateString(NewtVirtualMachine* vm, const char* str, NewtValue* value);
NEWT_IMPORTED NewtResult	newtAcquireString(NewtVirtualMachine* vm, NewtValue value);
NEWT_IMPORTED NewtResult	newtReleaseString(NewtVirtualMachine* vm, NewtValue value);
NEWT_IMPORTED NewtResult	newtGetString(NewtVirtualMachine* vm, NewtValue value, const char** dst);

/* value.c */
NEWT_IMPORTED NewtValue		newtNull();
NEWT_IMPORTED NewtValue		newtBoolean(int boolean);
NEWT_IMPORTED NewtValue		newtInteger(uint64_t integer);
NEWT_IMPORTED NewtValue		newtReal(float real);

/* vm_init.c */
NEWT_IMPORTED NewtResult 	newtCreateVirtualMachine(NewtVirtualMachine** vm);
NEWT_IMPORTED NewtResult	newtDestroyVirtualMachine(NewtVirtualMachine* vm);

NEWT_end_

#endif