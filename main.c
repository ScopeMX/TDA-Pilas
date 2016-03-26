#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

int main(int argc, char const *argv[])
{
	Pila validar;
	FILE *archivo_html = NULL;
	int archivo_validado = 0;
	int error = 0;

	validar.ultimo_agregado=0;

	archivo_html = fopen(argv[1], "r");
	if(archivo_html == NULL){
		printf("%s\n", "Error al abrir el archivo");
		exit(0);
	}

	error = almacenar_documento_html(archivo_html, &validar);
	error = validar_documento_html(&validar);

	if(error == 1){
		printf("%s\n", "OK");
	}
	else{
		printf("%s\n", "html invalido");
	}

	fclose(archivo_html);

	return 0;
}
