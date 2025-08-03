// src/client/net.cpp

#include <iostream>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include "net.hpp"

int sockfd;
sockaddr_in serverAddr;

bool net_init_client(const char* server_ip, int port) {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) return false;

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &serverAddr.sin_addr);

    return true;
}

void net_send_input(char input) {
    sendto(sockfd, &input, sizeof(input), 0, (sockaddr*)&serverAddr, sizeof(serverAddr));
}

int net_receive_state(char* buffer, int bufferSize) {
    socklen_t addrLen = sizeof(serverAddr);
    return recvfrom(sockfd, buffer, bufferSize, 0, (sockaddr*)&serverAddr, &addrLen);
}

void net_cleanup() {
    close(sockfd);
}

