#include "abb.h"
#include "my_abb.h"
#include "mis_pruebas.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define ABB_RECORRER_INORDEN   0
#define ABB_RECORRER_PREORDEN  1
#define ABB_RECORRER_POSTORDEN 2
#define DATO_INT 1
#define DATO_CHAR 2
#define DATO_STRING 2

const int VACIO = 1;
const int NO_VACIO = 0;
const int PUDO = 0;
const int NO_PUDO = -1;

const int COINCIDENCIA = 0;
const int MENOR = -1;
const int MAYOR = 1;

int comparar_enteros(void* elemento1, void* elemento2);
int comparar_palabras(void* elemento1, void* elemento2);
int comparar_letras(void* elemento1, void* elemento2);

typedef struct alumno{
    int padron;
    int documento;
    char nombre[50];
}alumno_t;

alumno_t* crear_alumno(int padron, int documento, char nombre[]);
void destruir_alumno(alumno_t* alumno);
int comparar_alumnos(void* elemento1, void* elemento2);
void destructor_de_alumnos(void* elemento);
bool mostrar_elementos(void* elemento, void* extra);
bool mostrar_hasta_105525(void* elemento, void* extra);

typedef struct cosa{
    int clave;
    char contenido[10];
}cosa;

cosa* crear_cosa(int clave){
    cosa* c = (cosa*)malloc(sizeof(cosa));
    if(c)
	c->clave = clave;
    return c;
}

void destruir_cosa(cosa* c){
    if(c)
	free(c);
}

int comparar_cosas(void* elemento1, void* elemento2){
    if(!elemento1 || !elemento2)
	return 0;

    if(((cosa*)elemento1)->clave>((cosa*)elemento2)->clave)
	return 1;
    if(((cosa*)elemento1)->clave<((cosa*)elemento2)->clave)
	return -1;
    return 0;
}

void destructor_de_cosas(void* elemento){
    if(!elemento)
	return;
    destruir_cosa((cosa*)elemento);
}

bool mostrar_elemento(void* elemento, void* extra){
  extra=extra; //para que no se queje el compilador, gracias -Werror -Wall
  if(elemento)
    printf("%i ", ((cosa*)elemento)->clave);
  return false;
}

bool mostrar_hasta_5(void* elemento, void* extra){
  extra=extra; //para que no se queje el compilador, gracias -Werror -Wall
  if(elemento){
    printf("%i ", ((cosa*)elemento)->clave);
    if(((cosa*)elemento)->clave == 5)
      return true;
  }
  return false;
}

bool mostrar_acumulado(void* elemento, void* extra){
  if(elemento && extra){
    *(int*)extra += ((cosa*)elemento)->clave;
    printf("%i ", *(int*)extra);
  }
  return false;
}

