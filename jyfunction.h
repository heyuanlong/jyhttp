#ifndef JYFUNCTION
#define JYFUNCTION

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include "jylog.h"
#include "jyepoll.h"

struct contentstruct
{
    char filetype[10];//由于之前这里设置为5，长度不够，导致当type过长时，回接着输出contenttype值。
    char contenttype[50];
};


extern int serverfd;

void sig_for(int sig);
void setsignal();
void read_conf(const char *,int &,int &,int &,char *);
void my_getopt(int argc, char *argv[],int &p,int &n);
void delev(jyepoll &jepoll,int fd,struct epoll_event *fordel);
void read_content_type(struct contentstruct *str,int len);

#endif
