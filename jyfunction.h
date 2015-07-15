#ifndef JYFUNCTION
#define JYFUNCTION

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#include "jylog.h"
extern int serverfd;

void sig_for(int sig);
void setsignal();
void read_conf(const char *,int &,int &,int &,char *);
void my_getopt(int &,int &);

#endif
