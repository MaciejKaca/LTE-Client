CC = gcc
CC_FLAGS = -w

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
EXEC = lte_client

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

clean:
	rm -f $(EXEC) $(OBJECTS)