#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>



int clientConnectServer(char const *ip, int port);


int main(int argc, char const *argv[])
{
	int clientSocket = clientConnectServer("127.0.0.1", atoi(argv[1]));


	char recvbuf[1024]="qwertyuiop";
	char sendbuf[1024]="123456789";


		size_t len=strlen(sendbuf);
		ssize_t sendnum=0;
		while(sendnum < len)
		  sendnum=send(clientSocket,sendbuf+sendnum,len-sendnum,0);



		ssize_t recvnum=0;
		while(recvnum < len)
		recvnum=recv(clientSocket,recvbuf+recvnum,1024,0);
	    recvbuf[recvnum]='\0';
	    printf("%s\n", recvbuf);



	close(clientSocket);
	return 0;
}





int clientConnectServer(char const *ip, int port)
{
	//socket
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket == -1)
	{
		perror("client socket");
		exit(1);
	}
	
	//connetc
	struct sockaddr_in clientSockAddr;
	memset(&clientSockAddr, 0, sizeof(clientSockAddr));

	clientSockAddr.sin_family = AF_INET;
	clientSockAddr.sin_port = htons(port);
	clientSockAddr.sin_addr.s_addr = inet_addr(ip);

	if(connect(clientSocket, (struct sockaddr *)&clientSockAddr, sizeof(struct sockaddr)) == -1)
	{
		perror("client connect");
		close(clientSocket);
		exit(1);
	}

	printf("already connected to the server\n");

	return clientSocket;
}