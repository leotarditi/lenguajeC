#include "hash.h"
#include "lista_modificada.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#define CANTIDAD_POR_DEFECTO 10
#define ERROR -1
#define EXITO 0

const float COTA_MINIMA = 0.25;
const float COTA_MAXIMA = 0.75;
const size_t AUMENTO_REDIMENSION = 2;
const size_t VACIA = 0;

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

size_t funcion_hashing(const char* clave, size_t capacidad) {
	size_t clave_modificada = (size_t)*clave;
	size_t clave_hash = clave_modificada % capacidad;
	return clave_hash;
}

/* ******************************************************************
 *           PRIMITIVAS DEL AUXILIAR HASH CAMPO
 * *****************************************************************/
hash_campo_t* hash_campo_crear(char* clave, void* elemento) {
	hash_campo_t* nuevo_hash_campo = calloc(1, sizeof(hash_campo_t));
	if (nuevo_hash_campo == NULL) {
		return NULL;
	}
	nuevo_hash_campo->clave = clave;
	nuevo_hash_campo->elemento = elemento;
	return nuevo_hash_campo;
}

int agregar_campo(lista_iterador_t* iterador_lista, const char* clave, void* elemento) {
	char* copia_clave = calloc(strlen(clave)+1, sizeof(char));
	strcpy(copia_clave, clave);
	hash_campo_t* nuevo_campo = hash_campo_crear(copia_clave, elemento);
	if (nuevo_campo == NULL) {
		return ERROR;
	}
	int insertado_ok = lista_iterador_insertar(iterador_lista, nuevo_campo); 
	return insertado_ok; 
}

lista_iterador_t* buscar_campo(lista_t* lista, const char* clave) {
	lista_iterador_t* iterador = lista_iterador_crear(lista);
	while (lista_iterador_tiene_siguiente(iterador)) {
		hash_campo_t* campo = lista_iterador_ver_actual(iterador);
		if (strcmp(campo->clave, clave) == 0) {
			break;
		}
		lista_iterador_siguiente(iterador);
	}
	return iterador;
}


void hash_campo_borrar(hash_campo_t* campo, hash_destruir_dato_t destruir_dato){
	if(destruir_dato) {
		destruir_dato(campo->elemento);
	}
	free(campo->clave);
	free(campo);
}

/* ******************************************************************
 *               AUXILIARES DE PRIMITIVAS DEL HASH
 * *****************************************************************/
float factor_de_carga(hash_t* hash){
	if(hash == NULL) {
		return -1;
	}
	return ((float)hash->usado/(float)hash->tamanio);
}

lista_t** crear_tabla(hash_t* hash, size_t capacidad_nueva) {
	if(hash == NULL) {
		return NULL;
	}
	lista_t** nueva_tabla = calloc(capacidad_nueva, sizeof(lista_t*));
	if(nueva_tabla == NULL) {
		return NULL;	
	} 

	for(size_t i = 0; i < capacidad_nueva; i++){
		nueva_tabla[i] = lista_crear();
		if(nueva_tabla[i] == NULL) {
			return NULL;
		}
	}
	return nueva_tabla;
}

void destruir_tabla(hash_t* hash){
	if(hash == NULL) {
		return;
	}
	for(size_t i = 0; i < hash->tamanio; i++) {
		lista_t* lista_a_destruir = hash->tabla[i];
		if(!lista_a_destruir) {
			continue;
		}
		lista_iterador_t* iterador = lista_iterador_crear(lista_a_destruir);
		while(lista_iterador_tiene_siguiente(iterador)) {
			hash_campo_t* campo_actual = lista_iterador_borrar(iterador);
			hash_campo_borrar(campo_actual, hash->destructor);
		}
		lista_iterador_destruir(iterador);
		lista_destruir(lista_a_destruir);
	}
	free(hash->tabla);
}

bool re_hasheo(hash_t* hash, lista_t** nueva_tabla, size_t capacidad_nueva) {
	if(hash == NULL) {
		return false;
	}
	for(size_t i = 0; i < hash->tamanio; i++){
		lista_t* lista_a_trasladar = hash->tabla[i];
		if(lista_vacia(lista_a_trasladar)){
			lista_destruir(lista_a_trasladar);
			continue;
		}
		lista_iterador_t* iterador = lista_iterador_crear(lista_a_trasladar);
		while(lista_iterador_tiene_siguiente(iterador)){
			hash_campo_t* campo = lista_iterador_borrar(iterador); 
			size_t pos_nueva = funcion_hashing(campo->clave, capacidad_nueva); 
			int estado = lista_insertar_en_posicion(nueva_tabla[pos_nueva], campo, 0); 
			if(estado == ERROR) {
				return false;
			}
		}
		lista_iterador_destruir(iterador);
		lista_destruir(lista_a_trasladar);
	}
	return true;
}

