#include "jyhttp.h"

#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int jyhttp::parse(char *request)
{
    char method[5]={0};
    char path[1024]={0};
    char ht[10]={0};
    sscanf(request,"%s %s %s",method,path,ht);
    printf("分析request的第一行：%s %s %s\n",method,path,ht );

    if (strcmp(method,"GET") == 0) {
    }

    int len=strlen(path);
    for (int i = len-1; i >= 0 ; --i) {
        path[i+1]=path[i];
    }
    path[0]='.';
    printf("分析request的第一行：%s %s %s\n",method,path,ht );

    struct stat fileinfo;
    stat(path,&fileinfo);
    printf("%s --->size = %d\n",path,(int)fileinfo.st_size);



    strcpy(this->method,method);
    strcpy(filepath,path);
    filesize=(int)fileinfo.st_size;

    return 0;
}
int jyhttp::compound(char *response)
{


    return 0;
}
