#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int fd;
int rgb[3];
char line[20];

int main(){
  
  fd = open("img.ppm", O_CREAT | O_WRONLY | O_TRUNC, 0666);

  //Header
  strcpy(line, "P3 500 500 255 \n");
  write(fd, "P3 500 500 255 \n", sizeof(char)*16);

  //Gradient
  for(int i = 0; i < 500; i ++){
    for(int j = 0; j < 500; j ++){
      rgb[0] = (i * i) % 256;
      rgb[1] = (i * j) % 256;
      rgb[2] = (i + j) % 256;
      sprintf(line, "%d %d %d ", rgb[0], rgb[1], rgb[2]);
      write(fd, line, strlen(line));
    }
  }

  close(fd);
  return 0;
}
