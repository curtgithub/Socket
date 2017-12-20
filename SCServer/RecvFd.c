/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "SCServer.h"

int RecvFd() {

    int recvFd = 0;

    // Get socket file descriptor
    struct addrinfo *addrinfoResult;
    recvFd = SocketFd(&addrinfoResult);

    // Connect to server
    if (connect(recvFd, addrinfoResult->ai_addr, addrinfoResult->ai_addrlen) == -1) {
        printf("Server is not running.\n");
        close(recvFd);
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    return (recvFd);
}