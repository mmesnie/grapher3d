/*
 * Please see README for copying information.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <malloc.h>
#include "globals.h"

#define num_axis_points 18

  int main(int argc, char** argv) {

  /*Subroutines*/

  void calculate(double a[][3],
                 double c, int d, double e, double f, double g, 
                 double h, char function[100]);
  void transform(double a[][3],
                 double b[][2],
                 double xr, double yr, double zr, int points);
  void graph(double b[][3], double a[][2],
             double c, int x,
             double centerx, double centery,
             FILE **output, char *color, int type);
  int widgets(FILE **output);

  /*Variable Declaration*/

  double horiz[max_points*max_points][3];   /*3-D horizontal points*/
  double t_horiz[max_points*max_points][2]; /*2-D transformed*/
  double x_rot = 0.392;
  double y_rot = 0.196;
  double z_rot = 0.196; 
  double zoom  = 30.0;
  double exag  = 3.0;
  double centerx = 150;
  double centery = 150;
  int x, y;
  int xres, yres;
  int points = 10.0;
  char c, menu_choice;
  double xmin = -3.14;
  double xmax =  3.14;
  double ymin = -3.14;
  double ymax =  3.14;
  char infix[100] = "sin(x+y)"; /*Default infix expresson*/
  char postfix[100];
  int i;
  int j;
  char draw[80]         = "blue"; 
  char draw_points[80]  = "red"; 
  char draw_lines[80]   = "grey"; 
  char geom[50]; 
  char tcl[100];
  char data_file[100];
  FILE *input, *output;
  double data_points[MAX_DATA_POINTS][3];
  double transformed_data_points[MAX_DATA_POINTS][2];
  int num_data_points;
  double axis_points[num_axis_points][3];
  double transformed_axis_points[num_axis_points][2];
  int plot_function = true;
  int plot_points = false;
  int plot_axis = true;
  int recalculate;
  int retransform;
  int replot;
  char error[100];
  int result;
  double zmin = -3.14;
  double zmax = +3.14;
  int plot_type = FRAME;
  boolean connectDots = true;
  int child(char *cmd, FILE **input, FILE **output);
  int get_points(char *file, double points[][3], int *num_points, char *error);
  int infix2postfix(char *infix, char* postfix);
  void graph_points(double a[][2], int points, double centerx, double centery,
		    FILE **output, char *color, char*line_color, double zoom, boolean connectDots);
  char *rc;
  
  /*
   * Start "wish" as a child process and 
   * communicate via input and output
   */

  child("wish", &input, &output);
  widgets(&output);

  /*
   * Calculate axis points.
   */

    axis_points[0][0] = xmax; axis_points[0][1] = ymax; axis_points[0][2] = zmax; 
    axis_points[1][0] = xmax; axis_points[1][1] = ymin; axis_points[1][2] = zmax; 
    axis_points[2][0] = xmin; axis_points[2][1] = ymin; axis_points[2][2] = zmax;
    axis_points[3][0] = xmin; axis_points[3][1] = ymax; axis_points[3][2] = zmax; 
    axis_points[4][0] = xmax; axis_points[4][1] = ymax; axis_points[4][2] = zmax; 
    axis_points[5][0] = xmax; axis_points[5][1] = ymax; axis_points[5][2] = zmin; 
    axis_points[6][0] = xmax; axis_points[6][1] = ymin; axis_points[6][2] = zmin; 
    axis_points[7][0] = xmin; axis_points[7][1] = ymin; axis_points[7][2] = zmin; 
    axis_points[8][0] = xmin; axis_points[8][1] = ymax; axis_points[8][2] = zmin; 
    axis_points[9][0] = xmax; axis_points[9][1] = ymax; axis_points[9][2] = zmin; 
    axis_points[10][0] = xmin; axis_points[10][1] = ymax; axis_points[10][2] = zmin; 
    axis_points[11][0] = xmin; axis_points[11][1] = ymax; axis_points[11][2] = zmax; 
    axis_points[12][0] = xmin; axis_points[12][1] = ymax; axis_points[12][2] = zmin; 
    axis_points[13][0] = xmin; axis_points[13][1] = ymin; axis_points[13][2] = zmin; 
    axis_points[14][0] = xmin; axis_points[14][1] = ymin; axis_points[14][2] = zmax; 
    axis_points[15][0] = xmin; axis_points[15][1] = ymin; axis_points[15][2] = zmin; 
    axis_points[16][0] = xmax; axis_points[16][1] = ymin; axis_points[16][2] = zmin; 
    axis_points[17][0] = xmax; axis_points[17][1] = ymin; axis_points[17][2] = zmax; 

  /*
   * Wait for commands from GUI
   */

  do {
    recalculate = false;
    retransform = false;
    replot = false;
    do {
      rc = fgets(tcl, 80, input);
      c = tcl[0];

      /*Event Handler*/

      switch(c)
      {
        case 'a': plot_axis = true; 
                  replot = true;
                  break;
        case 'b': plot_axis = false; 
                  replot = true;
                  break;
        case 'F': plot_points = true; 
                  sscanf(&tcl[1], "%s", data_file);
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[0], "%s", draw_points);  
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[0], "%s", draw_lines);  
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[0], "%lf", &zoom);  
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[0], "%lf", &x_rot);  
                  x_rot = (2*(3.1415927)*x_rot)/360;
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[0], "%lf", &y_rot);  
                  y_rot = (2*(3.1415927)*y_rot)/360;
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[0], "%lf", &z_rot);  
                  z_rot = (2*(3.1415927)*z_rot)/360;
                  if (get_points(data_file, data_points, &num_data_points, error) < 0) {
                    fprintf(output, "Error \"%s\"\n", error);
                    fflush(output);
                  } else {
                    if (num_data_points > MAX_DATA_POINTS) {
                      fprintf(output, "Error \"Data file too large. Maximum #points = %i.\"\n",
                              MAX_DATA_POINTS);
                      fflush(output);
                    } else {
                      recalculate = true;
                    }
                  }
                  break;
        case 'G': plot_points = false; 
                  replot = true;
                  break;
        case 't': x_rot = y_rot = z_rot = 0;
                  retransform = true;
                  break;
        case 'x': sscanf(&tcl[1], "%lf", &x_rot);  
                  x_rot = (2*(3.1415927)*x_rot)/360;
                  retransform = true;
                  break;
        case 'y': sscanf(&tcl[1], "%lf", &y_rot);  
                  y_rot = (2*(3.1415927)*y_rot)/360;
                  retransform = true;
                  break;
        case 'z': sscanf(&tcl[1], "%lf", &z_rot);  
                  z_rot = (2*(3.1415927)*z_rot)/360;
                  retransform = true;
                  break;
        case 'Z': recalculate = true;
                  sscanf(&tcl[1], "%lf", &zoom); /* necessary? */  
                  break;
        case 'R': recalculate = true;
                  sscanf(&tcl[1], "%i", &points);  
                  break;
        case 'E': recalculate = true;
                  sscanf(&tcl[1], "%lf", &exag); /* necessary? */
                  break;
        case 'D': recalculate = true;
                  sscanf(&tcl[1], "%lf", &xmin);  
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[0], "%lf", &xmax);
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[0], "%lf", &ymin);
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[0], "%lf", &ymax);
                  break;
        case 'f': plot_function = true;
                  recalculate = true;
                  sscanf(&tcl[1], "%s", infix);
                  #ifdef DEBUG_MAIN
                  printf("infix = %s\n", infix);
                  #endif
                  result = infix2postfix(infix, postfix);
                  if (result <= 0) {
                    fprintf(stderr, "parsing error: %s\n", infix);
                    fprintf(stderr, "               ");
                    for (i=0;i<-result;i++) {
                      fprintf(stderr, " ");
                    }
                    fprintf(stderr, "^\n");
                    recalculate = false;
                  } else {
                    #ifdef DEBUG_MAIN
                    printf("postfix = %s\n", postfix);
                    #endif
                  }
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[1], "%lf", &xmin);  
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[1], "%lf", &xmax);  
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[1], "%lf", &ymin);  
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[1], "%lf", &ymax);  
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[1], "%s", draw);  
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[0], "%i", &points);  
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[0], "%lf", &exag);  
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[0], "%lf", &zoom);  
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[0], "%lf", &x_rot);  
                  x_rot = (2*(3.1415927)*x_rot)/360;
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[0], "%lf", &y_rot);  
                  y_rot = (2*(3.1415927)*y_rot)/360;
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[0], "%lf", &z_rot);  
                  z_rot = (2*(3.1415927)*z_rot)/360;
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[0], "%ix%i+%i+%i", &xres, &yres, &x, &y);  
                  rc = fgets(tcl, 80, input);
                  sscanf(&tcl[0], "%i", &plot_type);  
                  centerx = xres/2;
                  centery = yres/2;
                  break;
        case 'g': plot_function = false; 
                  replot = true;
                  break;
        case 'c': connectDots = false; 
                  replot = true;
                  break;
        case 'C': connectDots = true; 
                  replot = true;
                  break;
      }
    } while ((c!='q')&&(c!='*'));

    /* Re-calculate points if necessary */

    if (recalculate) {
      if (plot_function) {
        calculate(horiz, exag, points, xmin, xmax, ymin, ymax, postfix);
      } 
      axis_points[0][0] = xmax; axis_points[0][1] = ymax; axis_points[0][2] = zmax; 
      axis_points[1][0] = xmax; axis_points[1][1] = ymin; axis_points[1][2] = zmax; 
      axis_points[2][0] = xmin; axis_points[2][1] = ymin; axis_points[2][2] = zmax;
      axis_points[3][0] = xmin; axis_points[3][1] = ymax; axis_points[3][2] = zmax; 
      axis_points[4][0] = xmax; axis_points[4][1] = ymax; axis_points[4][2] = zmax; 
      axis_points[5][0] = xmax; axis_points[5][1] = ymax; axis_points[5][2] = zmin; 
      axis_points[6][0] = xmax; axis_points[6][1] = ymin; axis_points[6][2] = zmin; 
      axis_points[7][0] = xmin; axis_points[7][1] = ymin; axis_points[7][2] = zmin; 
      axis_points[8][0] = xmin; axis_points[8][1] = ymax; axis_points[8][2] = zmin; 
      axis_points[9][0] = xmax; axis_points[9][1] = ymax; axis_points[9][2] = zmin; 
      axis_points[10][0] = xmin; axis_points[10][1] = ymax; axis_points[10][2] = zmin; 
      axis_points[11][0] = xmin; axis_points[11][1] = ymax; axis_points[11][2] = zmax; 
      axis_points[12][0] = xmin; axis_points[12][1] = ymax; axis_points[12][2] = zmin; 
      axis_points[13][0] = xmin; axis_points[13][1] = ymin; axis_points[13][2] = zmin; 
      axis_points[14][0] = xmin; axis_points[14][1] = ymin; axis_points[14][2] = zmax; 
      axis_points[15][0] = xmin; axis_points[15][1] = ymin; axis_points[15][2] = zmin; 
      axis_points[16][0] = xmax; axis_points[16][1] = ymin; axis_points[16][2] = zmin; 
      axis_points[17][0] = xmax; axis_points[17][1] = ymin; axis_points[17][2] = zmax; 
      retransform = true;
    } 
  
    /* Transform 3D to 2D */

    if (retransform) {
      if (plot_function) {
        transform(horiz,t_horiz, x_rot, y_rot, z_rot, points*points);
      }
      if (plot_points) {
        transform(data_points, transformed_data_points, x_rot, y_rot, z_rot,
                  num_data_points);
      } 
      transform(axis_points, transformed_axis_points, x_rot, y_rot, z_rot,
                num_axis_points);
      replot = true;
    }

    /* plot everything */

    fprintf(output, ".canvas delete all\n");
    if (replot) {
      if (plot_function) {
        graph(horiz, t_horiz, zoom, points, centerx, centery, &output, draw, plot_type);
      }
      if (plot_points) {
        graph_points(transformed_data_points, num_data_points, centerx, centery, 
                     &output, draw_points, draw_lines, zoom, connectDots);
      }
      if (plot_axis) {
        graph_points(transformed_axis_points, num_axis_points, centerx, centery,
                     &output, draw_points, draw_lines, zoom, true);
      }
    } 

    /* flush commands to GUI */

    fflush(output);
  } while (c!='q');
  return 0;
}
