LDFLAGS=
CFLAGS=
CC=g++

main: String.o Main.o
	$(CC) -o $@ $^ $(LDFLAGS)

String.o: String.cpp String.h
	$(CC) -c $(CFLAGS) $<

Main.o: Main.cpp String.h
	$(CC) -c $(CFLAGS) $<

clean:
	rm *.o a.out


