/*lnodes.h*/

#include <stddef.h>
#include <stdlib.h>

typedef struct listnode
{
  void *dataptr;
  struct listnode *nextptr;
}
  LISTNODE;

LISTNODE *ln_create(void *dataprt, LISTNODE *nodeptr);
void ln_destroy(LISTNODE *nodeptr);
