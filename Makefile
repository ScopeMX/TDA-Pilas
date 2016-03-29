run: a.out
	./a.out index.html

a.out: main.o pila.o
	gcc main.o pila.o
	make clean

main.o: main.c
	gcc -c main.c -o main.o

pila.o: pila.c
	gcc -c pila.c -o pila.o

clean:
	rm main.o pila.o
