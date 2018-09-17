#pragma once

#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

class TcpServer {
private:
	SOCKET listenSock;
	SOCKET clientSock;
	
	sockaddr_in hostaddr;
	sockaddr_in clientaddr;
	in_addr addr;

	string data;

public:
	bool isClientSockConnect;
	bool isReceiveData;

	TcpServer();
	bool InitWinSock();
	bool ListenSocket(const string ip, const unsigned short port);
	bool WaitClientConnect();

	bool SendData(const string &data);
	bool ReceiveData();

	int CloseSocket();
	void ShutdownSocket();
	string GetData();
};