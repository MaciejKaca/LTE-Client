#pragma once

#include "common.h"

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>

extern int client_socket;

void create_session(char *server_addres, int port);

void create_socket();

void connect_to_server();

void set_socket_non_blocking(int socket);

void send_data(int socket, void *data, message_label label);

int read_data(int socket, void *data, int data_size);

int receive_data(int socket, void *data, message_label *label);
