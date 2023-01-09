CC = gcc
CFLAGS = -Wall -g -fPIC

all: graph

graph: node.o edge.o graph.o algo.o main.o
	$(CC) $(CFLAGS) $^ -o $@

#------- o files-------
%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@	
#------------------------------

clean:
	rm  *.o graph