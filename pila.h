#ifndef PILA__H__
#define PILA__H__

struct pilas
{
	int elementos_pila[100];
	int ultimo_agregado;
}

typedef struct pilas Pila;
//Función que saca el último elemento de la pila
int pop(Pila *, int);//Devuelve el último elemento que tenga la pila.
//Función que mete un elemento a la pila
int push(Pila *);//Devuelve si funciono o no.

#endif