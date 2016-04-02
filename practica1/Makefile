a.out: main.o pila.o validar_html.o
	gcc main.o pila.o validar_html.o
	make clean

main.o: main.c
	gcc -c main.c -o main.o

pila.o: pila.c
	gcc -c pila.c -o pila.o

validar_html.o: validar_html.c
	gcc -c validar_html.c -o validar_html.o

clean:
	rm main.o pila.o validar_html.o
