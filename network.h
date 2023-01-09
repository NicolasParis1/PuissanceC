//
// Created by nicolas on 09/01/23.
//

#ifndef PUISSANCEC_NETWORK_H
#define PUISSANCEC_NETWORK_H

void create_connection(int port, int *sock, int *client_sock);
void send_int(int data, int *client_sock);
int wait_for_int(int *client_sock);
void close_socket(int *sock);
void connect_to(char *ip, int port, int *sock);

#endif //PUISSANCEC_NETWORK_H
