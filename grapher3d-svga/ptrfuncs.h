/*ptrfuncts.h*/

#if !defined(POINTER_TYPEDEFS)
#define POINTER_TYPEDEFS

enum status {UPDATE, CREATE};

typedef int (*CMP_FPTR) (const void *, const void *);
typedef void (*ACT_FPTR) (void *);
typedef void *(*UPD_FPTR) (void *, enum status);

#endif
