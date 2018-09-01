#include "apue.h"

int main(void)
{
  struct stat statbuf;

  // 设置set-group-ID，关闭组执行权限
  if (stat("foo", &statbuf) < 0)
  {
    err_sys("stat error for foo");
  }
  if (chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
  {
    err_sys("chmod error for foo");
  }

  // 设置绝对全新 "rw-r--r--"
  if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
  {
    err_sys("chmod error for bar");
  }

  return 0;
}