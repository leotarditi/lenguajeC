#include "hash.h"
#include "hash_iterador.h"
#include "lista_modificada.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

const bool TIENE = true;
const bool NO_TIENE = false;
const int PUDO = 0;
const int NO_PUDO = -1;

void prueba_insertar(hash_t* hash, const char* clave, void* elemento, int inserto, int* contador) {
	if(hash_insertar(hash, clave, elemento) == inserto) {
		printf("APROBADO \n");
		(*contador) ++;
	} else {
		printf("DESAPROBADO \n");
	}
}

void prueba_quitar(hash_t* hash, const char* clave, int quito, int* contador) {
	if(hash_quitar(hash, clave) == quito) {
		printf("APROBADO \n");
		(*contador) ++;
	} else {
		printf("DESAPROBADO \n");
	}
}

void prueba_obtener(hash_t* hash, const char* clave, void* elemento, int* contador) {
	if(hash_obtener(hash, clave) == elemento) {
		printf("APROBADO \n");
		(*contador) ++;
	} else {
		printf("DESAPROBADO \n");
	}
}

void prueba_contiene(hash_t* hash, const char* clave, bool contiene, int* contador) {
	if(hash_contiene(hash, clave) == contiene) {
		printf("APROBADO \n");
		(*contador) ++;
	} else {
		printf("DESAPROBADO \n");
	}
}

void prueba_cantidad(hash_t* hash, int cantidad, int* contador) {
	if(hash_cantidad(hash) == cantidad) {
		printf("APROBADO \n");
		(*contador) ++;
	} else {
		printf("DESAPROBADO \n");
	}
}

void prueba_iterador_crear(hash_t* hash, hash_iterador_t* iterador, int* contador) {
	if(hash_iterador_crear(hash) == iterador) {
		printf("APROBADO \n");
		(*contador) ++;
	} else {
		printf("DESAPROBADO \n");
	}
}

void prueba_iterador_siguiente(hash_iterador_t* iterador, const char* clave, int* contador) {
	const char* retorno = hash_iterador_siguiente(iterador);
	if(retorno != NULL) {
		if (strcmp(retorno, clave) == 0) {
			printf("APROBADO \n");
			(*contador) ++;	
		}
	} else if(retorno == clave) {
		printf("APROBADO \n");
		(*contador) ++;
	} else {
		printf("DESAPROBADO \n");
	}
}

void prueba_iterador_tiene_siguiente(hash_iterador_t* iterador, bool tiene, int* contador) {
	if(hash_iterador_tiene_siguiente(iterador) == tiene) {
		printf("APROBADO \n");
		(*contador) ++;
	} else {
		printf("DESAPROBADO \n");
	}
}

void prueba_masiva(int contador_errores, int cantidad_errores_esperados, int* contador) {
	if(contador_errores == cantidad_errores_esperados) {
		printf("APROBADO \n");
		(*contador) ++;
	} else {
		printf("DESAPROBADO, hubo %i errores \n", contador_errores);
	}
}

int DadoUnHashVacioCuandoRealiceLasDiferentesFuncionesDevolveraLoPreestablecidoEnElContrato() {
	int contador = 0, cantidad_pruebas = 4;
	
	char* clave = "ABCD";
	void* elemento = NULL;
	int cantidad = 0;
	
	hash_t* hash = hash_crear(NULL, 10);

	printf("Prueba quitar un elemento en hash vacio: ");
	prueba_quitar(hash, clave, NO_PUDO, &contador);
	printf("Prueba obtener elemento en hash vacio: ");
	prueba_obtener(hash, clave, elemento, &contador);
	printf("Prueba si contiene un elemento en hash vacio: ");
	prueba_contiene(hash, clave, NO_TIENE, &contador);
	printf("Prueba cantidad en hash vacio: ");
	prueba_cantidad(hash, cantidad, &contador);

	hash_destruir(hash);

	printf("PRUEBA 1: ");
	if(contador == cantidad_pruebas) {
		printf("Aprobaste %i/%i", contador, cantidad_pruebas);
		return 1;
	}
	printf("Desaprobaste %i/%i", contador, cantidad_pruebas);
	return 0;
}

