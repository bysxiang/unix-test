#include "apue.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

// 设置屏蔽位，修改默认文件的权限
// 文件默认为666, 目录为777

int main(void)
{
  umask(0);
  if (creat("foo", RWRWRW) < 0)
  {
    err_sys("creat error for foo");
  }

  umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  if (creat("bar", RWRWRW) < 0)
  {
    err_sys("creat error for bar");
  }

  return 0;
}