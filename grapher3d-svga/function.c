/*Function.c
 *Function.c is responsible for the evaluation of the postfix expression
 *stored as an array of characters f.  This function is called by 
 *calculate.c once for every point (x,y) in the domain.  The method
 *of evaluation follows a standard postfix evaluation algorithm.
 */


#include <math.h>
#include "stacks.h"
#include <curses.h>
#include <ctype.h>
#include <string.h>

double f(double x, double y, char f[100])
{
  /*number converts a character string into an integer*/
  double number(char f[100], int *i); 
  STACK s = stack_create(); /*number stack for operands*/
  double *dptr;
  int i;
  double a, b;

  for (i=0; i<strlen(f); i++)
  {
    dptr = malloc(sizeof(double));
    if (isdigit(*(f+i))) *dptr = number(f, &i); 
    else switch (tolower(*(f+i)))
    {
      case 'x': *dptr = x;
                break;
      case 'y': *dptr = y;
                break;
      case '+': a = *((double *) stack_top(s));
                s = stack_pop(s);
                b = *((double *) stack_top(s));
                s = stack_pop(s);
                *dptr = b + a;
                break;
      case '-': a = *((double *) stack_top(s));
                s = stack_pop(s);
                b = *((double *) stack_top(s));
                s = stack_pop(s);
                *dptr = b - a;
                break;
      case '*': a = *((double *) stack_top(s));
                s = stack_pop(s);
                b = *((double *) stack_top(s));
                s = stack_pop(s);
                *dptr = b*a;
                break;
      case '/': a = *((double *) stack_top(s));
                s = stack_pop(s);
                b = *((double *) stack_top(s));
                s = stack_pop(s);
                if (b!=0) *dptr = b/a;
                else *dptr = a/(b+0.0000000000001);
                break;
      case 's': a = *((double *) stack_top(s));  
                s = stack_pop(s); 
                *dptr = sin(a);
                break;
      case 'c': a = *((double *) stack_top(s));  
                s = stack_pop(s); 
                *dptr = cos(a);
                break;
      case '^': a = *((double *) stack_top(s));
                s = stack_pop(s);
                b = *((double *) stack_top(s));
                s = stack_pop(s);
                *dptr = pow(b,a);
                break;
      case 'e': a = *((double *) stack_top(s));
                s = stack_pop(s);
                *dptr = exp(a);
                break; 
      case 'l': a = *((double *) stack_top(s));
                s = stack_pop(s);
                if (a<=0) a=1;
                *dptr = log(a);
                break;     
      case 'n': a = *((double *) stack_top(s));
                s = stack_pop(s);
                *dptr = -a;
                break; 
    }
    s = stack_push(s, dptr); /*pushing a number on the stack, either
                              *an integer, the result of a binary operation 
                              *or the result of a unary operation*/
  }
  return *((double *) stack_top(s)); /*There should only be one element
                                      *in the stack if the postfix
                                      *expression was valid*/
}

double number(char f[100], int *i)
{
int c, j = 0;
double sum = 0;
char number_string[100];

while(isdigit(*(f+(*i))))
  *(number_string+(j++)) = *(f+((*i)++));
*(number_string+j) = '\0';
for (c=0; c<j; c++)
  sum += pow(10,c)*(*(number_string+j-1-c) - '0');
(*i)--;
return sum;
}
