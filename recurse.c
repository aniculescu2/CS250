#include <stdio.h>
#include <math.h>

int recurse(int input){
  if(input == 0)
    return -2;
  return 3*input+2*recurse(input-1)-2;
}

int main(int argc, char *argv[]){
  int output = recurse(atoi(argv[1]));
  printf("%d\n", output);
}
