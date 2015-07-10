#include "jythread.h"
#include "jymutex.h"

#include <string.h>
#include <queue>
#include <pthread.h>

extern jysock jsock;
extern pthread_cond_t has_product;
extern hmx_mutex jlock;
extern std::queue<int> qfd;

void go_theadpool(int num,std::queue<int> &pfd)
{
    pthread_t pid;
    //线程属性
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);//设置为分离属性

    int i;
    for ( i = 0; i < num; i++) {
        pthread_creat(&pid,&attr,workmethod,NULL);
    }
    pthread_attr_destroy(&attr);
}
void workmethod(void *arg)
{

    while(1)
    {
        jlock.lock();
        while (pfd.empty() == true) {
            pthread_cond_wait(&has_product,&(jlock.get()) );

        int fd=pfd.front();
        pfd.pop();
        jlock.unlock();
            }
        char buf[1024]={0};
        jysock.jyread(fd,buf);
        printf("%s\n", buf);
        buf="HTTP/1.1 200 OK\nServer: nginx\nDate: Fri, 10 Jul 2015 07:33:22 GMT\nContent-Type: application/x-javascript\nConnection: keep-alive\nLast-Modified: Fri, 16 Jan 2015 09:34:29 GMT\nVary: Accept-Encoding\nExpires: Wed, 06 Jan 2016 07:33:22 GMT\nCache-Control: max-age=15552000\nContent-Length: 19467\n\n
        <html><body>dddddddddddddd</body></html>";
        jysock.jywrite(fd,buf,strlen(buf));
        memset(buf,0,sizeof(buf));
        ///work
    }
}
