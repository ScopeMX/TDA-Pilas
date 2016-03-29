#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pila.h"

int numero_de_etiquetas = 121;

Etiqueta etiquetas_html[121];

char caracter_auxiliar = ' ';
char cadena_auxiliar[15];
int apertura_encontrada = 0;
int es_apertura = 0;
int caracteres_almacenados = 0;
int id_etiqueta = 0;
int error = 0;
int contador = 0;
int unica = 0;
int cerrando_etiqueta = 0;

//toma el archivo etiquetas_html.txt para cargar las etiquetas validas
void iniciar_etiquetas(){
	FILE * archivo_etiquetas = NULL;
	char contenedor_auxiliar[20];
	char * separacion_auxiliar = NULL;
	int contador = 0;
	int es_unico = 0;

	archivo_etiquetas = fopen("etiquetas_html.txt", "r");
	if(archivo_etiquetas == NULL){
		printf("%s\n", "Error al abrir el archivo de las etiquetas html.");
		exit(0);
	}

	while(feof(archivo_etiquetas) == 0){
		fscanf(archivo_etiquetas, "%s", contenedor_auxiliar);
		separacion_auxiliar = strtok(contenedor_auxiliar, ",");
		strcat(etiquetas_html[contador].etiqueta, separacion_auxiliar);
		etiquetas_html[contador].unico = 0;
		while( separacion_auxiliar != NULL ){
			es_unico = atoi(separacion_auxiliar);
			if(es_unico > 0){
				etiquetas_html[contador].unico = es_unico;
			}
			separacion_auxiliar = strtok(NULL, ",");
	    }
		contador++;
	}
}

//Función que mete elementos a la pila
int push(Pila * A, int elemento){
	A->elementos_pila[A->ultimo_agregado] = elemento;
	A->ultimo_agregado++;
	return 1;
}

//funcion que saca elementos de la pila y retorna el elemento
int pop(Pila * A){
	A->ultimo_agregado--;
	return A->elementos_pila[A->ultimo_agregado];
}

int almacenar_documento_html(FILE * archivo_html, Pila * A){
	iniciar_etiquetas();

	while(feof(archivo_html)==0){
		caracter_auxiliar = tolower(fgetc(archivo_html));
		if(apertura_encontrada == 1){
			if(cerrando_etiqueta == 0){
				if(caracter_auxiliar != '>' && caracter_auxiliar != ' ' && caracter_auxiliar != '<'){
					es_apertura = encontrar_cierre(caracter_auxiliar);
					if(es_apertura == 0){
						contador++;
					}
					if(es_apertura == 0){
						continue;
					}
					cadena_auxiliar[caracteres_almacenados] = caracter_auxiliar;
					caracteres_almacenados++;
					if(caracteres_almacenados == 3 && strncmp(cadena_auxiliar, "!--", caracteres_almacenados) == 0){
						id_etiqueta = encontrar_etiqueta(cadena_auxiliar, caracteres_almacenados);
						unica = es_unica();
						cadena_auxiliar[0] = ' ';
						cadena_auxiliar[1] = ' ';
						cerrando_etiqueta = 1;
						caracteres_almacenados = 0;
					}
				}
				else{
					if(strncmp(cadena_auxiliar, "!doctype", caracteres_almacenados) == 0 && caracteres_almacenados > 0){
						cadena_auxiliar[caracteres_almacenados] = '-';
						caracteres_almacenados++;
					}
					else{
						if(caracteres_almacenados > 0){
							id_etiqueta = encontrar_etiqueta(cadena_auxiliar, caracteres_almacenados);
							unica = es_unica();
							if(caracter_auxiliar == '>'){
								error = guardar(A);
							}
							else{
								cerrando_etiqueta = 1;
								caracteres_almacenados = 0;
							}
						}
						else{apertura_encontrada = 0;}
					}
				}
			}
			else{
				cerrar_etiqueta(A);
			}
		}
		if(apertura_encontrada == 0){
			apertura_encontrada = encontrar_apertura(caracter_auxiliar);
		}
	}
	if(cerrando_etiqueta == 1){
		error = guardar(A);
	}
	return 0;
}

int encontrar_apertura(char caracter){
	if(caracter == '<'){
		return 1;
	}
	else{
		return 0;
	}
}

int encontrar_etiqueta(char * cadena, int limite){
	int i = 0;
	int cadena_encontrada = 0;
	for(i = 0; i < numero_de_etiquetas; i++){
		cadena_encontrada = strncmp(cadena, etiquetas_html[i].etiqueta, limite);
		if(cadena_encontrada == 0){
			if(i+1 == 121){
				cadena_encontrada = strncmp(cadena, etiquetas_html[i].etiqueta, 3);
				if(cadena_encontrada == 0){
					return i+1;
				}
				else{
					return -1;
				}
			}
			else{
				return i+1;
			}
		}
	}
	return -1;
}

int encontrar_cierre(char caracter){
	if(caracter == '/'){
		return 0;
	}
	else{
		return 1;
	}
}

int es_unica(){
	if(etiquetas_html[id_etiqueta-1].unico == 1){
		return 1;
	}
	if(etiquetas_html[id_etiqueta-1].unico == 2){
		return 2;
	}
	if(etiquetas_html[id_etiqueta-1].unico == 3){
		return 3;
	}
	return 0;
}

void reiniciar_variables(){
	caracteres_almacenados = 0;
	es_apertura = 0;
	apertura_encontrada = 0;
	contador = 0;
	cerrando_etiqueta = 0;
	unica = 0;
}

int validar_cierre_etiqueta(){
	if(unica == 1){
		if(strncmp(cadena_auxiliar, "/>", caracteres_almacenados) == 0 || caracter_auxiliar == '>'){
			return 1;
		}
	}
	if(unica == 0){
		if(caracter_auxiliar == '>' && strncmp(cadena_auxiliar, "/>", caracteres_almacenados)){
			return 1;
		}
	}
	if(unica == 2){
		if(caracter_auxiliar == '>'){
			return 1;
		}
	}
	if(unica == 3){
		if(strncmp(cadena_auxiliar, "-->", caracteres_almacenados) == 0){
			return 1;
		}
	}
	return -1;
}

int cerrar_etiqueta(Pila * A){
	if(caracter_auxiliar == '>' || caracter_auxiliar == '/' || caracter_auxiliar == '-'){
		if(strncmp(cadena_auxiliar, "--", caracteres_almacenados+1) != 0){
			cadena_auxiliar[caracteres_almacenados] = caracter_auxiliar;
			caracteres_almacenados++;
		}
		if(caracter_auxiliar == '>'){
			error = guardar(A);
		}
	}
	return 1;
}


int guardar(Pila * A){
	error = validar_cierre_etiqueta();
	if(error != 1){
		error = push(A, 1000);
		return 0;
	}
	if(contador > 0){
		id_etiqueta = id_etiqueta * -1;
	}
	error = push(A, id_etiqueta);
	if(unica == 1 || unica == 2 || unica == 3){
		error = push(A, id_etiqueta * -1);
	}
	reiniciar_variables();
	return 0;
}

int validar_documento_html(Pila * A){
	int validar_suma = 0; //debe ser 0 al final para que el documento se considere correcto
	int i = 0;
	for(i = 0; i < A->ultimo_agregado; i++){
		validar_suma = validar_suma + A->elementos_pila[i];
	}
	if(validar_suma == 0){
		return 1;
	}
	else{
		return 0;
	}
}
