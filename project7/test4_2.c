#include "apue.h"
#include <setjmp.h>

// 测试  setjmp和longjmp

jmp_buf jmpbuffer;

void f1(int);

//void f2(int);

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    printf("请键入命令行参数\n");
  }
  else
  {
    int a = 5;
    int val = setjmp(jmpbuffer);
    if (val != 0)
    {
      printf("f1出错跳转回来, argv[1]: %s, a = %d\n", argv[1], a);
      exit(0);
    }
    else
    {
      printf("val值：%d\n", val);
    }

    a = 6;
    printf("argv[1]: %s\n", argv[1]);


    f1(atoi(argv[1]));
  }

  exit(0);
}

void f1(int a)
{
  if (a == 1)
  {
    printf("f1 出错跳转");
    longjmp(jmpbuffer, 1);
  }
  else
  {
    printf("f1执行完毕");
  }
}