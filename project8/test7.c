#include "apue.h"
#include <sys/wait.h>

char	*env_init[] = { "USER=unknown", "PATH=/tmp", NULL };

int main(void)
{
	pid_t	pid;

	if ((pid = fork()) < 0) 
  {
		err_sys("fork error");
	} 
  else if (pid == 0) /* 指定路径，指定环境变量 */
  {	
    // 传递的路径参数，需要包含eachall.exe
		if (execle("/home/ybs/bin/echoall.exe", "echoall.exe", "myarg1",
				"MY ARG2", (char *)0, env_init) < 0)
			err_sys("execle error");
	}

	if (waitpid(pid, NULL, 0) < 0)
		err_sys("wait error");

	if ((pid = fork()) < 0) 
  {
		err_sys("fork error");
	} 
  else if (pid == 0) /* specify filename, inherit environment */
  {	
		if (execlp("echoall.exe", "echoall.exe", "only 1 arg", (char *)0) < 0)
			err_sys("execlp error");
	}

	exit(0);
}
