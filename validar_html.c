#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pila.h"
#include "validar_html.h"


Etiqueta	etiquetas_html[121];
Pila pila_auxiliar;

char		caracter_auxiliar = ' ';
char		cadena_auxiliar[15];

int		numero_de_etiquetas = 121;
int		apertura_encontrada = 0;
int		es_apertura = 0;
int		caracteres_almacenados = 0;
int		identificador_etiqueta = 0;
int		error = 0;
int		contador = 0;
int		unica = 0;
int		cerrando_etiqueta = 0;
int		comillas_activas = 0;
int		comillas_dobles_detectadas = -1;
int		comillas_simples_detectadas = -1;
int documento_valido = 0;

//toma el archivo etiquetas_html.txt para cargar las etiquetas validas
void
iniciar_etiquetas()
{
	FILE           *archivo_etiquetas = NULL;
	char		contenedor_auxiliar[20];
	char           *separacion_auxiliar = NULL;
	int		contador = 0;
	int		es_unico = 0;

	archivo_etiquetas = fopen("etiquetas_html.txt", "r");
	if (archivo_etiquetas == NULL) {
		printf("%s\n", "Error al abrir el archivo de las etiquetas html.");
		exit(0);
	}
	while (feof(archivo_etiquetas) == 0) {
		fscanf(archivo_etiquetas, "%s", contenedor_auxiliar);
		separacion_auxiliar = strtok(contenedor_auxiliar, ",");
		strcat(etiquetas_html[contador].etiqueta, separacion_auxiliar);
		etiquetas_html[contador].unico = 0;
		while (separacion_auxiliar != NULL) {
			es_unico = atoi(separacion_auxiliar);
			if (es_unico > 0) {
				etiquetas_html[contador].unico = es_unico;
			}
			separacion_auxiliar = strtok(NULL, ",");
		}
		contador++;
	}
}

int
almacenar_documento_html(FILE * archivo_html)
{
    if(archivo_html == NULL){
        printf("%s\n", "El archivo no es valido");
        exit(0);
    }
    pila_auxiliar.ultimo_agregado = 0;
	iniciar_etiquetas();
	while (feof(archivo_html) == 0) {
		caracter_auxiliar = tolower(fgetc(archivo_html));
		evaluar_comillas();
		if (apertura_encontrada == 1) {
			if (cerrando_etiqueta == 0) {
				if (caracter_auxiliar != '>' && caracter_auxiliar != ' ' && caracter_auxiliar != '<') {
					es_apertura = encontrar_cierre(caracter_auxiliar);
					if (es_apertura == 0) {
						contador++;
						continue;
					}
					cadena_auxiliar[caracteres_almacenados] = caracter_auxiliar;
					caracteres_almacenados++;
					evaluar_comentario();
				} else {
					evaluar_etiqueta();
				}
			} else {
				cerrar_etiqueta();
			}
		}
		if (apertura_encontrada == 0) {
			apertura_encontrada = encontrar_apertura(caracter_auxiliar);
		}
	}
	if (cerrando_etiqueta == 1) {
		guardar();
	}
    validar_documento_html();
    return documento_valido;
}

void
evaluar_etiqueta()
{
	if (strncmp(cadena_auxiliar, "!doctype", caracteres_almacenados) == 0 && caracteres_almacenados > 0) {
		cadena_auxiliar[caracteres_almacenados] = '-';
		caracteres_almacenados++;
	} else {
		if (caracteres_almacenados > 0) {
			identificador_etiqueta = encontrar_etiqueta(cadena_auxiliar, caracteres_almacenados);
			es_unica();
			if (caracter_auxiliar == '>') {
				guardar();
			} else {
				cerrando_etiqueta = 1;
				caracteres_almacenados = 0;
			}
		} else {
			apertura_encontrada = 0;
		}
	}
}

void
guardar()
{
	validar_cierre_etiqueta();
	if (documento_valido != 1) {
		error = push(&pila_auxiliar, 1000);
	}
    else{
        if (contador == 1) {
    		identificador_etiqueta = identificador_etiqueta * -1;
    	}
    	error = push(&pila_auxiliar, identificador_etiqueta);
    	if (identificador_etiqueta == 94 || identificador_etiqueta == 102) {
    		comillas_activas = 1;
    	}
    	if (identificador_etiqueta == -94 || identificador_etiqueta == -102) {
    		comillas_activas = 0;
    	}
    	if (unica == 1 || unica == 2 || unica == 3) {
    		error = push(&pila_auxiliar, identificador_etiqueta * -1);
    	}
    	reiniciar_variables();
    }
}

