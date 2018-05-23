#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "operationsOnDatabase.h"


int main (int argc, char **argv) {
  printf("\033[2J\033[H"); // clear terminal
  menu();
  return 0;
}
