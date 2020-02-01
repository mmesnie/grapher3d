/*
 * Please see README for copying information.
 */

#include <math.h>
#include <curses.h>
#include <ctype.h>
#include <strings.h>
#define MAX_NUM_SCALARS 100

/*
void main() {
  double x = 2.0;
  double y = 2.0;
  double postfix2real(double, double , char *);

  printf("%lf + %lf = %lf\n", x, y, f(x, y, "xy+"));
  printf("%lf - %lf = %lf\n", x, y, f(x, y, "xy-"));
  printf("%lf * %lf = %lf\n", x, y, f(x, y, "xy*"));
  printf("%lf / %lf = %lf\n", x, y, f(x, y, "xy/"));
  printf("%lf ^ %lf = %lf\n", x, y, f(x, y, "xy^"));
  printf("sin(%lf) = %lf\n", x, f(x, y, "xs"));
  printf("cos(%lf) = %lf\n", x, f(x, y, "xc"));
  printf("exp(%lf) = %lf\n", x, f(x, y, "xe"));
  printf("log(%lf) = %lf\n", x, f(x, y, "xl"));
  printf("-(%lf) = %lf\n", x, f(x, y, "xn"));
  printf("abs(%lf) = %lf\n", x, f(x, y, "xa"));
  printf("sqrt(%lf) = %lf\n", x, f(x, y, "xq"));
}
*/

double postfix2real(double x, double y, char f[100])
{

  double char2double(char f[100], int *i); 
  double scalar_stack[MAX_NUM_SCALARS];
  int num_scalars=0;
  double a, b;
  double result; 
  int i;

  for (i=0; i<strlen(f); i++)
  {
    if (isdigit(f[i])) result = char2double(f, &i); 
    else switch (tolower(f[i]))
    {
      case 'x': result = x;
                break;
      case 'y': result = y;
                break;
      case '+': a = scalar_stack[num_scalars-1];
                num_scalars--;
                b = scalar_stack[num_scalars-1];
                num_scalars--;
                result = b + a;
                break;
      case '-': a = scalar_stack[num_scalars-1];
                num_scalars--;
                b = scalar_stack[num_scalars-1];
                num_scalars--;
                result = b - a;
                break;
      case '*': a = scalar_stack[num_scalars-1];
                num_scalars--;
                b = scalar_stack[num_scalars-1];
                num_scalars--;
                result = b * a;
                break;
      case '/': a = scalar_stack[num_scalars-1];
                num_scalars--;
                b = scalar_stack[num_scalars-1];
                num_scalars--;
                result = b / a;
                break;
      case 's': a = scalar_stack[num_scalars-1];  
                num_scalars--;
                result = sin(a);
                break;
      case 'c': a = scalar_stack[num_scalars-1];  
                num_scalars--;
                result = cos(a);
                break;
      case '^': a = scalar_stack[num_scalars-1];
                num_scalars--;
                b = scalar_stack[num_scalars-1];
                num_scalars--;
                result = pow(b,a);
                break;
      case 'e': a = scalar_stack[num_scalars-1];  
                num_scalars--;
                result = exp(a);
                break;
      case 'l': a = scalar_stack[num_scalars-1];  
                num_scalars--;
                if (a<=0) a=1;
                result = log(a);
                break;
      case 'n': a = scalar_stack[num_scalars-1];  
                num_scalars--;
                result = -a;
                break;
      case 'a': a = scalar_stack[num_scalars-1];  
                num_scalars--;
                result = fabs(a);
                break;
      case 'q': a = scalar_stack[num_scalars-1];  
                num_scalars--;
                if (a<0) {
                  result = 0.0;
                } else {
                  result = sqrt(a);
                } 
                break;
    }

    #ifdef DEBUG_POSTFIX
    printf("scalar_stack[%i] = %lf\n", num_scalars, result);
    #endif
    scalar_stack[num_scalars] = result;
    num_scalars++;
  }
  if (num_scalars > 1) printf("ERROR!!\n");
  return scalar_stack[0];
}

double char2double(char f[100], int *i)
{
  double x;
  sscanf(f+(*i), "%lf", &x);
  *i = strlen(f) - strlen(strchr(f+(*i), '#')+1) - 1; 
  /*
  printf("i in = %i\n", *i);
  printf("string = %s\n", f);
  printf("x = %lf\n", x);
  printf("the rest = %s\n", strchr(f+(*i), '#')+1);
  printf("length = %i\n", strlen(f));
  printf("i out = %i\n", *i);
  */
  return x;
}
