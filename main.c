#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

int main(int argc, char const *argv[])
{
	Pila validar;
	FILE *archivo = NULL;
	char caracter = ' ';

	validar.ultimo_agregado=0;

	archivo = fopen(argv[1], "r");
	if(archivo == NULL){
		printf("%s\n", "Error al abrir el archivo");
		exit(0);
	}

	while(feof(archivo)==0){
		caracter = fgetc(archivo);
		printf("%c", caracter);
	}

	fclose(archivo);

	return 0;
}
