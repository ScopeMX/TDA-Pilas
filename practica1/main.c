#include <stdio.h>
#include <stdlib.h>
#include "validar_html.h"
#include "pila.h"

int
main(int argc, char const *argv[])
{
	FILE           *archivo_html = NULL;
	int		error = 0;

	archivo_html = fopen(argv[1], "r");
	if (archivo_html == NULL) {
		printf("%s\n", "Error al abrir el archivo");
		exit(0);
	}
	error = almacenar_documento_html(archivo_html);

	fclose(archivo_html);

	if (error == 1) {
		printf("%s\n", "Etiquetas balanceadas");
	} else {
		printf("%s\n", "Etiquetas no balanceadas");
	}

	return 0;
}
