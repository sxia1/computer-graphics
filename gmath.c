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
  
  return NULL;
}