int DadoUnHashVacioCuandoItereEseHashDevolveraLoPreestablecidoEnElContrato() {
	int contador = 0, cantidad_pruebas = 2;

	hash_t* hash = hash_crear(NULL, 10);
	hash_iterador_t* iterador = hash_iterador_crear(hash);

	printf("Prueba iterador siguiente con hash vacio: ");
	prueba_iterador_siguiente(iterador, NULL, &contador);
	printf("Prueba iterador tiene siguiente con hash vacio: ");
	prueba_iterador_tiene_siguiente(iterador, NO_TIENE, &contador);

	hash_iterador_destruir(iterador);
	hash_destruir(hash);

	printf("PRUEBA 2: ");
	if(contador == cantidad_pruebas) {
		printf("Aprobaste %i/%i", contador, cantidad_pruebas);
		return 1;
	}
	printf("Desaprobaste %i/%i", contador, cantidad_pruebas);
	return 0;
}

int DadaUnaCantidadDeClavesYElementosCuandoInserteDevolveraLosValoresEsperados() {
	int contador = 0, cantidad_pruebas = 14;
	char* clave1 = "elefante"; void* elemento1 = "prrrrr";
	char* clave2 = "tero"; void* elemento2 = "teroterotero";
	char* clave3 = "pollito"; void* elemento3 = "piopiopio";
	int cantidad = 1;

	hash_t* hash = hash_crear(NULL, 10);

	//Inserto un elemento y luego los borro
	printf("Prueba insertar clave1: ");
	prueba_insertar(hash, clave1, elemento1, PUDO, &contador);
	printf("Prueba cantidad de elementos es 1: ");
	prueba_cantidad(hash, cantidad, &contador);
	printf("Prueba de obtener el clave1: ");
	prueba_obtener(hash, clave1, elemento1, &contador);
	printf("Prueba hash contiene clave1: ");
	prueba_contiene(hash, clave1, TIENE, &contador);
	printf("Prueba quitar clave1: ");
	prueba_quitar(hash, clave1, PUDO, &contador);
	printf("Prueba cantidad de elementos es 0: ");
	cantidad = 0;
	prueba_cantidad(hash, cantidad, &contador);

	//Inserto otros 2 elementos y no los borra (los destruye con el hash)
	printf("Prueba insertar clave2: ");
	prueba_insertar(hash, clave2, elemento2, PUDO, &contador);
	printf("Prueba cantidad de elementos es 1: ");
	cantidad = 1;
	prueba_cantidad(hash, cantidad, &contador);
	printf("Prueba de obtener el clave2: ");
	prueba_obtener(hash, clave2, elemento2, &contador);
	printf("Prueba hash contiene clave2: ");
	prueba_contiene(hash, clave2, TIENE, &contador);

	printf("Prueba insertar clave3: ");
	prueba_insertar(hash, clave3, elemento3, PUDO, &contador);
	printf("Prueba cantidad de elementos es 2: ");
	cantidad = 2;
	prueba_cantidad(hash, cantidad, &contador);
	printf("Prueba de obtener el clave3: ");
	prueba_obtener(hash, clave3, elemento3, &contador);
	printf("Prueba hash contiene clave3: ");
	prueba_contiene(hash, clave3, TIENE, &contador);

	hash_destruir(hash);

	printf("PRUEBA 3: ");
	if(contador == cantidad_pruebas) {
		printf("Aprobaste %i/%i", contador, cantidad_pruebas);
		return 1;
	}
	printf("Desaprobaste %i/%i", contador, cantidad_pruebas);
	return 0;
}

