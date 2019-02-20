#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  color c;

  c.red = 0;
  c.green = MAX_COLOR;
  c.blue = 0;

  clear_screen(s);
  
  struct matrix *edges;
  struct matrix *modmatrix;

  modmatrix = new_matrix(4, 4);
  ident(modmatrix);
  edges = new_matrix(4, 4);

  for(int r = 0; r < edges->rows; r++){
    for(int c = 0; c < edges->cols; c++){
      edges->m[r][c] = r+c;
    }
  }

  
  printf("\nMODMATRIX\n");
  print_matrix(modmatrix);
  printf("\nEDGES\n");
  print_matrix(edges);

  printf("\nMODMATRIX(IDENT) X EDGES\n");
  matrix_mult(modmatrix, edges);
  print_matrix(edges);

  printf("\nMODMATRIX\n");
  for(int r = 0; r < modmatrix->rows; r++){
    for(int c = 0; c < modmatrix->cols; c++){
      modmatrix->m[r][c] = r+c;
    }
  }  
  print_matrix(modmatrix);  
  printf("\nMODMATRIX X EDGES\n");
  matrix_mult(modmatrix, edges);
  print_matrix(edges);

  
  free_matrix( edges );
  free_matrix( modmatrix );

  display(s);
  save_extension(s, "matrix.png");
}  
