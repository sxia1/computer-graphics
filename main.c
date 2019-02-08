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

  for(int j = 0; j < 500; j += 50){
    for(int i = 0; i < 500; i += 20){
      c.blue += 1;
      c.red += 1;
      draw_line(i, j, i +20, j +25, s, c);
      draw_line(i+20, j+25, i, j+50, s, c);
    }
  }

  display(s);
  save_extension(s, "lines.png");
}
