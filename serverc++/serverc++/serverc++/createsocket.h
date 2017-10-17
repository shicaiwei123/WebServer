#include<iostream>
#include<winsock2.h>
#include<string>

//����һ��socket��
class seversocket
{
private:
	int  version_a,version_b;//socket��汾
	int  PORT;               //�������Ķ˿ں�ip
	char*  IP_ADDRESS;
public:
	int get_version_a();
	int get_version_b();
	int get_PORT();
	char* get_IP_ADDRESS();
	int init(int m_version_a,int m_version_b,int m_PORT,char* m_IP_ADDRESS);  //��ʼ���汾���˿��Լ�ip��ַ
	SOCKET createsocket(int m_version_a,int m_version_b);//����socket
	int Bind(SOCKET s,int m_PORT,char* m_IP_ADDRESS);
	int Connect(SOCKET s,int m_PORT,char* m_IP_ADDRESS);

};
//˽�г�Ա�����ķ���
int seversocket::get_version_a()
{
	return version_a;
}
int seversocket::get_version_b()
{
	return version_b;
}
int seversocket::get_PORT()
{
	return PORT;
}
char* seversocket::get_IP_ADDRESS()
{
	return IP_ADDRESS;
}

//˽�г�Ա������ֵ
int seversocket::init(int m_version_a,int m_version_b,int m_PORT,char* m_IP_ADDRESS)
{
	version_a=m_version_a;
	version_b=m_version_b;
	PORT=m_PORT;
	IP_ADDRESS=m_IP_ADDRESS;
	return 1;
}

//socket��������
SOCKET seversocket::createsocket(int m_version_a,int m_version_b)
{
	WSADATA Ws ;
    SOCKET ServerSocket;
	if(WSAStartup(MAKEWORD( m_version_a,m_version_b), &Ws) != 0)
       {
              std::cout<< "Init Windows Socket Failed::" <<GetLastError() << std::endl;
              return -1;
       }
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
       if(ServerSocket== INVALID_SOCKET)
       {
             std::cout<< "Create Socket Failed::" << GetLastError() << std::endl;
              return -1;
       }
      
	   return ServerSocket;



}
//��sock��������
int seversocket::Bind(SOCKET s,int m_PORT,char* m_IP_ADDRESS)
{
	int iRet;
	struct sockaddr_in LocalAddr;
    LocalAddr.sin_family = AF_INET;
    LocalAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    LocalAddr.sin_port = htons(PORT);
    memset(LocalAddr.sin_zero, 0x00, 8);
	//Bind Socket
    iRet = bind(s, (struct sockaddr*)&LocalAddr, sizeof(LocalAddr));
    if(iRet != 0)
       {
              std::cout<< "Bind Socket Failed::" << GetLastError() << std::endl;
              return -1;
       }
	return 1;
}

//���ӿͻ��˵�������
int seversocket::Connect(SOCKET s,int m_PORT,char* m_IP_ADDRESS)
{
	int iRet;
	struct sockaddr_in LocalAddr;
    LocalAddr.sin_family = AF_INET;
    LocalAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    LocalAddr.sin_port = htons(PORT);
    memset(LocalAddr.sin_zero, 0x00, 8);
	//connetc Socket
    iRet = connect(s, (struct sockaddr*)&LocalAddr, sizeof(LocalAddr));
    if(iRet != 0)
       {
              std::cout<< "connnect Socket Failed::" << GetLastError() << std::endl;
              return -1;
       }
	return 1;
}