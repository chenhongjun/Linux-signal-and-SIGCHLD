#include "signal.h"

Sigfunc* Signal(int signo, Sigfunc* func)
{
	struct sigaction act, oact;
	memset(&act, 0 , sizeof(act));
	memset(&oact, 0 , sizeof(oact));
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);//�ڸ��źŴ����������ڼ䣬������������ź�
	act.sa_flags = 0;
	if (signo == SIGALRM)//�������ڳ�ʱ�ж�ϵͳ���ã����Բ���Ϊ�ж�����
	{
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
#endif
	}
	else 
	{
#ifdef SA_RESTART//ϵͳ�иù��ܣ�����Ӧ�ź��жϵ�ϵͳ���ý����ں��Զ�������
		act.sa_flags |= SA_RESTART;
#endif
	}
	if (sigaction(signo, &act, &oact) < 0)
	  return SIG_ERR;
	return oact.sa_handler;
}

/*//��ʬ���̵Ĵ���
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
