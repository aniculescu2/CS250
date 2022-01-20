#include <stdio.h>
#include <math.h>
int main(int argc, char *argv[]){
  double argument = pow(2,atoi(argv[1])) - 1;
  printf("%.0lf\n", argument);
}
