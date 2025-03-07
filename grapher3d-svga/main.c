
/* Main.c
 * Main.c starts the user in graphics mode and is responsible for
 * all 'hot key' management.  The "original" (main procedure) variables 
 * reside here and are passed to and from the functions listed below.
 * A function is plotted by 1) calling Calculate, 2)  calling Transform
 * and 3) calling Graph.
 */

#include "globals.h"
#include <vga.h>
#include <curses.h> 
#define pi 3.1415927
#include <ctype.h>
  
int main()
{
  char menu();
  void calculate(double a[][max_points][3],
                 double b[][max_points][3],
                 double c, int d, double e, double f, double g, double h, char function[100]);
  void transform(double a[][max_points][3],
                 double b[][max_points][2],
                 double c[][max_points][3],
                 double d[][max_points][2],
                 double e,double f,double g, int h);
  void graph(double a[][max_points][2],
             double b[][max_points][2],
             double c,int d, int x,
             double centerx, double centery);
  void instructions();
  void domain_range(double *a, double *b, double *c, double *d);
  void new_function(char function[100]);

  double horiz[max_points][max_points][3];   /*3-D horizontal points*/
  double vert[max_points][max_points][3];    /*3-D vertical points*/
  double t_horiz[max_points][max_points][2]; /*2-D transformed*/
  double t_vert[max_points][max_points][2];  /*2-D transformed*/

  double x_rot;
  double y_rot;
  double z_rot;
  double mult  = 30; double mult_inc = 2;
  double zoom  = 2; double zoom_inc = .5;
  double centerx = 640/2;
  double centery = 480/2;
  int color = 1;
  int recalculate; int retransform;
  int points = 10; int point_inc = 5;
  int range_checking = false;
  char c, menu_choice;
  double xmin = -3;
  double xmax =  3;
  double ymin = -3;
  double ymax =  3;
  char postfix[100] = "xy+s"; /*Default postfix expression*/
  int i;
  int j;



 initscr();
 vga_init();
 vga_setmode(G640x480x16);
 x_rot=y_rot=z_rot=(pi/32)*2; 
 calculate(horiz,vert,zoom, points, xmin, xmax, ymin, ymax, postfix);
 transform(vert,t_vert, horiz,t_horiz, x_rot,y_rot,z_rot, points);
 x_rot=y_rot=z_rot=(pi/32)*2; 
 do
 {
   vga_setcolor(color);
   graph(t_horiz, t_vert, mult, range_checking, points, centerx, centery);
   c = vga_getch();
   vga_setcolor(0);
   graph(t_horiz,t_vert, mult,range_checking, points, centerx, centery);
   recalculate = false;
   retransform = false;
   /*Hot key management*/
   switch(tolower(c))
   {
      case '7': xmin+=.10;
                xmax+=.10;
                ymin+=.10;
                ymax+=.10;
                recalculate = true;
                break;
      case '8': xmin-=.10;
                xmax-=.10;
                ymin-=.10;
                ymax-=.10;
                recalculate = true;
                break; 
      case '9': xmin-=.05;
                xmax-=.05;
                ymax+=.05;
                ymin+=.05;
                recalculate = true;
                break;
      case '0': xmin+=.05;
                xmax+=.05;
                ymax-=.05;
                ymin-=.05;
                recalculate = true;
                break; 
      case '5': if (points-point_inc>=min_points)
                {
                  points -= point_inc;
                  recalculate = true;
                }
                break;
      case '6': if (points+3<=max_points)
                {
                  points += point_inc;
                  recalculate = true;
                }
                break;
      case 't': x_rot = y_rot = z_rot = 0;
                retransform = true;
                break;
      case 'x': x_rot += pi/32;
                retransform = true;
                break;
      case 'y': y_rot += pi/32;
                retransform = true;
                break;
      case 'z': z_rot += pi/32;
                retransform = true;
                break;
      case '+': mult += mult_inc;
                break;
      case '-': mult -= mult_inc;
                break;
      case 'c': color += 1;
                if (color==15) color = 1;
                break;
      case '1': zoom += zoom_inc;
                recalculate = true;
                break;
      case '2': zoom -= zoom_inc;
                recalculate = true;
                break;
      case '3': range_checking = true;
                break;
      case '4': range_checking = false;
                break;
      case 'm': vga_setmode(0);
                while ((tolower(menu_choice=menu()))!='p')
                {
                  switch(tolower(menu_choice))
                  {
                    case 'n': new_function(postfix);
                              recalculate = true;
                              mult = 30;
                              zoom = 1;
                              points = 10;
                              break;
                    case 'd': domain_range(&xmin, &xmax, &ymin, &ymax);
                              recalculate = true;
                              break; 
                    case 'i': instructions();
                              break;
                    case 'q': return 0;
                  }
                }
                vga_setmode(G640x480x16);
                break;
    }
    if (recalculate)
       calculate(horiz,vert,zoom, points, xmin, xmax, ymin, ymax, postfix),
       transform(horiz,t_horiz,
                 vert,t_vert,
                 x_rot,y_rot,z_rot, points); 
    else if (retransform)
       transform(horiz,t_horiz,
                 vert,t_vert,
                 x_rot,y_rot,z_rot, points);
  }
  while (c!='q');
  endwin(); /* added 1/28/2020 */
  return 0;
}

