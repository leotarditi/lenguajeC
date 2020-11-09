#include "hash.h"
#include "hash_iterador.h"
#include "lista_modificada.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct hash{
	lista_t** tabla;
    size_t usado;
    size_t tamanio;
    hash_destruir_dato_t destructor;
};

typedef struct hash_campo {
    char* clave;
    void* elemento;
} hash_campo_t;

struct hash_iter {
	hash_t* hash;
	lista_iterador_t* lista_iterador;
	size_t posicion;
};

bool encontrar_pos_no_vacia(hash_t* hash, size_t* posicion_iterador ,lista_iterador_t** iterador_de_lista){
	for(size_t i = *posicion_iterador; i < hash->tamanio; i++) {
		if(!lista_vacia(hash->tabla[i])){
			*posicion_iterador = i;
			*iterador_de_lista = lista_iterador_crear(hash->tabla[i]);
			return true;
		}
	}
	*iterador_de_lista = NULL;
	return false;
}

hash_iterador_t* hash_iterador_crear(hash_t* hash) {
	if(hash == NULL) {
		return NULL;
	}
	hash_iterador_t* hash_iterador = calloc(1, sizeof(hash_iterador_t));
	if(hash_iterador == NULL) {
		return NULL;
	}
	hash_iterador->hash = hash;
	hash_iterador->posicion = 0;
	encontrar_pos_no_vacia(hash, &hash_iterador->posicion, &hash_iterador->lista_iterador);
	return hash_iterador;
}


void* hash_iterador_siguiente(hash_iterador_t* iterador) {
	if (iterador == NULL) {
		return NULL;
	}
	if(!hash_iterador_tiene_siguiente(iterador)) {
		return NULL;
	}
	hash_campo_t* campo = lista_iterador_ver_actual(iterador->lista_iterador);
	if(lista_iterador_tiene_siguiente(iterador->lista_iterador)) {
		lista_iterador_siguiente(iterador->lista_iterador);
		return (void*)campo->clave;
	}
	lista_iterador_destruir(iterador->lista_iterador);
	iterador->posicion ++;
	if(!encontrar_pos_no_vacia(iterador->hash, &iterador->posicion, &iterador->lista_iterador)) {
		return NULL;
	}
	return hash_iterador_siguiente(iterador);
}

bool hash_iterador_tiene_siguiente(hash_iterador_t* iterador) {
	if(iterador == NULL || iterador->lista_iterador == NULL) {
		return false;
	}
	if(lista_vacia(iterador->hash->tabla[iterador->posicion])) {
		return false;
	}
	return true;
}

void hash_iterador_destruir(hash_iterador_t* iterador) {
	if(iterador == NULL) {
		return;
	}
	if (iterador->lista_iterador) {
		lista_iterador_destruir(iterador->lista_iterador);
	}
	free(iterador);
}