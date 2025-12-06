#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "roundoff.h"

char *double_to_hex(double x)
{
  static char buf[100];
  union {
    double d;
    long l[2];
  } u;
  u.d = x;
  sprintf(buf, "'%0lx', '%0lx' (%.18f)", u.l[0], u.l[1], u.d);
  return buf;
}

int main() {
  initialize_roundoff();
  printf("Hex of powers used in box dimensions\n");
  char expected[] =
    "pow(2, 0/6) = '3ff0000000000000', '0' (1.000000000000000000)\n"
    "pow(2, 1/6) = '3ff1f59ac3c7d6c0', '3fc5555555555555' (1.122462048309373017)\n"
    "pow(2, 2/6) = '3ff428a2f98d728b', '3fd5555555555555' (1.259921049894873191)\n"
    "pow(2, 3/6) = '3ff6a09e667f3bcd', '3fe0000000000000' (1.414213562373095145)\n"
    "pow(2, 4/6) = '3ff965fea53d6e3c', '3fe5555555555555' (1.587401051968199361)\n"
    "pow(2, 5/6) = '3ffc823e074ec129', '3feaaaaaaaaaaaab' (1.781797436280678548)\n";
  static char buf[1000];
  int offset = 0;
  for (int i = 0; i < 6; i++) {
    offset += sprintf(buf + offset, "pow(2, %d/6) = %s\n", i, double_to_hex(pow((double)(2), (double)(i)/(double)(6.0))));
  }
  if (!roundoff_ok()) {
    printf("Error --  unexpected roundoff error!\n");
    exit(-2);
  }
  if (strncmp(expected, buf, strlen(expected)) == 0) {
    printf(buf);
    printf("Powers above are correct.\n");
    exit(0);
  } else {
    printf(buf);
    printf("Error --  powers above are not correct!\n");
  }
  exit(-1);
}
