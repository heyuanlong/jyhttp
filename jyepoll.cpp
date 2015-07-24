#include "jyepoll.h"

#include "jylog.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void jyepoll::jyepollinit(int maxev)
{
	maxevents=maxev;
	fepoll=epoll_create1(0);
	check(fepoll>0,"epoll_create1");

	events=(struct epoll_event*)malloc(sizeof(struct epoll_event) * maxevents);
	check(events!=NULL,"malloc");

}
void jyepoll::add(int fd,struct epoll_event *event)
{
	printf("epoll add %d 描述符\n",fd );
  int ad=epoll_ctl(fepoll,EPOLL_CTL_ADD,fd,event);
	check(ad==0,"EPOLL_CTL_ADD");
}
void jyepoll::del(int fd,struct epoll_event *event)
{
	int ad=epoll_ctl(fepoll,EPOLL_CTL_DEL,fd,event);
	check(ad==0,"EPOLL_CTL_DEL");
}
void jyepoll::mod(int fd,struct epoll_event *event)
{
	int ad=epoll_ctl(fepoll,EPOLL_CTL_MOD,fd,event);
	check(ad==0,"EPOLL_CTL_MOD");
}
int jyepoll::wait(int timeout)
{
	int n=epoll_wait(fepoll,events,maxevents,timeout);
	check(n>=0,"epoll_wait");
	return n;
}
struct epoll_event& jyepoll::get(int i)
{
	//如何检查i的值是否合法呢？
		return events[i];
}
