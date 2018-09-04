#pragma once

#include "common.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

extern int client_socket;

void create_session(char *server_addres, int port);

void create_socket();

void connect_to_server();
