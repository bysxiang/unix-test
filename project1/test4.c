#include "apue.h"
#include <sys/wait.h>

// 演示执行命令

int main(void)
{
  char buf[MAXLINE];
  pid_t pid;
  int status;

  printf("%% ");
  while (fgets(buf, MAXLINE, stdin) != NULL)
  {
    if (buf[strlen(buf) - 1] == '\n')
    {
      buf[strlen(buf) - 1] = 0; // 用null替换换行符
    }

    pid = fork();
    if (pid < 0)
    {
      err_sys("fork error");
    }
    else if (pid == 0) //子进程
    {
      execlp(buf, buf, (char *)0);
      err_ret("couldn't execute: %s", buf);

      exit(127);
    }
    else //父进程
    {
      if ((pid = waitpid(pid, &status, 0)) < 0)
      {
        err_sys("waitpid error");
      }

      printf("%% ");
    }

  }

  return 0;
}