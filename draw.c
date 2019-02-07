#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {

  //if second pair of coordinates is to the left of the first
  if(x0 > x1){
    //swap the first and second coordinates
    int temp = x1; x1 = x0; x0 = temp;
    temp = y1; y1 = y0; y0 = temp;
  }
  
  //if horizontal lines
  if((y1 - y0) == 0){
    int x = x0;
    while(x <= x1){
      plot(s, c, x, y0);
      x ++;
    }
  }
  //if vertical lines
  if((x1 - x0) == 0){
    int y = y0;
    while(y <= y1){
      plot(s, c, x0, y);
      y ++;
    }
  }

  //if sloped
  else{
    int x = x0;
    int y = y0;
    int A = y1-y0;
    int B = -(x1-x0);
    //Octant I and V
    /*
    int d = 2*A + B;
    while(x <= x1){
      plot(s, c, x, y);
      if(d > 0){
	y ++;
	d += 2*B;
      }
      x ++;
      d += 2*A;
    }
    */
    //Octant II and VI
    /*
    int d = A + 2*B;
    while(y <= y1){
      plot(s, c, x, y);
      if(d < 0){
	x ++;
	d += 2*A;
      }
      y ++;
      d += 2*B;
    }
    */
    //Octant III and VII

    //Octant VI and VIII
  }
}
