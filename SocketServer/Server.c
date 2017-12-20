/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: owner
 *
 * Created on December 2, 2017, 4:43 PM
 */

#include "SCServer.h"

int main(int argc, char *argv[]) {
    printf("SERVER: Startup.\n");

    int clientFd = 0;
    int listenFd = 0;

    listenFd = ListenFd();
    while (1) { // main accept() loop

        struct sockaddr_storage clientaddr;
        socklen_t addrsize;
        printf("SERVER: Waiting for client connection.\n");
        clientFd = accept(listenFd, (struct sockaddr *) &clientaddr, &addrsize);
        if (clientFd == -1) {
            perror("accept");
            continue;
        }
        if (!fork()) { // this is the child process
            close(listenFd); // child doesn't need the listener

            ServerProcess(clientFd);

            close(clientFd);
            printf("SERVER: Child process exiting.\n");
            exit(EXIT_SUCCESS);
        }
        printf("SERVER: Closing clientFd.\n");
        close(clientFd); // parent doesn't need this
    }

    printf("SERVER: Shutdown.\n");

    return 0;
}


