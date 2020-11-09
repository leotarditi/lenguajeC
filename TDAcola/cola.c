#include "cola.h"
#include <stdlib.h>
#include <stdio.h>

const int ERROR = -1;
const int EXITO = 0;

cola_t* cola_crear() {
	cola_t* cola;
	cola = calloc(1, sizeof(cola_t));
	if (cola == NULL) {
		return NULL;
	}
	return cola;
}

int cola_encolar(cola_t* cola, void* elemento) {
	nodo_t* nodo_nuevo;

	if(cola == NULL) {
		return ERROR;
	}
	nodo_nuevo = calloc(1, sizeof(nodo_t));
	if(nodo_nuevo == NULL) {
		return ERROR;
	}
	nodo_nuevo->elemento = elemento;
	if(cola_vacia(cola)) {
		cola->nodo_inicio = nodo_nuevo;
		cola->nodo_fin = nodo_nuevo;
		cola->cantidad ++;
	} else {
		cola->nodo_fin->siguiente = nodo_nuevo;
		cola->nodo_fin = nodo_nuevo;
		cola->cantidad ++;
	}
	return EXITO;
}

int cola_desencolar(cola_t* cola){
	nodo_t* nodo_auxiliar;

	if(cola == NULL) {
		return ERROR;
	}
	if(cola_vacia(cola)) {
		return ERROR;
	}
	nodo_auxiliar = cola->nodo_inicio;
	if(cola->nodo_inicio == cola->nodo_fin) {
		cola->nodo_inicio = NULL;
		cola->nodo_fin = NULL;
	} else {
		cola->nodo_inicio = cola->nodo_inicio->siguiente;	
	}
	free(nodo_auxiliar);
	cola->cantidad --;
	return EXITO;
}

bool cola_vacia(cola_t* cola) {
	if(cola == NULL) {
		return true;
	}
	if(cola->cantidad == 0) {
		return true;
	}
	return false;
}

int cola_cantidad(cola_t* cola) {
	if(cola == NULL) {
		return 0;
	}
	return cola->cantidad;
}

void* cola_primero(cola_t* cola) {
	if(cola == NULL || cola->nodo_inicio == NULL) {
		return NULL;
	}
	return cola->nodo_inicio->elemento;
}

void cola_destruir(cola_t* cola) {
	if(cola == NULL) {
		return;
	}
	
	nodo_t* nodo_a_liberar;
	nodo_t* nodo_liberado;
	nodo_a_liberar = cola->nodo_inicio;
	while (nodo_a_liberar != NULL) {
		nodo_liberado = nodo_a_liberar;
		nodo_a_liberar = nodo_liberado->siguiente;
		free(nodo_liberado);
	}
	free(cola);
}