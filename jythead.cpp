##include "jythread.h"

extern pthread_cond_t has_product;

void go_theadpool(int num,std::queue<int> &pfd,hmx_mutex &jlock)
{
    struct thread_arg targ={pfd,jlock};
    pthread_t pid;
    //线程属性
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);//设置为分离属性

    int i;
    for ( i = 0; i < num; i++) {
        pthread_creat(&pid,&attr,workmethod,&targ);
    }
    pthread_attr_destroy(&attr);
}
void workmethod(void *arg)
{
    std::queue<int> &pfd=(struct thread_arg*)arg->que;
    hmx_mutex &jlock=(struct thread_arg*)arg->mut;

    while(1)
    {
        jlock.lock();
        while (pfd.empty() == true) {
            pthread_cond_wait(&has_product,&(jlock.get()) );

        int fd=pfd.front();
        pfd.pop();
        jlock.unlock();
            }

        ///work
    }
}
