#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;

class TcpClient {
private:
	SOCKET clientSock;
	
	sockaddr_in hostaddr;
	in_addr addr;

	string data;

public:
	bool isCreateSocket;
	bool isConnectSocket;
	bool isSendDataOK;
	bool isReceiveDataOK;

	TcpClient();
	bool InitSocket();
	bool CreateSocket();
	bool ConnectSocket(const string ip, const unsigned short port);
	bool SendData(const string &data);
	bool ReceiveData();
	string GetData();
};
