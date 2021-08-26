#pragma once
#include <stdio.h>
#include <string.h>
#include <WinSock2.h> //windows
#include <Windows.h>
#include <windowsx.h>
#include <sstream>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996) 

class Proxy
{
public:
	Proxy();
	~Proxy();
	void Initialize(int hostPort,std::string remoteAddress,int remotePort);
	void Start();
	void SendServer(char*,int size);
	void SendClient(char*,int size);
	void Disable();
private:
	int hostPort;
	std::string remoteAddr;
	int remotePort;

	int serverSock;
	int clientSock;
	sockaddr clientaddr;
	struct sockaddr_in serveraddr;
};