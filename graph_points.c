/*
 * Please see README for copying information.
 */

#include "globals.h"
#include <stdio.h>

void graph_points(double a[][2], int points, double centerx, double centery,
           FILE **output, char *color, char*line_color, double zoom, boolean connectDots)
{
  int i;
  double xp,yp;
  double xp2,yp2;


  for (i=0;i<points-1;i++) {
    xp =  a[i][0]*zoom+centerx;
    yp =  centery-a[i][1]*zoom;
    xp2 =  a[i+1][0]*zoom+centerx;
    yp2 =  centery-a[i+1][1]*zoom;
    fprintf(*output,".canvas create rectangle %lf %lf %lf %lf -fill %s\n", xp-2, yp-2, xp+2, yp+2, color);
    if (connectDots) {
    fprintf(*output,".canvas create line %lf %lf %lf %lf -fill %s\n", xp, yp, xp2, yp2, line_color);
    }
  }
  xp =  a[points-1][0]*zoom+centerx;
  yp =  centery-a[points-1][1]*zoom;
  fprintf(*output,".canvas create rectangle %lf %lf %lf %lf -fill %s\n", xp-2, yp-2, xp+2, yp+2, color);
}
