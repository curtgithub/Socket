/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "SCServer.h"

#include <arpa/inet.h>

int SocketFd(struct addrinfo **addrinfoResult) {
    int socketFd = 0;

    // Get address of HOSTNAME.
    struct addrinfo addrinfoInput;
    memset(&addrinfoInput, 0, sizeof (addrinfoInput));
    addrinfoInput.ai_family = AF_INET; // use IPv4
    addrinfoInput.ai_socktype = SOCK_STREAM;
    addrinfoInput.ai_flags = AI_PASSIVE; // fill in my IP for me
    if (getaddrinfo(HOSTNAME, PORTNUMBER, &addrinfoInput, addrinfoResult)) {
        perror("getaddrinfo() failed!");
        exit(EXIT_FAILURE);
    }

    // Make a socket from the HOSTNAME address:
    if (!(socketFd = socket((*addrinfoResult)->ai_family,
            (*addrinfoResult)->ai_socktype, (*addrinfoResult)->ai_protocol))) {
        perror("socket() failed");
        exit(EXIT_FAILURE);
    }
    
    char *ip;
    struct sockaddr_in *addr;
    addr = (struct sockaddr_in *) (*addrinfoResult)->ai_addr;
    ip = inet_ntoa((struct in_addr) addr->sin_addr);
    printf("SocketFD: IP address = %s\n", ip);

    return (socketFd);
}
