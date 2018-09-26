#pragma once
#include "common.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Queue_Entry
{
	char text[60];
	struct Queue_Entry *next;
} Queue_Entry;

typedef struct Queue
{
	Queue_Entry *first_entry;
	Queue_Entry *actual_entry;
	unsigned capacity;
	unsigned size;
	unsigned how_many_to_show;
} Queue;

Queue *createQueue(unsigned capacity);

void add_log_entry(char item[]);

char *get_next_log_entry();

void reset_queue();