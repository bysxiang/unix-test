// 习题8.2

#include "apue.h"

void f1();

int main(void)
{
  printf("调用方\n");

  // 会产生段错误，因为vfork子进程中返回会破坏栈帧结构。，它运行在父进程的地址空间中
  f1();
  

  printf("我是父进程\n");
  return 0;
}

void f1()
{
  pid_t pid = vfork();
  if (pid == 0) // 子进程
  {
    printf("现在在子进程中\n");

    // 如果
    return;
  }
}
