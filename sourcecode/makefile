CC=gcc
CFLAGS=-pedantic -ansi -std=iso9899:1999 -Wall

sprawdziany: main.o wczytaj.o pytania.o przedmioty.o flog.o
	$(CC) main.o wczytaj.o pytania.o przedmioty.o flog.o -o ../sprawdziany.out

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

wczytaj.o: wczytaj.c
	$(CC) $(CFLAGS) -c wczytaj.c -o wczytaj.o

pytania.o: pytania.c
	$(CC) $(CFLAGS) -c pytania.c -o pytania.o

przedmioty.o: przedmioty.c
	$(CC) $(CFLAGS) -c przedmioty.c -o przedmioty.o

flog.o: flog.c
	$(CC) $(CFLAGS) -c flog.c -o flog.o

clean:
	rm -f *.o

test:
	./sprawdziany.out wypisz pytania.txt

.PHONY: clean
