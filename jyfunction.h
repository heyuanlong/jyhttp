#ifndef JYFUNCTION
#define JYFUNCTION

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include "jylog.h"
#include "jyepoll.h"
extern int serverfd;

void sig_for(int sig);
void setsignal();
void read_conf(const char *,int &,int &,int &,char *);
void my_getopt(int argc, char *argv[],int &p,int &n);
void delev(jyepoll &jepoll,int fd,struct epoll_event *fordel);


#endif
