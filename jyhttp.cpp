#include "jyhttp.h"
#include "jyfunction.h"

#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>

#define CONTENTNUM 400////要这样来引用外部数组
extern struct contentstruct content_type[CONTENTNUM];//可能编译失败

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
    get_type();


   //先判断文件大小
   if (filesize == 0) {//304
       sprintf(response,"HTTP/1.1 404 Not Found\r\n");
       sprintf(response,"%sServer: jyhttp\r\n",response);
       sprintf(response, "%sContent-length: %d\r\n", response, filesize);
       sprintf(response, "%sContent-Type: %s\r\n", response, content_type[type_num].contenttype);

        sprintf(response, "%s\r\n", response);

         printf("%s\n", response);
   }
   else if (filesize > 0 && filesize < 1024*(1024-1) ) {
       sprintf(response,"HTTP/1.1 200 OK\r\n");
       sprintf(response,"%sServer: jyhttp\r\n",response);
       sprintf(response, "%sContent-length: %d\r\n", response, filesize);
       sprintf(response, "%sContent-Type: %s\r\n", response, content_type[type_num].contenttype);

       sprintf(response, "%s\r\n", response);
       int fd=open(filepath,O_RDONLY);
       check(fd != -1,"open filepath");
       int len=strlen(response);
       int r=read(fd,(void*)(response+len),1024*(1024-1) );
       printf("读取的文件字节数量：%d\n", r);
    //   printf("%s\n", response);
   }
   else {///使用mmap
       /* code */
   }
    return 0;
}
void jyhttp::get_type()
{
    //默认是index
    char *p=strrchr(filepath,'.');
    char tp[10]={0};
    strcpy(tp,p);
    printf("文件的后缀：%s\n",tp );
    int i=0;
    while ( strcmp(tp,content_type[i].filetype)!=0  &&
            strcmp("",content_type[i].filetype)!=0){
        ++i;

    }

    if ( strcmp("",content_type[i].filetype) == 0 ) {//没找到
        type_num= 0;
        return;
    }
    printf("文件对应的类型：%s\n",content_type[i].contenttype );
    type_num = i;
}


/*
        localtime_r(&(out->mtime), &tm);
        strftime(buf, SHORTLINE,  "%a, %d %b %Y %H:%M:%S GMT", &tm);
        sprintf(header, "%sLast-Modified: %s\r\n", header, buf);
*/


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



/*
请求/favicon.ico HTTP/1.1失败时Microsoft-IIS/6.0由下返回

HTTP/1.1 404 Not Found
Content-Length: 1308
Content-Type: text/html
Server: Microsoft-IIS/6.0
X-Powered-By: ASP.NET
Date: Wed, 29 Jul 2015 03:56:39 GMT

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<HTML><HEAD><TITLE>无法找到该页</TITLE>
<META HTTP-EQUIV="Content-Type" Content="text/html; charset=GB2312">
<STYLE type="text/css">
  BODY { font: 9pt/12pt 宋体 }
  H1 { font: 12pt/15pt 宋体 }
  H2 { font: 9pt/12pt 宋体 }
  A:link { color: red }
  A:visited { color: maroon }
</STYLE>
</HEAD><BODY><TABLE width=500 border=0 cellspacing=10><TR><TD>

<h1>无法找到该页</h1>
您正在搜索的页面可能已经删除、更名或暂时不可用。
<hr>
<p>请尝试以下操作：</p>
<ul>
<li>确保浏览器的地址栏中显示的网站地址的拼写和格式正确无误。</li>
<li>如果通过单击链接而到达了该网页，请与网站管理员联系，通知他们该链接的格式不正确。
</li>
<li>单击<a href="javascript:history.back(1)">后退</a>按钮尝试另一个链接。</li>
</ul>
<h2>HTTP 错误 404 - 文件或目录未找到。<br>Internet 信息服务 (IIS)</h2>
<hr>
<p>技术信息（为技术支持人员提供）</p>
<ul>
<li>转到 <a href="http://go.microsoft.com/fwlink/?linkid=8180">Microsoft 产品支持服务</a>并搜索包括&ldquo;HTTP&rdquo;和&ldquo;404&rdquo;的标题。</li>
<li>打开&ldquo;IIS 帮助&rdquo;（可在 IIS 管理器 (inetmgr) 中访问），然后搜索标题为&ldquo;网站设置&rdquo;、&ldquo;常规管理任务&rdquo;和&ldquo;关于自定义错误消息&rdquo;的主题。</li>
</ul>

</TD></TR></TABLE></BODY></HTML>

*/
