#ifndef PILA__H__
#define PILA__H__

struct pilas
{
	int elementos_pila[100];
	int ultimo_agregado;
}

typedef struct pilas Pila;

int pop(Pila *, int);//Devuelve si funciono o no.
int push(Pila *);//Devuelve el último elemento que tenga la pila.

#endif