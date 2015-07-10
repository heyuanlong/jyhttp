#makefile
.PHONY:clean
#防止clean时出错而中断

CC1=g++ -std=c++11
CC=g++ -c -std=c++11

main:jymain.o jythead.o jysock.o jyfunction.o jyepoll.o jyconf.o
	$(CC1) jymain.o jythead.o jysock.o jyfunction.o jyepoll.o jyconf.o -o main -lpthread
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
jyconf.o:
	$(CC) jyconf.cpp -o jyconf.o -lpthread


clean:#可以在命令中输入 make clean 来执行这个规则
	$(RM) *.o main
