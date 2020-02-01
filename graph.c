/*
 * Please see README for copying information.
 */

#include "globals.h"
#include <stdio.h>

void graph(double b[][3], double a[][2], double m, int points, double centerx, 
           double centery, FILE **output, char *color, int type)
{
  int i,j;
  double xpa1,ypa1,xpa2,xpa3,xpa4,ypa2,ypa3,ypa4;

  switch (type) {

  case FRAME:

    for (i=0;i<points;i++) { 
      for (j=0;j<points-1;j++) {
        xpa1 =  a[i*points+j][0]*m+centerx;
        ypa1 =  centery-a[i*points+j][1]*m;
        xpa2 =  a[i*points+j+1][0]*m+centerx;
        ypa2 =  centery-a[i*points+j+1][1]*m;
        fprintf(*output,".canvas create line %lf %lf %lf %lf -fill %s\n", 
                xpa1, ypa1, xpa2, ypa2, color);
      }
    }

    for (j=0;j<points;j++) {
      for (i=0;i<points-1;i++) { 
        xpa1 =  a[i*points+j][0]*m+centerx;
        ypa1 =  centery-a[i*points+j][1]*m;
        xpa2 =  a[(i+1)*points+j][0]*m+centerx;
        ypa2 =  centery-a[(i+1)*points+j][1]*m;
        fprintf(*output,".canvas create line %lf %lf %lf %lf -fill %s\n", 
                xpa1, ypa1, xpa2, ypa2, color);
      }
    }
    break;
 
  case POLYGONS: 

    for (i=0;i<points-1;i++) { 
      for (j=0;j<points-1;j++) {

/*
        printf("%i %i x = %lf\n", i*points+j, 0, a[i*points+j][0]);
        printf("%i %i y = %lf\n", i*points+j, 1, a[i*points+j][1]);
        printf("%i %i x = %lf\n", i*points+j+1, 0, a[i*points+j+1][0]);
        printf("%i %i y = %lf\n", i*points+j+1, 1, a[i*points+j+1][1]);
        printf("%i %i x = %lf\n", (i+1)*points+j+1, 0, a[(i+1)*points+j+1][0]);
        printf("%i %i y = %lf\n", (i+1)*points+j+1, 1, a[(i+1)*points+j+1][1]);
        printf("%i %i x = %lf\n", (i+1)*points+j, 0, a[(i+1)*points+j][0]);
        printf("%i %i y = %lf\n", (i+1)*points+j, 1, a[(i+1)*points+j][1]);
*/

        xpa1 =  centerx + a[i*points+j][0]*m;
        ypa1 =  centery - a[i*points+j][1]*m;
        xpa2 =  centerx + a[i*points+j+1][0]*m;
        ypa2 =  centery-a[i*points+j+1][1]*m;
        xpa3 =  centerx + a[(i+1)*points+j+1][0]*m;
        ypa3 =  centery - a[(i+1)*points+j+1][1]*m;
        xpa4 =  centerx + a[(i+1)*points+j][0]*m;
        ypa4 =  centery - a[(i+1)*points+j][1]*m;

        fprintf(*output,".canvas create polygon %lf %lf %lf %lf %lf %lf %lf %lf -fill %s -outline black\n", xpa1, ypa1, xpa2, ypa2, xpa3, ypa3, xpa4, ypa4, color);

      }
    }
    break;
  }
}