int miniprueba() {
	abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

    cosa* c1= crear_cosa(1);
    cosa* c2= crear_cosa(2);
    cosa* c3= crear_cosa(3);
    cosa* c4= crear_cosa(4);
    cosa* c5= crear_cosa(5);
    cosa* c6= crear_cosa(6);
    cosa* c7= crear_cosa(7);
    cosa* auxiliar = crear_cosa(0);
    
    arbol_insertar(arbol, c4);
    arbol_insertar(arbol, c2);
    arbol_insertar(arbol, c6);
    arbol_insertar(arbol, c1);
    arbol_insertar(arbol, c3);
    arbol_insertar(arbol, c5);
    arbol_insertar(arbol, c7);

    printf("El nodo raiz deberia ser 4: %s\n", ((cosa*)arbol_raiz(arbol))->clave==4?"SI":"NO");

    auxiliar->clave = 5;
    printf("Busco el elemento 5: %s\n", ((cosa*)arbol_buscar(arbol, auxiliar))->clave==5?"SI":"NO");

    auxiliar->clave = 7;
    printf("Borro nodo hoja (7): %s\n", (arbol_borrar(arbol, auxiliar))==0?"SI":"NO");

    auxiliar->clave = 6;
    printf("Borro nodo con un hijo (6): %s\n", (arbol_borrar(arbol, auxiliar))==0?"SI":"NO");

    auxiliar->clave = 2;
    printf("Borro nodo con dos hijos (2): %s\n", (arbol_borrar(arbol, auxiliar))==0?"SI":"NO");

    auxiliar->clave = 4;
    printf("Borro la raiz (4): %s\n", (arbol_borrar(arbol, auxiliar))==0?"SI":"NO");

    auxiliar->clave = 3;
    printf("Busco el elemento (3): %s\n", ((cosa*)arbol_buscar(arbol, auxiliar))->clave==3?"SI":"NO");

    cosa* elementos[10];

    printf("Recorrido inorden (deberian salir en orden 1 3 5): ");
    int cantidad = arbol_recorrido_inorden(arbol, (void**)elementos, 10);
    for(int i=0;i<cantidad;i++)
	printf("%i ", elementos[i]->clave);
    printf("\n");

    printf("\n\nInserto mas valores y pruebo el iterador interno\n\n");
    arbol_insertar(arbol, crear_cosa(15));
    arbol_insertar(arbol, crear_cosa(0));
    arbol_insertar(arbol, crear_cosa(9));
    arbol_insertar(arbol, crear_cosa(7));
    arbol_insertar(arbol, crear_cosa(4));

    
    printf("Recorrido inorden iterador interno: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_elemento, NULL);
    printf("\n");

    printf("Recorrido preorden iterador interno: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_elemento, NULL);
    printf("\n");
    
    printf("Recorrido postorden iterador interno: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_elemento, NULL);
    printf("\n");

    printf("\nRecorrido inorden hasta encontrar el 5: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_hasta_5, NULL);
    printf("\n");

    printf("Recorrido preorden hasta encontrar el 5: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_hasta_5, NULL);
    printf("\n");

    printf("Recorrido postorden hasta encontrar el 5: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_hasta_5, NULL);
    printf("\n");

    int acumulador=0;
    printf("\nRecorrido inorden acumulando los valores: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_acumulado, &acumulador);
    printf("\n");

    acumulador=0;
    printf("Recorrido preorden acumulando los valores: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_acumulado, &acumulador);
    printf("\n");

    acumulador=0;
    printf("Recorrido postorden acumulando los valores: ");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_acumulado, &acumulador);
    printf("\n");
    
    free(auxiliar);
    arbol_destruir(arbol);
    return 1;
}

int DadoUnArbolNULLCuandoRealiceLasFuncionesDevolveraLosValoresPreestablecidos() {
	abb_t* arbol = NULL;
	void* elemento = NULL;
	int contador = 0, cantidad_pruebas = 5;
	printf("Prueba de insertar con arbol NULL: ");
	prueba_insertar(arbol, elemento, NO_PUDO, &contador);
	printf("Prueba de borrar con arbol NULL: ");
	prueba_borrar(arbol, elemento, NO_PUDO, &contador);
	printf("Prueba de buscar en arbol NULL: ");
	prueba_buscar(arbol, elemento, NO_PUDO, &contador);
	printf("Prueba la raiz de arbol NULL: ");
	prueba_raiz(arbol, elemento, &contador);
	printf("Arbol NULL esta vacio: ");
	prueba_estado(arbol, VACIO, &contador);

	printf("Prueba 1: ");
	if(cantidad_pruebas == contador) {
		printf("OK");
		return 1;
	} else {
		printf("FALLIDA");	
	}
	return 0;
}

int DadoUnArbolVacioCuandoRealiceLasFuncionesDevolveraLosValoresPreestablecidos() {
	abb_t* arbol = arbol_crear(NULL, NULL);
	void* elemento = NULL;
	int contador = 0, cantidad_pruebas = 4;
	printf("Prueba de borrar con arbol vacio: ");
	prueba_borrar(arbol, elemento, NO_PUDO, &contador);
	printf("Prueba de buscar en arbol vacio: ");
	prueba_buscar(arbol, elemento, NO_PUDO, &contador);
	printf("Prueba de raiz con arbol vacio: ");
	prueba_raiz(arbol, elemento, &contador);
	printf("Prueba si el arbol esta vacio: ");
	prueba_estado(arbol, VACIO, &contador);
	arbol_destruir(arbol);

	printf("Prueba 2: ");
	if(cantidad_pruebas == contador) {
		printf("OK");
		return 1;
	} else {
		printf("FALLIDA");	
	}
	return 0;
}

int DadoUnArbolDeEnterosCuandoRealiceLasFuncionesDevolveraLosValoresPreestablecidos() {
	int vector[7] = {25, 10, 30, 5, 15, 26, 35};
	int contador = 0, cantidad_pruebas = 24;
	int* arrai[7];
	int tamanio = 7;
	int raiz = 25;

	abb_t* arbol = arbol_crear(comparar_enteros, NULL);
	printf("Prueba arbol vacio: ");
	prueba_estado(arbol, VACIO, &contador);
	for (int i = 0; i < 7; i++) {
		printf("Prueba insertar un elemento: ");
		prueba_insertar(arbol, (void*)&vector[i], PUDO, &contador);
	}
	printf("Prueba arbol con elementos: ");
	prueba_estado(arbol, NO_VACIO, &contador);
	printf("Imprime el recorrido inorden (5 10 15 25 26 30 35): ");
	imprimir_recorridos(arbol, (void**)arrai, tamanio, arbol_recorrido_inorden, DATO_INT);
	printf("Imprime el recorrido postorden (5 15 10 26 35 30 25): ");
	imprimir_recorridos(arbol, (void**)arrai, tamanio, arbol_recorrido_postorden, DATO_INT);
	printf("Imprime el recorrido preorden (25 10 5 15 30 26 35): ");
	imprimir_recorridos(arbol, (void**)arrai, tamanio, arbol_recorrido_preorden, DATO_INT);
	printf("La Raiz es la esperada (25): ");
	prueba_raiz(arbol, (void*)&raiz, &contador);
	printf("Prueba borrar la raiz: ");
	prueba_borrar(arbol, (void*)&raiz, PUDO, &contador);
	printf("Prueba buscar la raiz borrada: ");
	prueba_buscar(arbol, (void*)&raiz, NO_PUDO, &contador);
	raiz = 15;
	printf("La Raiz es la esperada (15): ");
	prueba_raiz(arbol, (void*)&raiz, &contador);
	printf("Prueba borrar la raiz: ");
	prueba_borrar(arbol, (void*)&raiz, PUDO, &contador);
	printf("Prueba buscar la raiz borrada: ");
	prueba_buscar(arbol, (void*)&raiz, NO_PUDO, &contador);
	raiz = 10;
	printf("La Raiz es la esperada (10): ");
	prueba_raiz(arbol, (void*)&raiz, &contador);
	printf("Prueba borrar la raiz: ");
	prueba_borrar(arbol, (void*)&raiz, PUDO, &contador);
	printf("Prueba buscar la raiz borrada: ");
	prueba_buscar(arbol, (void*)&raiz, NO_PUDO, &contador);
	raiz = 5;
	printf("La Raiz es la esperada (5): ");
	prueba_raiz(arbol, (void*)&raiz, &contador);
	printf("Prueba borrar la raiz: ");
	prueba_borrar(arbol, (void*)&raiz, PUDO, &contador);
	printf("Prueba buscar la raiz borrada: ");
	prueba_buscar(arbol, (void*)&raiz, NO_PUDO, &contador);
	raiz = 30;
	printf("La Raiz es la esperada (30): ");
	prueba_raiz(arbol, (void*)&raiz, &contador);
	printf("Prueba borrar la raiz: ");
	prueba_borrar(arbol, (void*)&raiz, PUDO, &contador);
	printf("Prueba buscar la raiz borrada: ");
	prueba_buscar(arbol, (void*)&raiz, NO_PUDO, &contador);
	arbol_destruir(arbol);

	printf("Prueba 3: ");
	if(cantidad_pruebas == contador) {
		printf("OK");
		return 1;
	} else {
		printf("FALLIDA");
	}
	return 0;	
}

int DadoUnArbolDeLetrasCuandoRealiceLasFuncionesDevolveraLosValoresPreestablecidos() {
	char vector[7] = "hdqbfkx";
	int contador = 0, cantidad_pruebas = 24;
	char* arrai[7];
	int tamanio = 7;
	char raiz = 'h';

	abb_t* arbol = arbol_crear(comparar_letras, NULL);
	printf("Prueba arbol vacio: ");
	prueba_estado(arbol, VACIO, &contador);
	for (int i = 0; i < 7; i++) {
		printf("Prueba insertar un elemento: ");
		prueba_insertar(arbol, (void*)&vector[i], PUDO, &contador);
	}
	printf("Prueba arbol con elementos: ");
	prueba_estado(arbol, NO_VACIO, &contador);
	printf("Imprime el recorrido inorden (b d f h k q x): ");
	imprimir_recorridos(arbol, (void**)arrai, tamanio, arbol_recorrido_inorden, DATO_CHAR);
	printf("Imprime el recorrido postorden (b f d k x q h): ");
	imprimir_recorridos(arbol, (void**)arrai, tamanio, arbol_recorrido_postorden, DATO_CHAR);
	printf("Imprime el recorrido preorden (h d b f q k x): ");
	imprimir_recorridos(arbol, (void**)arrai, tamanio, arbol_recorrido_preorden, DATO_CHAR);
	printf("La Raiz es la esperada (h): ");
	prueba_raiz(arbol, (void*)&raiz, &contador);
	printf("Prueba borrar la raiz: ");
	prueba_borrar(arbol, (void*)&raiz, PUDO, &contador);
	printf("Prueba buscar la raiz borrada: ");
	prueba_buscar(arbol, (void*)&raiz, NO_PUDO, &contador);
	raiz = 'f';
	printf("La Raiz es la esperada (f): ");
	prueba_raiz(arbol, (void*)&raiz, &contador);
	printf("Prueba borrar la raiz: ");
	prueba_borrar(arbol, (void*)&raiz, PUDO, &contador);
	printf("Prueba buscar la raiz borrada: ");
	prueba_buscar(arbol, (void*)&raiz, NO_PUDO, &contador);
	raiz = 'd';
	printf("La Raiz es la esperada (d): ");
	prueba_raiz(arbol, (void*)&raiz, &contador);
	printf("Prueba borrar la raiz: ");
	prueba_borrar(arbol, (void*)&raiz, PUDO, &contador);
	printf("Prueba buscar la raiz borrada: ");
	prueba_buscar(arbol, (void*)&raiz, NO_PUDO, &contador);
	raiz = 'b';
	printf("La Raiz es la esperada (b): ");
	prueba_raiz(arbol, (void*)&raiz, &contador);
	printf("Prueba borrar la raiz: ");
	prueba_borrar(arbol, (void*)&raiz, PUDO, &contador);
	printf("Prueba buscar la raiz borrada: ");
	prueba_buscar(arbol, (void*)&raiz, NO_PUDO, &contador);
	raiz = 'q';
	printf("La Raiz es la esperada (q): ");
	prueba_raiz(arbol, (void*)&raiz, &contador);
	printf("Prueba borrar la raiz: ");
	prueba_borrar(arbol, (void*)&raiz, PUDO, &contador);
	printf("Prueba buscar la raiz borrada: ");
	prueba_buscar(arbol, (void*)&raiz, NO_PUDO, &contador);
	arbol_destruir(arbol);

	printf("Prueba 4: ");
	if(cantidad_pruebas == contador) {
		printf("OK");
		return 1;
	} else {
		printf("FALLIDA");
	}
	return 0;	
}

int DadoUnArbolLlenoDeAlumnosCuandoRealiceLasDiferentesFuncionesDevolveraLosValoresEsperados() {
	int contador = 0, cantidad_pruebas = 16;

	alumno_t* alumno1 = crear_alumno(104010, 41780679, "Santiago Lopez");
	alumno_t* alumno2 = crear_alumno(100203, 95564899, "Jhon Millan");
	alumno_t* alumno3 = crear_alumno(104521, 41526050, "Leo Tarditi");
	alumno_t* alumno4 = crear_alumno(95480, 34508554, "Antonella Maresca");
	alumno_t* alumno5 = crear_alumno(90822, 38837892, "Maria Martinez");
	alumno_t* alumno6 = crear_alumno(105525, 36275819, "Hernan Levi");
	alumno_t* alumno7 = crear_alumno(110321, 35367341, "Santiago Henin");

	abb_t* arbol = arbol_crear(comparar_alumnos, destructor_de_alumnos);

	printf("Prueba insertar un alumno: ");
	prueba_insertar(arbol, alumno1, PUDO, &contador);
	printf("Prueba insertar un alumno: ");
	prueba_insertar(arbol, alumno2, PUDO, &contador);
	printf("Prueba insertar un alumno: ");
	prueba_insertar(arbol, alumno3, PUDO, &contador);
	printf("Prueba insertar un alumno: ");
	prueba_insertar(arbol, alumno4, PUDO, &contador);
	printf("Prueba insertar un alumno: ");
	prueba_insertar(arbol, alumno5, PUDO, &contador);
	printf("Prueba insertar un alumno: ");
	prueba_insertar(arbol, alumno6, PUDO, &contador);
	printf("Prueba insertar un alumno: ");
	prueba_insertar(arbol, alumno7, PUDO, &contador);

	printf("\n");
	printf("Recorrido inorden iterador interno (padrones: 90822 95480 100203 104010 104521 105525 110321):\n");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_elementos, NULL);
    printf("\n");
    printf("Recorrido preorden iterador interno (padrones: 104010 100203 95480 90822 104521 105525 110321):\n");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_elementos, NULL);
    printf("\n");
    printf("Recorrido postorden iterador interno (padrones: 90822 95480 100203 110321 105525 104521 104010):\n");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_elementos, NULL);
    printf("\n");
    printf("Recorrido inorden hasta encontrar el 105525 (padrones: 90822 95480 100203 104010 104521 105525):\n");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_hasta_105525, NULL);
    printf("\n");
    printf("Recorrido preorden hasta encontrar el 105525 (padrones: 104010 100203 95480 90822 104521 105525):\n");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_hasta_105525, NULL);
    printf("\n");
    printf("Recorrido postorden hasta encontrar el 105525 (padrones: 90822 95480 100203 110321 105525):\n");    
    abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_hasta_105525, NULL);
    printf("\n");

    int raiz = 104010;
    printf("Prueba nodo raiz es el alumno1 (padron 104510): ");
    prueba_raiz(arbol, (void*)&raiz, &contador);
    int elemento = 110321;
    printf("Prueba borrar el alumno7 (padron 110321): ");
    prueba_borrar(arbol, (void*)&elemento, PUDO, &contador);
    elemento = 104521;
    printf("Prueba buscar el alumno3 (padron 104521): ");
    prueba_buscar(arbol, (void*)&elemento, PUDO, &contador);
    printf("Prueba borra el alumno3 (padron 104521): ");
    prueba_borrar(arbol, (void*)&elemento, PUDO, &contador);
    elemento = 100203;
    printf("Prueba buscar el alumno2 (padron 100203): ");
    prueba_buscar(arbol, (void*)&elemento, PUDO, &contador);
    printf("Prueba borra el alumno2 (padron 100203): ");
    prueba_borrar(arbol, (void*)&elemento, PUDO, &contador);
    printf("Prueba borrar la raiz: ");
    prueba_borrar(arbol, (void*)&raiz, PUDO, &contador);
    printf("Prueba buscar la raiz borrada: ");
    prueba_buscar(arbol, (void*)&raiz, NO_PUDO, &contador);
    raiz = 95480;
    printf("Prueba nodo raiz es el alumno4 (padron 95480): ");
    prueba_raiz(arbol, (void*)&raiz, &contador);

    arbol_destruir(arbol);
	printf("Prueba 5: ");
	if(cantidad_pruebas == contador) {
		printf("OK");
		return 1;
	} else {
		printf("FALLIDA");
	}
	return 0;    
}

int DadoUnArbolDegeneraCuandoRealiceLasDiferentesFuncionesDevolveraLoPreestablecido() {
	char Algebra[15] = {"Algrebra"};
	char Derecho[15] = {"Derecho"};
	char Fisica[15] = {"Fisica"};
	char Matematica[15] = {"Matematica"};
	char Probabilidad[15] = {"Probabilidad"};
	char Quimica[15] = {"Quimica"};
	int contador = 0, cantidad_pruebas = 24;

	abb_t* arbol = arbol_crear(comparar_palabras, NULL);

	printf("Prueba insertar una palabra (Algebra): ");
	prueba_insertar(arbol, (void*)Algebra, PUDO, &contador);
	printf("Prueba insertar una palabra (Derecho): ");
	prueba_insertar(arbol, (void*)Derecho, PUDO, &contador);
	printf("Prueba insertar una palabra (Fisica): ");
	prueba_insertar(arbol, (void*)Fisica, PUDO, &contador);
	printf("Prueba insertar una palabra (Matematica): ");
	prueba_insertar(arbol, (void*)Matematica, PUDO, &contador);
	printf("Prueba insertar una palabra (Probabilidad): ");
	prueba_insertar(arbol, (void*)Probabilidad, PUDO, &contador);
	printf("Prueba insertar una palabra (Quimica): ");
	prueba_insertar(arbol, (void*)Quimica, PUDO, &contador);
	printf("La Raiz es la esperada (Algebra): ");
	prueba_raiz(arbol, (void*)Algebra, &contador);
	printf("Prueba borrar la raiz: ");
	prueba_borrar(arbol, (void*)Algebra, PUDO, &contador);
	printf("Prueba buscar la raiz borrada: ");
	prueba_buscar(arbol, (void*)Algebra, NO_PUDO, &contador);
	printf("La Raiz es el siguiente como en una lista (Derecho): ");
	prueba_raiz(arbol, (void*)Derecho, &contador);
	printf("Prueba borrar la raiz: ");
	prueba_borrar(arbol, (void*)Derecho, PUDO, &contador);
	printf("Prueba buscar la raiz borrada: ");
	prueba_buscar(arbol, (void*)Derecho, NO_PUDO, &contador);
	printf("La Raiz es el siguiente como en una lista (Fisica): ");
	prueba_raiz(arbol, (void*)Fisica, &contador);
	printf("Prueba borrar la raiz: ");
	prueba_borrar(arbol, (void*)Fisica, PUDO, &contador);
	printf("Prueba buscar la raiz borrada: ");
	prueba_buscar(arbol, (void*)Fisica, NO_PUDO, &contador);
	printf("La Raiz es el siguiente como en una lista (Matematica): ");
	prueba_raiz(arbol, (void*)Matematica, &contador);
	printf("Prueba borrar la raiz: ");
	prueba_borrar(arbol, (void*)Matematica, PUDO, &contador);
	printf("Prueba buscar la raiz borrada: ");
	prueba_buscar(arbol, (void*)Matematica, NO_PUDO, &contador);
	printf("La Raiz es el siguiente como en una lista (Probabilidad): ");
	prueba_raiz(arbol, (void*)Probabilidad, &contador);
	printf("Prueba borrar la raiz: ");
	prueba_borrar(arbol, (void*)Probabilidad, PUDO, &contador);
	printf("Prueba buscar la raiz borrada: ");
	prueba_buscar(arbol, (void*)Probabilidad, NO_PUDO, &contador);
	printf("La Raiz es el siguiente como en una lista (Quimica): ");
	prueba_raiz(arbol, (void*)Quimica, &contador);
	printf("Prueba borrar la raiz: ");
	prueba_borrar(arbol, (void*)Quimica, PUDO, &contador);
	printf("Prueba buscar la raiz borrada: ");
	prueba_buscar(arbol, (void*)Quimica, NO_PUDO, &contador);
	arbol_destruir(arbol);

	printf("Prueba 6: ");
	if(cantidad_pruebas == contador) {
		printf("OK");
		return 1;
	} else {
		printf("FALLIDA");
	}
	return 0;	
}

int DadaUnaCantidadMasivaDeNumerosCuandoLosInserteYBorreDelArbolDevolveraLosValoresEstablecidos() {
	int elemento;
	int raiz = 456;
	int contador = 0, cantidad_pruebas = 10;

	abb_t* arbol = arbol_crear(comparar_enteros, NULL);
	printf("Prueba de arbol vacio: ");
	prueba_estado(arbol, VACIO, &contador);
	printf("Prueba insertar un elemento: ");
	prueba_insertar(arbol, (void*)&raiz, PUDO, &contador);
	printf("INSERTO 10K ELEMENTOS\n");
	for (int i = 0; i < 10000; ++i) {
		elemento = rand() % 10000;
		arbol_insertar(arbol, (void*)&elemento);
	}
	printf("Prueba arbol no vacio: ");
	prueba_estado(arbol, NO_VACIO, &contador);
	printf("Prueba que la raiz es el primer elemento insertado: ");
	prueba_raiz(arbol, (void*)&raiz, &contador);
	printf("Prueba borrar la raiz: ");
	prueba_borrar(arbol, (void*)&raiz, PUDO, &contador);
	arbol_destruir(arbol);

	arbol = arbol_crear(comparar_enteros, NULL);
	printf("Prueba de arbol vacio: ");
	prueba_estado(arbol, VACIO, &contador);
	printf("Prueba insertar un elemento: ");
	prueba_insertar(arbol, (void*)&raiz, PUDO, &contador);
	printf("INSERTO 5K ELEMENTOS\n");
	for (int i = 0; i < 5000; ++i) {
		elemento = rand() % 5000;
		arbol_insertar(arbol, (void*)&elemento);
	}
	printf("Prueba arbol no vacio: ");
	prueba_estado(arbol, NO_VACIO, &contador);
	printf("Prueba que la raiz es el primer elemento insertado: ");
	prueba_raiz(arbol, (void*)&raiz, &contador);
	printf("Prueba borrar la raiz: ");
	prueba_borrar(arbol, (void*)&raiz, PUDO, &contador);
	arbol_destruir(arbol);
	printf("Prueba 7: ");
	if(cantidad_pruebas == contador) {
		printf("OK");
		return 1;
	} else {
		printf("FALLIDA");
	}
	return 0;
}

int main(){
	srand((unsigned int) time(NULL));
	int cantidad_pruebas = 8;
	int cantidad_pruebas_pasadas = 0;
	cantidad_pruebas_pasadas += miniprueba();
	printf("\n\n\n\n");
	cantidad_pruebas_pasadas += DadoUnArbolNULLCuandoRealiceLasFuncionesDevolveraLosValoresPreestablecidos();
	printf("\n\n\n\n");
	cantidad_pruebas_pasadas += DadoUnArbolVacioCuandoRealiceLasFuncionesDevolveraLosValoresPreestablecidos();
	printf("\n\n\n\n");
	cantidad_pruebas_pasadas += DadoUnArbolDeEnterosCuandoRealiceLasFuncionesDevolveraLosValoresPreestablecidos();
	printf("\n\n\n\n");
	cantidad_pruebas_pasadas += DadoUnArbolDeLetrasCuandoRealiceLasFuncionesDevolveraLosValoresPreestablecidos();
	printf("\n\n\n\n");
	cantidad_pruebas_pasadas += DadoUnArbolLlenoDeAlumnosCuandoRealiceLasDiferentesFuncionesDevolveraLosValoresEsperados();
	printf("\n\n\n\n");
	cantidad_pruebas_pasadas += DadoUnArbolDegeneraCuandoRealiceLasDiferentesFuncionesDevolveraLoPreestablecido();
	printf("\n\n\n\n");
	cantidad_pruebas_pasadas += DadaUnaCantidadMasivaDeNumerosCuandoLosInserteYBorreDelArbolDevolveraLosValoresEstablecidos();
	printf("\n\n\n\n");
	if(cantidad_pruebas_pasadas == cantidad_pruebas) {
		printf("Has pasado la totalidad de las pruebas %i/%i \n", cantidad_pruebas_pasadas, cantidad_pruebas);
	} else {
		printf("Has pasado %i/%i de las pruebas \n", cantidad_pruebas_pasadas, cantidad_pruebas);
	}
	return 0;
}

/**************************************************************************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
***************************************************************************************************************************************************************
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int comparar_enteros(void* elemento1, void* elemento2){
    if(!elemento1 || !elemento2)
	return NO_PUDO;

    if(*(int*)elemento1 > *(int*)elemento2) return MAYOR;
    if(*(int*)elemento1 < *(int*)elemento2) return MENOR;
    return COINCIDENCIA;
}

int comparar_palabras(void* elemento1, void* elemento2){
    if(!elemento1 || !elemento2)
	return NO_PUDO;

    return strcmp((char*)elemento1, (char*)elemento2);
}

int comparar_letras(void* elemento1, void* elemento2){
    if(!elemento1 || !elemento2)
	return NO_PUDO;

    if(*(char*)elemento1 > *(char*)elemento2) return MAYOR;
    if(*(char*)elemento1 < *(char*)elemento2) return MENOR;
    return COINCIDENCIA;
}

alumno_t* crear_alumno(int padron, int documento, char nombre[]){
    alumno_t* alumno = calloc(1, sizeof(alumno_t));
    if(alumno == NULL) {
    	return NULL;
    }
	alumno->padron = padron;
	alumno->documento = documento;
	strcpy(alumno->nombre, nombre);
    return alumno;
}

void destruir_alumno(alumno_t* alumno){
    if(alumno)
	free(alumno);
}

int comparar_alumnos(void* elemento1, void* elemento2){
    if(!elemento1 || !elemento2)
	return 0;

    if(((alumno_t*)elemento1)->padron > ((alumno_t*)elemento2)->padron)
	return MAYOR;
    if(((alumno_t*)elemento1)->padron < ((alumno_t*)elemento2)->padron)
	return MENOR;
    return COINCIDENCIA;
}

void destructor_de_alumnos(void* elemento){
    if(!elemento)
	return;
    destruir_alumno((alumno_t*)elemento);
}

bool mostrar_elementos(void* elemento, void* extra){
  extra=extra; //para que no se queje el compilador, gracias -Werror -Wall
  if(elemento)
    printf("Padron:%i Documento:%i Nombre:%s \n", ((alumno_t*)elemento)->padron, ((alumno_t*)elemento)->documento, ((alumno_t*)elemento)->nombre);
  return false;
}

bool mostrar_hasta_105525(void* elemento, void* extra){
  extra=extra; //para que no se queje el compilador, gracias -Werror -Wall
  if(elemento){
    printf("Padron:%i Documento:%i Nombre:%s \n", ((alumno_t*)elemento)->padron, ((alumno_t*)elemento)->documento, ((alumno_t*)elemento)->nombre);
    if(((alumno_t*)elemento)->padron == 105525)
      return true;
  }
  return false;
}