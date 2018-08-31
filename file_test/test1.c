#include "apue.h"
#include <unistd.h>
#include <fcntl.h>

// 接受控制台输入，写入文件中

#define BUFFSIZE 4096

int main(void)
{
  char buf[BUFFSIZE];
  int writer = open("./s1.txt", O_WRONLY);
  if (writer != -1)
  {
    if (lseek(writer, 0L, SEEK_END) != -1) // 将文件指针移到末尾
    {
      int n = read(STDIN_FILENO, buf, BUFFSIZE);
      while (n > 0)
      {
        if (write(writer, buf, n) != n)
        {
          err_sys("write error");
        }

        n = read(STDIN_FILENO, buf, BUFFSIZE);
      } // while .. end
    } 
    else
    {
      err_sys("seek error");
    }
  }
  else
  {
    err_sys("不能打开s1.txt");
  }

  printf("写入完毕");

  return 0;
}