#include "apue.h"

// fgets, fputs版本

int main(void)
{
  int len = 5;
  char buf[len];

  while (fgets(buf, len, stdin) != NULL)
  {
    if (fputs(buf, stdout) == EOF)
    {
      err_sys("output error");
    }
  }

  if (ferror(stdin))
  {
    err_sys("input error");
  }

  return 0;
}