bool hash_redimensionar(hash_t* hash, size_t capacidad_nueva){
	if(hash == NULL) {
		return false;
	}
	lista_t** nueva_tabla = crear_tabla(hash, capacidad_nueva);
	if(nueva_tabla == NULL) {
		return false;
	}
	if(!re_hasheo(hash, nueva_tabla, capacidad_nueva)) {
		return false;
	}
	free(hash->tabla);
	hash->tabla = nueva_tabla;
	hash->tamanio = capacidad_nueva;
	return true;	
}


bool supera_minimo_aceptado(float capacidad){
	float capacidad_nueva = capacidad / COTA_MINIMA;
	capacidad_nueva = capacidad - capacidad_nueva;
	if (capacidad_nueva >= CANTIDAD_POR_DEFECTO) {
		return true;
	}
	return false;
}

lista_iterador_t* encontrar_clave(const hash_t* hash, const char* clave){
	if(hash == NULL) {
		return false;
	}
	size_t pos_guardado = funcion_hashing(clave, hash->tamanio);
	lista_t* lista_elegida = hash->tabla[pos_guardado];
	lista_iterador_t* iterador = buscar_campo(lista_elegida, clave);
	return iterador;
}

/* ******************************************************************
 *                        PRIMITIVAS DEL HASH
 * *****************************************************************/

hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad) {
	hash_t* hash = calloc(1, sizeof(hash_t));
	if (hash == NULL) {
		return NULL;
	}
	lista_t** tabla = crear_tabla(hash, capacidad);
	if(tabla == NULL) {
		free(hash);
		return NULL;
	}
	hash->tabla = tabla;
	hash->destructor = destruir_elemento;
	hash->tamanio = capacidad;
	return hash;
}

int hash_insertar(hash_t* hash, const char* clave, void* elemento) {
	if(hash == NULL || clave == NULL) {
		return ERROR;
	}
	if (factor_de_carga(hash) >= COTA_MAXIMA) {
		size_t nueva_capacidad = hash->tamanio * AUMENTO_REDIMENSION;
		if (!hash_redimensionar(hash, nueva_capacidad)) {
			return ERROR;
		}
	}
	lista_iterador_t* iterador = encontrar_clave(hash, clave);
	hash_campo_t* campo = lista_iterador_ver_actual(iterador);
	if (campo) {
		if(strcmp(campo->clave, clave) == 0) {
			if(hash->destructor) {
				hash->destructor(campo->elemento);
			}
			campo->elemento = elemento;
			lista_iterador_destruir(iterador);
			return EXITO;
		}
	}
	int agregado_ok = agregar_campo(iterador, clave, elemento);
	if (agregado_ok == EXITO) {
		hash->usado ++;
	}
	lista_iterador_destruir(iterador);
	return agregado_ok;
}

int hash_quitar(hash_t* hash, const char* clave) {
	if(hash == NULL || clave == NULL) {
		return ERROR;
	}
	if (factor_de_carga(hash) <= COTA_MINIMA && supera_minimo_aceptado((float)hash->tamanio)) {
		float nueva_capacidad = (float)hash->tamanio - (float)hash->tamanio * COTA_MINIMA;
		if (!hash_redimensionar(hash, (size_t)nueva_capacidad)) {
			return ERROR;
		}
	}
	lista_iterador_t* iterador = encontrar_clave(hash, clave);
	hash_campo_t* campo = lista_iterador_borrar(iterador);
	lista_iterador_destruir(iterador);
	if (campo == NULL) {
		return ERROR;
	}
	hash->usado --;
	hash_campo_borrar(campo, hash->destructor);
	return EXITO;
}

void* hash_obtener(hash_t* hash, const char* clave) {
	if(hash == NULL || clave == NULL) {
		return NULL;
	}
	lista_iterador_t* iterador = encontrar_clave(hash, clave);
	hash_campo_t* campo = lista_iterador_ver_actual(iterador);
	lista_iterador_destruir(iterador);
	if (campo) {
		return campo->elemento;
	}
	return NULL;
}

bool hash_contiene(hash_t* hash, const char* clave){
	if(hash == NULL || clave == NULL) {
		return false;
	}
	lista_iterador_t* iterador = encontrar_clave(hash, clave);
	hash_campo_t* campo = lista_iterador_ver_actual(iterador);
	lista_iterador_destruir(iterador);
	if (campo == NULL) {
		return false;
	}
	return true;
}

size_t hash_cantidad(hash_t* hash){
	if(hash == NULL) {
		return VACIA;
	}
	return hash->usado;
}

void hash_destruir(hash_t* hash){
	if(hash != NULL) {
		destruir_tabla(hash);
		free(hash);
	}
}