int DadaUnaCantidadDeClavesConElmentosCuandoQuieraInsertarLaMismaClaveConDistintoElementoDevolveraLaClaveConElUltimoElementoIngresado() {
	int contador = 0, cantidad_pruebas = 10;
	char* clave1 = "Mountain Bike"; void *elemento1a = "Rodado 29", *elemento1b = "Marca Trenel";
	char* clave2 = "Playera Bike"; void *elemento2a = "Rodado 26", *elemento2b = "Marca Junin";
	int cantidad = 2;

	hash_t* hash = hash_crear(NULL, 10);

	//Inserta dos elementos y luego los reemplaza
	printf("Prueba insertar clave1: ");
	prueba_insertar(hash, clave1, elemento1a, PUDO, &contador);
	printf("Prueba de obtener el clave1 es elemento1a: ");
	prueba_obtener(hash, clave1, elemento1a, &contador);
	printf("Prueba insertar clave2: ");
	prueba_insertar(hash, clave2, elemento2a, PUDO, &contador);
	printf("Prueba de obtener el clave2 es elemento2a: ");
	prueba_obtener(hash, clave2, elemento2a, &contador);
	printf("Prueba cantidad de elementos es 2: ");
	prueba_cantidad(hash, cantidad, &contador);
	
	printf("Prueba insertar clave1 con otro elemento: ");
	prueba_insertar(hash, clave1, elemento1b, PUDO, &contador);
	printf("Prueba de obtener el clave1 es elemento1b: ");
	prueba_obtener(hash, clave1, elemento1b, &contador);
	printf("Prueba insertar clave2 con otro elmento: ");
	prueba_insertar(hash, clave2, elemento2b, PUDO, &contador);
	printf("Prueba de obtener el clave2 es elemento2b: ");
	prueba_obtener(hash, clave2, elemento2b, &contador);
	printf("Prueba cantidad de elementos es 2: ");
	prueba_cantidad(hash, cantidad, &contador);

	hash_destruir(hash);

	printf("PRUEBA 4: ");
	if(contador == cantidad_pruebas) {
		printf("Aprobaste %i/%i", contador, cantidad_pruebas);
		return 1;
	}
	printf("Desaprobaste %i/%i", contador, cantidad_pruebas);
	return 0;
}

void destruir_elemento(void* elemento){
  if(elemento){
    printf("(Destructor) Libero el elemento ");
    free(elemento);
  }
}

int DadoUnaCantidadDeClavesConElementosAlmacenadosEnMemoriaDinamicaCuandoLosReemplazeYDestruyanDevolveranLosValoresEsperados() {
	int contador = 0, cantidad_pruebas = 10;
	char* clave1 = "Mountain Bike", *elemento1a, *elemento1b;
	char* clave2 = "Playera Bike", *elemento2a, *elemento2b;

	// Pide memoria para 4 elementos
	elemento1a = malloc(10 * sizeof(char));
	elemento1b = malloc(10 * sizeof(char));
	elemento2a = malloc(10 * sizeof(char));
	elemento2b = malloc(10 * sizeof(char));

	int cantidad = 2;

	hash_t* hash = hash_crear(destruir_elemento, 10);	

	//Inserta dos elementos y luego los reemplaza
	printf("Prueba insertar clave1: ");
	prueba_insertar(hash, clave1, elemento1a, PUDO, &contador);
	printf("Prueba de obtener el clave1 es elemento1a: ");
	prueba_obtener(hash, clave1, elemento1a, &contador);
	printf("Prueba insertar clave2: ");
	prueba_insertar(hash, clave2, elemento2a, PUDO, &contador);
	printf("Prueba de obtener el clave2 es elemento2a: ");
	prueba_obtener(hash, clave2, elemento2a, &contador);
	printf("Prueba cantidad de elementos es 2: ");
	prueba_cantidad(hash, cantidad, &contador);
	
	printf("Prueba insertar clave1 con otro elemento: ");
	prueba_insertar(hash, clave1, elemento1b, PUDO, &contador);
	printf("Prueba de obtener el clave1 es elemento1b: ");
	prueba_obtener(hash, clave1, elemento1b, &contador);
	printf("Prueba insertar clave2 con otro elmento: ");
	prueba_insertar(hash, clave2, elemento2b, PUDO, &contador);
	printf("Prueba de obtener el clave2 es elemento2b: ");
	prueba_obtener(hash, clave2, elemento2b, &contador);
	printf("Prueba cantidad de elementos es 2: ");
	prueba_cantidad(hash, cantidad, &contador);

	hash_destruir(hash);

	printf("\nPRUEBA 5: ");
	if(contador == cantidad_pruebas) {
		printf("Aprobaste %i/%i", contador, cantidad_pruebas);
		return 1;
	}
	printf("Desaprobaste %i/%i", contador, cantidad_pruebas);
	return 0;
}

