#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <queue>

#include "jyconf.h"
#include "jylog.h"
#include "jyepoll.h"
#include "jydaemon.h"
#include "jymutex.h"
#include "jysock.h"
#include "jythread.h"
#include "jyfunction.h"


#define  DEBUG

 const char *conf_file="./conf.txt";
 int MAXEVENTS=1024;
 int PORT=6004;
 int THREADNUM=6;
 char logpath[1024];

jysock jsock;
jyepoll jepoll;
hmx_mutex jlock;//qfd的全局锁
jyhttp jhttp;
pthread_cond_t has_product=PTHREAD_COND_INITIALIZER;//条件变量
std::queue<int> qfd;//网络描述符

int serverfd;

int main(int argc, char const *argv[]) {
    read_conf(conf_file,MAXEVENTS,PORT,THREADNUM,logpath);
    jepoll.jyepollinit(MAXEVENTS);
    int serfd = jsock.socketinit(PORT);//开启serversocket
	serverfd=serfd;
    go_theadpool(THREADNUM);//初始化线程组

    setsignal();//设置signal处理




    struct epoll_event serepollevent;
    serepollevent.events=EPOLLIN | EPOLLET;//边缘触发
    serepollevent.data.fd=serfd;
    jepoll.add(serfd,&serepollevent);

    int n,i;
    while(1)
    {
        n=jepoll.wait(-1);//timeout为-1，表阻塞
        jlock.lock();
        for ( i = 0; i < n; i++) {
            printf("%d->", jepoll.get(i).data.fd);
            qfd.push(jepoll.get(i).data.fd);
        }
        pthread_cond_broadcast(&has_product);//通知所有子线程
        jlock.unlock();
    }


  return 0;
}
