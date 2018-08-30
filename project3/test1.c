#include "apue.h"

// 测试是否支持设置偏移量
// ./test1.exe < ./apue.h 将文件内容作为标准输入

int main(void)
{
  if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
  {
    printf("cannot seek\n");
  }
  else
  {
    printf("seek OK\n");
  }

  return 0;
}