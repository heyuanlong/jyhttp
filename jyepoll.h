#ifndef JYEPOLL
#define JYEPOLL

#include <unistd.h>
#include <sys/epoll.h>
#include <iosteam>
#include "jydebug.h"

class jyepoll{
public:
	jyepoll(int maxev);
	~jyepoll(){ free events; }


	void add(int fd;struct epoll_event *event);
	void del(int fd;struct epoll_event *event);
	void mod(int fd;struct epoll_event *event);
	int wait(int timeout);
	struct epoll_event& get(int i);


private:
	jyepoll(jyepoll &lhs);
	jyepoll& operator=(jyepoll &rhs);

	int fepoll,maxevents;
	struct epoll_event *events;
};

#endif
