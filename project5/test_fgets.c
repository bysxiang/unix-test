#include "apue.h"

// 测试输入超过缓冲区长度
// fgets只从stdin中接收指定长度的数据
// 那些超出的还在stdin(键盘、文件)中，
// 需要再次通过fgets函数读取，而却
// 不需要再次回车，这些数据也并不会丢失

int main(void)
{
  int len = 5;
  char buf[len];

  char * str = fgets(buf, len, stdin);
  fputs(buf, stdout);

  printf("\n再次读取输入\n");


  fgets(buf, len, stdin);
  fputs(buf, stdout);

  if (ferror(stdin))
  {
    err_sys("input error");
  }

  return 0;
}