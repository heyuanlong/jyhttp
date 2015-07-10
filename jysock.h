#ifndef JYSOCK
#define JYSOCK

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

class jysock{
public:
  jysock(){};
  ~jysock(){close(serverfd);};

  int socketinit(int n);
  int acceptsocket();
  int jyread(int fd,char *buf);
  int jywrite(int fd,char *buf,size_t len);

private:
  jysock(jysock &lhs);
  jysock& operator=(jysock &rhs);
  void set_socket_nonblock(int fd);

  int serverfd;
  int port;
  enum{listennum=128};
};



#endif
