#pragma once

#include "common.h"

void print_received_data_type(char message[]);

void print_sent_data_type(char message[]);

void resolve_ping();

void server_listen_respond();

void server_send_requests();

void resolve_backup_server_info();

void resolve_handover_control();

void resolve_handover_start();

void download_file();

void server_handle_IO();