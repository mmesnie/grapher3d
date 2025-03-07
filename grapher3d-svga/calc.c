/*Calculate.c
 *Calculate.c is responsible for filling the array of three dimensional,
 *untransformed points.  It needs to know the domain over which to 
 *generate the surface, and these are passed here via x_min, x_max, y_min,
 *y_max.  Surfaces are generated using a collection of vertical and 
 *horizontal lines.  The points which determine these lines are stored in
 *the arrays h and v.
 */

#include "globals.h"
#include <math.h>

void calculate(double h[][max_points][3],double v[][max_points][3],
               double zoom, int points, double x_min, double x_max,  
               double y_min, double y_max, char postfix[100])
{
  /*f evaluates the postfix expression at each point (x,y) that is passed
   *to it.  The returned value is f(x,y)=z
   */
  double f(double x, double y, char function[100]); 
  double x_inc; /*step between x points*/
  double y_inc; /*step between y points*/
  int i,j; 
  double x = x_min;
  double y = y_min;
  x_inc = (x_max-x_min)/(points-1);
  y_inc = (y_max-y_min)/(points-1);
  /*Let's make the horizontal lines*/
  /*i counts the number of lines, j counts the number of points on 
   *each line*/
  for (i=0;i<points;i++)
    {
      for (j=0;j<points;j++) 
        {
          *(*(*(h+i)+j)+0) = x;
          *(*(*(h+i)+j)+1) = y;
          *(*(*(h+i)+j)+2) = zoom*f(x,y,postfix);
          x += x_inc;
        }
      x = x_min;
      y += y_inc;
    }
  x = x_min;
  y = y_min;
  /*Now let's make the vertical lines.  Again, i counts the number of lines
   *and j counts the number of points on each line*/
  for (i=0;i<points;i++)
    {
      for (j=0;j<points;j++)
        {
          *(*(*(v+i)+j)+0) = x;
          *(*(*(v+i)+j)+1) = y;
          *(*(*(v+i)+j)+2) = zoom*f(x,y,postfix);
          y += y_inc;
        }
      y = y_min;
      x += x_inc;
    }
}





