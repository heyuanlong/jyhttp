//

#include <unistd.h>
#include <sys/epoll.h>
#include <iosteam>
#include "jydebug.h"

class jyepoll{
public:
	jyepoll(int maxev);
	~jyepoll(){ delete[] events; }


	jyepoll_add(int fd;struct epoll_event *event);
	jyepoll_del(int fd;struct epoll_event *event);
	jyepoll_mod(int fd;struct epoll_event *event);
	jyepoll_wait(int timeout);
	struct epoll_event & jyepoll_get(int i);


private:
	jyepoll(jyepoll &lhs);
	jyepoll& operator=(jyepoll &rhs);

	int fepoll,maxevents;
	struct epoll_event *events;
};

