#ifndef JYHTTP
#define JYHTTP



class jyhttp
{
public:
   jyhttp(){}
   ~jyhttp(){}
   int parse(char *request);
   int compound(char *response);
   void get_type();



private:
    char method[10];
    int filesize;
    char filepath[1024];

    int type_num;//指向Content-Type

};


#endif
