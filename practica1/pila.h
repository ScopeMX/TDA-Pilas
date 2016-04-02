#ifndef __PILA_H__
#define __PILA_H__

struct pilas {
	int		elementos_pila[400];
	int		ultimo_agregado;
};

typedef struct pilas Pila;

int		pop        (Pila *);

int		push       (Pila *, int);

#endif
