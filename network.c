//
// Created by nicolas on 09/01/23.
//

#include "network.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

void create_connection(int port, int *sock, int *client_sock) {
    // create a socket
    *sock = socket(AF_INET, SOCK_STREAM, 0);

    // bind the socket to a local address
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    bind(*sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));    //TODO: if 0

    // listen for incoming connections
    listen(*sock, 1);

    // accept incoming connections
    struct sockaddr_in cli_addr;
    socklen_t cli_len = sizeof(cli_addr);
    *client_sock = accept(*sock, (struct sockaddr*)&cli_addr, &cli_len);
}

void connect_to(char *ip, int port, int *sock) {
    // create a socket
    *sock = socket(AF_INET, SOCK_STREAM, 0);

    // connect to the server
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port);
    if(connect(*sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1) {
        perror("connect()");
        exit(errno);
    }

}

void close_socket(int *sock) {
    close(*sock);
}

void send_int(int data, int *client_sock) {
    char c = data;
    send(*client_sock, &c, sizeof(c), 0);
}

int wait_for_int(int *sock) {
    char c;
    int x;
    do {
        recv(*sock, &c, sizeof(c), 0);
        x = (int)c;
    } while(x<0 || x>6);
    return x;
}