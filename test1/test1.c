#include <stdio.h>

typedef int MyTest(int);
typedef int (* mm)(int);

int test(int);

int main(void)
{
  mm pf = test;

  int x = pf(3);

  printf("这样可以吗,2 %d\n", x);
  return 0;
}

int test(int a)
{
  return a * 2;
}