int DadaUnaCantidadDeClavesYElementosCuandoBorreDevolveraLosValoresEsperados() {
	int contador = 0, cantidad_pruebas = 25;
	char* clave1 = "elefante"; void* elemento1 = "prrrrr";
	char* clave2 = "tero"; void* elemento2 = "teroterotero";
	char* clave3 = "pollito"; void* elemento3 = "piopiopio";
	int cantidad = 3;

	hash_t* hash = hash_crear(NULL, 10);

	printf("Prueba insertar clave1: ");
	prueba_insertar(hash, clave1, elemento1, PUDO, &contador);
	printf("Prueba insertar clave2: ");
	prueba_insertar(hash, clave2, elemento2, PUDO, &contador);
	printf("Prueba insertar clave3: ");
	prueba_insertar(hash, clave3, elemento3, PUDO, &contador);
	printf("Prueba cantidad de elemento es 3: ");
	prueba_cantidad(hash, cantidad, &contador);
	
	printf("Prueba contiene clave3: ");
	prueba_contiene(hash, clave3, TIENE, &contador);
	printf("Prueba obtener clave3 devuelve elemento3: ");
	prueba_obtener(hash, clave3, elemento3, &contador);
	printf("Prueba quitar clave3: ");
	prueba_quitar(hash, clave3, PUDO, &contador);
	printf("Prueba no puede quitar clave3: ");
	prueba_quitar(hash, clave3, NO_PUDO, &contador);
	printf("Prueba hash no contiene clave3: ");
	prueba_contiene(hash, clave3, NO_TIENE, &contador);
	printf("Prueba obtener clave3 devuelve NULL: ");
	prueba_obtener(hash, clave3, NULL, &contador);
	printf("Prueba cantidad de elemento es 2: ");
	cantidad = 2;
	prueba_cantidad(hash, cantidad, &contador);

	printf("Prueba contiene clave2: ");
	prueba_contiene(hash, clave2, TIENE, &contador);
	printf("Prueba obtener clave2 devuelve elemento2: ");
	prueba_obtener(hash, clave2, elemento2, &contador);
	printf("Prueba quitar clave2: ");
	prueba_quitar(hash, clave2, PUDO, &contador);
	printf("Prueba no puede quitar clave2: ");
	prueba_quitar(hash, clave2, NO_PUDO, &contador);
	printf("Prueba hash no contiene clave2: ");
	prueba_contiene(hash, clave2, NO_TIENE, &contador);
	printf("Prueba obtener clave2 devuelve NULL: ");
	prueba_obtener(hash, clave2, NULL, &contador);
	printf("Prueba cantidad de elemento es 1: ");
	cantidad = 1;
	prueba_cantidad(hash, cantidad, &contador);
	
	printf("Prueba contiene clave1: ");
	prueba_contiene(hash, clave1, TIENE, &contador);
	printf("Prueba obtener clave1 devuelve elemento1: ");
	prueba_obtener(hash, clave1, elemento1, &contador);
	printf("Prueba quitar clave1: ");
	prueba_quitar(hash, clave1, PUDO, &contador);
	printf("Prueba no puede quitar clave1: ");
	prueba_quitar(hash, clave1, NO_PUDO, &contador);
	printf("Prueba hash no contiene clave1: ");
	prueba_contiene(hash, clave1, NO_TIENE, &contador);
	printf("Prueba obtener clave1 devuelve NULL: ");
	prueba_obtener(hash, clave1, NULL, &contador);
	printf("Prueba cantidad de elemento es 0: ");
	cantidad = 0;
	prueba_cantidad(hash, cantidad, &contador);

	hash_destruir(hash);

	printf("PRUEBA 6: ");
	if(contador == cantidad_pruebas) {
		printf("Aprobaste %i/%i", contador, cantidad_pruebas);
		return 1;
	}
	printf("Desaprobaste %i/%i", contador, cantidad_pruebas);
	return 0;
}

