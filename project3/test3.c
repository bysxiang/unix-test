#include "apue.h"

// 只使用read、write复制一个文件
// ./test3.exe < test3.c > cp3.c
// 重定向标准输入和输出，将test3.c复制到cp3.c

#define BUFFSIZE 4096

int main(void)
{
  int n;
  char buf[BUFFSIZE];
  n = read(STDIN_FILENO, buf, BUFFSIZE);
  if (n > 0)
  {
    while (n > 0)
    {
      if (write(STDOUT_FILENO, buf, n) != n)
      {
        err_sys("write error");
      }

      n = read(STDIN_FILENO, buf, BUFFSIZE);
    } // while .. end
  }
  else
  {
    err_sys("read error");
  }
  
  return 0;
}