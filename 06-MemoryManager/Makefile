CC=gcc
CFLAGS=-Wall -g -pthread

all: testmemmgr pthread_testmemmgr

testmemmgr: memory_manager.o testmemmgr.o
	$(CC) -o testmemmgr $^

pthread_testmemmgr: memory_manager.o pthread_testmemmgr.o
	$(CC) -pthread -o pthread_testmemmgr $^

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f testmemmgr pthread_testmemmgr *.o