int DadaUnaGranCantidadDeElementosCuandoLosInsertoyBorroDeUnHashDevolveraLosValoresEsperados(size_t largo) {
	int contador = 0, cantidad_pruebas = 7;
	int contador_errores = 0, cantidad_errores_esperados = 0;

	hash_t* hash = hash_crear(NULL, 10);
	const size_t largo_clave = 10;
	char (*claves)[largo_clave] = malloc(largo * largo_clave);

	unsigned* valores[largo];

	//Inserta 'largo' parejas en el hash
	bool ok = true;
	for (unsigned i = 0; i < largo; i++) {
		valores[i] = malloc(sizeof(int));
		sprintf(claves[i], "%08d", i);
		*valores[i] = i;
		ok = hash_insertar(hash, claves[i], valores[i]) == PUDO;
		if(!ok) {
			contador_errores ++;
			break;
		}
	}
	printf("Prueba hash almacenar muchos elementos: ");
	prueba_masiva(contador_errores, cantidad_errores_esperados, &contador);
	printf("Prueba hash cantidad de elementos es la correcta: ");
	prueba_cantidad(hash, (int)largo, &contador);
	
	// Verifica que devuelva los valores correctos
	contador_errores = 0;
	for (size_t i = 0; i < largo; i++) {
		ok = hash_contiene(hash, claves[i]);
		if(!ok) {
			contador_errores ++;
			break;
		}
		ok = hash_obtener(hash, claves[i]) == valores[i];
		if(!ok) {
			contador_errores ++;
			break;
		}
	}
	printf("Prueba hash pertenece y obtener muchos elementos: ");
	prueba_masiva(contador_errores, cantidad_errores_esperados, &contador);
	
	// Verifica que borre y devuelva los valores correctos	
	contador_errores = 0;
	for (size_t i = 0; i < largo; i++) {
		ok = hash_quitar(hash, claves[i]) == PUDO;
		if(!ok) {
			contador_errores ++;
			break;
		}
	}
	printf("Prueba hash quitar muchos elementos: ");
	prueba_masiva(contador_errores, cantidad_errores_esperados, &contador);
	
	//Destruye el hash y crea uno nuevo que libera
	hash_destruir(hash);
	hash = hash_crear(free, 10);

	//Inserta 'largo' parejas en el hash
	contador_errores = 0;
	for (size_t i = 0; i < largo; i++) {
		ok = hash_insertar(hash, claves[i], valores[i]) == PUDO;
		if(!ok) {
			contador_errores ++;
			break;
		}
	}
	printf("Prueba hash almacenar muchos elementos: ");
	prueba_masiva(contador_errores, cantidad_errores_esperados, &contador);
	printf("Prueba hash cantidad de elementos es la correcta: ");
	prueba_cantidad(hash, (int)largo, &contador);

	free(claves);
	
	// Destruye el hash - debería liberar los enteros
	hash_destruir(hash);
	printf("Prueba destruir hash masivo con Destructor: APROBADO \n");
	contador++;

	printf("PRUEBA 7: ");
	if(contador == cantidad_pruebas) {
		printf("Aprobaste %i/%i", contador, cantidad_pruebas);
		return 1;
	}
	printf("Desaprobaste %i/%i", contador, cantidad_pruebas);
	return 0;		
}

int DadoUnHashCuandoUseElIteradorDevolveraLosValoresEsperados() {
	int contador = 0, cantidad_pruebas = 12;
	char* claves[3] = {"silla", "bicicleta", "ventilador"};
	void* elementos[3] = {"4 patas", "2 ruedas", "calgado del techo"};
	int cantidad = 3;

	hash_t* hash = hash_crear(NULL, 10);

	printf("Prueba insertar clave1: ");
	prueba_insertar(hash, claves[0], elementos[0], PUDO, &contador);
	printf("Prueba insertar clave2: ");
	prueba_insertar(hash, claves[1], elementos[1], PUDO, &contador);
	printf("Prueba insertar clave3: ");
	prueba_insertar(hash, claves[2], elementos[2], PUDO, &contador);
	printf("Prueba cantidad de elemento es 3: ");
	prueba_cantidad(hash, cantidad, &contador);

	hash_iterador_t* iterador = hash_iterador_crear(hash);

	printf("Prueba clave siguiente devuelve clave1: ");
	prueba_iterador_siguiente(iterador, claves[0], &contador);
	printf("Prueba iterador tiene siguiente: ");
	prueba_iterador_tiene_siguiente(iterador, TIENE, &contador);

	printf("Prueba clave siguiente devuelve clave2: ");
	prueba_iterador_siguiente(iterador, claves[1], &contador);
	printf("Prueba iterador tiene siguiente: ");
	prueba_iterador_tiene_siguiente(iterador, TIENE, &contador);

	printf("Prueba clave siguiente devuelve clave3: ");
	prueba_iterador_siguiente(iterador, claves[2], &contador);
	printf("Prueba iterador tiene siguiente: ");
	prueba_iterador_tiene_siguiente(iterador, TIENE, &contador);

	printf("Prueba clave siguiente devuelve NULL: ");
	prueba_iterador_siguiente(iterador, NULL, &contador);
	printf("Prueba iterador no tiene siguiente: ");
	prueba_iterador_tiene_siguiente(iterador, NO_TIENE, &contador);		

	hash_iterador_destruir(iterador);
	hash_destruir(hash);

	printf("PRUEBA 8: ");
	if(contador == cantidad_pruebas) {
		printf("Aprobaste %i/%i", contador, cantidad_pruebas);
		return 1;
	}
	printf("Desaprobaste %i/%i", contador, cantidad_pruebas);
	return 0;
}


