#include "TcpServer.h"
#include <conio.h>
#include <iostream>
#include <vector>

#define AsciiEnter 13
#define AsciiR 114
#define AsciiE 101

void SplitString(const string& srcStr, vector<string>& Vec, const string& Separator) {
	string::size_type PosStringStart;
	string::size_type PosSeparator;

	PosSeparator = srcStr.find(Separator);
	PosStringStart = 0;
	while (string::npos != PosSeparator) {
		Vec.push_back(srcStr.substr(PosStringStart, PosSeparator - PosStringStart));

		PosStringStart = PosSeparator + Separator.size();
		PosSeparator = srcStr.find(Separator, PosStringStart);
	}

	if (PosStringStart != srcStr.length()) {
		Vec.push_back(srcStr.substr(PosStringStart));
	}
}

void main() {
	TcpServer tcpserver;

	tcpserver.InitWinSock();

	tcpserver.ListenSocket("127.0.0.1", 4568);

	if (!tcpserver.isClientSockConnect) {
		tcpserver.isClientSockConnect = tcpserver.WaitClientConnect();
	}
	string str;
	vector<string> vec;


	char key;
	int asciikey;

	while (true) {
		//Enter key ascii code = 13


		if (tcpserver.ReceiveData()) {
			str = tcpserver.GetData();
			SplitString(str, vec, "\c");

			for (size_t index = 0; index < vec.size(); index++) {
				std::cout << vec.at(index).c_str() << std::endl;
			}
		}
		

	}
	return;
}