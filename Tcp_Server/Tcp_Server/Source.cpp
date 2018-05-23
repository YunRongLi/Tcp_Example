#include "TcpServer.h"
#include <conio.h>

#define AsciiEnter 13
#define AsciiR 114
#define AsciiE 101

void main() {
	TcpServer tcpserver;

	tcpserver.InitWinSock();

	tcpserver.CreateSocket();

	tcpserver.BindIPandPort("192.168.0.158", 1994);

	tcpserver.ListenSocket();

	if (!tcpserver.isClientSockConnect) {
		tcpserver.isClientSockConnect = tcpserver.WaitClientConnect();
	}
	
	char key;
	int asciikey;

	while (true) {
		//Enter key ascii code = 13
		key = _getch();

		asciikey = key; 
		if (asciikey != 0) {
			cout << "Key: " << asciikey << endl;
		}

		if (asciikey == AsciiR) {
			tcpserver.SendData("r\r\n");
		}
		else if (asciikey == AsciiE) {
			tcpserver.SendData("e\r\n");
		}

		
		/*if (!tcpserver.isReceiveData) {
			tcpserver.isReceiveData = tcpserver.ReceiveData();

			if (!tcpserver.isReceiveData) {
				tcpserver.ShutdownSocket();
				cout << "Waiting Connect Client" << endl;
				tcpserver.isClientSockConnect = false;
			}
		}
		string data = tcpserver.GetData();

		if (tcpserver.isReceiveData && data != "jfzpoi" && data != "@end#") {
			tcpserver.isReceiveData = false;
		}
		if (tcpserver.isReceiveData && data == "jfzpoi") {
			tcpserver.SendData("sandeepin!\r\n");
			tcpserver.isReceiveData = false;
		}
		if (tcpserver.isReceiveData && data == "@end#"){
			int error = tcpserver.CloseSocket();
			if (error == SOCKET_ERROR) {
				cout << "Close Socket Failed" << endl;
			}
			if (WSACleanup() != 0) {
				cout << "WSA Clean Failed" << endl;
			}
			cout << "Close" << endl;
			break;
		}*/
	}
	return;
}