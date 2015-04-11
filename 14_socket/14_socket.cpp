// 14_socket.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Winsock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

#define PORT 4001
#define MAX_CON 1
#define BUF_SIZE 256



int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "windows1251");
	WSADATA wsad;
	int err;
	err = WSAStartup(MAKEWORD(2, 1), &wsad);
	if (err) {
		std::cout << "Couldn't initialize sockets or something" << std::endl;
		return 1;
	}

	sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	SOCKET sid = socket(PF_INET, SOCK_STREAM, 0);
	int binder = bind(sid, (sockaddr *)&addr, sizeof addr);
	listen(sid, MAX_CON);
	std::cout << "Listening on port " << PORT << std::endl;
	while (true) {
		SOCKET sid_new = accept(sid, NULL, NULL);
		long x;
		int n = recv(sid_new, (char*)&x, sizeof x, 0);
		std::cout << "Recieved " << x << std::endl;
		char buf[BUF_SIZE];
		itoa(x, buf, 2);
		std::cout << "Sending " << buf << std::endl;
		send(sid_new, buf, sizeof buf, 0);
		shutdown(sid_new, 2);
		closesocket(sid_new);
	}
	shutdown(sid, 2);
	closesocket(sid);
	WSACleanup();
	return 0;
}

