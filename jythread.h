#ifndef JYTHREAD
#define JYTHREAD
#include <queue>
#include "jymutex.h"

void go_theadpool(int num,std::queue<int> &pfd,hmx_mutex &jlock);
void workmethod();

#endif
