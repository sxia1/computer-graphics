/*========== my_main.c ==========

  This is the only file you need to modify in order
  to get a working mdl project (for now).

  my_main.c will serve as the interpreter for mdl.
  When an mdl script goes through a lexer and parser,
  the resulting operations will be in the array op[].

  Your job is to go through each entry in op and perform
  the required action from the list below:

  push: push a new origin matrix onto the origin stack

  pop: remove the top matrix on the origin stack

  move/scale/rotate: create a transformation matrix
                     based on the provided values, then
                     multiply the current top of the
                     origins stack by it.

  box/sphere/torus: create a solid object based on the
                    provided values. Store that in a
                    temporary matrix, multiply it by the
                    current top of the origins stack, then
                    call draw_polygons.

  line: create a line based on the provided values. Store
        that in a temporary matrix, multiply it by the
        current top of the origins stack, then call draw_lines.

  save: call save_extension with the provided filename

  display: view the screen
  =========================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "parser.h"
#include "symtab.h"
#include "y.tab.h"

#include "matrix.h"
#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "stack.h"
#include "gmath.h"

void my_main() {

  int i;
  struct matrix *tmp;
  struct matrix *polygons;
  struct matrix *edges;
  struct stack *systems;
  screen t;
  zbuffer zb;
  color g;
  double step_3d = 20;
  double theta;

  //Lighting values here for easy access
  color ambient;
  ambient.red = 50;
  ambient.green = 50;
  ambient.blue = 50;

  double light[2][3];
  light[LOCATION][0] = 0.5;
  light[LOCATION][1] = 0.75;
  light[LOCATION][2] = 1;

  light[COLOR][RED] = 0;
  light[COLOR][GREEN] = 255;
  light[COLOR][BLUE] = 255;

  double view[3];
  view[0] = 0;
  view[1] = 0;
  view[2] = 1;

  //default reflective constants if none are set in script file
  struct constants white;
  white.r[AMBIENT_R] = 0.1;
  white.g[AMBIENT_R] = 0.1;
  white.b[AMBIENT_R] = 0.1;

  white.r[DIFFUSE_R] = 0.5;
  white.g[DIFFUSE_R] = 0.5;
  white.b[DIFFUSE_R] = 0.5;

  white.r[SPECULAR_R] = 0.5;
  white.g[SPECULAR_R] = 0.5;
  white.b[SPECULAR_R] = 0.5;

  //constants are a pointer in symtab, using one here for consistency
  struct constants *reflect;
  reflect = &white;

  systems = new_stack();
  tmp = new_matrix(4, 1000);
  polygons = new_matrix(4, 4);
  edges = new_matrix(4, 4);
  clear_screen( t );
  clear_zbuffer(zb);
  g.red = 0;
  g.green = 0;
  g.blue = 0;

  print_symtab();
  for (i=0;i<lastop;i++) {
    printf("%d: ",i);
    switch (op[i].opcode)
      {
      case PUSH:
	push(systems);
	printf("PUSH");
	break;
      case POP:
	pop(systems);
	printf("POP");
	break;
      case MOVE:
	printf("MOVE: %6.2f %6.2f %6.2f",
	       op[i].op.move.d[0],op[i].op.move.d[1],
	       op[i].op.move.d[2]);
	if (op[i].op.move.p != NULL)
	  {
	    printf("\tknob: %s",op[i].op.move.p->name);
	  }
	tmp = make_translate(op[i].op.move.d[0], op[i].op.move.d[1], op[i].op.move.d[2]);
	matrix_mult(peek(systems), tmp);
	copy_matrix(tmp, peek(systems));
	break;
      case ROTATE:
	printf("ROTATE: axis: %6.2f degrees: %6.2f",
	       op[i].op.rotate.axis,
	       op[i].op.rotate.degrees);
	if (op[i].op.rotate.p != NULL)
	  {
	    printf("\tknob: %s",op[i].op.rotate.p->name);
	  }
	double theta = op[i].op.rotate.degrees * (M_PI / 180);
	double axis = op[i].op.rotate.axis;
	if ( axis == 0.0 )
	  tmp = make_rotX( theta );
	else if ( axis == 1.0 )
	  tmp = make_rotY( theta );
	else
	  tmp = make_rotZ( theta );
	matrix_mult(peek(systems), tmp);
	copy_matrix(tmp, peek(systems));
	break;
      case SCALE:
	printf("Scale: %6.2f %6.2f %6.2f",
	       op[i].op.scale.d[0],op[i].op.scale.d[1],
	       op[i].op.scale.d[2]);
	if (op[i].op.scale.p != NULL)
	  {
	    printf("\tknob: %s",op[i].op.scale.p->name);
	  }
	tmp = make_scale( op[i].op.scale.d[0], op[i].op.scale.d[1], op[i].op.scale.d[2]);
	matrix_mult(peek(systems), tmp);
	copy_matrix(tmp, peek(systems));
	break;
      case BOX:
	printf("Box: d0: %6.2f %6.2f %6.2f d1: %6.2f %6.2f %6.2f",
	       op[i].op.box.d0[0],op[i].op.box.d0[1],
	       op[i].op.box.d0[2],
	       op[i].op.box.d1[0],op[i].op.box.d1[1],
	       op[i].op.box.d1[2]);
	if (op[i].op.box.constants != NULL)
	  {
	    printf("\tconstants: %s",op[i].op.box.constants->name);
	  }
	if (op[i].op.box.cs != NULL)
	  {
	    printf("\tcs: %s",op[i].op.box.cs->name);
	  }
	add_box(polygons, op[i].op.box.d0[0], op[i].op.box.d0[1], op[i].op.box.d0[2],
	       op[i].op.box.d1[0], op[i].op.box.d1[1], op[i].op.box.d1[2]);
	matrix_mult(peek(systems), polygons);
	draw_polygons(polygons, t, zb,
		      view, light, ambient, reflect);
	polygons->lastcol = 0;
	break;
      case SPHERE:
	printf("Sphere: %6.2f %6.2f %6.2f r=%6.2f",
	       op[i].op.sphere.d[0],op[i].op.sphere.d[1],
	       op[i].op.sphere.d[2],
	       op[i].op.sphere.r);
	if (op[i].op.sphere.constants != NULL)
	  {
	    printf("\tconstants: %s",op[i].op.sphere.constants->name);
	  }
	if (op[i].op.sphere.cs != NULL)
	  {
	    printf("\tcs: %s",op[i].op.sphere.cs->name);
	  }
	add_sphere( polygons, op[i].op.sphere.d[0],op[i].op.sphere.d[1], op[i].op.sphere.d[2],
		    op[i].op.sphere.r, step_3d);
	matrix_mult(peek(systems), polygons);
	draw_polygons(polygons, t, zb,
		      view, light, ambient, reflect);
	polygons->lastcol = 0;
	break;
      case TORUS:
	printf("TORUS: %6.2f %6.2f %6.2f r0=%6.2f r1=%6.2f",
	       op[i].op.torus.d[0],op[i].op.torus.d[1],
	       op[i].op.torus.d[2],
	       op[i].op.torus.r0,op[i].op.torus.r1);
	if (op[i].op.torus.constants != NULL)
	  {
	    printf("\tconstants: %s",op[i].op.torus.constants->name);
	  }
	if (op[i].op.torus.cs != NULL)
	  {
	    printf("\tcs: %s",op[i].op.torus.cs->name);
	  }
	add_torus( polygons, op[i].op.torus.d[0],op[i].op.torus.d[1],
		   op[i].op.torus.d[2],
		   op[i].op.torus.r0,op[i].op.torus.r1, step_3d);
	matrix_mult(peek(systems), polygons);
	draw_polygons(polygons, t, zb,
		      view, light, ambient, reflect);
	polygons->lastcol = 0;
	break;
      case CONSTANTS:
	printf("CONSTANTS");
	break;
      case LINE:
	printf("LINE: from: %6.2f %6.2f %6.2f to: %6.2f %6.2f %6.2f",
	       op[i].op.line.p0[0],op[i].op.line.p0[1],
	       op[i].op.line.p0[1],
	       op[i].op.line.p1[0],op[i].op.line.p1[1],
	       op[i].op.line.p1[1]);
	if (op[i].op.line.constants != NULL)
	  {
	    printf("\n\tConstants: %s",op[i].op.line.constants->name);
	  }
	if (op[i].op.line.cs0 != NULL)
	  {
	    printf("\n\tCS0: %s",op[i].op.line.cs0->name);
	  }
	if (op[i].op.line.cs1 != NULL)
	  {
	    printf("\n\tCS1: %s",op[i].op.line.cs1->name);
	  }
	add_edge(edges, op[i].op.line.p0[0],op[i].op.line.p0[1],
	       op[i].op.line.p0[1],
	       op[i].op.line.p1[0],op[i].op.line.p1[1],
	       op[i].op.line.p1[1]);
	matrix_mult(peek(systems), edges);
	draw_lines(edges, t, zb, g);
	edges->lastcol = 0;
	break;
      case SAVE:
	printf("SAVE: %s",op[i].op.save.p->name);
	save_extension(t, op[i].op.save.p->name);
	break;
      case DISPLAY:
	printf("DISPLAY");
	display( t );
	break;   
    }
    printf("\n");
  }
}
