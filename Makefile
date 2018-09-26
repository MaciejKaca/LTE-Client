CC = gcc
CC_FLAGS = -g
IP = localhost
PORT = 2222

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
EXEC = lte_client

$(EXEC): $(OBJECTS)
	$(CC) -pthread $(OBJECTS) -lm -o $(EXEC)
	rm -f *.o *~

%.o: %.c
	$(CC) -c $(CC_FLAGS) $< -o $@

valgrind:
	valgrind --leak-check=full \
		 --show-leak-kinds=all \
		 --track-origins=yes \
		 --verbose \
		 --log-file=valgrind-out.txt \
		 ./$(EXEC) $(IP) $(PORT)
