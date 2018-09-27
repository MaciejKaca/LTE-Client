#pragma once
#include "common.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


typedef struct Queue_Ping
{
	Queue_Entry *first_entry;
	Queue_Entry *actual_entry;
	unsigned capacity;
	unsigned size;
	unsigned how_many_to_show;
} Queue_Ping;

Queue_Ping *Ping_createQueue(unsigned capacity);

void Ping_add_log_entry(char item[]);

char *Ping_get_next_log_entry();

void Ping_reset_queue();