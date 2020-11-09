#ifndef __LISTA_H__
#define __LISTA_MODIFICADA_H__

#include <stdbool.h>
#include <stddef.h>

typedef struct lista lista_t;
typedef struct lista_iterador lista_iterador_t;

/*
 * Crea la lista reservando la memoria necesaria.
 * Devuelve un puntero a la lista creada o NULL en caso de error.
 */
lista_t* lista_crear();

/*
 * Inserta un elemento al final de la lista.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar(lista_t* lista, void* elemento);

/*
 * Inserta un elemento en la posicion indicada, donde 0 es insertar
 * como primer elemento y 1 es insertar luego del primer elemento.  
 * En caso de no existir la posicion indicada, lo inserta al final.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion);

/*
 * Quita de la lista el elemento que se encuentra en la ultima posición.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar(lista_t* lista);

/*
 * Quita de la lista el elemento que se encuentra en la posición
 * indicada, donde 0 es el primer elemento.  
 * En caso de no existir esa posición se intentará borrar el último
 * elemento.  
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar_de_posicion(lista_t* lista, size_t posicion);

/*
 * Devuelve el elemento en la posicion indicada, donde 0 es el primer
 * elemento.
 *
 * Si no existe dicha posicion devuelve NULL.
 */
void* lista_elemento_en_posicion(lista_t* lista, size_t posicion);

/* 
 * Devuelve el último elemento de la lista o NULL si la lista se
 * encuentra vacía.
 */
void* lista_ultimo(lista_t* lista);

/* 
 * Devuelve true si la lista está vacía o false en caso contrario.
 */
bool lista_vacia(lista_t* lista);

/*
 * Devuelve la cantidad de elementos almacenados en la lista.
 */
size_t lista_elementos(lista_t* lista);

/*
 * Libera la memoria reservada por la lista.
 */
void lista_destruir(lista_t* lista);

/*
 * Iterador interno. Recorre la lista e invoca la funcion con cada
 * elemento de la misma.
 */
void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*));

/*
 * Crea un iterador para una lista. El iterador creado es válido desde
 * el momento de su creación hasta que no haya mas elementos por
 * recorrer o se modifique la lista iterada (agregando o quitando
 * elementos de la lista).
 *
 * Devuelve el puntero al iterador creado o NULL en caso de error.
 */
lista_iterador_t* lista_iterador_crear(lista_t* lista);

/*
 * Devuelve true si hay mas elementos sobre los cuales iterar o false
 * si no hay mas.
 */
bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador);

/*
 * Avanza el iterador al proximo elemento y lo devuelve.
 * En caso de error devuelve NULL.
 */
void* lista_iterador_siguiente(lista_iterador_t* iterador);

/*
 * Libera la memoria reservada por el iterador.
 */
void lista_iterador_destruir(lista_iterador_t* iterador);

/* ******************************************************************
 *               PRIMITIVAS DEL ITERADOR EXTERNO NUEVAS
 * *****************************************************************/

// Obtiene el valor al que apunta el iterador de la lista.
// Pre: la lista fue creada, no esta vacia, y su iterador fue creado.
// Post: se devolvió el valor del elemento al que que esta apuntando el iterador 
// de la lista.
void* lista_iterador_ver_actual(lista_iterador_t *iter);

// Agrega un nuevo elemento en la posicion a la que apunta el iterador de la lista . 
// Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, dato se encuentra en la posición
// a la que apunta el iterador de la lista.
int lista_iterador_insertar(lista_iterador_t* iterador, void* elemento);

// Elimina el elemento en la posicion a la que apunta el iterador de la lista . 
// Devuelve NULL en caso de error.
// Pre: la lista fue creada.
// Post: se eliminó el elemento al que apuntaba el iterador, el iterador ahora apunta
// a la posición siguiente.
void* lista_iterador_borrar(lista_iterador_t* iterador);

#endif //__LISTA_MODIFICADA_H__