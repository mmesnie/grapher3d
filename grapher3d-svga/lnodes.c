/* Lnodes.c
 * Manage linked list nodes.
 * ln_create - create new list node.
 * ln_destroy - free space used by existing node.
 */

#include "lnodes.h"

LISTNODE *ln_create(void *dataptr, LISTNODE *nodeptr)
{
  LISTNODE *nptr = malloc(sizeof(LISTNODE));

  if (nptr!=NULL)
  {
    nptr->dataptr = dataptr;
    nptr->nextptr = nodeptr;
  }
  return nptr;
}

void ln_destroy(LISTNODE *nptr)
{
  free(nptr);
}
