/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SCServer.h
 * Author: owner
 *
 * Created on December 8, 2017, 8:27 PM
 */

#ifndef SCSERVER_H
#define SCSERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#include <string.h>

#include <stdlib.h>

#include <stdio.h>
#include <unistd.h>

#define HOSTNAME "localhost"
#define PORT 8080
#define PORTNUMBER "8080"
#define BACKLOG 1
#define BSIZE 1024

#ifdef __cplusplus
extern "C" {
#endif

   
    int ListenFd();

    int RecvFd();
    
    int SocketFd(struct addrinfo **addrinfoResult);
    
    void ServerProcess(int clientFd);
    

#endif /* SCSERVER_H */