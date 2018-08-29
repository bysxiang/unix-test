#include "apue.h"

#define BUFFSIZE 4096

int main(void)
{
  int n;
  char buf[BUFFSIZE];

  n = read(STDIN_FILENO, buf, BUFFSIZE);
  if (n < 0)
  {
    err_sys("write error");
  }
  else
  {
    while (n > 0)
    {
      if (write(STDOUT_FILENO, buf, n) != n)
      {
        err_sys("write error");
      }

      n = read(STDIN_FILENO, buf, BUFFSIZE);
    }
  }
  
  return 0;
}