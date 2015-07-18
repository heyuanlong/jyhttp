#include <string.h>
#include <queue>
#include <pthread.h>

#include "jylog.h"
#include "jyepoll.h"

#include "jymutex.h"
#include "jysock.h"
#include "jythread.h"
#include "jyhttp.h"

extern jyepoll jepoll;
extern jysock jsock;
extern pthread_cond_t has_product;
extern hmx_mutex jlock;
extern jyhttp jhttp;
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
            printf("get a fd:%d\n", ac);
            continue;
        }
        char request[1024]={0};
        char response[1048576]={0};//1M
		debug(go);
        jsock.jyread(fd,request);
        jhttp.run(request,response);
        //



        //printf("%s\n", buf);

    // HTTP/1.1 200 OK
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


    //jsock.jywrite(fd,response,strlen(response));
    //memset(buf,0,sizeof(request));

        strcpy(response,"HTTP/1.1 200 OK\nServer: jyhttp\nContent-Type: text/html;charset=UTF-8\nContent-Length: 40\r\n\r\n<html><body>dddddddddddddd</body></html>");
        printf("%s\n",response );
        jsock.jywrite(fd,response,strlen(response));
        memset(response,0,sizeof(response));


    //    jepoll.del(fd,&epollevent);//某些情况会报错
    //    close(fd);///可能重复关闭

    //如何保持长链接，何时关闭链接，如何保证不会重复jepoll.del和close
    //短链接呢？   http的知识不够！！！！

        ///work
    }
}





// HTTP/1.1 200 OK
// Server: JSP3/2.0.8
// Date: Wed, 15 Jul 2015 09:06:34 GMT
// Content-Type: image/jpeg
// Content-Length: 37960
// Connection: keep-alive
// ETag: b1d2062a8a094f493056bd4a4893a817
// Last-Modified: Thu, 01 Jan 1970 00:00:00 GMT
// Expires: Thu, 23 Jul 2015 20:15:58 GMT
// Age: 1896636
// Cache-Control: max-age=2628000
// Access-Control-Allow-Origin: *
// Timing-Allow-Origin: http://pos.baidu.com
//
//      JFIF   


//Content-Type: image/png
//Content-Type: image/gif
    //
