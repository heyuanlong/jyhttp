#include "jysock.h"
#include "jylog.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int jysock::socketinit(int n)
{
    port=n;
    serverfd=socket(AF_INET,SOCK_STREAM,0);
    check(serverfd>0,"socket init");

    struct sockaddr_in saddr;
    bzero(&saddr,sizeof(saddr));
    saddr.sin_family=AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int b=bind(serverfd,(struct sockaddr *)&saddr,sizeof(saddr));
    check(b == 0,"bind");
    int l=listen(serverfd,listennum);
    check(l == 0,"listen");
    set_socket_nonblock(serverfd);
    return serverfd;
}
int jysock::acceptsocket()
{
    int ac=accept(serverfd,NULL,0);
    if (ac>=0) {
        set_socket_nonblock(ac);
    }
    return ac;
}
int jysock::jyread(int fd,char *buf)
 {
     int nread;
	 printf("下面是recv\n");
     nread=recv(fd,buf,1024,0);
	 printf("recv:%d\n-------revc 完毕\n",nread);
     return nread;
 }
int jysock::jywrite(int fd,char *buf,size_t len)
{
    int nread;
	 printf("下面是send\n");
    nread=send(fd,buf,len,0);
	printf("send:%d\n--------send 完毕\n",nread);
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
