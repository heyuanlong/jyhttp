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
int jyread(int fd,char *buf)
 {
     int nread;
     nread=read(fd,buf,1024);
     return nread;
 }
int jywrite(int fd,char *buf,size_t len)
{
    int nread;
    nread=write(fd,buf,len);
    return nread;
}



void jysock::set_socket_nonblock(int fd)
{
   int s;
   s=fcntl(fd,F_SETFL,fcntl(fd,F_GETFL,0) | O_NONBLOCK);
   check(s != -1,"fcntl");

//int  nb;
//nb = 1;
//return ioctl(s, FIONBIO, &nb);
}
