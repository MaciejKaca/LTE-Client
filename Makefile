CC = gcc
CC_FLAGS = -g

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
EXEC = lte_client

$(EXEC): $(OBJECTS)
	$(CC) -pthread $(OBJECTS) -o $(EXEC)
	rm -f *.o *~

%.o: %.c
	$(CC) -c $(CC_FLAGS) $< -o $@

