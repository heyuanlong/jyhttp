#include <unistd.h>
#include <errno.h>
#include <queue>

#include "jyconf.h"
#include "jylog.h"
#include "jyepoll.h"
#include "jydaemon.h"

const int MAXEVENTS=1024;
const int PORT=6000;

jysock jsock(PORT);
jyepoll jepoll(MAXEVENTS);
std::queue<int> qfd;//网络描述符

int main(int argc, char const *argv[]) {
    int serfd = jsock.socketinit();

    struct epoll_event serepollevent;
    serepollevent.events=EPOLLIN | EPOLLET;//边缘触发
    serepollevent.data.fd=serfd;
    jsock.add(serfd,&serepollevent);

    int n;
    while(1)
    {
        n=jsock.wait(-1);//timeout为-1，表阻塞

    }






  return 0;
}
