#include "abb.h"
#include "my_abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ABB_RECORRER_INORDEN   0
#define ABB_RECORRER_PREORDEN  1
#define ABB_RECORRER_POSTORDEN 2

const int ERROR = -1;
const int EXITO = 0;


abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor) {
	abb_t* arbol;
	arbol = calloc(1, sizeof(abb_t));
	if(arbol == NULL) {
		return NULL;
	}
	arbol->comparador = comparador;
	arbol->destructor = destructor;
	return arbol;
}

int arbol_insertar(abb_t* arbol, void* elemento) {
	if(arbol == NULL) {
		return ERROR;
	}
	nodo_abb_t* nuevo = calloc(1, sizeof(nodo_abb_t));
	if(nuevo == NULL) {
		return ERROR;
	}
	nuevo->elemento = elemento;
	if(arbol->nodo_raiz == NULL) {
		arbol->nodo_raiz = nuevo;
	} else {
		insertar_nodo(arbol, arbol->nodo_raiz, nuevo);
	}
	return EXITO;
}


int arbol_borrar(abb_t* arbol, void* elemento) {
	if(arbol == NULL) {
		return ERROR;
	}
	nodo_abb_t* nodo = buscar_nodo(arbol, arbol->nodo_raiz, elemento);
	if(nodo == NULL) {
		return ERROR;
	}
	return borrar_nodo(arbol, nodo);
}


void* arbol_buscar(abb_t* arbol, void* elemento) {
	if(arbol_vacio(arbol)) {
		return NULL;
	}
	nodo_abb_t* nodo = buscar_nodo(arbol, arbol->nodo_raiz, elemento); // explicar esto en el readme
	if(nodo == NULL) {
		return NULL;
	}
	return nodo->elemento;
}


void* arbol_raiz(abb_t* arbol) {
	if(arbol_vacio(arbol)){
		return NULL;
	}
	return arbol->nodo_raiz->elemento;
}

bool arbol_vacio(abb_t* arbol) {
	if(arbol == NULL) {
		return true;
	}
	if(arbol->nodo_raiz == NULL) {
		return true;
	}
	return false;
}

int arbol_recorrido_inorden(abb_t* arbol, void** array, int tamanio_array) {
	int tamanio_usado = 0;

	if(arbol == NULL) {
		return 0;
	}
	recorrido_inorden(arbol->nodo_raiz, array, tamanio_array, &tamanio_usado);
	return tamanio_usado;
}


int arbol_recorrido_preorden(abb_t* arbol, void** array, int tamanio_array) {
	int tamanio_usado = 0;

	if(arbol == NULL) {
		return 0;
	}
	recorrido_preorden(arbol->nodo_raiz, array, tamanio_array, &tamanio_usado);
	return tamanio_usado;
}


int arbol_recorrido_postorden(abb_t* arbol, void** array, int tamanio_array) {
	int tamanio_usado = 0;

	if(arbol == NULL) {
		return 0;
	}
	recorrido_postorden(arbol->nodo_raiz, array, tamanio_array, &tamanio_usado);
	return tamanio_usado;
}

void arbol_destruir(abb_t* arbol) {
	if(arbol == NULL) {
		return;
	}
	destruir(arbol, arbol->nodo_raiz);
	free(arbol);
	arbol = NULL;
}

void abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra) {
	if (arbol == NULL) {
		return;
	}
	if (funcion == NULL) {
		return;
	}

	nodo_abb_t* nodo = arbol->nodo_raiz;
	bool no_sigo = false;

	if(recorrido == ABB_RECORRER_INORDEN) {
		recorrido_interno_inorden(nodo, funcion, extra, &no_sigo);
	}

	if(recorrido == ABB_RECORRER_PREORDEN) {
		recorrido_interno_preorden(nodo, funcion, extra, &no_sigo);
	}

	if(recorrido == ABB_RECORRER_POSTORDEN) {
		recorrido_interno_postorden(nodo, funcion, extra, &no_sigo);
	}
}

