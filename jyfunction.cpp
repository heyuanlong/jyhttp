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
