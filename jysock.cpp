#include "jysock.h"

int jysock::socketinit()
{
    serverfd=socket(AF_INET,SOCK_STREAM,0);
    check(serverfd>0,"socket init");

    struct sockaddr_in saddr;
    bzero(&addr,sizeof(addr));
    saddr.sin_family=AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int b=bind(s_addr,(struct sockaddr *)&saddr,sizeof(strcut sockaddr));
    check(b>0,"bind");
    int l=listen(saddr,listennum);
    check(l>0,"listen");
    set_socket_nonblock(serverfd);
    return serverfd;
}
int jysock::acceptsocket()
{
    int ac=accept(serverfd,NULL,0);
    if (ac>0) {
        set_socket_nonblock(ac);
    }
    return ac;
}
void jysock::set_socket_nonblock(int fd)
{
   int flag,s;
   flag = fcntl(fd,F_GETFL,0);
   check(flag != -1,"fcntl");

   flag |= O_NONBLOCK;
   s=fcntl(fd,F_SETFL,flag);
   check(s != -1,"fcntl");
}
