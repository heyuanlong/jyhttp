#ifndef JYSOCK
#define JYSOCK

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

jysock{
  jysock(int p):post(p){};
  ~jysock(){close(serverfd)};

  int socketinit();
  int acceptsocket();

private:
  jysock(jysock &lhs);
  jysock& operator=(jysock &rhs);
  void set_socket_nonblock(int fd);

  int serverfd;
  int port;
  enum{listennum=128;}
};



#endif
