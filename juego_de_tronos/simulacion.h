#ifndef __SIMULACION_H__
#define __SIMULACION_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* FUNCION DE SIMULACION */
//PRE:	que el reino no sea NULL
char* simulacion(int cantidad_anios, reino_t* reino);
//POS:	se encarga de simular cierta cantidad de años en el reino pasado
/* FUNCION AUXILIAR DE SIMULACION */
//PRE:	que el reino no sea NULL
char* casa_ganadora(reino_t* reino);
//POS:	se encarga de ver que casa tiene mayor cantidad de integrantes y devuelve su nombre

/* FUNCION DE AGREGAR */
//PRE:	que el reino y el archivo no sean NULL
void agregar_nueva_casa(char* nombre_archivo, reino_t* reino);
//POS:	se encarga de agregar una nueva casa en el reino y agregar sus integrantes si esta casa ya existe

/* FUNCION DE LISTAR */
//PRE:	que el reino no sea NULL
void mostrar_casas_por_integrantes(reino_t* reino);
//POS:	muestra todos las casa con sus respectivos integrantes ordenadas por cantidad de integrantes

/* FUNCION DE EXTINTAS */
//PRE:	que el reino no sea NULL
void mostrar_casas_extintas(reino_t* reino);
//POS:	muestra las casas extintas en el orden en que fueron eliminadas

#endif /* __SIMULACION_H__ */