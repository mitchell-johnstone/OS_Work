CC=gcc
CFLAGS=-Wall -g

all: smTester

smTester: stackm.o smTester.o
	$(CC) -o smTester $^

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f smTester *.o