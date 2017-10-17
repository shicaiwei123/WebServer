#include<iostream>
#include<winsock2.h>
#include<string>

class Cresponse       //定义一个请求回应类
{
public: 
    int sendres(SOCKET s,char*buf,int len);
};
int Cresponse::sendres(SOCKET s,char*buf,int len)
{
	    int iSet=0;
		FILE *fp = fopen(file , "rb" );                       //准备开始读取信息
		if( fp == 0 )
			 {
				char response[] = "HTTP/1.1 404 NOT FOUND\r\n\r\n";
			 	send(s, response, strlen( response ), 0 );
				memset(response, 0x00, sizeof(response));     //每次创建新线程就把这个清空，准备接收新信息接收
			 }
	    else     //将文件信息导出
			{

				int file_size ;
				char *content;
				char response[1024];
				fseek( fp, 0, SEEK_END );//指针移动到文件结尾
				file_size = ftell( fp );//计算长度
				fseek( fp, 0, SEEK_SET );//指针移动到开头
				content = (char*)malloc( file_size + 1 );
				fread( content, file_size, 1, fp );//从fp指向文件读取长度为file的一个数据项
				content[file_size] = 0; 
				//回复
				sprintf( buf, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %d\r\n\r\n%s", file_size, content );
				iSet=send( s, buf, strlen(buf ), 0 );
				free( content );
			}
       if(iSet == SOCKET_ERROR)
              {
                     std::cout<< "Server::Send Info Error!" <<std::endl;
                   //  break;
              }
	   return 1;

}