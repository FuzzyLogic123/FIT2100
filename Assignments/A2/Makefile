OBJS = main.o FCFS.o
CC = gcc
CFLAGS = -Wall -c
LFLAGS = -Wall

FCFS: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o FCFS

main.o: main.c main.h
	$(CC) $(CFLAGS) main.c

FCFS.o: FCFS.c
	$(CC) $(CFLAGS) FCFS.c