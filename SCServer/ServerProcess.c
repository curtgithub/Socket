/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "SCServer.h"

void ServerProcess(int clientFd) {
    char ibuf[BSIZE] = {0};
    char obuf[BSIZE] = {0};
    int nbytes;
    char* header = "Acknowledge message. ";
    int hdrlen = strlen(header);
    while ((nbytes = recv(clientFd, ibuf, BSIZE, MSG_WAITALL))) {
        printf("SERVER: Received nbytes = %d\n", nbytes);
        printf("SERVER: Received message. %s\n", ibuf);

        sprintf(obuf, "%s%s", header, ibuf);
        send(clientFd, obuf, hdrlen + nbytes, MSG_NOSIGNAL);
        printf("SERVER: Sent nbytes = %d\n", hdrlen + nbytes);
        printf("SERVER: Sent message  -> %s\n", obuf);
    }

    printf("SERVER: Received nbytes = %d\n", nbytes);

}