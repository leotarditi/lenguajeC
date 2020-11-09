#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int ERROR = -1;
const int EXITO = 0;
const int NODO_INICIAL = 0;

typedef struct nodo {
	void* elemento;
	struct nodo* siguiente;
} nodo_t;

struct lista {
	nodo_t* nodo_inicio;
	nodo_t* nodo_fin; 
	size_t cantidad;
};

struct lista_iterador {
	nodo_t* previo;
	nodo_t* ultimo_retornado;
};


lista_t* lista_crear() {
	lista_t* lista;
	lista = calloc(1, sizeof(lista_t));
	if (lista == NULL) {
		return NULL;
	}
	return lista;
}

int lista_insertar(lista_t* lista, void* elemento) {
	nodo_t* nodo_nuevo;

	if(lista == NULL) {
		return ERROR;
	}
	nodo_nuevo = calloc(1, sizeof(nodo_t));
	if(nodo_nuevo == NULL) {
		return ERROR;
	}
	nodo_nuevo->elemento = elemento;
	if(lista_vacia(lista)) {
		lista->nodo_inicio = nodo_nuevo;
		lista->nodo_fin = nodo_nuevo;
	} else {
		lista->nodo_fin->siguiente = nodo_nuevo;
		lista->nodo_fin = nodo_nuevo;
	}
	lista->cantidad ++;
	return EXITO;
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion) {
	nodo_t* nodo_a_insertar;
	nodo_t* nodo_anterior;
	
	if(lista == NULL) {
		return ERROR;
	}

	nodo_anterior = lista->nodo_inicio;
	if (posicion+1 >= lista->cantidad) {
		lista_insertar(lista, elemento);
	} else {
		nodo_a_insertar = calloc(1, sizeof(nodo_t));
		if(nodo_a_insertar == NULL) {
			return ERROR;
		}
		nodo_a_insertar->elemento = elemento;
		if(posicion == NODO_INICIAL) { 
			nodo_a_insertar->siguiente = lista->nodo_inicio;
			lista->nodo_inicio = nodo_a_insertar;
		} else {
			for (int i = 1; i < posicion; i++) {
				nodo_anterior = nodo_anterior->siguiente;
			}
			nodo_a_insertar->siguiente = nodo_anterior->siguiente;
			nodo_anterior->siguiente = nodo_a_insertar;
		}
		lista->cantidad ++;	
	}
	return EXITO;
}

int lista_borrar(lista_t* lista) {
	nodo_t* nodo_auxiliar;
	nodo_t* nodo_a_borrar;

	if(lista == NULL) {
		return ERROR;
	}
	if(lista_vacia(lista)) {
		return ERROR;
	}
	nodo_auxiliar = lista->nodo_inicio;
	if(lista->nodo_inicio == lista->nodo_fin) {
		free(nodo_auxiliar);
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
	} else {
		for (int i = 2; i < lista->cantidad; i++) {
			nodo_auxiliar = nodo_auxiliar->siguiente;
		}
		nodo_a_borrar = nodo_auxiliar->siguiente;
		nodo_auxiliar->siguiente = NULL;
		lista->nodo_fin = nodo_auxiliar;
		free(nodo_a_borrar);
	}
	lista->cantidad --;
	return EXITO;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion) {
	nodo_t* nodo_auxiliar;
	nodo_t* nodo_a_borrar;

	if(lista == NULL) {
		return ERROR;
	}
	if(lista_vacia(lista)) {
		return ERROR;
	}
	nodo_auxiliar = lista->nodo_inicio;
	if (posicion >= lista->cantidad) {
		lista_borrar(lista);
	} else if (posicion == NODO_INICIAL){
		lista->nodo_inicio = nodo_auxiliar->siguiente;
		free(nodo_auxiliar);
		lista->cantidad --;
	} else {
		for (int i = 1; i < posicion; i++) {
			nodo_auxiliar = nodo_auxiliar->siguiente;
		}
		nodo_a_borrar = nodo_auxiliar->siguiente;
		nodo_auxiliar->siguiente = nodo_a_borrar->siguiente;
		free(nodo_a_borrar);
		lista->cantidad --;
	}
	return EXITO;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion) {
	nodo_t* nodo_auxiliar;
	void* elemento;

	if(lista == NULL) {
		return NULL;
	}
	nodo_auxiliar = lista->nodo_inicio;
	if (posicion >= lista->cantidad) {
		return NULL;
	} else {
		for (int i = 0; i < posicion; i++) {
			nodo_auxiliar = nodo_auxiliar->siguiente;
		}
		elemento = nodo_auxiliar->elemento;
	}
	return elemento;
}

void* lista_ultimo(lista_t* lista) {
	if(lista == NULL) {
		return NULL;
	}
	if(lista_vacia(lista)) {
		return NULL;
	}
	return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t* lista) {
	if(lista == NULL) {
		return true;
	}
	if(lista->cantidad == 0) {
		return true;
	}
	return false;
}

size_t lista_elementos(lista_t* lista) {
	if(lista == NULL) {
		return 0;
	}
	return lista->cantidad;
}

void lista_destruir(lista_t* lista) {
	if(lista == NULL) {
		return;
	}
	
	nodo_t* nodo_a_liberar;
	nodo_t* nodo_liberado;
	nodo_a_liberar = lista->nodo_inicio;
	while (nodo_a_liberar != NULL) {
		nodo_liberado = nodo_a_liberar;
		nodo_a_liberar = nodo_liberado->siguiente;
		free(nodo_liberado);
	}
	free(lista);
}

lista_iterador_t* lista_iterador_crear(lista_t* lista) {
	lista_iterador_t* iterador;
	if(lista == NULL) {
		return NULL;
	}
	iterador = calloc(1, sizeof(lista_iterador_t));
	if(iterador == NULL) {
		return NULL;
	}
	iterador->previo = lista->nodo_inicio;
	return iterador; 
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador) {
	if(iterador == NULL) {
		return false;
	}
	if(iterador->previo == NULL) {
		return false;
	}
	return true;
}

void* lista_iterador_siguiente(lista_iterador_t* iterador) {
	if(iterador == NULL) {
		return NULL;
	}
	if(lista_iterador_tiene_siguiente(iterador)) {
		iterador->ultimo_retornado = iterador->previo;
		iterador->previo = iterador->previo->siguiente;
	}
	return iterador->ultimo_retornado->elemento;
}

void lista_iterador_destruir(lista_iterador_t* iterador) {
	if(iterador == NULL) {
		return;
	}
	free(iterador);
}

void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*)) {
	lista_iterador_t* iterador = lista_iterador_crear(lista);
	void* elemento;
	while(lista_iterador_tiene_siguiente(iterador)) {
  		elemento = lista_iterador_siguiente(iterador);
  		funcion(elemento);
  	}
	
	lista_iterador_destruir(iterador);
}