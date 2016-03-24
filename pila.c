#include <stdio.h>
#include "pila.h"

//Función que mete elementos a la pila
int push(Pila * A, int elemento){
	A->ultimo_agregado+=1;
	A->elementos_pila[A->ultimo_agregado]=elemento;
}

int pop(Pila * A){
	return A->elementos_pila[A->ultimo_agregado];
}
