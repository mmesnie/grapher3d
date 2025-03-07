/*Transform.c
 *Transform.c takes as input the set of three dimensional points and 
 *projects them into two dimensions.  This functions performs nothing
 *more than simple matrix multiplication where x, y, and z are the 
 *transformation matrices and xr, yr, and zr and the x, y, and z
 *rotations in radians. The transformed points are returned in the arrays
 *a2 and b2.
 */

#include "globals.h"
#include <math.h>

void transform(double a[][max_points][3],double a2[][max_points][2],
               double b[][max_points][3],double b2[][max_points][2],
               double xr,double yr,double zr, int points)
{
  double x[3][3];
  double y[3][3];
  double z[3][3];
  double t[3][3];
  double temp[3][3];
  int h,i,j,k;
  double sumt,suma,sumb;

  *(*(x+0)+0) = 1;
  *(*(x+0)+1) = 0;
  *(*(x+0)+2) = 0;
  *(*(x+1)+0) = 0;
  *(*(x+1)+1) = cos(xr);
  *(*(x+1)+2) = -sin(xr);
  *(*(x+2)+0) = 0;
  *(*(x+2)+1) = sin(xr);
  *(*(x+2)+2) = cos(xr);
  *(*(y+0)+0) = cos(yr);
  *(*(y+0)+1) = 0;
  *(*(y+0)+2) = sin(yr);
  *(*(y+1)+0) = 0;
  *(*(y+1)+1) = 1;
  *(*(y+1)+2) = 0;
  *(*(y+2)+0) = -sin(yr);
  *(*(y+2)+1) = 0;
  *(*(y+2)+2) = cos(yr);
  *(*(z+0)+0) = cos(zr);
  *(*(z+0)+1) = -sin(zr);
  *(*(z+0)+2) = 0;
  *(*(z+1)+0) = sin(zr);
  *(*(z+1)+1) = cos(zr);
  *(*(z+1)+2) = 0;
  *(*(z+2)+0) = 0;
  *(*(z+2)+1) = 0;
  *(*(z+2)+2) = 1;
  for (i=0;i<3;i++)
    for (j=0;j<3;j++)
    {
      for(sumt=0,k=0;k<3;k++)
        sumt+= *(*(y+i)+k) * *(*(x+k)+j);  
      *(*(temp+i)+j) = sumt;
    }
  for (i=0;i<3;i++)
    for (j=0;j<3;j++)
    {
      for(sumt=0,k=0;k<3;k++)
        sumt+= *(*(z+i)+k) * *(*(temp+k)+j);
      *(*(t+i)+j) = sumt;
    }
  for (h=0;h<points;h++)
    for (i=0;i<points;i++)
      for(j=0;j<2;j++)
      {
        for(suma=0,sumb=0,k=0;k<3;k++)
          suma += *(*(*(a+h)+i)+k) * *(*(t+k)+j),
          sumb += *(*(*(b+h)+i)+k) * *(*(t+k)+j);
        *(*(*(a2+h)+i)+j) = suma;
        *(*(*(b2+h)+i)+j) = sumb;
      }  
}
