#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

int main() {

  screen s;
  color c;

  c.red = 0;
  c.green = MAX_COLOR;
  c.blue = 0;

  clear_screen(s);

  //Test Vertical and Horizontal Lines
  draw_line(250, 0, 250, 500, s, c); //SUCCESS
  draw_line(0, 250, 500, 250, s, c); //SUCCESS

  //Test Octant I
  draw_line(250, 250, 500, 450, s, c); //SUCCESS
  draw_line(250, 250, 500, 400, s, c); //SUCCESS
  draw_line(250, 250, 500, 350, s, c); //SUCCESS
  draw_line(250, 250, 500, 300, s, c); //SUCCESS
  
  //Test Octant IV
  draw_line(250, 250, 0, 50, s, c); //SUCCESS
  draw_line(250, 250, 0, 100, s, c); //SUCCESS
  draw_line(250, 250, 0, 150, s, c); //SUCCESS
  draw_line(250, 250, 0, 200, s, c); //SUCCESS

  //Test Octant II
  draw_line(250, 250, 450, 500, s, c); //SUCCESS
  draw_line(250, 250, 400, 500, s, c); //SUCCESS
  draw_line(250, 250, 350, 500, s, c); //SUCCESS
  draw_line(250, 250, 300, 500, s, c); //SUCCESS

  //Test Octant VI 
  draw_line(250, 250, 50, 0, s, c); //SUCCESS
  draw_line(250, 250, 100, 0, s, c); //SUCCESS
  draw_line(250, 250, 150, 0, s, c); //SUCCESS
  draw_line(250, 250, 200, 0, s, c); //SUCCESS
  
  //Test Octant VII
  draw_line(250, 250, 450, 0, s, c); //SUCCESS
  draw_line(250, 250, 400, 0, s, c); //SUCCESS
  draw_line(250, 250, 350, 0, s, c); //SUCCESS
  draw_line(250, 250, 300, 0, s, c); //SUCCESS

  //Test Octant III
  draw_line(250, 250, 50, 500, s, c); //SUCCESS
  draw_line(250, 250, 100, 500, s, c); //SUCCESS
  draw_line(250, 250, 150, 500, s, c); //SUCCESS
  draw_line(250, 250, 200, 500, s, c); //SUCCESS

  //Test Octant IV
  draw_line(250, 250, 0, 450, s, c); //SUCCESS
  draw_line(250, 250, 0, 400, s, c); //SUCCESS
  draw_line(250, 250, 0, 350, s, c); //SUCCESS
  draw_line(250, 250, 0, 300, s, c); //SUCCESS
  
  //Test Octant VIII
  draw_line(250, 250, 500, 50, s, c); //SUCCESS
  draw_line(250, 250, 500, 100, s, c); //SUCCESS
  draw_line(250, 250, 500, 150, s, c); //SUCCESS
  draw_line(250, 250, 500, 200, s, c); //SUCCESS

  display(s);
  save_extension(s, "lines.png");
}
