#Server

#include <iostream.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <net.hpp>
#include <vector.h>

int sockfd;

bool net_init(int port) {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if ( sockfd < 0 ) return false;

    sockaddr_in serverAddr{};
    severAddr.in_family = AF_INET;
    severAddr.sin_addr.s_addr = INADDR_ANY;
    severAddr.sin_port = htons(port);

    return bind(sockfd, (sockaddr*)&severAddr, sizeof(severAddr)) == 0;
}

int net_receive_input(char* input, sockaddr_in* clientAddr) {
    socklen_t addrLen = sizeof(*clinetAddr);
    return recvfrom(sockfd, input, sizeof(char), 0, (sockaddr*)clienrAddr, &addrLen);
}

void net_send_state(const char* state, size_t size, const sockaddr_in& clientAddr) {
    sendto(sockfd, state, size, 0, (sockaddr*)&clientAddr, sizeof(clientAddr));
}

void net_cleanup() {
    close(sockfd);
}