/*Below are the components of the "Main Menu."*/

char menu()
{
  char c;
  int top = 5;
  clear();
  move(top,35);
  printw("MENU\n\n");
  move(top + 2,30);
  printw("(P)lot Surface\n");
  move(top + 3,30);
  printw("(N)ew Function\n");
  move(top + 4,30);
  printw("(D)omain\n");
  move(top + 5,30);
  printw("(I)nstructions\n");
  move(top + 6,30);
  printw("(Q)uit\n");
  refresh();
  cbreak(); /* added 1/28/2020 */
  c = getch();
  return c;
}  

void new_function(char *function)
{ 
  int top = 2;
  clear();
  move(top,31);
  printw("New Function\n\n\n");
  printw("Defined Functions:\n\n");
  printw("Addition      '+'\n");
  printw("Subtraction   '-'\n");
  printw("Mutiplication '*'\n");
  printw("Division      '/'\n");
  printw("Powers        '^'\n");
  printw("Cosine        'c'\n");
  printw("Sine          's'\n");
  printw("Exp (base e)  'e'\n");
  printw("Log (base e)  'l'\n");
  printw("Negation      'n'\n");
  move(top + 17, 24);
  printw("Current Functon: Z = %s", function);
  move(top + 19, 24);
  printw("Z = ");
  scanw("%s", function);
  refresh();
}

void domain_range(double *a, double *b, double *c, double *d)
{
  int top = 5;
  clear();
  move(top,31);
  printw("Domain/Range\n");
  move(top + 2, 28);
  printw("Minimum X value -> "); scanw("%lf", a);
  move(top + 3, 28);
  printw("Maximum X value -> "); scanw("%lf", b);
  move(top + 4, 28);
  printw("Minimum Y value -> "); scanw("%lf", c);
  move(top + 5, 28);
  printw("Maximum Y value -> "); scanw("%lf", d); 
  refresh();
}

void instructions()
{
  int top = 5;
  int left = 26;
  clear();
  move(top,31);
  printw("Instructions\n");
  move(top + 2, left);
  printw("'x' - rotates x axis\n");
  move(top + 3, left);
  printw("'y' - rotates y axis\n");
  move(top + 4, left);
  printw("'z' - rotates z axis\n");
  move(top + 5, left);
  printw("'1' - stretch z value\n");
  move(top + 6, left);
  printw("'2' - shrink x value\n");
  move(top + 7, left);
  printw("'3' - range checking on\n");
  move(top + 8, left);
  printw("'4' - range checking off\n");
  move(top + 9, left);
  printw("'5' - increase resolution\n"); 
  move(top + 10, left);
  printw("'6' - decrease resolution\n");
  move(top + 11, left);
  printw("'7', '8', '9', '0' - try them...they're fun!\n");  
  move(top + 12, left);
  printw("'+' - zoom in\n");
  move(top + 13, left);
  printw("'-' - zoom out\n");
  move(top + 14, left);
  printw("'q' - Quit\n");
  move(top + 15, left);
  printw("'m' - Exit to main menu\n"); 
  refresh();
  getch();
}
