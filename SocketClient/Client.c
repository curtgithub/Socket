/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: owner
 *
 * Created on December 2, 2017, 4:53 PM
 */

// Client side C/C++ program to demonstrate Socket programming

#include "SCServer.h"

int main(int argc, char *argv[]) {
    printf("CLIENT: Startup.\n");

    int recvFd = RecvFd();

    printf("CLIENT: Connected to server.\n");

    char buf[BSIZE] = {0};
    int nbytes = 0;
    char* header = "Request ";
    int hdrlen = strlen(header);
    for (int i = 0; i < 10; i++) {
        sprintf(buf, "%s%d", header, i);
        send(recvFd, buf, hdrlen + 2, 0);
        printf("CLIENT: sent nbytes = %d\n", hdrlen + 2);
        printf("CLIENT: sent message -> %s\n", buf);

        nbytes = recv(recvFd, buf, BSIZE, 0);
        printf("CLIENT: received nbytes = %d\n", nbytes);
        printf("CLIENT: received message -> %s\n", buf);
    }

    printf("CLIENT: Shutdown.\n");

    return 0;
}