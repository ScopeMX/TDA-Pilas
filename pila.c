#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pila.h"

int numero_de_etiquetas = 120;

Etiqueta etiquetas_html[120];

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

void iniciar_etiquetas(){
	 strcat(etiquetas_html[0].etiqueta, "!doctype");
	 etiquetas_html[0].unico = 2;

	 strcat(etiquetas_html[1].etiqueta, "a");
	 strcat(etiquetas_html[2].etiqueta, "abbr");
	 strcat(etiquetas_html[3].etiqueta, "acronym");
	 strcat(etiquetas_html[4].etiqueta, "address");
	 strcat(etiquetas_html[5].etiqueta, "applet");
	 strcat(etiquetas_html[6].etiqueta, "area");
	 strcat(etiquetas_html[7].etiqueta, "article");
	 strcat(etiquetas_html[8].etiqueta, "aside");
	 strcat(etiquetas_html[9].etiqueta, "audio");
	 strcat(etiquetas_html[10].etiqueta, "b");

	 strcat(etiquetas_html[11].etiqueta, "base");
	 strcat(etiquetas_html[12].etiqueta, "basefont");
	 strcat(etiquetas_html[13].etiqueta, "bdi");
	 strcat(etiquetas_html[14].etiqueta, "bdo");
	 strcat(etiquetas_html[15].etiqueta, "big");
	 strcat(etiquetas_html[16].etiqueta, "blockquote");
	 strcat(etiquetas_html[17].etiqueta, "body");

	 strcat(etiquetas_html[18].etiqueta, "br");
	 etiquetas_html[18].unico = 1;

	 strcat(etiquetas_html[19].etiqueta, "button");
	 strcat(etiquetas_html[20].etiqueta, "canvas");

	 strcat(etiquetas_html[21].etiqueta, "caption");
	 strcat(etiquetas_html[22].etiqueta, "center");
	 strcat(etiquetas_html[23].etiqueta, "cite");
	 strcat(etiquetas_html[24].etiqueta, "code");
	 strcat(etiquetas_html[25].etiqueta, "col");
	 strcat(etiquetas_html[26].etiqueta, "colgroup");
	 strcat(etiquetas_html[27].etiqueta, "datalist");
	 strcat(etiquetas_html[28].etiqueta, "dd");
	 strcat(etiquetas_html[29].etiqueta, "del");
	 strcat(etiquetas_html[30].etiqueta, "details");

	 strcat(etiquetas_html[31].etiqueta, "dfn");
	 strcat(etiquetas_html[32].etiqueta, "dialog");
	 strcat(etiquetas_html[33].etiqueta, "dir");
	 strcat(etiquetas_html[34].etiqueta, "div");
	 strcat(etiquetas_html[35].etiqueta, "dl");
	 strcat(etiquetas_html[36].etiqueta, "dt");
	 strcat(etiquetas_html[37].etiqueta, "em");
	 strcat(etiquetas_html[38].etiqueta, "embed");
	 strcat(etiquetas_html[39].etiqueta, "fieldset");
	 strcat(etiquetas_html[40].etiqueta, "figcaption");

	 strcat(etiquetas_html[41].etiqueta, "figure");
	 strcat(etiquetas_html[42].etiqueta, "font");
	 strcat(etiquetas_html[43].etiqueta, "footer");
	 strcat(etiquetas_html[44].etiqueta, "form");
	 strcat(etiquetas_html[45].etiqueta, "frame");
	 strcat(etiquetas_html[46].etiqueta, "frameset");
	 strcat(etiquetas_html[47].etiqueta, "h1");
	 strcat(etiquetas_html[48].etiqueta, "h2");
	 strcat(etiquetas_html[49].etiqueta, "h3");
	 strcat(etiquetas_html[50].etiqueta, "h4");

	 strcat(etiquetas_html[51].etiqueta, "h5");
	 strcat(etiquetas_html[52].etiqueta, "h6");
	 strcat(etiquetas_html[53].etiqueta, "head");
	 strcat(etiquetas_html[54].etiqueta, "header");
	 strcat(etiquetas_html[55].etiqueta, "hr");
	 strcat(etiquetas_html[56].etiqueta, "html");
	 strcat(etiquetas_html[57].etiqueta, "i");
	 strcat(etiquetas_html[58].etiqueta, "iframe");
	 strcat(etiquetas_html[59].etiqueta, "img");
	 etiquetas_html[59].unico = 1;

	 strcat(etiquetas_html[60].etiqueta, "input");
	 strcat(etiquetas_html[61].etiqueta, "ins");
	 strcat(etiquetas_html[62].etiqueta, "kbd");
	 strcat(etiquetas_html[63].etiqueta, "keygen");
	 strcat(etiquetas_html[64].etiqueta, "label");
	 strcat(etiquetas_html[65].etiqueta, "legend");
	 strcat(etiquetas_html[66].etiqueta, "li");
	 strcat(etiquetas_html[67].etiqueta, "link");
	 etiquetas_html[67].unico = 1;
	 strcat(etiquetas_html[68].etiqueta, "main");
	 strcat(etiquetas_html[69].etiqueta, "map");
	 strcat(etiquetas_html[70].etiqueta, "mark");

	 strcat(etiquetas_html[71].etiqueta, "menu");
	 strcat(etiquetas_html[72].etiqueta, "menuitem");
	 strcat(etiquetas_html[73].etiqueta, "meta");
	 etiquetas_html[73].unico = 1;

	 strcat(etiquetas_html[74].etiqueta, "meter");
	 strcat(etiquetas_html[75].etiqueta, "nav");
	 strcat(etiquetas_html[76].etiqueta, "noframes");
	 strcat(etiquetas_html[77].etiqueta, "noscript");
	 strcat(etiquetas_html[78].etiqueta, "object");
	 strcat(etiquetas_html[79].etiqueta, "ol");
	 strcat(etiquetas_html[80].etiqueta, "optgroup");

	 strcat(etiquetas_html[81].etiqueta, "option");
	 strcat(etiquetas_html[82].etiqueta, "output");
	 strcat(etiquetas_html[83].etiqueta, "p");
	 strcat(etiquetas_html[84].etiqueta, "param");
	 strcat(etiquetas_html[85].etiqueta, "pre");
	 strcat(etiquetas_html[86].etiqueta, "progress");
	 strcat(etiquetas_html[87].etiqueta, "q");
	 strcat(etiquetas_html[88].etiqueta, "rp");
	 strcat(etiquetas_html[89].etiqueta, "rt");
	 strcat(etiquetas_html[90].etiqueta, "ruby");

	 strcat(etiquetas_html[91].etiqueta, "s");
	 strcat(etiquetas_html[92].etiqueta, "samp");
	 strcat(etiquetas_html[93].etiqueta, "script");
	 strcat(etiquetas_html[94].etiqueta, "section");
	 strcat(etiquetas_html[95].etiqueta, "select");
	 strcat(etiquetas_html[96].etiqueta, "small");
	 strcat(etiquetas_html[97].etiqueta, "source");
	 etiquetas_html[97].unico = 1;
	 strcat(etiquetas_html[98].etiqueta, "span");
	 strcat(etiquetas_html[99].etiqueta, "strike");
	 strcat(etiquetas_html[100].etiqueta, "strong");

	 strcat(etiquetas_html[101].etiqueta, "style");
	 strcat(etiquetas_html[102].etiqueta, "sub");
	 strcat(etiquetas_html[103].etiqueta, "table");
	 strcat(etiquetas_html[104].etiqueta, "tbody");
	 strcat(etiquetas_html[105].etiqueta, "td");
	 strcat(etiquetas_html[106].etiqueta, "textarea");
	 strcat(etiquetas_html[107].etiqueta, "tfoot");
	 strcat(etiquetas_html[108].etiqueta, "th");
	 strcat(etiquetas_html[109].etiqueta, "thead");
	 strcat(etiquetas_html[110].etiqueta, "time");

	 strcat(etiquetas_html[111].etiqueta, "title");
	 strcat(etiquetas_html[112].etiqueta, "tr");
	 strcat(etiquetas_html[113].etiqueta, "track");
	 etiquetas_html[113].unico = 1;
	 strcat(etiquetas_html[114].etiqueta, "tt");
	 strcat(etiquetas_html[115].etiqueta, "u");
	 strcat(etiquetas_html[116].etiqueta, "ul");
	 strcat(etiquetas_html[117].etiqueta, "var");
	 strcat(etiquetas_html[118].etiqueta, "video");
	 strcat(etiquetas_html[119].etiqueta, "wbr");
}
//etiquetas_html[1].etiqueta = "a";

