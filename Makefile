#Makefile
all: add-nbo

add-nbo: main.o
	g++ -o add-nbo main.o

main.o: main.c
	g++ -c -o main.o main.c

clean:
	rm -f add-nbo
	rm -f *.o
