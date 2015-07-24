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
    // nread=jyreadn(fd,buf,1024);
	 printf("recv:%d-------revc 完毕\n",nread);
     return nread;
 }
int jysock::jywrite(int fd,char *buf,size_t len)
{
    int nread;
	 printf("下面是send\n");
    nread=send(fd,buf,len,0);
    //nread = jywriten(fd,buf,len);
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

ssize_t jysock::jyreadn(int fd,char *ptr,size_t n)
{
    size_t nleft;
    ssize_t nread;
    nleft=n;
    while (nleft > 0 ) {
        if ( (nread = recv(fd,ptr,nleft,0)) <0 ) {
            if (nleft  == n)
                return -1;
            else
                break;
        }
        else if(nread == 0) {
                break;
            }

        nleft -=nread;
        ptr +=nread;

    }
    return (n-nleft);
}


ssize_t jysock::jywriten(int fd,const char *ptr,size_t n)
{
    size_t nleft;
    ssize_t nwrite;
    nleft=n;

    while (nleft > 0) {
        if ( (nwrite = send(fd,ptr,nleft,0)) <0 ) {
            if (nleft == n)
                return -1;
            else
                break;
        }
        else if (nwrite == 0) {
                break;
            }

        nleft -=nwrite;
        ptr +=nwrite;
    }
    return (n-nleft);
}
