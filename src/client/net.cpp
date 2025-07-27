#Client

#include <iostream.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <net.hpp>
#include <vector.h>

int sockfd;
sockaddr_in serverAddr;

bool net_init(const char* server_ip, int port) {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if ( sockfd < 0 ) return false;
    
    memset(&serverAddr, 0, sizeof(serverAddr));
    severAddr.in_family = AF_INET;
    severAddr.sin_port = htons(port);
    inet_pton(AF_INET, sever_ip, &serverAddr.sin_addr);

    return true; 
}

int net_receive_input(char input) {
    sento(sockfd, &input, sizeof(input), 0, (sockaddr*)serverAddr, sizeof(serverAddr));
}

int net_receive_state(char* buffer, size_t bufferSize) {
    socklen_t addrLen = sizeof(serverAddr);
    return recvfrom(sockfd, buffer, bufferSize, 0, (sockaddr*)&serverAddr, &addrLen);
}

void net_cleanup() {
    close(sockfd);
}
