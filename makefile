CC = gcc
CFLAGS = -Wall -Wextra -fPIC

all: main
	clear
	./main

main: main.o graph.o algo.o
	$(CC) $(CFLAGS) $^ -o $@

#------- o files-------
%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@	
#------------------------------

clean:
	rm  *.o main