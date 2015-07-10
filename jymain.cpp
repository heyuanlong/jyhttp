#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <queue>

#include "jyconf.h"
#include "jylog.h"
#include "jyepoll.h"
#include "jydaemon.h"
#include "jymutex.h"

const int MAXEVENTS=1024;
const int PORT=6000;
const int THREADNUM=6000;

jysock jsock(PORT);
jyepoll jepoll(MAXEVENTS);
hmx_mutex jlock;//qfd的全局锁
pthread_cond_t has_product=PTHREAD_COND_INITIALIZER;//条件变量
std::queue<int> qfd;//网络描述符


int main(int argc, char const *argv[]) {
    int serfd = jsock.socketinit();//开启serversocket
    go_theadpool(THREADNUM,qfd);//初始化线程组

    struct epoll_event serepollevent;
    serepollevent.events=EPOLLIN | EPOLLET;//边缘触发
    serepollevent.data.fd=serfd;
    jsock.add(serfd,&serepollevent);

    int n,i;
    while(1)
    {
        n=jsock.wait(-1);//timeout为-1，表阻塞
        jlock.lock();
        for ( i = 0; i < n; i++) {
            qfd.push(jsock.get(i).data.fd);
        }
        pthread_cond_broadcast(&has_product);//通知所有子线程
        jlock.unlock();
    }


  return 0;
}
