//
// Created by nicolas on 28/09/22.
//

#ifndef PUISSANCEC_NETWORK_O_H
#define PUISSANCEC_NETWORK_O_H

typedef int SOCKET;

void createSocket(int, SOCKET*, SOCKET*);
void closeSocket(SOCKET, SOCKET);

int connectSocket(char*, int);
void closeClient(int);

#endif //PUISSANCEC_NETWORK_O_H