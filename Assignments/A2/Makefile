OBJS = main.o
CC = gcc
CFLAGS = -Wall -c
LFLAGS = -Wall -g

all: FCFS RR

FCFS: $(OBJS) FCFS.o
	$(CC) $(LFLAGS) $(OBJS) FCFS.o -o FCFS

RR: $(OBJS) RR.o
	$(CC) $(LFLAGS) $(OBJS) RR.o -o RR

main.o: main.c main.h
	$(CC) $(CFLAGS) main.c

FCFS.o: FCFS.c
	$(CC) $(CFLAGS) FCFS.c

RR.o: RR.c
	$(CC) $(CFLAGS) RR.c
