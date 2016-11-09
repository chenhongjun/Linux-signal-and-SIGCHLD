#include "signal.h"

Sigfunc* Signal(int signo, Sigfunc* func)
{
	struct sigaction act, oact;
	memset(&act, 0 , sizeof(act));
	memset(&oact, 0 , sizeof(oact));
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);//在该信号处理函数运行期间，不阻塞额外的信号
	act.sa_flags = 0;
	if (signo == SIGALRM)//闹钟用于超时中断系统调用，所以不设为中断自启
	{
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
#endif
	}
	else 
	{
#ifdef SA_RESTART//系统有该功能（由相应信号中断的系统调用将由内核自动重启）
		act.sa_flags |= SA_RESTART;
#endif
	}
	if (sigaction(signo, &act, &oact) < 0)
	  return SIG_ERR;
	return oact.sa_handler;
}

/*//僵尸进程的处理
 * void sig_chld(int signo)
 *{
 *		pid_t pid;
 *		int stat;
 *		pid = wait(&stat);
 *		printf("child %d terminated.  stat: %d.\n", pid, stat);
 *		return;
 *}
 *Signal(SIGCHLD, sig_chld);
 */
