#include "../include/network_interface.hpp"

#include <cstdio>
#include <thread>
#include <utility>

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

void NetworkInterface::init(std::string ip, int port) {
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

    serverIP = std::move(ip);
    serverPort = port;
}

void NetworkInterface::tryConnect() {
    SOCKADDR_IN serverAddr = {0};
    serverAddr.sin_family = AF_INET;  // IPv4
    serverAddr.sin_addr.s_addr = inet_addr(serverIP.c_str());
    serverAddr.sin_port = htons(serverPort);

    if (connect(connectSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("connect() error!\n");
        return;
    }
    if (connectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        return;
    }
    printf("Connected...\n");
    connected = true;

    unsigned long nonBlockingMode = 1;
    if (ioctlsocket(connectSocket, FIONBIO, &nonBlockingMode) == SOCKET_ERROR)
    {
        printf("ioctlsocket failed: %d\n", WSAGetLastError());
        return;
    }
}

std::string NetworkInterface::receiveData() {
    int iResult;

    iResult = recv(connectSocket, receiveBuffer, receiveBufferLen, 0);
    if (iResult > 0) {
        receiveBuffer[iResult] = '\0';
        printf(receiveBuffer);
        return std::string(receiveBuffer);
    }
    else if (iResult == 0){
        connected = false;
        printf("Connection closing...\n");
        return "";
    }
    else {
        int err = WSAGetLastError();
        if (err == WSAEWOULDBLOCK) {
            return "";
        }
        connected = false;
        printf("recv failed: %d\n", err);
        closesocket(connectSocket);
        return "";
    }
}

void NetworkInterface::sendData(std::string data) {
    int iSendResult = send(connectSocket, data.c_str(), data.size(), 0);
    if (iSendResult == SOCKET_ERROR) {
        int err = WSAGetLastError();
        if (err == WSAEWOULDBLOCK) {
            return;
        }
        printf("send failed: %d\n", err);
        closesocket(connectSocket);
        WSACleanup();
        connected = false;
        return;
    }
}