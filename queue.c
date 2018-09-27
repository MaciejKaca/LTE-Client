#include "Headers/queue.h"

Queue *logs_queue;

Queue *createQueue(unsigned capacity)
{
	Queue *queue = (Queue *)malloc(sizeof(Queue));
	queue->capacity = capacity;
	queue->size = 0;
	queue->first_entry = NULL;
	queue->actual_entry = NULL;
	return queue;
}

void add_log_entry(char item[60])
{
	Queue_Entry *entry = (Queue_Entry *)malloc(sizeof(Queue_Entry));
	strcpy(entry->text, item);

	if (logs_queue->first_entry == NULL)
		logs_queue->first_entry = entry;
	else
	{
		Queue_Entry *actual_entry = logs_queue->first_entry;
		while (actual_entry->next != NULL)
		{
			actual_entry = actual_entry->next;
		}
		actual_entry->next = entry;
	}

	if (logs_queue->size != logs_queue->capacity)
		logs_queue->size++;
	else
		logs_queue->first_entry = logs_queue->first_entry->next;
}

char *get_next_log_entry(Queue *queue)
{
	if (logs_queue->actual_entry == NULL)
		return NULL;
	char *actual_entry = logs_queue->actual_entry->text;
	logs_queue->actual_entry = logs_queue->actual_entry->next;
	return actual_entry;
}

void reset_queue() { logs_queue->actual_entry = logs_queue->first_entry; }