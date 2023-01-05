CC = gcc
CFLAGS = -Wall -g -fPIC

all: graph
	clear
#   ./main

graph: main.o graph.o algo.o
	$(CC) $(CFLAGS) $^ -o $@

#------- o files-------
%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@	
#------------------------------

clean:
	rm  *.o graph