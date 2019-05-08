# CC = gcc
# CFLAGS = -Wall -std=c99
#
# all: test
#
# airport.o: airport.c shortest_path.h
# 	$(CC) $(CFLAGS) -c airport.c
#
# airport_map.o: airport_map.c shortest_path.h
# 	$(CC) $(CFLAGS) -c airport_map.c
#
# dijkstra.o: dijkstra.c shortest_path.h
# 	$(CC) $(CFLAGS) -c dijkstra.c
#
# bellman.o: bellman.c shortest_path.h
# 	$(CC) $(CFLAGS) -c bellman.c
#
# test: airport.o airport_map.o dijkstra.o bellman.o
# 	$(CC) $(CFLAGS) -o test airport_map.o airport.o dijkstra.o bellman.o
#
# clean:
# 	rm *.o test



CC = gcc
CFLAGS = -Wall -std=c99

all: test

airport.o: airport.c shortest_path.h
	$(CC) $(CFLAGS) -c airport.c

bellman.o: bellman.c shortest_path.h
	$(CC) $(CFLAGS) -c bellman.c

test: airport.o bellman.o
	$(CC) $(CFLAGS) -o test airport.o bellman.o

clean:
	rm *.o test
