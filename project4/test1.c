#include "apue.h"

int main(int argc, char * argv[])
{
  int i;
  struct stat buf; // buf是stat这种结构的一个变量
  char * ptr;

  for (i = 1; i < argc; i++)
  {
    printf("%s: ", argv[i]);
    if (lstat(argv[i], &buf) < 0)
    {
      err_ret("lstat error");
    }
    else
    {
      if (S_ISREG(buf.st_mode))
      {
        ptr = "regular";
      }
      else if (S_ISDIR(buf.st_mode))
      {
        ptr = "directory";
      }
      else if (S_ISBLK(buf.st_mode))
      {
        ptr = "block special";
      }
      else if (S_ISFIFO(buf.st_mode))
      {
        ptr = "fifo";
      }
      else if (S_ISLNK(buf.st_mode))
      {
        ptr = "symbolic link";
      }
      else if (S_ISSOCK(buf.st_mode))
      {
        ptr = "socket";
      }
      else
      {
        ptr = "** unkown mode **";
      }

      printf("%s\n", ptr);
    }
  } // for .. end

  return 0;
}