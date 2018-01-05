/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "SCServer.h"

int ListenFd() {


    int listenFd = 0;

    // Get socket file descriptor
    struct addrinfo *addrinfoResult;
    listenFd = SocketFd(&addrinfoResult);

    // Bind the socket to the PORTNUMBER
    if (bind(listenFd, addrinfoResult->ai_addr, addrinfoResult->ai_addrlen)) {
        perror("bind() failed!");
        exit(EXIT_FAILURE);
    }

    // Listen 
    if (listen(listenFd, BACKLOG)) {
        perror("listen() failed!");
        exit(EXIT_FAILURE);
    }


    return (listenFd);
}
