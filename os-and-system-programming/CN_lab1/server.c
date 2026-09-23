#include <stdio.h>
#include <winsock2.h>
#include "NetData.h"

#pragma comment(lib, "ws2_32.lib")

void startTCPServer(int port) {
    SOCKET listenSock, clientSock;
    struct sockaddr_in addr;
    LabPacket packet;

    listenSock = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    bind(listenSock, (struct sockaddr*)&addr, sizeof(addr));
    listen(listenSock, 1);

    clientSock = accept(listenSock, NULL, NULL);
    recv(clientSock, (char*)&packet, sizeof(LabPacket), 0);

    printLabPacket("Received dto by TCP", &packet);

    send(clientSock, (char*)&packet, sizeof(LabPacket), 0);
    printf("Send back to client received dto by TCP\n");

    closesocket(clientSock);
    closesocket(listenSock);
}

void startUDPServer(int port) {
    SOCKET sock;
    struct sockaddr_in addr, clientAddr;
    int clientLen = sizeof(clientAddr);
    LabPacket packet;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    bind(sock, (struct sockaddr*)&addr, sizeof(addr));

    recvfrom(sock, (char*)&packet, sizeof(LabPacket), 0, (struct sockaddr*)&clientAddr, &clientLen);
    printLabPacket("Received dto by UDP", &packet);

    sendto(sock, (char*)&packet, sizeof(LabPacket), 0, (struct sockaddr*)&clientAddr, clientLen);
    printf("Send back to client received dto by UDP\n");

    closesocket(sock);
}

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    printf("-----------------TCP---------------------\n");
    startTCPServer(12345);
    printf("-----------------UDP---------------------\n");
    startUDPServer(18189);

    WSACleanup();
    system("pause");
    return 0;
}