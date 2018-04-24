#include <newt/newt.h>

#define NEWTP_CUSTOM_TYPE_MASK			0xc0000000
#define NEWTP_CUSTOM_TYPE_MASK_HANDLE	0x40000000
#define NEWTP_CUSTOM_TYPE_MASK_ENUM		0x80000000

#define NEWTP_IS_CUSTOM_TYPE(type)		(type & NEWTP_CUSTOM_TYPE_MASK)
#define NEWTP_IS_CUSTOM_HANDLE(type)	(type & NEWTP_CUTSOM_TYPE_MASK_HANDLE)
#define NEWTP_IS_CUSTOM_ENUM(type)		(type & NEWTP_CUTSOM_TYPE_MASK_ENUM)

#define NEWTP_CUSTOM_TYPE_INDEX(type)	(type | (~NEWTP_CUSTOM_TYPE_MASK))

struct NewtpFreeList_ {
	uint32_t*	data;
	uint32_t	size;
	uint32_t	capacity;
};
typedef struct NewtpFreeList_ NewtpFreeList;

NewtResult	newtpInitFreeList(NewtpFreeList* freeList);
void		newtpDestroyFreeList(NewtpFreeList* freeList);
int			newtpPopFreeList(NewtpFreeList* freeList, uint32_t* value);
NewtResult	newtpPushFreeList(NewtpFreeList* freeList, uint32_t value);

struct NewtpHandleType_ {
	char*				name;
	NewtType			parentType;
	NewtHandleCallback	callback;
};
typedef struct NewtpHandleType_ NewtpHandleType;

struct NewtpHandleTypeCollection_ {
	NewtpHandleType*	data;
	uint32_t			count;
	uint32_t			capacity;
};
typedef struct NewtpHandleTypeCollection_ NewtpHandleTypeCollection;

struct NewtpStrings_ {
	char**			data;
	uint8_t*		refcount;
	uint32_t		size;
	uint32_t		capacity;
	NewtpFreeList	freeList;
};
typedef struct NewtpStrings_ NewtpStrings;

struct NewtVirtualMachine_ {
	NewtpHandleTypeCollection	types;
	NewtpStrings				strings;
	uint64_t					regs[256];
};

NewtResult newtpInitVirtualMachineStrings(NewtpStrings* strings);
void       newtpDestroyVirtualMachineStrings(NewtpStrings* strings);