/**************************************************************************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
***************************************************************************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
**************************************************************************************************************************************************************/


void insertar_nodo(abb_t* arbol, nodo_abb_t* raiz, nodo_abb_t* nuevo) {
	if(arbol->comparador(raiz->elemento, nuevo->elemento) >= 0) {
		if(raiz->izquierda == NULL) {
			raiz->izquierda = nuevo;
		} else {
			insertar_nodo(arbol, raiz->izquierda, nuevo);
		}
	} else {
		if(raiz->derecha == NULL) {
			raiz->derecha = nuevo;
		} else {
			insertar_nodo(arbol, raiz->derecha, nuevo);
		}
	}
}

int borrar_nodo(abb_t* arbol, nodo_abb_t* nodo) {
	if(nodo == NULL) {
		return ERROR;
	}
	nodo_abb_t* padre;
	nodo_abb_t* mayor;
	if(nodo->izquierda == NULL && nodo->derecha == NULL) {
		padre = obtener_padre(arbol->nodo_raiz, nodo);
		if(padre != NULL) {
        	if(padre->derecha == nodo) {
        		padre->derecha = NULL;
        	} else {
        		padre->izquierda = NULL;
        	}
        }
        if(arbol->comparador(arbol_raiz(arbol),nodo->elemento) == 0 && nodo->elemento != NULL) {
			arbol->nodo_raiz = NULL;
		}
        if(arbol->destructor != NULL) arbol->destructor(nodo->elemento);
        free(nodo);
	} else if(nodo->izquierda == NULL && nodo->derecha != NULL) {
		padre = obtener_padre(arbol->nodo_raiz, nodo);
		if(padre != NULL) {
			if(padre->derecha == nodo) {
				padre->derecha = nodo->derecha;
			} else {
				padre->izquierda = nodo->derecha;
			}
		}
		if(arbol->comparador(arbol_raiz(arbol),nodo->elemento) == 0 && nodo->elemento != NULL) {
			arbol->nodo_raiz = nodo->derecha;
		}
		if(arbol->destructor != NULL) arbol->destructor(nodo->elemento);
		if(arbol_raiz(arbol) == nodo) {
			arbol->nodo_raiz = nodo->derecha;
		}
		free(nodo);
	} else if(nodo->izquierda != NULL && nodo->derecha == NULL) {
		padre = obtener_padre(arbol->nodo_raiz, nodo);
		if(padre != NULL) {
			if(padre->derecha == nodo) {
				padre->derecha = nodo->izquierda;
			} else {
				padre->izquierda = nodo->izquierda;
			}
		}
		if(arbol->comparador(arbol_raiz(arbol),nodo->elemento) == 0 && nodo->elemento != NULL) {
			arbol->nodo_raiz = nodo->izquierda;
		}
		if(arbol->destructor != NULL) arbol->destructor(nodo->elemento);
		free(nodo);
	} else {
		mayor = obtener_mayor(nodo->izquierda);
		if(arbol->destructor != NULL) arbol->destructor(nodo->elemento);
		nodo->elemento = mayor->elemento;
		mayor->elemento = NULL;
		borrar_nodo(arbol, mayor);
	}
	return EXITO;
}

nodo_abb_t* obtener_padre(nodo_abb_t* raiz, nodo_abb_t* nodo) {
	if(raiz == NULL) {
		return NULL;
	}
	if(raiz->izquierda == nodo || raiz->derecha == nodo) {
		return raiz;
	} 
	nodo_abb_t* a = obtener_padre(raiz->izquierda, nodo);
    nodo_abb_t* b = obtener_padre(raiz->derecha, nodo);
    if(a != NULL) return a;
    if(b != NULL) return b;
    return NULL;
}

nodo_abb_t* obtener_mayor(nodo_abb_t* nodo) {
	if(nodo->derecha == NULL) {
		return nodo;
	}
	return obtener_mayor(nodo->derecha);
}

