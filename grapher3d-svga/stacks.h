/*stacks.h*/

#include "lists.h"

typedef LISTNODE *STACK;

#define stack_create() NULL            /* create an empty stack */
#define stack_empty(s) ((s) == NULL)    /* is stack empty? */
#define stack_top(s)   ((s) ->dataptr) /* first item on stack */

STACK stack_push(STACK s, void *dataptr);
STACK stack_pop(STACK s);
