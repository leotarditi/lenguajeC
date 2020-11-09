#include "pila.h"
#include "my_pila.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int ERROR = -1;
const int EXITO = 0;
const int DOBLE = 2;
const int MITAD = 2;

pila_t* pila_crear(){
	pila_t* pila;
	int tamanio_inicial = 2, cantidad_inicial = 0;

	pila = (pila_t*)malloc(sizeof(pila_t));
	if (pila == NULL) {
		return NULL;
	}
	pila->elementos = calloc(2, sizeof(void*));
	if (pila->elementos == NULL) {
		free(pila);
		return NULL;
	}
	pila->tamanio = tamanio_inicial;
	pila->tope = cantidad_inicial;
	return pila;
}

int pila_apilar(pila_t* pila, void* elemento) {
	if (pila == NULL) {
		return ERROR;
	}
	redimensionar_pila(&pila);
	pila->elementos[pila->tope] = elemento;
	pila->tope ++;
	return EXITO;
}

int pila_desapilar(pila_t* pila) {
	if (pila == NULL) {
		return ERROR;
	}
	if (pila_vacia(pila)) {
		return ERROR;
	}
	redimensionar_pila(&pila);
	pila->tope --;
	return EXITO;
}

int redimensionar_pila(pila_t** pila) {
	void* elemento_auxiliar;
	if((*pila)->tamanio == (*pila)->tope) {
		(*pila)->tamanio *= DOBLE;
		elemento_auxiliar = realloc((*pila)->elementos, sizeof(void*) * (size_t)(*pila)->tamanio);
		if(elemento_auxiliar == NULL) {
			return ERROR;
		}
		(*pila)->elementos = elemento_auxiliar;
	} else if((*pila)->tope < ((*pila)->tamanio/MITAD)) {
		(*pila)->tamanio /= MITAD;
		elemento_auxiliar = realloc((*pila)->elementos, sizeof(void*) * (size_t)(*pila)->tamanio);
		if(elemento_auxiliar == NULL) {
			return ERROR;
		}
		(*pila)->elementos = elemento_auxiliar;
	}
	return EXITO;
}

bool pila_vacia(pila_t* pila) {
	if (pila == NULL) {
		return true;
	}
	if (pila->tope == 0) {
		return true;
	}
	return false;
}

int pila_cantidad(pila_t* pila) {
	int cantidad_pila = 0;
	if (pila == NULL) {
		return cantidad_pila;
	}
	cantidad_pila = pila->tope;
	return cantidad_pila;
}

void* pila_tope(pila_t* pila) {
	void* elemento_tope;

	if (pila == NULL) {
		return NULL;
	}
	if (pila_vacia(pila)) {
		return NULL;
	}
	elemento_tope = pila->elementos[pila->tope-1];
	return elemento_tope;
}

void pila_destruir(pila_t* pila) {
	if (pila == NULL) {
		return;
	}
	free(pila->elementos);
	free(pila);
}

