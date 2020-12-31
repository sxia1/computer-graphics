#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"


/*======== void parse_file () ==========
Inputs:   char * filename
          struct matrix * transform,
          struct matrix * pm,
          screen s
Returns:

Goes through the file named filename and performs all of the actions listed in that file.
The file follows the following format:
     Every command is a single character that takes up a line
     Any command that requires arguments must have those arguments in the second line.
     The commands are as follows:
         line: add a line to the edge matrix -
               takes 6 arguemnts (x0, y0, z0, x1, y1, z1)
         ident: set the transform matrix to the identity matrix -
         scale: create a scale matrix,
                then multiply the transform matrix by the scale matrix -
                takes 3 arguments (sx, sy, sz)
         translate: create a translation matrix,
                    then multiply the transform matrix by the translation matrix -
                    takes 3 arguments (tx, ty, tz)
         rotate: create a rotation matrix,
                 then multiply the transform matrix by the rotation matrix -
                 takes 2 arguments (axis, theta) axis should be x y or z
         apply: apply the current transformation matrix to the edge matrix
         display: clear the screen, then
                  draw the lines of the edge matrix to the screen
                  display the screen
         save: clear the screen, then
               draw the lines of the edge matrix to the screen
               save the screen to a file -
               takes 1 argument (file name)
         quit: end parsing

See the file script for an example of the file format

IMPORTANT MATH NOTE:
the trig functions int math.h use radian mesure, but us normal
humans use degrees, so the file will contain degrees for rotations,
be sure to conver those degrees to radians (M_PI is the constant
for PI)
====================*/
void parse_file ( char * filename, 
                  struct matrix * transform, 
                  struct matrix * edges,
                  screen s) {
  FILE *f;
  char line[256];
  clear_screen(s);

  color c;  
  c.red = 0;
  c.green = MAX_COLOR;
  c.blue = 0;

  if ( strcmp(filename, "stdin") == 0 ) 
    f = stdin;
  else
    f = fopen(filename, "r");
  
  while ( fgets(line, 255, f) != NULL ) {
    line[strlen(line)-1]='\0';
    printf(":%s:\n",line);

    //line
    if(strcmp(line, "line") == 0){
      char *buffer = fgets(line, 255, f);
      char *params = calloc(6, sizeof(double));
      for(int i = 0; i < 6; i ++){
        params[i] = atof(strsep(&buffer, " "));
	//printf("%d\t", params[i]);
      }
      add_edge(edges, params[0], params[1], params[2], params[3], params[4], params[5]);
      free(buffer);
      free(params);
    }
    //ident
    if(strcmp(line, "ident") == 0){
      ident(transform);
      //print_matrix(transform);
    }
    //scale
    if(strcmp(line, "scale") == 0){
      char *buffer = fgets(line, 255, f);
      char *params = calloc(3, sizeof(double));
      for(int i = 0; i < 3; i ++){
        params[i] = atof(strsep(&buffer, " "));
	//printf("%d\t", params[i]);
      }
      matrix_mult(make_scale(params[0], params[1], params[2]), transform);
      //print_matrix(transform);
      free(buffer);
      free(params);
    }
    //translate
    if(strcmp(line, "move") == 0){
      char *buffer = fgets(line, 255, f);
      char *params = calloc(3, sizeof(double));
      for(int i = 0; i < 3; i ++){
	params[i] = atof(strsep(&buffer, " "));
	//printf("%d\t", params[i]);
      }
      matrix_mult(make_translate(params[0], params[1], params[2]), transform);
      //print_matrix(transform);
      free(buffer);
      free(params);
    }
    //rotate
    if(strcmp(line, "rotate") == 0){
      char *buffer = fgets(line, 255, f);
      char *axis = malloc(sizeof(char));
      strcpy(axis, strsep(&buffer, " "));
      double theta = atof(strsep(&buffer, " "));
      //printf("%s, %lf\t", axis, theta);
      if(strcmp(axis, "x") == 0){
	matrix_mult(make_rotX(theta), transform);
      }
      else if(strcmp(axis, "y") == 0){
	matrix_mult(make_rotY(theta), transform);
      }
      else if(strcmp(axis, "z") == 0){
	matrix_mult(make_rotZ(theta), transform);
      }
      //print_matrix(transform);
      free(buffer);
      free(axis);
    }
    //apply
    if(strcmp(line, "apply") == 0){
      matrix_mult(transform, edges);
    }
    //display
    if(strcmp(line, "display") == 0){
      clear_screen(s);
      draw_lines(edges, s, c);
      display(s);
    }
    //save
    if(strcmp(line, "save") == 0){
      char *fname = calloc(256, sizeof(char));
      fgets(fname, 255, f);
      fname[strlen(fname)-1]='\0';
      fgets(fname, 255, f);

      clear_screen(s);
      draw_lines(edges, s, c);
      save_extension(s, fname);
    }
    //quit
    if(strcmp(line, "quit") == 0){
      fseek(f, 0, SEEK_END);
    }
  }
  
}
