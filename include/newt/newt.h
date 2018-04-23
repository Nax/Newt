#ifndef INCLUDED_NEWT_NEWT_H
#define INCLUDED_NEWT_NEWT_H

#include <stdint.h>

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
	NEWT_OK = 0,
	NEWT_ERROR_MEMORY = 1
};
typedef enum NewtResult_ NewtResult;

enum NewtType_ {
	NEWT_TYPE_BOOLEAN  = 1,
	NEWT_TYPE_INTEGER  = 2,
	NEWT_TYPE_REAL     = 3,
	NEWT_TYPE_STRING   = 4,
	NEWT_TYPE_ARRAY    = 5,
	NEWT_TYPE_TABLE    = 6,
	NEWT_TYPE_FUNCTION = 7,
	NEWT_TYPE_HANDLE   = 8
};
typedef enum NewtType_ NewtType;

struct NewtVirtualMachine_ {
	uint64_t	regs[256];
};
typedef struct NewtVirtualMachine_ NewtVirtualMachine;

NEWT_begin_
NEWT_IMPORTED NewtResult 	newtCreateVirtualMachine(NewtVirtualMachine** vm);
NEWT_IMPORTED NewtResult	newtDestroyVirtualMachine(NewtVirtualMachine* vm);
NEWT_end_

#endif