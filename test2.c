#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

void main(int argc, char** argv) {
  srand(time(NULL)); // for random
  while (1) {
    int x = rand();
    if (x < 10)
      break;
  }
}
