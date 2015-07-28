#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <queue>


#include "jylog.h"
#include "jyepoll.h"
#include "jydaemon.h"
#include "jymutex.h"
#include "jysock.h"
#include "jythread.h"
#include "jyfunction.h"
#include "jyhttp.h"

#define  DEBUG

 const char *conf_file="./conf.txt";
 int MAXEVENTS;
 int PORT;
 int THREADNUM;
 char logpath[1024];

jysock jsock;
jyepoll jepoll;
hmx_mutex jlock;//qfd的全局锁
pthread_cond_t has_product=PTHREAD_COND_INITIALIZER;//条件变量
std::queue<int> qfd;//网络描述符

int serverfd;

int main(int argc, char *argv[]) {

    read_conf(conf_file,MAXEVENTS,PORT,THREADNUM,logpath);
    my_getopt(argc,argv,PORT,THREADNUM);


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
    struct epoll_event fordelepoll;
    while(1)
    {
        n=jepoll.wait(-1);//timeout为-1，表阻塞
        jlock.lock();
        printf("epoll wait 到 %d 个描述符\n", n);
        for ( i = 0; i < n; i++) {

            if (  jepoll.get(i).events & EPOLLERR  )
            {
                fprintf (stderr, "epoll EPOLLERR\n");
                delev(jepoll,i,&fordelepoll);
                continue;
            }
            if (  jepoll.get(i).events & EPOLLHUP  )
            {
                fprintf (stderr, "epoll EPOLLHUP\n");
                delev(jepoll,i,&fordelepoll);
                continue;
            }

            printf("push进 %d  描述符\n", jepoll.get(i).data.fd);
            qfd.push(jepoll.get(i).data.fd);
        }
        pthread_cond_broadcast(&has_product);//通知所有子线程
        jlock.unlock();
    }


  return 0;
}



/*
1.当客户端关闭tcp链接时候 或者 客户端挂掉，服务端的epoll接受到EPOLLERR
2.360浏览器：一段时间后会自动关闭tcp，  IE浏览器不会自动关闭tcp链接。所以确保浪费资源，还得让服务器在满足一定条件的情况下主动关闭tcp链接。




*/
