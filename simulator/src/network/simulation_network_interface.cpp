#include "../../include/network/simulation_network_interface.hpp"

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


std::string SimulationNetworkInterface::receiveDataFromSocket() {
    int iResult;

    iResult = recv(clientSocket, receiveBuffer, receiveBufferLen, 0);
    if (iResult > 0) {
        printf(receiveBuffer);
        printf("\n");
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

void SimulationNetworkInterface::sendDataToSocket(std::string data) {
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

SimulationNetworkInterface::SimulationNetworkInterface() {
    serverSocket = INVALID_SOCKET;
    clientSocket = INVALID_SOCKET;
    this->connected = false;
}

SimulationNetworkInterface::~SimulationNetworkInterface() {
    closesocket(serverSocket);
    closesocket(clientSocket);
}

bool SimulationNetworkInterface::isConnected() {
    return connected;
}

void SimulationNetworkInterface::listenOnPort(int port) {
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

void SimulationNetworkInterface::tryAcceptConnection() {
    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTriedConnection).count() > 1000) {
        lastTriedConnection = now;

        printf("Awaiting connection...\n");

        /*int nfds = 0;
        fd_set readfds, writefds, exceptfds;
        constexpr timeval timeout = {.tv_sec = 0, .tv_usec = 500};

        FD_ZERO(&readfds);
        FD_SET(serverSocket, &readfds);
        FD_SET(clientSocket, &readfds);
        auto res = select(nfds, &readfds, &writefds, &exceptfds, &timeout);*/

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

void SimulationNetworkInterface::simulationStep() {
    rx.push(receiveDataFromSocket());
    if (!tx.empty()) {
        sendDataToSocket(tx.front());
        tx.pop();
    }
}

std::string SimulationNetworkInterface::receiveData() {
    if (!rx.empty()) {
        auto data = rx.front();
        rx.pop();
        return data;
    }
    return "";
}

void SimulationNetworkInterface::sendData(const std::string& data) {
    tx.push(data);
}

