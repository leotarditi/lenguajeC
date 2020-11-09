#include "abb.h"
#include "my_abb.h"
#include "mis_pruebas.h"
#include <stdio.h>

const int DATO_INT = 1;
const int DATO_CHAR = 2;
const int DATO_STRING = 3;

void prueba_insertar(abb_t* arbol, void* elemento, int inserto, int* contador) {
	if(arbol_insertar(arbol, elemento) == inserto) {
		printf("APROBADO\n");
		(*contador) ++;
	} else {
		printf("DESAPROBADO\n");
	}
}

void prueba_borrar(abb_t* arbol, void* elemento, int borro, int* contador) {
	if(arbol_borrar(arbol, elemento) == borro) {
		printf("APROBADO\n");
		(*contador) ++;
	} else {
		printf("DESAPROBADO\n");
	}
}

void prueba_buscar(abb_t* arbol, void* elemento, int encontro, int* contador) {
	if (encontro == -1 && arbol_buscar(arbol, elemento) == NULL) {
		printf("APROBADO\n");
		(*contador) ++;
	} else if(arbol->comparador(arbol_buscar(arbol, elemento), elemento) == 0) {
		printf("APROBADO\n");
		(*contador) ++;
	} else {
		printf("DESAPROBADO\n");
	}
}

void prueba_raiz(abb_t* arbol, void* elemento_raiz, int* contador) {
	if(elemento_raiz == NULL && arbol_raiz(arbol) == elemento_raiz) {
		printf("APROBADO\n");
		(*contador) ++;
	} else if(arbol->comparador(arbol_raiz(arbol), elemento_raiz) == 0) {
		printf("APROBADO\n");
		(*contador) ++; 
	} else {
		printf("DESAPROBADO\n");
	}
}

void prueba_estado(abb_t* arbol, int estado, int* contador) {
	if(arbol_vacio(arbol) == estado) {
		printf("APROBADO\n");
		(*contador) ++;
	} else {
		printf("DESAPROBADO\n");
	}
}

void imprimir_recorridos(abb_t* arbol, void** array, int tamanio_array, int (*funcion_recorrido)(abb_t*,void**,int), int tipo_dato) {
	
	int cantidad = funcion_recorrido(arbol, array, tamanio_array);
	if(tipo_dato == DATO_INT) {
		for (int i = 0; i < cantidad; i++) {
			printf(" %i ", *(int*)array[i]);
		}
	}
	if(tipo_dato == DATO_CHAR) {
		for (int i = 0; i < cantidad; i++) {
			printf(" %c ", *(char*)array[i]);
		}
	}
	if(tipo_dato == DATO_STRING) {
		for (int i = 0; i < cantidad; i++) {
			printf(" %c ", *(char*)array);
		}
	}
	printf("\n");
}