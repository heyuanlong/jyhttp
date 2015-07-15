#include "jyfunction.h"

void sig_for(int sig)
{
    if (sig == SIGQUIT) {
        close(serverfd);
    }
    exit(-1);
}

void setsignal()
{
    struct sigaction actionquit;
    actionquit.sa_handler=sig_for;
    sigemptyset(&actionquit.sa_mask);
    actionquit.sa_flags=0;
    sigaction(SIGQUIT,&actionquit,0);

    struct sigaction actionpipe;
    actionpipe.sa_handler=SIG_IGN;
    sigemptyset(&actionpipe.sa_mask);
    actionpipe.sa_flags=0;
    sigaction(SIGPIPE,&actionpipe,0);

}

void read_conf(const char *file,int &maxe,int &p,int &n,char *logpath)
{
    FILE* fp=fopen(file,"r");
    check(fp != NULL,"open conf_file");
    char buf[1024]={0};
	int len;

    while(fgets(buf,1024,fp))
    {
		len=strlen(buf);
		if(buf[len-1]=='\n')buf[len-1]='\0';

		if(	strncmp(buf,"maxevents",9) == 0)//maxevents=1024
			maxe=atoi(buf+9+1);
		if(	strncmp(buf,"port",4) == 0)
			p=atoi(buf+4+1);
		if(	strncmp(buf,"threadnum",9) == 0)
			n=atoi(buf+9+1);
		if(	strncmp(buf,"logpath",7) == 0)
			strcpy(logpath,buf+7+1);

        check(maxe>0,"conf maxevents");
        check(p>0,"conf port");
        check(n>0,"conf threadnum");

    }
}



void my_getopt(int &p,int &n)
{
    int opt;
    while ((opt = getopt(argc, argv, "p:n:")) != -1) {
              switch (opt) {
              case 'p':
                  p = atoi(optarg);
                  break;
              case 'n':
                  n = atoi(optarg);
                  break;
              default: /* '?' */
              }
      }
}
