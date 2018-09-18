#include "apue.h"

int main(void)
{
  // 子进程的进程组id是父进程的进程id
  // main进程的进程组id等于它的进程id
  pid_t pid = fork();
  if (pid == 0)
  {
    printf("pid: %d, pgid: %d\n", (int) getpid(), (int) getpgrp());
  }
  else if (pid > 0)
  {
    printf("main pid: %d，pgid: %d\n", getpid(), getpgrp());

    waitpid(pid, NULL, 0);
  }

  return 0;
}