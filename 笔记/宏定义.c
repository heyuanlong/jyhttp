#include<stdio.h>
#include<string.h>
#include <errno.h>
#include <stdlib.h>

#define clean_errno() (errno == 0 ? "None" : strerror(errno))
#define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); /* exit(1); */ }

int main()
{
int i=5;
int ij=0;
check(i>0,"gggg");
check(ij>0,"fuck","dfsdfsdfssd","ddddddddddd");
}