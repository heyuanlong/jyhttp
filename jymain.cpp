#include <unistd.h>
#include <errno.h>
#include <queue>

#include "jyconf.h"
#include "jylog.h"
#include "jyepoll.h"
#include "jydaemon.h"

const int MAXEVENTS=1024;
const int PORT=6000;

jysock jsock(PORT);
jyepoll jepoll(MAXEVENTS);
std::queue<int> qfd;//网络描述符

int main(int argc, char const *argv[]) {






  return 0;
}
