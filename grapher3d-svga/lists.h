/*lists.h*/

#include "lnodes.h"
#include "ptrfuncs.h"

typedef LISTNODE *LIST;

LIST list_create(void);
void list_traverse(LIST l, ACT_FPTR action);
LIST list_insert(LIST l,void *dataptr, CMP_FPTR cmp);
void list_destroy(LIST l);
LIST list_update(LIST l, void *dataptr, CMP_FPTR cmp, UPD_FPTR upd);
