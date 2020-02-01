/*
 * Please see README for copying information.
 */

/*
 * Here we can read in an arbitrary array of 3d points.
 */

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

int get_points(char *file, double points[][3], int *num_points, char *error) {
  FILE *handle;
  double x, y, z;
  char line[81]; 
  int count = 0;

  if ((handle = fopen(file, "r")) == NULL) {
    sprintf(error, "Error opening \\\"%s\\\"", file); 
    return -1;
  }
  while (fgets(line, 80, handle) != NULL) {
    if (sscanf(line, "%lf %lf %lf", &x, &y, &z) != 3) {
      sprintf(error, "Error reading \\\"%s\\\" line %d.", file, count+1); 
      return -1;
    }
    points[count][0] = x;
    points[count][1] = y;
    points[count][2] = z;
    count++;
  }
  *num_points = count;
  fclose(handle);
  return 0;
} 
