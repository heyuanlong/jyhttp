#makefile
.PHONY:clean all
#防止clean时出错而中断

CC1=g++ -std=c++11
CC=g++ -c -std=c++11

all:main client

client:client.cpp
	$(CC1) -o client

main:jymain.o jythead.o jysock.o jyfunction.o jyepoll.o jyhttp.o
	$(CC1) jymain.o jythead.o jysock.o jyfunction.o jyepoll.o jyhttp.o -o main -lpthread
jymain.o:
	$(CC) jymain.cpp -o jymain.o -lpthread
jythead.o:
	$(CC) jythead.cpp -o jythead.o -lpthread
jysock.o:
	$(CC) jysock.cpp -o jysock.o -lpthread
jyfunction.o:
	$(CC) jyfunction.cpp -o jyfunction.o -lpthread
jyepoll.o:
	$(CC) jyepoll.cpp -o jyepoll.o -lpthread
jyhttp.o:
	$(CC) jyhttp.cpp -o jyhttp.o -lpthread


clean:#可以在命令中输入 make clean 来执行这个规则
	$(RM) *.o main
