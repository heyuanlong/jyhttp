#ifndef JYLOG
#define JYLOG

#include <errno.h>

//sterror是非线程安全函数

#define clean_errno() (errno==0? "none" : strerror(errno))
#define log_err(M,...) {fprintf(stderr, "ERROR=%s:%d :errno: %s.....because->" M "\n",__FILE__, __LINE__, clean_errno(), ##__VA_ARGS__);exit(-1);}
#define check(A,M,...) if (!(A)) {log_err(M,##__VA_ARGS__);}

#define log_warn(M,...) fprintf(stderr, "WARN=%s:%d :errno: %s.....because->" M "\n",__FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
#define log_info(M,...) fprintf(stderr, "INFO=%s:%d :.....because->" M "\n",__FILE__, __LINE__, ##__VA_ARGS__)



#ifdef DEBUG
  #define  debug(M,...) fprintf(stdout, "DEBUG %s:%d: --->" M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
  #else
   #define  debug(M,...)
#endif



#endif
