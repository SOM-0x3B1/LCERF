#include "../../include/network/external_network_interface.hpp"

#include <cstdio>
#include <thread>

#include "../../../common/include/command.hpp"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#pragma comment(lib, "Ws2_32.lib")
#endif


std::string ExternalNetworkInterface::receiveDataFromSocket() {
    int iResult;

    iResult = recv(clientSocket, receiveBuffer, receiveBufferLen, 0);
    if (iResult > 0) {
        receiveBuffer[iResult] = '\0';
        printf("%s", receiveBuffer);
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
        closesocket(clientSocket);
        return "";
    }
}

void ExternalNetworkInterface::sendDataToSocket(std::string data) {
    int iSendResult = send(clientSocket, data.c_str(), data.size(), 0);
    if (iSendResult == SOCKET_ERROR) {
        int err = WSAGetLastError();
        if (err == WSAEWOULDBLOCK) {
            return;
        }
        connected = false;
        printf("send failed: %d\n", err);
        closesocket(clientSocket);
        return;
    }
}

ExternalNetworkInterface::ExternalNetworkInterface() {
    serverSocket = INVALID_SOCKET;
    clientSocket = INVALID_SOCKET;
    this->connected = false;
}

ExternalNetworkInterface::~ExternalNetworkInterface() {
    closesocket(serverSocket);
    closesocket(clientSocket);
}

bool ExternalNetworkInterface::isConnected() {
    return connected;
}

void ExternalNetworkInterface::listenOnPort(int port) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup() error!");
        return;
    }
    printf("WSAStartup() succeed\n");

    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        printf("socket() error!\n");
        return;
    }
    printf("Server socket created\n");

    SOCKADDR_IN serverAddr = {0};
    serverAddr.sin_family = AF_INET;  // IPv4
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("bind() error!");
        return;
    }
    printf("Bind on port %d...\n", port);

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        printf("listen() error!");
        return;
    }
    printf("Listening...\n");

    unsigned long nonBlockingMode = 1;
    if (ioctlsocket(serverSocket, FIONBIO, &nonBlockingMode) == SOCKET_ERROR)
    {
        printf("ioctlsocket failed: %d\n", WSAGetLastError());
        return;
    }

    tryAcceptConnection();
}

void ExternalNetworkInterface::tryAcceptConnection() {
    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTriedConnection).count() > 1000) {
        lastTriedConnection = now;

        printf("Awaiting connection...\n");

        clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            int err = WSAGetLastError();
            if (err == WSAEWOULDBLOCK) {
                return;
            }
            printf("Accept failed: %d\n", err);
            closesocket(serverSocket);
            WSACleanup();
            return;
        }
        printf("Client connected\n");
        connected = true;
    }
}

void ExternalNetworkInterface::simulationStep() {
    std::string received = receiveDataFromSocket();
    if (!received.empty())
        rx.push(received);

    if (!tx.empty()) {
        sendDataToSocket(tx.front());
        tx.pop();
    }
}

std::string ExternalNetworkInterface::receiveData() {
    if (!rx.empty()) {
        auto data = rx.front();
        rx.pop();
        return data;
    }
    return "";
}

void ExternalNetworkInterface::sendData(std::string data) {
    tx.push(data);
}
