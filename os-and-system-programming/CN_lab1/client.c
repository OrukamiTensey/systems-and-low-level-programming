#include <stdio.h>
#include <winsock2.h>
#include "NetData.h"

#pragma comment(lib, "ws2_32.lib")

void sendTCPMessage(const char* ip, int port, LabPacket* data) {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    connect(sock, (struct sockaddr*)&addr, sizeof(addr));

    printLabPacket("Send dto by TCP", data);
    send(sock, (char*)data, sizeof(LabPacket), 0);

    LabPacket response;
    recv(sock, (char*)&response, sizeof(LabPacket), 0);
    printLabPacket("Received dto by TCP", &response);

    closesocket(sock);
}

void sendUDPMessage(const char* ip, int port, LabPacket* data) {
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    printLabPacket("Send dto by UDP", data);
    sendto(sock, (char*)data, sizeof(LabPacket), 0, (struct sockaddr*)&addr, sizeof(addr));

    LabPacket response;
    recvfrom(sock, (char*)&response, sizeof(LabPacket), 0, NULL, NULL);
    printLabPacket("Received dto by UDP", &response);

    closesocket(sock);
}

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // ²í³ö³àë³çàö³ÿ 7 long òà 7 int
    LabPacket myData = {
        {100, 200, 300, 400, 500, 600, 700},
        {1, 2, 3, 4, 5, 6, 7}
    };

    printf("-----------------TCP---------------------\n");
    sendTCPMessage("127.0.0.1", 12345, &myData);
    printf("-----------------UDP---------------------\n");
    sendUDPMessage("127.0.0.1", 18189, &myData);

    WSACleanup();
    system("pause");
    return 0;
}