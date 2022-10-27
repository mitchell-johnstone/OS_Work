CC=gcc
CFLAGS=-Wall -Wextra -c -g
LDFLAGS=
SOURCES=ttsh.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=ttsh

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $(LDFLAGS) $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
