#include<iostream>
#include<winsock2.h>
#include<string>

class Cresponse       //����һ�������Ӧ��
{
public: 
    int sendres(SOCKET s,char*buf,int len);
};
int Cresponse::sendres(SOCKET s,char*buf,int len)
{
	    int iSet=0;
		FILE *fp = fopen(file , "rb" );                       //׼����ʼ��ȡ��Ϣ
		if( fp == 0 )
			 {
				char response[] = "HTTP/1.1 404 NOT FOUND\r\n\r\n";
			 	send(s, response, strlen( response ), 0 );
				memset(response, 0x00, sizeof(response));     //ÿ�δ������߳̾Ͱ������գ�׼����������Ϣ����
			 }
	    else     //���ļ���Ϣ����
			{

				int file_size ;
				char *content;
				char response[1024];
				fseek( fp, 0, SEEK_END );//ָ���ƶ����ļ���β
				file_size = ftell( fp );//���㳤��
				fseek( fp, 0, SEEK_SET );//ָ���ƶ�����ͷ
				content = (char*)malloc( file_size + 1 );
				fread( content, file_size, 1, fp );//��fpָ���ļ���ȡ����Ϊfile��һ��������
				content[file_size] = 0; 
				//�ظ�
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