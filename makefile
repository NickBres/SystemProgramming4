CC = gcc
CFLAGS = -Wall -Wextra -fPIC

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
	rm  *.o main