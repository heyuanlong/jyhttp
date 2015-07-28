#include "jyhttp.h"

#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

extern char **content_type;//可能编译失败

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
    int st = stat(path,&fileinfo);
    if (-1 == st) {
        printf("%s : 访问这个文件时出错！！\n",path);
        fileinfo.st_size=0;
    }
    else
    printf("%s --->size = %d\n",path,(int)fileinfo.st_size);


    strcpy(this->method,method);//获取method，文件相对路径，文件大小
    strcpy(filepath,path);
    filesize=(int)fileinfo.st_size;

    return 0;
}
int jyhttp::compound(char *response)
{

   //先判断文件大小
    return 0;
}






//
//
// stat系列函数错误返回-1，错误码存在errno中，errno取值如下：
//
// 复制代码
// 1、ENOENT 参数file_name 指定的文件不存在
// 2、ENOTDIR 路径中的目录存在但却非真正的目录
// 3、ELOOP 欲打开的文件有过多符号连接问题, 上限为16 符号连接
// 4、EFAULT 参数buf 为无效指针, 指向无法存在的内存空间
// 5、EACCESS 存取文件时被拒绝
// 6、ENOMEM 核心内存不足
// 7、ENAMETOOLONG 参数file_name 的路径名称太长
