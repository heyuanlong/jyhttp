#ifndef JYHTTP
#define JYHTTP



class jyhttp
{
public:
   jyhttp(){}
   ~jyhttp(){}
   int parse(char *request);
   int compound(char *response);


private:
    char method[10];
    int filesize;
    char filepath[1024];

};


#endif
