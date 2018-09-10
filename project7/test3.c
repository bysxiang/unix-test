#include "apue.h"

// 显示命令行参数

int main(int argc, char * argv [])
{
  int i;
  for (i = 0; i < argc; i++)
  {
    printf("argv[%d]: %s\n", i, argv[i]);
  }

  exit(0);
}