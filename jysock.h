#ifndef JYSOCK
#define JYSOCK

jysock{
  jysock(int p):post(p){};
  ~jysock(){close(serverfd)};

  int socketinit();
  int acceptsocket();
  int set_socket_nonblock(int fd);


private:
  jysock(jysock &lhs);
  jysock& operator=(jysock &rhs);

  int serverfd;
  int port;
};



#endif