nodo_abb_t* buscar_nodo(abb_t* arbol, nodo_abb_t* raiz, void* elemento) {
	if (raiz == NULL) {
		return NULL;
	} 
	if(arbol->comparador(raiz->elemento, elemento) == 0) {
		return raiz;
	} else if(arbol->comparador(elemento, raiz->elemento) < 0) {
		return buscar_nodo(arbol, raiz->izquierda, elemento);
	} else {
		return buscar_nodo(arbol, raiz->derecha, elemento);	
	}
	return NULL;
}

void recorrido_inorden(nodo_abb_t* nodo, void** array, int tamanio_array, int* tamanio_usado) {
	if((*tamanio_usado) == tamanio_array) {
		return;
	}
	
	if(nodo->izquierda) recorrido_inorden(nodo->izquierda, array, tamanio_array, tamanio_usado);
	if((*tamanio_usado) == tamanio_array) return;
	array[(*tamanio_usado)] = nodo->elemento;
	(*tamanio_usado)++;
	if((*tamanio_usado) == tamanio_array) return;
	if(nodo->derecha) recorrido_inorden(nodo->derecha, array, tamanio_array, tamanio_usado);
}

void recorrido_preorden(nodo_abb_t* nodo, void** array, int tamanio_array, int* tamanio_usado) {
	if((*tamanio_usado) == tamanio_array) {
		return;
	}
	
	array[(*tamanio_usado)] = nodo->elemento;
	(*tamanio_usado)++;
	if(nodo->izquierda) recorrido_preorden(nodo->izquierda, array, tamanio_array, tamanio_usado);
	if((*tamanio_usado) == tamanio_array) return;
	if(nodo->derecha) recorrido_preorden(nodo->derecha, array, tamanio_array, tamanio_usado);
	if((*tamanio_usado) == tamanio_array) return;
}

void recorrido_postorden(nodo_abb_t* nodo, void** array, int tamanio_array, int* tamanio_usado) {
	if((*tamanio_usado) == tamanio_array) {
		return;
	}
	
	if(nodo->izquierda) recorrido_postorden(nodo->izquierda, array, tamanio_array, tamanio_usado);
	if((*tamanio_usado) == tamanio_array) return;
	if(nodo->derecha) recorrido_postorden(nodo->derecha, array, tamanio_array, tamanio_usado);
	if((*tamanio_usado) == tamanio_array) return;
	array[(*tamanio_usado)] = nodo->elemento;
	(*tamanio_usado)++;
}

void destruir(abb_t* arbol, nodo_abb_t* raiz) {
	if(raiz != NULL) {
		destruir(arbol, raiz->izquierda);
		destruir(arbol, raiz->derecha);
		if(arbol->destructor != NULL){
			arbol->destructor(raiz->elemento);
		}
		free(raiz);
	}
}

void recorrido_interno_inorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra, bool* no_sigo){
	if(nodo->izquierda) recorrido_interno_inorden(nodo->izquierda, funcion, extra, no_sigo);
	if(*no_sigo) return;
	(*no_sigo) = funcion(nodo->elemento, extra);
	if(*no_sigo) return;
	if(nodo->derecha) recorrido_interno_inorden(nodo->derecha, funcion, extra, no_sigo);
	if(*no_sigo) return;
}

void recorrido_interno_preorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra, bool* no_sigo){
	(*no_sigo) = funcion(nodo->elemento, extra);
	if(*no_sigo) return;
	if(nodo->izquierda) recorrido_interno_preorden(nodo->izquierda, funcion, extra, no_sigo);
	if(*no_sigo) return;
	if(nodo->derecha) recorrido_interno_preorden(nodo->derecha, funcion, extra, no_sigo);
	if(*no_sigo) return;
}

void recorrido_interno_postorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra, bool* no_sigo){
	if(nodo->izquierda) recorrido_interno_postorden(nodo->izquierda, funcion, extra, no_sigo);
	if(*no_sigo) return;
	if(nodo->derecha) recorrido_interno_postorden(nodo->derecha, funcion, extra, no_sigo);
	if(*no_sigo) return;
	(*no_sigo) = funcion(nodo->elemento, extra);
	if(*no_sigo) return;
}