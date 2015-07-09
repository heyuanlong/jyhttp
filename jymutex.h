#ifndef JYMUTEX
#define JYMUTEX

#include <pthread.h>

//锁被多次释放会怎么样，如何处理
//答：linux经测试，unlock过多，没有什么影响。



class hmx_mutex
{
public:
hmx_mutex()
	{
	pthread_mutex_init(&mutex, NULL);
	}
~hmx_mutex()
	{
	pthread_mutex_destroy(&mutex);
	}

void lock()
	{
	pthread_mutex_lock(&mutex);
	}

void unlock()
	{
	pthread_mutex_unlock(&mutex);
	}

private:
    pthread_mutex_t mutex;
};

#endif
