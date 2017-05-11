LDFLAGS=
CFLAGS=-std=c++11
CC=g++
OBJ=String.o Main.o

main: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

String.o: String.cpp String.h
	$(CC) -c $(CFLAGS) $<

Main.o: Main.cpp String.h Stack.h
	$(CC) -c $(CFLAGS) $<

clean:
	rm $(OBJ) main