void
validar_documento_html()
{
	int		validar_suma = 0;
	//debe ser 0 al final para que el documento se considere correcto
	int		posicion = 0;
	for (posicion = 0; posicion < pila_auxiliar.ultimo_agregado; posicion++) {
		validar_suma = validar_suma + pila_auxiliar.elementos_pila[posicion];
	}
	if (validar_suma == 0) {
		documento_valido = 1;
	} else {
		documento_valido = 0;
	}
}

void
cerrar_etiqueta()
{
	if (caracter_auxiliar == '\"') {
		comillas_dobles_detectadas = comillas_dobles_detectadas * -1;
	}
	if (caracter_auxiliar == '\'') {
		comillas_simples_detectadas = comillas_simples_detectadas * -1;
	}
	if (comillas_dobles_detectadas < 0 && comillas_simples_detectadas < 0) {
		if (caracter_auxiliar == '>' || caracter_auxiliar == '/' || caracter_auxiliar == '-') {
			if (strncmp(cadena_auxiliar, "--", caracteres_almacenados + 1) != 0) {
				cadena_auxiliar[caracteres_almacenados] = caracter_auxiliar;
				caracteres_almacenados++;
			}
			if (caracter_auxiliar == '>') {
				guardar();
			}
		}
	}
}



int
encontrar_apertura(char caracter)
{
	if (caracter == '<') {
		return 1;
	} else {
		return 0;
	}
}

int
encontrar_etiqueta(char *cadena, int limite)
{
	int		posicion = 0;
	int		cadena_encontrada = 0;
	for (posicion = 0; posicion < numero_de_etiquetas; posicion++) {
		cadena_encontrada = strncmp(cadena, etiquetas_html[posicion].etiqueta, limite);
		if (cadena_encontrada == 0) {
			if (posicion + 1 == 121) {
				cadena_encontrada = strncmp(cadena, etiquetas_html[posicion].etiqueta, 3);
				if (cadena_encontrada == 0) {
					return posicion + 1;
				} else {
					return -1;
				}
			} else {
				return posicion + 1;
			}
		}
	}
	return -1;
}

int
encontrar_cierre(char caracter)
{
	if (caracter == '/') {
		return 0;
	} else {
		return 1;
	}
}

void
es_unica()
{
    unica = 0;
	if (etiquetas_html[identificador_etiqueta - 1].unico == 1) {
		unica = 1;
	}
	if (etiquetas_html[identificador_etiqueta - 1].unico == 2) {
		unica = 2;
	}
	if (etiquetas_html[identificador_etiqueta - 1].unico == 3) {
		unica = 3;
	}
}

void
reiniciar_variables()
{
	caracteres_almacenados = 0;
	es_apertura = 0;
	apertura_encontrada = 0;
	contador = 0;
	cerrando_etiqueta = 0;
	unica = 0;
}

void
validar_cierre_etiqueta()
{
    documento_valido = -1;
	if (unica == 1) {
		if (strncmp(cadena_auxiliar, "/>", caracteres_almacenados) == 0 || caracter_auxiliar == '>') {
			documento_valido = 1;
		}
	}
	if (unica == 0) {
		if (caracter_auxiliar == '>' && strncmp(cadena_auxiliar, "/>", caracteres_almacenados) != 0) {
			documento_valido = 1;
		}
	}
	if (unica == 2) {
		if (caracter_auxiliar == '>') {
			documento_valido = 1;
		}
	}
	if (unica == 3) {
		if (strncmp(cadena_auxiliar, "-->", caracteres_almacenados) == 0) {
			documento_valido = 1;
		}
	}
}

void
evaluar_comentario()
{
	if (caracteres_almacenados == 3 && strncmp(cadena_auxiliar, "!--", caracteres_almacenados) == 0) {
		identificador_etiqueta = encontrar_etiqueta(cadena_auxiliar, caracteres_almacenados);
		es_unica();
		cadena_auxiliar[0] = ' ';
		cadena_auxiliar[1] = ' ';
		cerrando_etiqueta = 1;
		caracteres_almacenados = 0;
	}
}


void
evaluar_comillas()
{
	if (comillas_activas == 1) {
		if (caracter_auxiliar == '\"') {
			comillas_dobles_detectadas = comillas_dobles_detectadas * -1;
		}
		if (caracter_auxiliar == '\'') {
			comillas_simples_detectadas = comillas_simples_detectadas * -1;
		}
		if (comillas_dobles_detectadas > 0 || comillas_simples_detectadas > 0) {
			apertura_encontrada = 0;
		}
	}
}
