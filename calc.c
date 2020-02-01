/*
 * Please see README for copying information. 
 */

#include "globals.h"
#include <math.h>

void calculate(double h[][3], double zoom, int points, 
               double x_min, double x_max,  double y_min, double y_max, 
               char postfix[100])
{
  double postfix2real(double x, double y, char function[100]); 
  double x_inc; /*step between x points*/
  double y_inc; /*step between y points*/
  int i,j; 
  double x = x_min;
  double y = y_min;
  x_inc = (x_max-x_min)/(points-1);
  y_inc = (y_max-y_min)/(points-1);

  for (i=0;i<points;i++) {
    for (j=0;j<points;j++) {
      h[i*points+j][0] = x;
      h[i*points+j][1] = y;
      h[i*points+j][2] = zoom*postfix2real(x,y,postfix);
      x += x_inc;
    }
    x = x_min;
    y += y_inc;
  }
}
