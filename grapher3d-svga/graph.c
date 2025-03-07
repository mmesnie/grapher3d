/*Graph.c
 *This is where all the fun happens.  Graph.c is called once the three
 *dimensional points have been projected into two dimensions and are then
 *ready to be plotted.  It takes as input the horizontal and vertical 
 *lines stored in 'a' and 'b.'  'Points' is the number of points per line 
 *(resolution), 'm' is the multiplying constant (enlargement) and 
 *'checking' tells Graph.c whether to check for points that are 
 *"off the screen."
 */

#include "globals.h"
#include <vga.h>

void graph(double a[][max_points][2],double b[][max_points][2],double m,
           int checking, int points, double centerx, double centery)
{
  int i,j;
  double xpa1,ypa1,xpa2,ypa2;
  double xpb1,ypb1,xpb2,ypb2;


  /*Horizontal and vertical lines are plotted at the same time.
   *Pointer arithmetic is used to access array elements.
   *Lines are made up of a collection of segments.  (xpa1,ypa1),
   *(xpa2,ypa2) is the segment for the horizontal lines and
   *the vertical lines use (xpb1,ypb1) and (xpb2,ypb2).  Really,
   *all this function is doing is plotting the points and then
   *"connecting the dots."
   */

  for (i=0;i<points;i++) 
    for (j=0;j<points-1;j++)
    {
      xpa1 =  *(*(*(a+i)+j)+0)*m+centerx;
      ypa1 =  centery-*(*(*(a+i)+j)+1)*m;
      xpb1 =  *(*(*(b+i)+j)+0)*m+centerx;
      ypb1 =  centery-*(*(*(b+i)+j)+1)*m;
      xpa2 =  *(*(*(a+i)+j+1)+0)*m+centerx;
      ypa2 =  centery-*(*(*(a+i)+j+1)+1)*m;
      xpb2 =  *(*(*(b+i)+j+1)+0)*m+centerx; 
      ypb2 =  centery-*(*(*(b+i)+j+1)+1)*m;
      if (checking)
      {
        if ((xpa1>=0)&(ypa1>=0)&(xpa2>=0)&(ypa2>=0))
          if ((xpa1<=640)&(ypa1<=480)&(xpa2<=640)&(ypa2<=480))
            vga_drawline(xpa1,ypa1,xpa2,ypa2);
        if ((xpb1>=0)&(xpb1>=0)&(xpb2>=0)&(ypb2>=0))
          if ((xpb1<=640)&(ypb1<=480)&(xpb2<=640)&(ypb2<=480)) 
            vga_drawline(xpb1,ypb1,xpb2,ypb2);
      }
      else
      {
        vga_drawline(xpa1,ypa1,xpa2,ypa2);
        vga_drawline(xpb1,ypb1,xpb2,ypb2);
      }
    }
}
