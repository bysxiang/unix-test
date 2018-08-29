#include "apue.h"
#include <errno.h>

// 展示错误处理

int main(int argc, char * argv[])
{
  // strerror函数 将一个错误常量转换为字符串
  char * str = strerror(EACCES);

  printf("str: %s", str);

  fprintf(stderr, "EACCES: %s\n", str);
  errno = ENOENT;
  // perror 用于将errno的错误信息输出
  perror(argv[0]);

  return 0;
}