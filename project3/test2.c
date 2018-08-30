#include "apue.h"
#include <fcntl.h>

// 创建一个空洞文件

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void)
{
  int fd = creat("file.hole", FILE_MODE);
  if (fd < 0)
  {
    err_sys("creat error");
  }

  if (write(fd, buf1, 10) != 10)
  {
    err_sys("buf1 write error");
  }

  if (lseek(fd, 16384, SEEK_SET) == -1)
  {
    err_sys("lseek error");
  }

  if (write(fd, buf2, 10) != 10)
  {
    err_sys("buf2 write error");
  }

  return 0;
}