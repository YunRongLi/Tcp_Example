#include "TcpClient.h"

TcpClient::TcpClient() {
	isCreateSocket = false;
	isConnectSocket = false;
	isSendDataOK = false;
	isReceiveDataOK = false;
}
 
bool TcpClient::InitSocket() {
	WORD version = MAKEWORD(2, 2);
	WSADATA lpData;
	int Error = WSAStartup(version, &lpData);
	if (Error != 0) {
		cout << "WinSock Init Failed" << endl;
		return false;
	}
	cout << "WinSock Init Succes" << endl;
	return true;
}

bool TcpClient::CreateSocket() {
	clientSock = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSock == INVALID_SOCKET) {
		cout << "Sock Create Failed" << endl;
		return false;
	}
	cout << "Sock Create Success" << endl;
	return true;
}

bool TcpClient::ConnectSocket(const string ip, const unsigned short port) {
	hostaddr.sin_family = AF_INET;
	hostaddr.sin_port = htons(port);

	inet_pton(AF_INET, ip.c_str(), (void*)&addr);
	hostaddr.sin_addr = addr;
	cout << "ip(): " << addr.S_un.S_addr << endl;
	cout << "ip(normal): " << ip.c_str() << endl;

	int error = connect(clientSock, (sockaddr*)&hostaddr, sizeof(sockaddr));
	if (error == INVALID_SOCKET) {
		cout << "Connect Server Failed" << endl;
		return false;
	}
	return true;
}

bool TcpClient::SendData(const string& data) {
	int error = send(clientSock, data.c_str(), data.size(), 0);
	if (error == SOCKET_ERROR) {
		cout << "Send Failed" << endl;
		return false;
	}
	cout << "Send Msg: " << data.c_str() << endl;
	return true;
}

bool TcpClient::ReceiveData() {
	static int cnt = 1;
	char buf[1024] = "\0";

	int buflen = recv(clientSock, buf, 1024, 0);
	if (buflen == SOCKET_ERROR) {
		cout << "Receive Failed" << endl;
		return false;
	}

	data = string(buf);
	cout << "Receive Message(" << cnt++ << "): " << buf << endl;
	return  true;
}

string TcpClient::GetData() {
	return data;
}