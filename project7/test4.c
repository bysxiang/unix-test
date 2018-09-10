#include "apue.h"
#include <setjmp.h>

// setjmp和longjmp

#define TOK_ADD 5

jmp_buf jmpbuffer;

void do_line(char *);
void cmd_add(void);
int get_token(void);

int main(void)
{
  char line[MAXLINE];

  if (setjmp(jmpbuffer) != 0)
  {
    printf("error");
  }

  while (fgets(line, MAXLINE, stdin) != NULL)
  {
    do_line(line);
  }

  exit(0);
}

char * tok_ptr; // get_token()全局指针

void do_line(char * ptr)
{
  int cmd;

  tok_ptr = ptr;
  cmd = get_token();
  while (cmd > 0)
  {
    if (cmd == TOK_ADD)
    {
      cmd_add();
    }
    cmd = get_token();
  }
}

void cmd_add(void)
{
  int token = get_token();
  if (token < 0)
  {
    longjmp(jmpbuffer, 1);
  }
  // 此命令的其余处理
}

int get_token(void)
{
  // 从tok_ptr指向的行获取下一个输入
}