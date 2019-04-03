#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "gmath.h"
#include "matrix.h"
#include "ml6.h"


//vector functions
//normalize vector, should modify the parameter
void normalize( double *vector ) {
  double magn = sqrt(pow(vector[0], 2) +pow(vector[1], 2) +pow(vector[2], 2));
  vector[0] = vector[0]/magn;
  vector[1] = vector[1]/magn;
  vector[2] = vector[2]/magn;
}

//Return the dot product of a . b
double dot_product( double *a, double *b ) {
  return  a[0]*b[0] +a[1]*b[1] +a[2]*b[2];
}


//Calculate the surface normal for the triangle whose first
//point is located at index i in polygons
double *calculate_normal(struct matrix *polygons, int i) {
  double a[3];
  a[0] = polygons->m[0][i +1] - polygons->m[0][i];
  a[1] = polygons->m[1][i +1] - polygons->m[1][i];
  a[2] = polygons->m[2][i +1] - polygons->m[2][i];
  double b[3];
  b[0] = polygons->m[0][i +2] - polygons->m[0][i];
  b[1] = polygons->m[1][i +2] - polygons->m[1][i];
  b[2] = polygons->m[2][i +2] - polygons->m[2][i];
  double *norm = malloc(sizeof(double) *3);
  norm[0] = a[1]*b[2] -a[2]*b[1];
  norm[1] = a[2]*b[0] -a[0]*b[2];
  norm[2] = a[0]*b[1] -a[1]*b[0];
  
  return norm;
}
