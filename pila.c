#include <stdio.h>
#include "pila.h"

//Función que mete elementos a la pila
int push(Pila * A, int elemento){
	//Si es la primera vez que se le va a agregar deberia de llegar como NULL la variable
	if(A->ultimo_agregado==NULL){
		A->ultimo_agregado=0;
		A->elementos_pila[A->ultimo_agregado]=elemento;
	}else{
		A->ultimo_agregado+=1;
		A->elementos_pila[A->ultimo_agregado]=elemento;
	}
	return 1;
}

int pop(Pila * A){
	return A->elementos_pila[A->ultimo_agregado];
}
