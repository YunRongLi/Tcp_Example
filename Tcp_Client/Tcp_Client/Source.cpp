#include "TcpClient.h"

void main() {
	TcpClient tcpclient;
	
	if (tcpclient.InitSocket()) {
		while (true) {
			if (!tcpclient.isCreateSocket) {
				tcpclient.isCreateSocket = tcpclient.CreateSocket();
			}
			else {
				if (!tcpclient.isConnectSocket) {
					tcpclient.isConnectSocket = tcpclient.ConnectSocket("192.168.0.158", 1994);
				}
				else {
					if (!tcpclient.isSendDataOK) {
						tcpclient.isSendDataOK = tcpclient.SendData("jfz hello\r\n");
					}
					else {
						if (!tcpclient.isReceiveDataOK) {
							tcpclient.isReceiveDataOK = tcpclient.ReceiveData();
						}
						else {
							string data = tcpclient.GetData();
							if (data == "@end#") {
								WSACleanup();
								break;
							}
						}
					}
				}
			}
		}
	}

	return;
}