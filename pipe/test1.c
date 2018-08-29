#include <stdio.h>
#include <sys/wait.h>
#include "apue.h"

int main(void)
{
  int n;
  int fd[2]; // 存储管道 读句柄，写句柄
  pid_t pid;
  char line[MAXLINE];
  int status;

  if (pipe(fd) < 0)
  {
    err_sys("pipe error");
  }

  pid = fork();
  if ( pid < 0 )
  {
    err_sys("fork error");
  }
  else if (pid > 0) // 父进程
  {
    printf("进入父进程\n");

    sleep(1);

    close(fd[0]);
    write(fd[1], "hello world\n", 12);

    if (wait(&status) != pid)
    {
      err_sys("waitpid error");
    }
    
    printf("父进程结束\n");
  }
  else
  {
    printf("进入子进程\n");

    close(fd[1]);
    n = read(fd[0], line, MAXLINE);
    write(STDOUT_FILENO, line, n);

    int x = sleep(3);

    printf("子进程结束\n");
  }

  exit(0);
}