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


SimulationNetworkInterface::SimulationNetworkInterface() {
    serverSocket = INVALID_SOCKET;
    clientSocket = INVALID_SOCKET;
    this->connected = false;
}

SimulationNetworkInterface::~SimulationNetworkInterface() {
    closesocket(serverSocket);
    closesocket(clientSocket);
}

bool SimulationNetworkInterface::isConencted() {
    return connected;
}

void SimulationNetworkInterface::listenOnPort(int port) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup() error!");
        return;
    }
    printf("WSAStartup() succeed\n");

    SOCKET serverSocket = socket(PF_INET, SOCK_STREAM, 0);
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

    tryAcceptConnection();
}

void SimulationNetworkInterface::tryAcceptConnection() {
    clientSocket = INVALID_SOCKET;

    int nfds = 0;
    fd_set readfds, writefds, exceptfds;
    constexpr timeval timeout = {.tv_sec = 0, .tv_usec = 100};
    select(nfds, &readfds, &writefds, &exceptfds, &timeout);

    if (std::find(std::begin(readfds.fd_array), std::end(readfds.fd_array), serverSocket) != std::end(readfds.fd_array)) {
        clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            printf("Accept failed: %d\n", WSAGetLastError());
            closesocket(serverSocket);
            WSACleanup();
            return;
        }
    }
}

std::string SimulationNetworkInterface::receiveData() {
    int iResult;
    int iSendResult;

    iResult = recv(clientSocket, receiveBuffer, receiveBufferLen, 0);
    if (iResult > 0) {
        return std::string(receiveBuffer);
    }
    else if (iResult == 0){
        printf("Connection closing...\n");
        return "";
    }
    else {
        printf("recv failed: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
        return "";
    }
}