//Función que mete elementos a la pila
int push(Pila * A, int elemento){
	A->elementos_pila[A->ultimo_agregado] = elemento;
	A->ultimo_agregado++;
	return 1;
}

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
				if(caracter_auxiliar != '>' && caracter_auxiliar != ' '){
					es_apertura = encontrar_cierre(caracter_auxiliar);
					if(es_apertura == 0){
						contador++;
					}
					if(es_apertura == 0){
						continue;
					}
					cadena_auxiliar[caracteres_almacenados] = caracter_auxiliar;
					caracteres_almacenados++;
				}
				else{
					if(caracteres_almacenados > 0){
						id_etiqueta = encontrar_etiqueta(cadena_auxiliar, caracteres_almacenados);
						//if(id_etiqueta < 0){push(A, 1000);}
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
			else{
				if(caracter_auxiliar == '>' || caracter_auxiliar == '/'){
					cadena_auxiliar[caracteres_almacenados] = caracter_auxiliar;
					caracteres_almacenados++;
					if(caracter_auxiliar == '>'){
						error = guardar(A);
					}
				}
			}
		}
		if(apertura_encontrada == 0){
			apertura_encontrada = encontrar_apertura(caracter_auxiliar);
		}
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
			return i+1;
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
		if(strncmp(cadena_auxiliar, "/>", caracteres_almacenados) == 0){
			return 1;
		}
	}
	else{
		if(caracter_auxiliar == '>' && strncmp(cadena_auxiliar, "/>", caracteres_almacenados)){
			return 1;
		}
	}
	if(unica == 2){
		if(strncmp(cadena_auxiliar, ">", caracteres_almacenados) == 0){
			return 1;
		}
	}
	return -1;
}

int guardar(Pila * A){
	error = validar_cierre_etiqueta();
	if(error != 1){
		return 0;
	}
	if(contador > 0){
		id_etiqueta = id_etiqueta * -1;
	}
	error = push(A, id_etiqueta);
	if(unica == 1 || unica == 2){
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
