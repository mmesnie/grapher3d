/*
 * Please see README for copying information. 
 */

#include "globals.h"
#include <math.h>

void transform(double a[][3],double a2[][2], double xr,double yr,
               double zr, int points)
{
  double x[3][3];
  double y[3][3];
  double z[3][3];
  double t[3][3];
  double temp[3][3];
  int i,j,k;
  double sum;

  x[0][0] = 1; x[0][1] = 0;       x[0][2] =  0;
  x[1][0] = 0; x[1][1] = cos(xr); x[1][2] = -sin(xr);
  x[2][0] = 0; x[2][1] = sin(xr); x[2][2] =  cos(xr);

  y[0][0] =  cos(yr); y[0][1] = 0; y[0][2] = sin(yr);
  y[1][0] =  0;       y[1][1] = 1; y[1][2] = 0;
  y[2][0] = -sin(yr); y[2][1] = 0; y[2][2] = cos(yr);

  z[0][0] = cos(zr); z[0][1] = -sin(zr); z[0][2] = 0;
  z[1][0] = sin(zr); z[1][1] =  cos(zr); z[1][2] = 0;
  z[2][0] = 0;       z[2][1] =  0;       z[2][2] = 1;

  for (i=0;i<3;i++) {
    for (j=0;j<3;j++) {
      for(sum=0,k=0;k<3;k++) { 
        sum += y[i][k] * x[k][j];  
      }
      temp[i][j] = sum;
    }
  }
  for (i=0;i<3;i++) {
    for (j=0;j<3;j++) {
      for(sum=0,k=0;k<3;k++) {
        sum += z[i][k] * temp[k][j];
      }
      t[i][j] = sum;
    }
  }
  for (i=0;i<points;i++) {
    for(j=0;j<2;j++) {
      for(sum=0,k=0;k<3;k++) {
        sum += a[i][k] * t[k][j];
      }
      a2[i][j] = sum;
    }  
  }
}
