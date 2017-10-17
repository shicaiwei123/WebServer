#include<iostream>
#include<winsock2.h>
#include<string>
#define ver_a 2
#define ver_b 2
#define port 12345
#define ip "127.0.0.1"
#pragma comment(lib,"ws2_32.lib") 
#define MAX_PATH 2000
char* file=NULL;
#include"Recv.h"
#include"Send.h"
#include"createsocket.h"
//定义一个解析类
class analyse
{
public:
	int ALE(char* buf);
};

int analyse::ALE(char *buf)
{
	 char *a="/test.html";
     char *b="/hello.html";
	 char *token = strtok(  buf, " " );          //提取访问的资源的名称
     char *uri = strtok( 0, " " );
	 char ffile[64];
	 sprintf( ffile, "%s", uri );        
	if(!(strcmp(a,ffile)))                                //根据访问的资源名，指定文件路径
		{
			 file="F:\\P2P\\p2p\\test.html";
		}
	else if(!(strcmp(b,ffile)))
		{
			file="F:\\P2P\\p2p\\hello.html";
		}
	return 1;
}

//定义一个接收解析线程
DWORD WINAPI ClientRecvThread(LPVOID lpParameter)
{
        SOCKET ClientSocket = (SOCKET)lpParameter;
		receive REVE;                                 //实例化类对象
		analyse ale;
		Cresponse sendback;
        int iRet = 0;
	    int iSet=0;
        char chRecvBuffer[MAX_PATH];
	    char chSendBuffer[MAX_PATH];
		while(1)
		{
        memset(chRecvBuffer, 0x00, sizeof(chRecvBuffer));
        iRet = REVE.Recv(ClientSocket, chRecvBuffer, MAX_PATH, 0);
		if(iRet==-1)
		{
			std::cout<<"客户端离开"<<std::endl;
			return -1;
			break;
		}
		std::cout<< "接收的信息为：" << chRecvBuffer << std::endl;
	    ale.ALE(chRecvBuffer );
		memset(chSendBuffer, 0x00, sizeof(chSendBuffer));     //每次创建新线程就把这个清空，准备接收新信息接收
	    iSet=sendback.sendres(ClientSocket,chSendBuffer,MAX_PATH);
		if(iSet==-1)
		{
			std::cout<<"客户端离开"<<std::endl;
			return -1;
			break;
		}
		}
}


int main()
{
	int errinit;   
	int errbind;
	int m_versin_a;
	int m_versin_b;
	int m_PORT;
	int iRet;
	char* m_IP_ADDRESS;
	int AddrLen = 0;
	HANDLE hThread = NULL;
	SOCKET sever;   
	seversocket socket;                    //例化了seversocket类，生成sockte对象
  	errinit=socket.init(ver_a,ver_b, port,ip);
	if(errinit!=1)
	{
		std::cout<<"初始化失败";
		return -1;
	}
	else
	{
		std::cout<<"初始化成功"<<std::endl;
	}
	                                     //通过公有成员函数实现对私有成员变量的访问
	m_versin_a=socket.get_version_a();
	m_versin_b=socket.get_version_b();
	m_PORT=socket.get_PORT();
	m_IP_ADDRESS=socket.get_IP_ADDRESS();
	std::cout<<m_PORT<<std::endl;
	sever=socket.createsocket(m_versin_a,m_versin_b);
	errbind=socket.Bind(sever,m_PORT,	m_IP_ADDRESS);
	if(sever==-1)
	{
		std::cout<<"socket创建失败"<<std::endl;
		return -1;
	}
	else
		std::cout<<"socket创建成功"<<std::endl;

	iRet = listen(sever, 10);  //开始监听套接字
       if(iRet != 0)
       {
              std::cout<< "Listen Socket Failed !" << GetLastError() << std::endl;
              return -1;
       }
 
       std::cout << "服务端已经启动！" << std::endl;
	   struct sockaddr_in ClientAddr;
	   SOCKET ClientSocket;
	   AddrLen = sizeof(ClientAddr);
	   while(1)
	   {
		   ClientSocket= accept(sever, (struct sockaddr*)&ClientAddr, &AddrLen);
		   if(ClientSocket== INVALID_SOCKET)
				{
					  std::cout<< "Accept Failed::" << GetLastError() << std::endl;
					  return -1;
				}
		   std::cout<<"客户端连接::" << inet_ntoa(ClientAddr.sin_addr) << ":"<< ClientAddr.sin_port << std::endl;
		   hThread = CreateThread(NULL, 0, ClientRecvThread, (LPVOID)ClientSocket, 0, NULL);
		   if(hThread == NULL)
				{
						 std::cout<< "线程创建失败" << std::endl;
						 return -1;
				}
			 CloseHandle(hThread);
	   }
	   closesocket(sever);
       closesocket(ClientSocket);
       WSACleanup();
	return 1;
}


 