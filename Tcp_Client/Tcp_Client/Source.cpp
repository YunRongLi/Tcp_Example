#include "TcpClient.h"

#include <iostream>
#include <vector>
#include <conio.h>

void CombineString(string& dstStr, vector<string>& srcVec, const string& Separator) {
	size_t vecSize = srcVec.size();

	for (size_t index = 0; index < vecSize; index++) {
		dstStr.append(srcVec.at(index));

		if (index < (vecSize - 1)) {
			dstStr.append(Separator);
		}
	}
}

void main() {
	TcpClient tcpclient;
	vector<string> vec;

	vec.push_back("123");
	vec.push_back("456");
	vec.push_back("789");
	vec.push_back("147");
	vec.push_back("258");

	if (tcpclient.InitSocket()) {
		while (true) {
			if (!tcpclient.isCreateSocket) {
				tcpclient.isCreateSocket = tcpclient.CreateSocket();
			}
			else {
				if (!tcpclient.isConnectSocket) {
					tcpclient.isConnectSocket = tcpclient.ConnectSocket("127.0.0.1", 4568);
				}
				else {
					if (!tcpclient.isSendDataOK) {
						string msg;
						CombineString(msg, vec, "[");
						tcpclient.isSendDataOK = tcpclient.SendData(msg);
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