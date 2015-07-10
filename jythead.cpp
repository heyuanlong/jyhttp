#include <string.h>
#include <queue>
#include <pthread.h>

#include "jyconf.h"
#include "jylog.h"
#include "jyepoll.h"

#include "jymutex.h"
#include "jysock.h"
#include "jythread.h"

extern jyepoll jepoll;
extern jysock jsock;
extern pthread_cond_t has_product;
extern hmx_mutex jlock;
extern std::queue<int> qfd;



extern int serverfd;


void go_theadpool(int num)
{
    pthread_t pid;
    //线程属性
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);//设置为分离属性

    int i;
    for ( i = 0; i < num; i++) {
        pthread_create(&pid,&attr,workmethod,NULL);
    }
    pthread_attr_destroy(&attr);
}
void* workmethod(void *arg)
{
int fd;
struct epoll_event epollevent;
epollevent.events=EPOLLIN | EPOLLET;//边缘触发
//epollevent.data.fd=serfd;

    while(1)
    {
        jlock.lock();

        while (qfd.empty() == true)
            pthread_cond_wait(&has_product,&(jlock.get()) );

        fd=qfd.front();
        qfd.pop();
        jlock.unlock();

		printf("%d   %d\n", fd,serverfd);

        if(fd==serverfd){
            int ac=jsock.acceptsocket();
            epollevent.data.fd=ac;
            jepoll.add(ac,&epollevent);
            continue;
        }
        char buf[1024]={0};
		printf("1\n");
        jsock.jyread(fd,buf);

        printf("%s\n", buf);

    //     HTTP/1.1 200 OK
    // Server: Apache-Coyote/1.1
    // P3P: CP="NOI DEVa TAIa OUR BUS UNI"
    // Cache-Control: no-cache
    // Expires: 0
    // Pragma: No-cache
    // Content-Type: text/json;charset=UTF-8
    // Content-Language: zh-CN
    // Content-Length: 4
    // Date: Fri, 10 Jul 2015 09:41:51 GMT
    // Connection: close
    // Set-Cookie: gray=82493; Max-Age=30758400; Path=/; Domain=.yhd.com
    // 
    // null   

        strcpy(buf,"HTTP/1.1 200 OK\nServer: jyhttp\nContent-Type: text/html;charset=UTF-8\nContent-Length: 40\r\n\r\n<html><body>dddddddddddddd</body></html>");
       printf("%s\n",buf );
        jsock.jywrite(fd,buf,strlen(buf));
        memset(buf,0,sizeof(buf));
        ///work
    }
}
