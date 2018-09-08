#include "apue.h"

int main(void)
{
  int c = getc(stdin);
  while (c != EOF)
  {
    if (putc(c, stdout) == EOF)
    {
      err_sys("output error");
    }

    c = getc(stdin);
  }

  // 当getc出错时或到达末尾时，都会返回EOF，
  // 此函数检查是否是出错了
  if (ferror(stdin))
  {
    err_sys("input error");
  }

  return 0;
}