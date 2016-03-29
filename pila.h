#ifndef __PILA_H__
#define __PILA_H__

struct etiquetas {
	char		etiqueta  [15];
	int		unico;
};

typedef struct etiquetas Etiqueta;

struct pilas {
	int		elementos_pila[200];
	int		ultimo_agregado;
};

typedef struct pilas Pila;
//Funci ï ¿½ï¿½n que saca el ï ¿½ï¿½ltimo elemento de la pila
int		pop        (Pila *);
//Devuelve el ï ¿½ï¿½ltimo elemento que tenga la pila.
// Funci ï ¿½ï¿½n que mete un elemento a la pila
int		push       (Pila *, int);
//Devuelve 1 si funciono 0 si no

int		almacenar_documento_html(FILE *, Pila *);

int		encontrar_apertura(char);

int		encontrar_etiqueta(char *, int);

int		encontrar_cierre(char);

int		guardar    (Pila *);

int		es_unica   ();

int		validar_documento_html(Pila *);

void		cerrar_etiqueta(Pila *);

void		evaluar_comentario();

void		evaluar_comillas();

void		evaluar_etiqueta(Pila *);

#endif
