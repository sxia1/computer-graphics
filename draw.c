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
    int half = x1-x0;
    int m = 2 *(y1-y0);
    int x = x0;
    int y = y0;
    int A = y1-y0;
    int B = -(x1-x0);
    int d;
    //Positive Slope
    printf("\nhalf: %d m: %d\n", half, m);
    if(m > 0){
      if(m < half){
	//Octant I and V
	d = 2*A + B;
	while(x <= x1){
	  plot(s, c, x, y);
	  if(d > 0){
	    y ++;
	    d += 2*B;
	  }
	  x ++;
	  d += 2*A;
	}
      }
      else{
	//Octant II and VI !!!!!!!!!!!!!!!!!!!!!
	d = A + 2*B;
	while(y <= y1){
	  plot(s, c, x, y);
	  if(d < 0){
	    x ++;
	    d += 2*A;
	  }
	  y ++;
	  d += 2*B;
	}
      }
    }
    //Negative Slope
    else{
      if(-m > half){
	//Octant III and VII !!!!!!!!!!!!!!!!!!!!!
	d = 2*B -A;
	while(y >= y1){
	  plot(s, c, x, y);
	  if(d < 0){
	    x ++;
	    d -= 2*A;
	  }
	  y --;
	  d += 2*B;
	}
      }
      else{
	//Octant IV and VIII
	d = B -2*A;
	while(x <= x1){
	  plot(s, c, x, y);
	  if(d > 0){
	    y --;
	    d += 2*B;
	  }
	  x ++;
	  d -= 2*A;
	}
      }
    }
  }
}
