#ifndef JYTHREAD
#define JYTHREAD
#include <queue>
#include "jymutex.h"

// struct thread_arg
// {
//     std::queue<int> &que;
//     hmx_mutex &mut;
// };



void go_theadpool(int num);
void* workmethod(void *arg);

#endif
