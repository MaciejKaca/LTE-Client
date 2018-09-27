#include "Headers/queue_ping.h"

Queue_Ping *ping_queue;

Queue_Ping *Ping_createQueue(unsigned capacity)
{
	Queue_Ping *queue = (Queue_Ping *)malloc(sizeof(Queue_Ping));
	queue->capacity = capacity;
	queue->size = 0;
	queue->first_entry = NULL;
	queue->actual_entry = NULL;
	return queue;
}

void Ping_add_log_entry(char item[60])
{
	Queue_Entry *entry = (Queue_Entry *)malloc(sizeof(Queue_Entry));
	strcpy(entry->text, item);

	if (ping_queue->first_entry == NULL)
		ping_queue->first_entry = entry;
	else
	{
		Queue_Entry *actual_entry = ping_queue->first_entry;
		while (actual_entry->next != NULL)
		{
			actual_entry = actual_entry->next;
		}
		actual_entry->next = entry;
	}

	if (ping_queue->size != ping_queue->capacity)
		ping_queue->size++;
	else
		ping_queue->first_entry = ping_queue->first_entry->next;
}

char *Ping_get_next_log_entry(Queue *queue)
{
	if (ping_queue->actual_entry == NULL)
		return NULL;
	char *actual_entry = ping_queue->actual_entry->text;
	ping_queue->actual_entry = ping_queue->actual_entry->next;
	return actual_entry;
}

void Ping_reset_queue() { ping_queue->actual_entry = ping_queue->first_entry; }