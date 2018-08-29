#include "apue.h"

int main(void)
{
  int c;

  if (ferror(stdin))
  {
    err_sys("input error");
  }
  else
  {
    c = getc(stdin);
    while (c != EOF)
    {
      if (putc(c, stdout) == EOF)
      {
        err_sys("output error");
      }

      c = getc(stdin);
    }
  }
  
  return 0;
}