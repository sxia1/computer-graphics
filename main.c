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
  
  struct matrix *testedges;
  struct matrix *testmodmatrix;

  testmodmatrix = new_matrix(4, 4);
  testedges = new_matrix(4, 4);

  printf("\nIDENT TESTMODMATRIX\n");
  ident(testmodmatrix);
  print_matrix(testmodmatrix);
  printf("\nTESTEDGES\n");
  add_edge(testedges, 1, 2, 3, 4, 5, 6);
  print_matrix(testedges);

  printf("\nTESTMODMATRIX(IDENT) X TESTEDGES\n");
  matrix_mult(testmodmatrix, testedges);
  print_matrix(testedges);

  printf("\nPOPULATE TESTMODMATRIX\n");
  add_edge(testmodmatrix, 1,2,3,4,5,6);
  add_edge(testmodmatrix, 7,8,9,10,11,12);
  print_matrix(testmodmatrix);
  
  printf("\nTESTMODMATRIX X TESTEDGES\n");
  matrix_mult(testmodmatrix, testedges);
  print_matrix(testedges);
  
  free_matrix( testedges );
  free_matrix( testmodmatrix );

  
  struct matrix *edges;
  struct matrix *modmatrix;

  modmatrix = new_matrix(4, 4);
  edges = new_matrix(4, 4);

  //make a square
  add_edge(edges, 250, 125, 0, 375, 250, 0);
  add_edge(edges, 375, 250, 0, 250, 375, 0);
  add_edge(edges, 250, 375, 0, 125, 250, 0);
  add_edge(edges, 125, 250, 0, 250, 125, 0);
  draw_lines(edges, s, c);

  //ROTATION MODMATRIX
  ident(modmatrix);
  modmatrix->m[0][0] = 0.984807;
  modmatrix->m[0][1] = 0.173648;
  modmatrix->m[1][0] = -0.173648;
  modmatrix->m[1][1] = 0.984807;  

  for(int i = 0; i < 300; i ++){
    matrix_mult(modmatrix, edges);
    draw_lines(edges, s, c);
  }
  
  free_matrix( edges );
  free_matrix( modmatrix );
  
  display(s);
  save_extension(s, "matrix.png");
}  
