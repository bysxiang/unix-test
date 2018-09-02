#include "apue.h"
#include <fcntl.h>

// 实例4-16, 打开一个文件，解除它的链接。然后进程睡眠15秒，接着终止。

int main(void)
{
  if (open("tempfile", O_RDWR) < 0)
  {
    err_sys("open error");
  }

  if (unlink("tempfile") < 0)
  {
    err_sys("unlink error");
  }
  printf("file unlinked\n");
  sleep(15);
  printf("done\n");

  return 0;
}