#ifndef _MY_SIG_H_
#define _MY_SIG_H_
#include <signal.h>
#include <string.h>
typedef void Sigfunc(int);
Sigfunc* Signal(int signo, Sigfunc* func);

#endif //_MY_SIG_H_
