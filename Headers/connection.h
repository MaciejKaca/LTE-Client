#pragma once

#include "common.h"

#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "preambles.h"
#include "rrc_connection.h"
#include "GUI/gui_logs.h"
#include "user_equipment.h"

void create_session(char *server_addres, int port);

void create_socket();

void connect_to_server();

void set_socket_non_blocking(int socket);

int send_data(int socket, void *data, message_label label);

int read_data(int socket, void *data, int data_size);

int recive_data_blocking(int socket, void *data, message_label *label);
