#ifndef __TRONO_H__
#define __TRONO_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct reino reino_t;
typedef struct casa casa_t;
typedef struct integrante integrante_t;

/** FUNCION DE LEER *******************************/
//PRE:	que el archivo este inicializado
char* leer_linea(FILE* archivo);
//POS:	se encarga de ler una linea del archvo pasado

/********* FUNCION DE ESTRUCTURAS *****************/
//PRE:	que el tamanio sea de una estructura valida
void* crear_estructura(size_t tamanio);
//POS:	se encarga de reservarle memoria a una estructura del tamanio deseado

/************** FUNCIONES DE REINO ****************/
//PRE:	que los elementos no sean NULL, aunque uso un return pasa esos casos, seria mejor que no sean NULL
int comparador_casas(void* elmento1, void* elmento2);
//POS:	se encarga de comparar los nombres de dos casas distintas
//PRE:	que el nombre del archivo sea valido
reino_t* crear_reino(char nombre_archivo[]);
//POS:	se encarga de crear un reino y llenar todos sus campos
//PRE:	que el reino no sea NULL
void destruir_reino(reino_t* reino);
//POS:	se encarga de detruir todos los campos del reino

/*********************** FUNCIONES DE CASA ********/
//PRE:	que la casa ni la linea sean NULL
int llenar_casa(casa_t* casa, char* linea);
//POS:	se encarga de llenar los campos de la casa con lo que contiene la linea y devolver si pudo llenar o no
//PRE:	que el reino y la casa no sean NULL
void agregar_casa(reino_t* reino, casa_t* casa);
//POS:	se encarga de agregar una casa al reino
//PRE:	que la casa no sea NULL.
void agregar_nuevos_integrantes(int cantidad_a_nacer, casa_t* casa);
//POS:	se encarga de agregar la cantidad de integrantes a nacer en la casa
//PRE:	que la casa no sea NULL
void borrar_casa(casa_t* casa);
//POS:	se encarga de liberar todos los campos reservados en la casa

/******************** FUNCIONES DE INTEGRANTE ****/
//PRE:	que el integrante ni la linea sean NULL
int llenar_integrante(integrante_t* integrante, char* linea);
//POS:	se encarga de llenar los campos del integrante con lo que contiene la linea y devolver si pudo llenar o no
//PRE:	que la casa y el integrante no sean NULL
void agregar_integrante(casa_t* casa, integrante_t* integrante);
//POS:	se encarga de agregar un integrante a la casa
//PRE:	que el integrante no sea NULL
void destruir_integrante(void* integrante);
//POS:	se encarga de liberar la memoria reservada para el integrante
//PRE:	que la casa no sea NULL
void borrar_integrante(casa_t* casa, size_t posicion, size_t* posiciones_a_borrar);
//POS:	se encarga de borrar integrantes en determidad posicion de la lista de integrantes de la casa

/*************************** FUNCIONES DE MERGE **/
//PRE:	para las tres funciones se necesita que el vector este inicializado
void merge(void** vector,int inicio1, int fin1, int fin2, int size, int (*es_mayor)(void*, void*));
void merge_sort_interno(void** vector,int inicio, int fin, int size, int (*es_mayor)(void*, void*));
void merge_sort(void** vector,int cantidad, int size, int (*es_mayor)(void*, void*));
//POS:	se encarga de ordenar los elementos del vector con un metodo llamado merge sort
//PRE:	que los elementos no sean NULL
int es_mayor_casa (void* elemento1, void* elemento2);
//POS:	se encarga de devolver que casa tiene menor cantidad de integrantes
//PRE:	que el vector este inicializado
void mostrar_vector(void** vector, int N, int size, void (*funcion)(void*));
//POS:	muestra los elementos del vector
//PRE:	que el elemento no sea NULL (imprimiria null pero no es lo deseado)
void mostrar_casas(void* elemento);
//POS:	se encarga de mostrar el nombre de la casa y todos sus integrantes

#endif /* __TRONO_H__ */