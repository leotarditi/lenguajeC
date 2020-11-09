#include "lista.h"
#include "cola.h"
#include "ListaConCola.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR -1
#define EXITO 0

/**************************************************************************************************************************************************************
												DEFINICION DE ESTRUCTURAS
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct lista {
	cola_t* cola;
};

struct lista_iterador {
	cola_t* cola;
};

/**************************************************************************************************************************************************************
												FUNCION DE CREAR LISTA
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

lista_t* lista_crear() {
	lista_t* lista;
	lista = calloc(1, sizeof(lista_t));
	if (lista == NULL) {
		return NULL;
	}
	lista->cola = cola_crear();
	return lista;
}

/**************************************************************************************************************************************************************
												FUNCION AUXILIAR DE LISTA
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int insertar_al_final(cola_t* cola, void* elemento) {
	int encolo = cola_encolar(cola, elemento);
	if(encolo == ERROR) {
		return ERROR;
	}
	return EXITO;	
}

int cola_copiar(cola_t* original, cola_t* copia) {
	int encolo = cola_encolar(copia, cola_primero(original));
	if(encolo == ERROR) {
		return ERROR;
	}
	int desencolo = cola_desencolar(original);
	if(desencolo == ERROR) {
		return ERROR;
	}
	return EXITO;
}

/**************************************************************************************************************************************************************
												FUNCIONES DE INSERTAR EN LISTA
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int lista_insertar(lista_t* lista, void* elemento) {
	if(lista == NULL || lista->cola == NULL) {
		return ERROR;
	}

	return insertar_al_final(lista->cola, elemento);
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion) {
	if(lista == NULL || lista->cola == NULL) {
		return ERROR;
	}

	if (posicion >= cola_cantidad(lista->cola)) {
		lista_insertar(lista, elemento);
	} else {
		cola_t* cola_auxiliar = cola_crear();
		for (int i = 0; i < posicion; i++) {
			int copio = cola_copiar(lista->cola, cola_auxiliar);
			if(copio == ERROR) {
				return ERROR;
			}
		}
		int encolo = cola_encolar(cola_auxiliar, elemento);
		if(encolo == ERROR) {
			return ERROR;
		}
		int cantidad = cola_cantidad(lista->cola);
		for (int i = 0; i < cantidad; i++) {
			int copio = cola_copiar(lista->cola, cola_auxiliar);
			if(copio == ERROR) {
				return ERROR;
			}
		}
		cantidad = cola_cantidad(cola_auxiliar);
		for (int i = 0; i < cantidad; i++) {
			int copio = cola_copiar(cola_auxiliar, lista->cola);
			if(copio == ERROR) {
				return ERROR;
			}
		}
		cola_destruir(cola_auxiliar);
	}
	return EXITO;
}

/**************************************************************************************************************************************************************
												FUNCIONES DE BORRAR EN LISTA
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int lista_borrar(lista_t* lista) {
	if(lista_vacia(lista)) {
		return ERROR;
	}

	cola_t* cola_auxiliar = cola_crear();
	int cantidad = cola_cantidad(lista->cola);
	for (int i = 0; i < cantidad-1; i++) {
		int copio = cola_copiar(lista->cola, cola_auxiliar);
		if(copio == ERROR) {
			return ERROR;
		}
	}
	int desencolo = cola_desencolar(lista->cola);
	if(desencolo == ERROR) {
		return ERROR;
	}
	cantidad = cola_cantidad(cola_auxiliar);
	for (int i = 0; i < cantidad; i++) {
		int copio = cola_copiar(cola_auxiliar, lista->cola);
		if(copio == ERROR) {
			return ERROR;
		}
	}
	cola_destruir(cola_auxiliar);
	return EXITO;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion) {
	if(lista_vacia(lista)) {
		return ERROR;
	}
	
	if (posicion >= cola_cantidad(lista->cola)) {
		lista_borrar(lista);
	} else {
		cola_t* cola_auxiliar = cola_crear();
		for (int i = 0; i < posicion; i++) {
			int copio = cola_copiar(lista->cola, cola_auxiliar);
			if(copio == ERROR) {
				return ERROR;
			}
		}
		int desencolo = cola_desencolar(lista->cola);
		if(desencolo == ERROR) {
			return ERROR;
		}
		int cantidad = cola_cantidad(lista->cola);
		for (int i = 0; i < cantidad; i++) {
			int copio = cola_copiar(lista->cola, cola_auxiliar);
			if(copio == ERROR) {
				return ERROR;
			}
		}
		cantidad = cola_cantidad(cola_auxiliar);
		for (int i = 0; i < cantidad; i++) {
			int copio = cola_copiar(cola_auxiliar, lista->cola);
			if(copio == ERROR) {
				return ERROR;
			}
		}
		cola_destruir(cola_auxiliar);
	}
	return EXITO;
}

/**************************************************************************************************************************************************************
											FUNCIONES DE OBTENER ELEMENTOS DE LA LISTA
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion) {
	if(lista_vacia(lista)) {
		return NULL;
	}
	
	void* elemento;
	if (posicion >= cola_cantidad(lista->cola)) {
		return NULL;
	} else {
		cola_t* cola_auxiliar = cola_crear();
		for (int i = 0; i < posicion; i++) {
			int copio = cola_copiar(lista->cola, cola_auxiliar);
			if(copio == ERROR) {
				return NULL;
			}
		}
		elemento = cola_primero(lista->cola);
		int cantidad = cola_cantidad(lista->cola);
		for (int i = 0; i < cantidad; i++) {
			int copio = cola_copiar(lista->cola, cola_auxiliar);
			if(copio == ERROR) {
				return NULL;
			}
		}
		cantidad = cola_cantidad(cola_auxiliar);
		for (int i = 0; i < cantidad; i++) {
			int copio = cola_copiar(cola_auxiliar, lista->cola);
			if(copio == ERROR) {
				return NULL;
			}
		}
		cola_destruir(cola_auxiliar);
	}
	return elemento;
}

void* lista_ultimo(lista_t* lista) {
	if(lista_vacia(lista)) {
		return NULL;
	}

	size_t cantidad = (size_t)cola_cantidad(lista->cola);
	void* ultimo_elemento = lista_elemento_en_posicion(lista, cantidad-1);
	return ultimo_elemento;
}

/**************************************************************************************************************************************************************
											FUNCIONES DE CANTIDAD DE ELEMENTOS DE LA LISTA
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool lista_vacia(lista_t* lista) {
	if(lista == NULL) {
		return true;
	}
	if(cola_vacia(lista->cola)) {
		return true;
	}
	return false;
}

size_t lista_elementos(lista_t* lista) {
	if(lista_vacia(lista)) {
		return 0;
	}
	return (size_t)cola_cantidad(lista->cola);
}

/**************************************************************************************************************************************************************
												FUNCION DE DESTRUIR LA LISTA
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void lista_destruir(lista_t* lista) {
	if(lista == NULL) {
		return;
	}
	
	cola_destruir(lista->cola);
	free(lista);
}

/**************************************************************************************************************************************************************
												FUNCION AUXILIAR DE ITERADOR
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int copiar_en_dos_colas(cola_t* original, cola_t* copia1, cola_t* copia2) {
	int encolo = cola_encolar(copia1, cola_primero(original));
	if(encolo == ERROR) {
		return ERROR;
	}
	encolo = cola_encolar(copia2, cola_primero(original));
	if(encolo == ERROR) {
		return ERROR;
	}
	int desencolo = cola_desencolar(original);
	if(desencolo == ERROR) {
		return ERROR;
	}
	return EXITO;
}

/**************************************************************************************************************************************************************
												FUNCIONES DE ITERADOR EXTERNO
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

lista_iterador_t* lista_iterador_crear(lista_t* lista) {
	lista_iterador_t* iterador;
	if(lista == NULL) {
		return NULL;
	}
	iterador = calloc(1, sizeof(lista_iterador_t));
	if(iterador == NULL) {
		return NULL;
	}
	iterador->cola = cola_crear();
	cola_t* cola_auxiliar = cola_crear();
	int cantidad = cola_cantidad(lista->cola);
	for (int i = 0; i < cantidad; i++) {
		int copio = cola_copiar(lista->cola, cola_auxiliar);
		if(copio == ERROR) {
			return NULL;
		}
	}
	cantidad = cola_cantidad(cola_auxiliar);
	for (int i = 0; i < cantidad; i++) {
		int copio = copiar_en_dos_colas(cola_auxiliar, lista->cola, iterador->cola);
		if(copio == ERROR) {
			return NULL;
		}
	}
	cola_destruir(cola_auxiliar);
	return iterador; 
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador) {
	if(iterador == NULL || iterador->cola == NULL) {
		return false;
	}
	if(cola_vacia(iterador->cola)) {
		return false;
	}
	return true;
}

void* lista_iterador_siguiente(lista_iterador_t* iterador) {
	if(lista_iterador_tiene_siguiente(iterador)) {
		void* elemento_actual = cola_primero(iterador->cola);
		int desencolo = cola_desencolar(iterador->cola);
		if(desencolo == ERROR) {
			return NULL;
		}
		return elemento_actual;
	}
	return NULL;
}

void lista_iterador_destruir(lista_iterador_t* iterador) {
	if(iterador == NULL) {
		return;
	}
	cola_destruir(iterador->cola);
	free(iterador);
}

/**************************************************************************************************************************************************************
												FUNCION DE ITERADOR INTERNO
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*)) {
	lista_iterador_t* iterador = lista_iterador_crear(lista);
	void* elemento;
	while(lista_iterador_tiene_siguiente(iterador)) {
  		elemento = lista_iterador_siguiente(iterador);
  		funcion(elemento);
  	}
	lista_iterador_destruir(iterador);
}