int DadoUnHashConMuchosElementosCuandoUseElIteradorDevolveraLosValoresEsperados(size_t largo) {
	int contador = 0, cantidad_pruebas = 5;
	int contador_errores = 0, cantidad_errores_esperados = 0;

	hash_t* hash = hash_crear(NULL, 10);
	const size_t largo_clave = 10;
	char (*claves)[largo_clave] = malloc(largo * largo_clave);

	size_t valores[largo];	

	//Inserta 'largo' parejas en el hash
	bool ok = true;
	for (unsigned i = 0; i < largo; i++) {
		sprintf(claves[i], "%08d", i);
		valores[i] = i;
		ok = hash_insertar(hash, claves[i], &valores[i]) == PUDO;
		if(!ok) {
			contador_errores ++;
			break;
		}
	}
	
	// Prueba de iteración sobre las claves almacenadas
	hash_iterador_t* iterador = hash_iterador_crear(hash);
	printf("Prueba iterador tiene siguiente: ");
	prueba_iterador_tiene_siguiente(iterador, TIENE, &contador);
	
	ok = true;
	unsigned i;
	const char* clave;
	size_t* elemento;

	for (i = 0; i < largo; i++) {
		if ( !hash_iterador_tiene_siguiente(iterador) ) {
			ok = false;
			contador_errores ++;
			break;
		}
		clave = hash_iterador_siguiente(iterador);
		if ( clave == NULL ) {
			ok = false;
			contador_errores ++;
			break;
		}
		elemento = hash_obtener(hash, clave);
		if ( elemento == NULL ) {
			ok = false;
			contador_errores ++;
			break;
		}
		*elemento = largo;
	}
	printf("Prueba hash iteracion masivo: ");
	prueba_masiva(contador_errores, cantidad_errores_esperados, &contador);
	printf("Prueba hash iteracion masivo, recorrido todo el largo: ");
	prueba_masiva(contador_errores, cantidad_errores_esperados, &contador);
	printf("Prueba hash iteracion masivo, tiene siguiente: ");
	prueba_masiva(contador_errores, cantidad_errores_esperados, &contador);

	ok = true;
	contador_errores = 0;
	for (i = 0; i < largo; i++) {
		if ( valores[i] != largo ) {
			ok = false;
			contador_errores ++;
			break;
		}
	}
	printf("Prueba hash iteración en volumen, se cambiaron todo los elementos: ");
	prueba_masiva(contador_errores, cantidad_errores_esperados, &contador);

	free(claves);
	hash_iterador_destruir(iterador);
	hash_destruir(hash);

	printf("PRUEBA 9: ");
	if(contador == cantidad_pruebas) {
		printf("Aprobaste %i/%i", contador, cantidad_pruebas);
		return 1;
	}
	printf("Desaprobaste %i/%i", contador, cantidad_pruebas);
	return 0;
}

int DadoUnHashNULLCuandoRealiceLasDiferentesFuncionesDevolveraLoPreestablecidoEnElContrato() {
	int contador = 0, cantidad_pruebas = 5;
	
	char* clave = "ABCD";
	void* elemento = NULL;
	int cantidad = 0;
	
	hash_t* hash = NULL;

	printf("Prueba insertar un elemento en hash NULL: ");
	prueba_insertar(hash, clave, elemento, NO_PUDO, &contador);
	printf("Prueba quitar un elemento en hash NULL: ");
	prueba_quitar(hash, clave, NO_PUDO, &contador);
	printf("Prueba obtener elemento en hash NULL: ");
	prueba_obtener(hash, clave, elemento, &contador);
	printf("Prueba si contiene un elemento en hash NULL: ");
	prueba_contiene(hash, clave, NO_TIENE, &contador);
	printf("Prueba cantidad en hash NULL: ");
	prueba_cantidad(hash, cantidad, &contador);

	hash_destruir(hash);

	printf("PRUEBA 10: ");
	if(contador == cantidad_pruebas) {
		printf("Aprobaste %i/%i", contador, cantidad_pruebas);
		return 1;
	}
	printf("Desaprobaste %i/%i", contador, cantidad_pruebas);
	return 0;
}