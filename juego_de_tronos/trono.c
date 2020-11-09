#include "abb.h"
#include "my_abb.h"
#include "cola.h"
#include "lista.h"
#include "trono.h"
#include "simulacion.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ERROR -1
#define EXITO 0

#define MAX_NOMBRE 50

const char CASA = 'C';
const char INTEGRANTE = 'I';

const int EDAD_PROMEDIO = 60;

const char NOMBRE_NUEVO[] = "Junior";
const int EDAD_NACIMIENTO = 0;

struct reino {
	abb_t* casas;
	cola_t* casas_extintas;
	int cantidad_casas;
};

struct casa {
	lista_t* integrantes;
	char nombre_casa[MAX_NOMBRE];
	int factor_envejecimiento;
	int factor_nacimiento;
	size_t cantidad_integrantes;
};

struct integrante {
	char nombre_integrante[MAX_NOMBRE];
	int edad;
};

/**************************************************************************************************************************************************************
												FUNCION DE SIMULACION
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char* simulacion(int cantidad_anios, reino_t* reino) {
	void* casas_del_reino[reino->cantidad_casas];

	for(int j = 0; j < cantidad_anios; j++) {
		arbol_recorrido_inorden(reino->casas, casas_del_reino, reino->cantidad_casas);
		for (int i = 0; i < reino->cantidad_casas; i++) {
			casa_t* casa_buscada = (casa_t*)arbol_buscar(reino->casas, casas_del_reino[i]);
			lista_iterador_t* iterador = lista_iterador_crear(casa_buscada->integrantes);
			if(casa_buscada != NULL) {
				size_t posiciones_a_borrar[casa_buscada->cantidad_integrantes];
				size_t cantidad_posiciones = 0, lista_posicion = 0;
				while(lista_iterador_tiene_siguiente(iterador)) {
					integrante_t* integrante = (integrante_t*)lista_iterador_siguiente(iterador);
					integrante->edad += casa_buscada->factor_envejecimiento;
					if(integrante->edad >= EDAD_PROMEDIO) {
						posiciones_a_borrar[cantidad_posiciones] = lista_posicion;
						cantidad_posiciones ++;
					}
					lista_posicion ++;
				}
				for (size_t i = 0; i < cantidad_posiciones; i++) {
					borrar_integrante(casa_buscada, i, posiciones_a_borrar);
				}
				if(casa_buscada->cantidad_integrantes > 0) {
					int cantidad_a_nacer = (int)casa_buscada->cantidad_integrantes / casa_buscada->factor_nacimiento;
					if(cantidad_a_nacer > 0) {
						agregar_nuevos_integrantes(cantidad_a_nacer, casa_buscada);
					}
				} else {
					int pudo = cola_encolar(reino->casas_extintas, casa_buscada);
					if(pudo == ERROR) {
						printf("No pudo encolar la casa \n");
						return NULL;
					}
					arbol_borrar(reino->casas, casa_buscada);
					reino->cantidad_casas --;
				}
			}
			lista_iterador_destruir(iterador);
		}
	}
	
	if(reino->cantidad_casas == 0) {
		return NULL;
	}
	return casa_ganadora(reino);
}

/**************************************************************************************************************************************************************
												FUNCION AUXILIAR DE SIMULACION
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char* casa_ganadora(reino_t* reino) {
	casa_t* casa_ganadora; size_t cantidad_ganadora = 0;
	void* casas_del_reino[reino->cantidad_casas];
	arbol_recorrido_inorden(reino->casas, casas_del_reino, reino->cantidad_casas);
	for (int i = 0; i < reino->cantidad_casas; i++) {
		casa_t* casa_buscada = (casa_t*)arbol_buscar(reino->casas, casas_del_reino[i]);
		if(casa_buscada->cantidad_integrantes > cantidad_ganadora) {
			casa_ganadora = casa_buscada;
			cantidad_ganadora = casa_buscada->cantidad_integrantes;
		}
	}
	return casa_ganadora->nombre_casa;
}

/**************************************************************************************************************************************************************
												FUNCION DE AGREGAR
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void agregar_nueva_casa(char* nombre_archivo, reino_t* reino) {
	FILE* archivo = fopen(nombre_archivo, "r");
	if(archivo == NULL) {
		printf("No se pudo abrir el archivo \n");
		return;
	}
	casa_t* casa = (casa_t*)crear_estructura(sizeof(casa_t));
	int pudo = 2;
	char* linea = leer_linea(archivo);
	int leido = llenar_casa(casa, linea);
	if(leido == 3) {
		casa_t* casa_buscada = (casa_t*)arbol_buscar(reino->casas, casa); 
		linea = leer_linea(archivo);
		if(casa_buscada != NULL) {
			while(linea[0] == INTEGRANTE && pudo > 1) {
				integrante_t* integrante = (integrante_t*)crear_estructura(sizeof(integrante_t));
				pudo = llenar_integrante(integrante, linea);
				agregar_integrante(casa_buscada, integrante);
				linea = leer_linea(archivo);
			}
			casa_buscada->factor_nacimiento = casa->factor_nacimiento;
			casa_buscada->factor_envejecimiento = casa->factor_envejecimiento;
			borrar_casa(casa);
		} else {
			while(linea[0] == INTEGRANTE && pudo > 1) {
				integrante_t* integrante = (integrante_t*)crear_estructura(sizeof(integrante_t));
				pudo = llenar_integrante(integrante, linea);
				agregar_integrante(casa, integrante);
				linea = leer_linea(archivo);
			}
			agregar_casa(reino, casa);
		}
	}
	fclose(archivo);
}

/**************************************************************************************************************************************************************
												FUNCION DE LISTAR
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mostrar_casas_por_integrantes(reino_t* reino){
	if(reino->cantidad_casas == 0) {
		printf("No hay mas casas en el reino \n");
	} else {
		void* array[reino->cantidad_casas];
		arbol_recorrido_inorden(reino->casas, array, reino->cantidad_casas);
		merge_sort(array, reino->cantidad_casas, (int)sizeof(void*), es_mayor_casa);
		printf("Las casas de este reino son: \n");
		mostrar_vector(array, reino->cantidad_casas, (int)sizeof(void*), mostrar_casas);
	}
}

/**************************************************************************************************************************************************************
												FUNCION DE EXTINTAS
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mostrar_casas_extintas(reino_t* reino) {
	int cantidad = cola_cantidad(reino->casas_extintas);
	if(cantidad == 0) {
		printf("No hay casas extintas\n");
		return;
	} else {
		printf("Estas casas ya no existen: \n");	
	}
	cola_t* cola_auxiliar = cola_crear();
	for (int i = 0; i < cantidad; i++) {
		casa_t* casa_actual = (casa_t*)cola_primero(reino->casas_extintas);
		printf("%s \n", casa_actual->nombre_casa);
		cola_encolar(cola_auxiliar, casa_actual);
		cola_desencolar(reino->casas_extintas);
	}
	for (int i = 0; i < cantidad; i++) {
		casa_t* casa_actual = (casa_t*)cola_primero(cola_auxiliar);
		cola_encolar(reino->casas_extintas, casa_actual);
		cola_desencolar(cola_auxiliar);
	}
	cola_destruir(cola_auxiliar);
}

/**************************************************************************************************************************************************************
												FUNCION DE LEER
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char* leer_linea(FILE* archivo) {
	static char linea[500];

	char* s = fgets(linea, 500, archivo);
	if(s == NULL) {
		strcpy(linea, "NULL");
		linea[strlen(linea)-1] = '\0';
		return linea;	
	}
	linea[strlen(linea)-1] = '\0';
	return linea;
}

/**************************************************************************************************************************************************************
												FUNCION DE ESTRUCTURAS
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void* crear_estructura(size_t tamanio) {
	void* estructura = calloc(1, tamanio);
	if(estructura == NULL) {
		printf("No se pudo crear la estructura de %li bytes \n", tamanio);
		return NULL;
	}
	return estructura;
}

/**************************************************************************************************************************************************************
												FUNCIONES DE REINO
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int comparador_casas(void* elmento1, void* elmento2) {
	if(elmento1 == NULL || elmento2 == NULL) return 0;
	return strcmp(((casa_t*)elmento1)->nombre_casa, ((casa_t*)elmento2)->nombre_casa);
}

reino_t* crear_reino(char nombre_archivo[MAX_NOMBRE]) {
	FILE* archivo = fopen(nombre_archivo, "r");
	if(archivo == NULL) {
		printf("No se pudo abrir el archivo \n");
		return NULL;
	}
	reino_t* reino = (reino_t*)crear_estructura(sizeof(reino_t));
	reino->casas = arbol_crear(comparador_casas, NULL);
	reino->casas_extintas = cola_crear();
	int pudo;

	char* linea = leer_linea(archivo);
	while(linea[0] == CASA) {
		casa_t* casa = (casa_t*)crear_estructura(sizeof(casa_t));
		pudo = llenar_casa(casa, linea);
		if(pudo == ERROR) {
			printf("No se pudo llenar_casa \n");
			fclose(archivo);
			return NULL;
		}
		linea = leer_linea(archivo);
		while(linea[0] == INTEGRANTE && pudo > 1) {
			integrante_t* integrante = (integrante_t*)crear_estructura(sizeof(integrante_t));
			pudo = llenar_integrante(integrante, linea);
			if(pudo == ERROR) {
				printf("No pudo llenar_integrante \n");
				fclose(archivo);
				return NULL;
			}
			agregar_integrante(casa, integrante);
			linea = leer_linea(archivo);
		}
		agregar_casa(reino, casa);
	}
	fclose(archivo);
	return reino;
}

void destruir_reino(reino_t* reino) {
	void* array[reino->cantidad_casas];
	arbol_recorrido_inorden(reino->casas, array, reino->cantidad_casas);
	int cantidad_casas = reino->cantidad_casas;
	for (int i = 0; i < cantidad_casas; i++) {
		casa_t* casa_buscada = (casa_t*)arbol_buscar(reino->casas, array[i]);
		arbol_borrar(reino->casas, casa_buscada);
		borrar_casa(casa_buscada);
		reino->cantidad_casas --;
	}
	cantidad_casas = cola_cantidad(reino->casas_extintas);
	for (int i = 0; i < cantidad_casas; i++) {
		casa_t* casa = (casa_t*)cola_primero(reino->casas_extintas);
		borrar_casa(casa);
		cola_desencolar(reino->casas_extintas);
	}
	cola_destruir(reino->casas_extintas);
	arbol_destruir(reino->casas);
	reino->cantidad_casas = 0;
	free(reino);
}

/**************************************************************************************************************************************************************
												FUNCIONES DE CASA
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int llenar_casa(casa_t* casa, char* linea) {
	int guardo = sscanf(linea, "C;%[^;];%i;%i", casa->nombre_casa, &(casa->factor_envejecimiento), &(casa->factor_nacimiento));
	if(guardo == 3) {
		casa->integrantes = lista_crear();
	}
	return guardo;
}

void agregar_casa(reino_t* reino, casa_t* casa) {
	int pudo = arbol_insertar(reino->casas, casa);
	if(pudo == ERROR) {
		printf("NO PUDO INSERTAR CASA \n");
		return;
	}
	reino->cantidad_casas++;
}

void agregar_nuevos_integrantes(int cantidad_a_nacer, casa_t* casa) {
	for (int i = 0; i < cantidad_a_nacer; i++) {
		integrante_t* integrante = (integrante_t*)crear_estructura(sizeof(integrante_t));
		strcpy(integrante->nombre_integrante, NOMBRE_NUEVO);
		integrante->edad = EDAD_NACIMIENTO;
		agregar_integrante(casa, integrante);
	}
}

void borrar_casa(casa_t* casa) {
	size_t cantidad_integrantes = lista_elementos(casa->integrantes);
	for (size_t i = 0; i < cantidad_integrantes; i++) {
		size_t vector[1] = {0};
		borrar_integrante(casa, 0, vector);
	}
	casa->cantidad_integrantes = lista_elementos(casa->integrantes);
	lista_destruir(casa->integrantes);
	free(casa);
}

/**************************************************************************************************************************************************************
												FUNCIONES DE INTEGRANTE
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int llenar_integrante(integrante_t* integrante, char* linea) {
	int guardo = sscanf(linea, "I;%[^;];%i", integrante->nombre_integrante, &(integrante->edad));
	return guardo;
}


void agregar_integrante(casa_t* casa, integrante_t* integrante) {
	int pudo = lista_insertar(casa->integrantes, integrante);
	if (pudo == ERROR) {
		printf("NO PUDO INSERTAR INTEGRANTE \n");
		return;
	}
	casa->cantidad_integrantes = lista_elementos(casa->integrantes);
}

void destruir_integrante(void* integrante) {
	free((integrante_t*)integrante);
}

void borrar_integrante(casa_t* casa, size_t posicion, size_t* posiciones_a_borrar) {
	integrante_t* integrante = (integrante_t*)lista_elemento_en_posicion(casa->integrantes, posiciones_a_borrar[posicion]-posicion);
	destruir_integrante(integrante);
	int pudo = lista_borrar_de_posicion(casa->integrantes, posiciones_a_borrar[posicion]-posicion);
	if(pudo == ERROR) {
		printf("No pudo eliminar integrante moribundo \n");
		return;
	}
	casa->cantidad_integrantes = lista_elementos(casa->integrantes);
}

/**************************************************************************************************************************************************************
												FUNCIONES DE MERGE
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void merge(void** vector,int inicio1, int fin1, int fin2, int size, int (*es_mayor)(void*, void*)) {

	int inicio2 = fin1+1;

	char memoria[size];
	void* aux = &memoria;
	while(inicio1 <= fin1 && inicio2 <= fin2){
		if(es_mayor(vector[inicio1], vector[inicio2]))
			inicio1++; 
		else {
			if(aux == NULL) {
				printf("No pudo crear un auxiliar \n");
				return;
			}
			aux = vector[inicio2];
			for(int i = inicio2; i > inicio1; i--) {
	      		vector[i] = vector[i-1];
			}
	    	vector[inicio1] = aux;
	    	inicio1++;
	    	inicio2++;
	    	fin1++;
	    }
	}
}

void merge_sort_interno(void** vector,int inicio, int fin, int size, int (*es_mayor)(void*, void*)){
	
	if(inicio==fin) {
		return;
	}

	int medio = (fin+inicio)/2;
	merge_sort_interno(vector, inicio, medio, size, es_mayor);
	merge_sort_interno(vector, medio+1, fin, size, es_mayor);
	merge(vector, inicio, medio, fin, size, es_mayor);
}

void merge_sort(void** vector,int cantidad, int size, int (*es_mayor)(void*, void*)){
	merge_sort_interno(vector, 0, cantidad-1, size, es_mayor);
}

int es_mayor_casa (void* elemento1, void* elemento2){
	bool es_mayor = ((casa_t*)elemento1)->cantidad_integrantes > ((casa_t*)elemento2)->cantidad_integrantes;
	return es_mayor;
}

void mostrar_vector(void** vector, int N, int size, void (*funcion)(void*)){

	for(int i = 0; i < N; i++) {
		funcion(vector[i]);
	}
}

void mostrar_casas(void* elemento) {
	printf("%s \n", ((casa_t*)elemento)->nombre_casa);
	for(size_t i = 0; i < ((casa_t*)elemento)->cantidad_integrantes; i++) {
		printf("%s \n", ((integrante_t*)lista_elemento_en_posicion(((casa_t*)elemento)->integrantes, i))->nombre_integrante);
	}
	printf("\n\n");
}