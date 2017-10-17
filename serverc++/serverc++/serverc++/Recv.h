#include<iostream>
#include<winsock2.h>
#include<string>
//定义一个接收类
class receive
{
public:
	int Recv(SOCKET s,char*buf,int len,int flags);

};

int receive::Recv(SOCKET s,char*buf,int len,int flags)
{
	int err;
	err=recv( s,buf, len,flags);
	if(err == 0 || err== SOCKET_ERROR)
       {
            std::cout<< "接收消息错误！" << std::endl;
            char response[] = "HTTP/1.1 404 NOT FOUND\r\n\r\n";
		    send(s, response, strlen( response ), 0 );
			return err;
       }
	return err;

}