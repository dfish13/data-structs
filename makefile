LDFLAGS=
CFLAGS=-std=c++11
CC=g++
OBJ=String.o Integer.o main.o

main: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

String.o: String.cpp String.h
	$(CC) -c $(CFLAGS) $<

Integer.o: Integer.cpp Integer.h
	$(CC) -c $(CFLAGS) $<

main.o: main.cpp String.h Stack.h Integer.h
	$(CC) -c $(CFLAGS) $<

clean:
	rm $(OBJ) main
