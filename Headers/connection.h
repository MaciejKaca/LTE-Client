#pragma once

#include "common.h"

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

extern int client_socket;

void create_session(char *server_addres, int port);

void create_socket();

void connect_to_server();
