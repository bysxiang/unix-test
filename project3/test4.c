#include "apue.h"
#include <fcntl.h>

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    err_quit("usage: a.out <descriptor#>");
  }

  int a = atoi(argv[1]);
  printf("输出a: %d\n", a);

  int val = fcntl(a, F_GETFL, 0);
  if (val < 0)
  {
    err_sys("fcntl error for fd %d", atoi(argv[1]));
  }

  int temp_val = val & O_ACCMODE;
  if (temp_val == O_RDONLY)
  {
    printf("read only");
  }
  else if (temp_val == O_WRONLY)
  {
    printf("write only");
  }
  else if (temp_val == O_RDWR)
  {
    printf("read write");
  }
  else
  {
    err_dump("unknown access mode");
  }

  if (val & O_APPEND)
  {
    printf(", append");
  }

  if (val & O_NONBLOCK)
  {
    printf(", nonblocking");
  }

  if (val & O_SYNC)
  {
    printf(", synchronous writes");
  }

  #if ! defined(_POSIX_C_SOURCE) && defined(O_SYNC) && (O_FSYNC != O_SYNC)
    if (val & O_FSYNC)
    {
      printf(", synchronous writes");
    }
  #endif



  return 0;
}