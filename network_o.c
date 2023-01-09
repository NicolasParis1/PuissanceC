//
// Created by nicolas on 28/09/22.
//

#include "network_o.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(param) close(param)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

struct sockets {
    SOCKET sock;
    SOCKET csock;
};

void createSocket(int port, SOCKET* sock, SOCKET* csock) {

    /* Socket et contexte d'adressage du serveur */
    SOCKADDR_IN sin;
    //SOCKET sock;
    socklen_t recsize = sizeof(sin);

    /* Socket et contexte d'adressage du client */
    SOCKADDR_IN csin;
    //SOCKET csock;
    socklen_t crecsize = sizeof(csin);

    int sock_err;


    /* Création d'une socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);

    /* Si la socket est valide */
    if (sock != INVALID_SOCKET) {
        printf("La socket %d est maintenant ouverte en mode TCP/IP\n", sock);

        /* Configuration */
        sin.sin_addr.s_addr = htonl(INADDR_ANY);  /* Adresse IP automatique */
        sin.sin_family = AF_INET;                 /* Protocole familial (IP) */
        sin.sin_port = htons(port);               /* Listage du port */
        sock_err = bind(sock, (SOCKADDR *) &sin, recsize);

        /* Si la socket fonctionne */
        if (sock_err != SOCKET_ERROR) {
            /* Démarrage du listage (mode server) */
            sock_err = listen(sock, 5);
            printf("Listage du port %d...\n", port);

            /* Si la socket fonctionne */
            if (sock_err != SOCKET_ERROR) {
                /* Attente pendant laquelle le client se connecte */
                printf("Patientez pendant que le client se connecte sur le port %d...\n", port);
                csock = accept(sock, (SOCKADDR *) &csin, &crecsize);
                printf("Un client se connecte avec la socket %d de %s:%d\n", csock, inet_ntoa(csin.sin_addr),
                       htons(csin.sin_port));
            } else
                perror("listen");
        } else
            perror("bind");

        /* Fermeture de la socket client et de la socket serveur */
        printf("Fermeture de la socket client\n");
        closesocket(csock);
        printf("Fermeture de la socket serveur\n");
        closesocket(sock);
        printf("Fermeture du serveur terminée\n");
    }
}

void closeSocket(SOCKET sock, SOCKET csock) {
    closesocket(csock);
    closesocket(sock);
}

int connectSocket(char* hostname, int port) {

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET)
    {
        perror("socket()");
    }

    int client_fd;

    struct sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    inet_pton(AF_INET, hostname, &serv_addr.sin_addr);
    client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));


    char buffer[1024];
    if(send(sock, buffer, strlen(buffer), 0) < 0)
    {
        perror("send()");
    }
    return client_fd;

}

void closeClient(int client_fd) {
    close(client_fd);
}