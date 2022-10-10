OBJS = main.o
CC = gcc
CFLAGS = -Wall -c
LFLAGS = -Wall -g

all: FCFS RR deadline

FCFS: $(OBJS) FCFS.o
	$(CC) $(LFLAGS) $(OBJS) FCFS.o -o FCFS

RR: $(OBJS) RR.o
	$(CC) $(LFLAGS) $(OBJS) RR.o -o RR

deadline: $(OBJS) deadline.o
	$(CC) $(LFLAGS) $(OBJS) deadline.o -o deadline

main.o: main.c main.h
	$(CC) $(CFLAGS) main.c

FCFS.o: FCFS.c
	$(CC) $(CFLAGS) FCFS.c

RR.o: RR.c
	$(CC) $(CFLAGS) RR.c

deadline.o: deadline.c
	$(CC) $(CFLAGS) deadline.c