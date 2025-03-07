/* Stacks.c
 * Stack operations
 */

#include "stacks.h"   /* STACK type and prototypes */

STACK stack_push(STACK s, void *dptr)
{
  return ln_create(dptr, s);
}

STACK stack_pop(STACK s)
{
  LISTNODE *topptr = s;
  LISTNODE *secondptr = topptr->nextptr;

  ln_destroy(topptr);
  return secondptr;
}
