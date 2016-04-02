#include <stdio.h>
#include "pila.h"

// funcion que mete elementos a la pila
int
push(Pila * A, int elemento)
{
	if (A == NULL) {
		return -1;
	}
	A->elementos_pila[A->ultimo_agregado] = elemento;
	A->ultimo_agregado++;
	return 1;
}

//funcion que saca elementos de la pila y retorna el elemento
int
pop(Pila * A)
{
	if (A == NULL) {
		return -1;
	}
	A->ultimo_agregado--;
	return A->elementos_pila[A->ultimo_agregado];
}
