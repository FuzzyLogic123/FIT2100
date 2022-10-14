OBJS = main.o
CC = gcc
CFLAGS = -Wall -c
LFLAGS = -Wall -g

all: task1-32460929 task2-32460929 task3-32460929

task1-32460929: $(OBJS) task1-32460929.o
	$(CC) $(LFLAGS) $(OBJS) task1-32460929.o -o task1-32460929

task2-32460929: $(OBJS) task2-32460929.o
	$(CC) $(LFLAGS) $(OBJS) task2-32460929.o -o task2-32460929

task3-32460929: $(OBJS) task3-32460929.o
	$(CC) $(LFLAGS) $(OBJS) task3-32460929.o -o task3-32460929

main.o: main.c main.h
	$(CC) $(CFLAGS) main.c

task1-32460929.o: task1-32460929.c
	$(CC) $(CFLAGS) task1-32460929.c

task2-32460929.o: task2-32460929.c
	$(CC) $(CFLAGS) task2-32460929.c

task3-32460929.o: task3-32460929.c
	$(CC) $(CFLAGS) task3-32460929.c