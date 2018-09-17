#include "TcpServer.h"

TcpServer::TcpServer() {
	isClientSockConnect = false;
	isReceiveData = false;
}

bool TcpServer::InitWinSock() {
	WORD version = MAKEWORD(2, 2);
	WSADATA lpData;
	int Error = WSAStartup(version, &lpData);
	if (Error != 0) {
		cout << "WinSock Init Failed" << endl;
		return false;
	}
	cout << "WinSock Init Succes" << endl;

	listenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSock == INVALID_SOCKET) {
		cout << "Sock Create Failed" << endl;
		return false;
	}
	cout << "Sock Create Success" << endl;

	return true;
}

bool TcpServer::ListenSocket(const string ip, const unsigned short port) {
	hostaddr.sin_family = AF_INET;
	hostaddr.sin_port = htons(port);

	inet_pton(AF_INET, ip.c_str(), (void*)&addr);

	hostaddr.sin_addr = addr;

	int error = bind(listenSock, (struct sockaddr*)&hostaddr, sizeof(sockaddr));
	if (error != 0) {
		cout << "Host IP Bind Failed" << endl;
		return false;
	}

	error = listen(listenSock, 3);
	if (error != 0) {
		cout << "Socket Listen Failed" << endl;
		return false;
	}
	cout << "Socket Listening..." << endl;

	return true;
}

bool TcpServer::WaitClientConnect() {
	int len = sizeof(struct sockaddr);

	clientSock = accept(listenSock, (struct sockaddr*)&clientaddr, &len);
	cout << "Client Socket Number:" << clientSock << endl;
	if (clientSock == INVALID_SOCKET) {
		cout << "Client Connect Failed" << endl;
		cout << WSAGetLastError() << endl;
		return false;
	}
	return true;
}

bool TcpServer::SendData(const string &data) {
	int error = send(clientSock, data.c_str(), data.size(), 0);
	if (error == SOCKET_ERROR) {
		cout << "Send Failed" << endl;
		return false;
	}
	cout << "Send Msg: " << data << endl;
	return true;
}

bool TcpServer::ReceiveData() {
	static int cnt = 1;

	char buf[1024] = "\0";

	int buflen = recv(clientSock, buf, 1024, 0);
	if (buflen == SOCKET_ERROR) {
		cout << "Recvive Failed" << endl;
		return false;
	}
	data = string(buf);
	cout << "Receive Msg(" << cnt++ << "): " << buf << endl;
	return true;
}

int TcpServer::CloseSocket() {
	return closesocket(listenSock);
}

void TcpServer::ShutdownSocket() {
	int error = shutdown(clientSock, 2);
	if (error == SOCKET_ERROR) {
		cout << "Close Socket Failed" << endl;
	}
	return;
}

string TcpServer::GetData() {
	return data;
}

