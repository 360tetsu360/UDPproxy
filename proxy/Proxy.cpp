#include "Proxy.h"

Proxy::Proxy()
{
}

Proxy::~Proxy()
{
}

void Proxy::Initialize(int hostPort, std::string remoteAddress, int remotePort) {
	this->hostPort = hostPort;
	this->remoteAddr = remoteAddress;
	this->remotePort = remotePort;

    WSAData wsaData;
    WSAStartup(MAKEWORD(2, 0), &wsaData);
    serverSock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in proxyaddr;
    proxyaddr.sin_family = AF_INET;
    proxyaddr.sin_port = htons(hostPort); //proxy server
    proxyaddr.sin_addr.S_un.S_addr = INADDR_ANY;
    bind(serverSock, (struct sockaddr*)&proxyaddr, sizeof(proxyaddr));

    u_long val = 1;
    ioctlsocket(serverSock, FIONBIO, &val);

    WSAData wsaData2;
    WSAStartup(MAKEWORD(2, 0), &wsaData2);
    clientSock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr2;
    addr2.sin_family = AF_INET;
    addr2.sin_port = htons(19132);// target server
    addr2.sin_addr.S_un.S_addr = INADDR_ANY;
    bind(clientSock, (struct sockaddr*)&addr2, sizeof(addr2));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(remotePort);
    serveraddr.sin_addr.S_un.S_addr = inet_addr(remoteAddress.c_str());

    ioctlsocket(clientSock, FIONBIO, &val);

}
void Proxy::Start() {
    byte buf[4096];
    byte buf2[4096];
    while (true)
    {
        int length = sizeof(clientaddr);
        int t = recvfrom(serverSock, (char*)buf, sizeof(buf), 0, &clientaddr, &length);
        int t2 = recv(clientSock, (char*)buf2, sizeof(buf2), 0);
        if (t >= 1) {
            if ((int)buf[0] == 0x84) {

                std::vector<byte> data;
                data.insert(data.end(), &buf[14], buf + t);
                std::cout << std::hex << (int)data[0] << std::endl;
            }
            sendto(clientSock, (char*)buf, t, 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
        }
        if (t2 >= 1) {
            sendto(serverSock, (char*)buf2, t2, 0, (struct sockaddr*)&clientaddr, sizeof(clientaddr));
        }
    }
}
void Proxy::SendServer(char*, int size) {

}
void Proxy::SendClient(char*, int size) {

}
void Proxy::Disable() {
    closesocket(serverSock);
    closesocket(clientSock);
    WSACleanup();
}