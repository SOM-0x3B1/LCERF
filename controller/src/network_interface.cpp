#include "../include/network_interface.hpp"

#include <cstdio>
#include <thread>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#pragma comment(lib, "Ws2_32.lib")
#endif


NetworkInterface::NetworkInterface() {
    connectSocket = INVALID_SOCKET;
    this->connected = false;
}

NetworkInterface::~NetworkInterface() {
    closesocket(connectSocket);
}

bool NetworkInterface::isConnected() {
    return connected;
}

void NetworkInterface::connectTo(int port) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup() error!");
        return;
    }
    printf("WSAStartup() succeed\n");

    connectSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (connectSocket == INVALID_SOCKET) {
        printf("socket() error!\n");
        return;
    }
    printf("Server socket created\n");

    SOCKADDR_IN serverAddr = {0};
    serverAddr.sin_family = AF_INET;  // IPv4
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(port);

    if (connect(connectSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("connect() error!\n");
        return;
    }
    if (connectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        return;
    }
    printf("Connected...\n");
}

std::string NetworkInterface::receiveData() {
    int iResult;
    int iSendResult;

    iResult = recv(connectSocket, receiveBuffer, receiveBufferLen, 0);
    if (iResult > 0) {
        return std::string(receiveBuffer);
    }
    else if (iResult == 0){
        printf("Connection closing...\n");
        return "";
    }
    else {
        printf("recv failed: %d\n", WSAGetLastError());
        closesocket(connectSocket);
        WSACleanup();
        return "";
    }
}
