#include "apue.h"

// 打印出进程id

int main(void)
{
  printf("当前id：%ld\n", (long) getpid());

  return 0;
}