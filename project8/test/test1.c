#include "apue.h"

int		globvar = 6;		/* external variable in initialized data */

int main(void)
{
	int		var;		/* automatic variable on the stack */
	pid_t	pid;

	var = 88;
	printf("before vfork\n");	/* we don't flush stdio */
	if ((pid = vfork()) < 0) 
  {
		err_sys("vfork error");
	} 
  else if (pid == 0) /* child */
  {		
		globvar++;				/* modify parent's variables */
		var++;
    printf("执行exit(0), 等待结束 \n");
    fclose(stdout);
		exit(0);				/* child terminates */
	}

	/* parent continues here */
	int t_v = printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
  printf("printf返回值：%d\n", t_v);
	exit(0);
}
