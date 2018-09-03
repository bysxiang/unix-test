#include "apue.h"
#include <fcntl.h>

int main(int argc, char * argv[])
{
  int i, fd;
  struct stat statbuf;
  struct timespec times[2];
  for (i = 1; i < argc; i++)
  {
    if (stat(argv[i], &statbuf) < 0) // 获取当前时间
    {
      err_ret("%s: stat error", argv[i]);
    }
    else
    {
      fd = open(argv[i], O_RDWR | O_TRUNC);
      if (fd < 0)
      {
        err_sys("%s: open error", argv[i]);
      }
      else
      {
        times[0] = statbuf.st_atim;
        times[1] = statbuf.st_mtim;
        if (futimens(fd, times) < 0) // 重置时间
        {
          err_ret("%s: futimens error", argv[i]);
        }

        close(fd);
      }
    }
  } // for .. end

  return 0;
}