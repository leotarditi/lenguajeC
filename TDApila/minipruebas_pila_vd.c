#include "pila.h"
#include "my_pila.h"
#include "mis_pruebas.h"
#include <stdio.h>

const int VACIA = 1;
const int NO_VACIA = 0;
const int NO_PUDO = -1;
const int PUDO = 0;

int mini_prueba() {
	pila_t* pila = pila_crear();

	char elemento1 = '!';
	pila_apilar(pila, &elemento1);
	printf("Tamanio pila: %i\n", pila_cantidad(pila));
	char elemento2 = '2';
	pila_apilar(pila, &elemento2);
	char elemento3 = 'o';
	pila_apilar(pila, &elemento3);
	printf("Tamanio pila: %i\n", pila_cantidad(pila));
	char elemento4 = 'g';
	pila_apilar(pila, &elemento4);
	char elemento5 = 'l';
	pila_apilar(pila, &elemento5);
	printf("Tamanio pila: %i\n", pila_cantidad(pila));
	char elemento6 = 'A';
	pila_apilar(pila, &elemento6);
	
	printf("%c\n", *(char*)pila_tope(pila));
	pila_desapilar(pila);
	printf("Tamanio pila: %i\n", pila_cantidad(pila));
	printf("%c\n", *(char*)pila_tope(pila));
	pila_desapilar(pila);
	printf("Tamanio pila: %i\n", pila_cantidad(pila));
	printf("%c\n", *(char*)pila_tope(pila));
	pila_desapilar(pila);
	printf("Tamanio pila: %i\n", pila_cantidad(pila));
	printf("%c\n", *(char*)pila_tope(pila));
	pila_desapilar(pila);
	printf("Tamanio pila: %i\n", pila_cantidad(pila));
	printf("%c\n", *(char*)pila_tope(pila));
	pila_desapilar(pila);
	printf("Tamanio pila: %i\n", pila_cantidad(pila));
	printf("%c\n", *(char*)pila_tope(pila));
	pila_desapilar(pila);
	printf("Tamanio pila: %i\n", pila_cantidad(pila));
	
	pila_destruir(pila);
	
	return 1;
}

int DadaUnaCantidadVaridadDeElemento_CuandoApileYDesapile_EntoncesVeremosSiFuncionaComoLosEsperabamos () {
	int elemento[100];
	int contador = 0;
	int cantidad_almacenada;
	int tamanio_a_probar = 128, cantidad_a_probar = 100;
	char letra = 'N';
	int cantidad_pruebas = 16;

	pila_t* pila = pila_crear();

	printf("Prueba de pila vacia:");
	prueba_pila_estado(pila, &contador, VACIA);
	printf("Prueba de apilar una letra:");
	prueba_apilar(pila, &contador, &letra, PUDO);
	printf("Prueba de pila no vacia:");
	prueba_pila_estado(pila, &contador, NO_VACIA);
	printf("Prueba de cantidad con un elemento apilado:");
	cantidad_almacenada = 1;
	prueba_cantidad_almacenada(pila, &contador, cantidad_almacenada);
	printf("El tope es el elemento apilado:");
	prueba_tope_almacenado(pila, &contador);
	printf("Prueba desapilar un elemento:");
	prueba_desapilar(pila, &contador, PUDO);
	printf("Prueba pila vacia:");
	prueba_pila_estado(pila, &contador, VACIA);
	printf("Pila sin elementos:");
	cantidad_almacenada = 0;
	prueba_cantidad_almacenada(pila, &contador, cantidad_almacenada);
	printf("El tope es NULL:");
	prueba_tope_null(pila, &contador);
	printf("Prueba de desapilar pila vacia:");
	prueba_desapilar(pila, &contador, NO_PUDO);
	printf("\n");
	for (int i = 0; i < cantidad_a_probar; i++) {
		elemento[i] = i;
		pila_apilar(pila, &elemento[i]);
		if (pila_cantidad(pila) == pila->tamanio) {
			printf("El Tamanio de la pila es: %i \n", pila->tamanio);
		}
	}
	printf("\n");
	printf("El tope es el ultimos elemento apilado:");
	prueba_tope_almacenado(pila, &contador);
	printf("Prueba pila no vacia:");
	prueba_pila_estado(pila, &contador, NO_VACIA);
	printf("Prueba 100 elementos apilados:");
	prueba_cantidad_almacenada(pila, &contador, cantidad_a_probar);
	printf("Prueba de redimensionar:");
	prueba_pila_tamanio(pila, &contador, tamanio_a_probar);
	printf("\n");
	for (int i = 100; i > 0; i--) {
		pila_desapilar(pila);
		if (pila_cantidad(pila) < (pila->tamanio/2)) {
			printf("El Tamanio de la pila es: %i \n", pila->tamanio);
		}
	}
	printf("\n");
	printf("El tope es NULL:");
	prueba_tope_null(pila, &contador);
	printf("Prueba de redimensionar:");
	tamanio_a_probar = 2;
	prueba_pila_tamanio(pila, &contador, tamanio_a_probar);
	pila_destruir(pila);
	if (contador == cantidad_pruebas) {
		printf("Prueba 1: OK\n\n");
		return 1;
	}
	return 0;
}

int DadaUnaPilaVacia_CuandoDesapile_EntoncesDevolveraNULL() {
	pila_t* pila = pila_crear();
	int contador = 0;
	int cantidad_almacenada;
	int cantidad_pruebas = 4;

	printf("Prueba pila vacia:");
	prueba_pila_estado(pila, &contador, VACIA);
	printf("Pila sin elementos:");
	cantidad_almacenada = 0;
	prueba_cantidad_almacenada(pila, &contador, cantidad_almacenada);
	printf("El tope es NULL:");
	prueba_tope_null(pila, &contador);
	printf("Prueba de desapilar pila vacia:");
	prueba_desapilar(pila, &contador, NO_PUDO);
	pila_destruir(pila);
	if (contador == cantidad_pruebas) {
		printf("Prueba 2: OK\n\n");
		return 1;
	}
	return 0;
}

int DadaUnaCantidadPequeniaDeElementos_CuandoApileYDesapile_EntoncesDevolveraLosValoresEsperados() {
	pila_t* pila = pila_crear();
	int contador = 0;
	char elemento1 = 'L', elemento2 = 'e', elemento3 = 'o';
	int cantidad_almacenada, tamanio_esperado;
	int cantidad_pruebas = 17;

	printf("Prueba pila vacia:");
	prueba_pila_estado(pila, &contador, VACIA);
	printf("Prueba apilar un elemento:");
	prueba_apilar(pila, &contador, &elemento1, PUDO);
	printf("Prueba pila con un elemento:");
	prueba_pila_estado(pila, &contador, NO_VACIA);
	printf("Prueba cantidad con un elemento apilado:");
	cantidad_almacenada = 1;
	prueba_cantidad_almacenada(pila, &contador, cantidad_almacenada);
	printf("El tope es el elemento apilado:");
	prueba_tope_almacenado(pila, &contador);
	printf("Prueba apilar un elemento:");
	prueba_apilar(pila, &contador, &elemento2, PUDO);
	printf("Prueba apilar un elemento:");
	prueba_apilar(pila, &contador, &elemento3, PUDO);
	printf("Prueba pila con elementos:");
	prueba_pila_estado(pila, &contador, NO_VACIA);
	printf("Prueba cantidad de elementos esperados:");
	cantidad_almacenada = 3;
	prueba_cantidad_almacenada(pila, &contador, 3);
	printf("Prueba de redimensionar:");
	tamanio_esperado = 4;
	prueba_pila_tamanio(pila, &contador, tamanio_esperado);
	printf("Prueba desapilar un elemento:");
	prueba_desapilar(pila, &contador, PUDO);
	printf("Prueba desapilar un elemento:");
	prueba_desapilar(pila, &contador, PUDO);
	printf("Se desapila el primer elemento de la pila:");
	prueba_desapilar(pila, &contador, PUDO);
	printf("Prueba pila vacia:");
	prueba_pila_estado(pila, &contador, VACIA);
	printf("Pila sin elementos:");
	cantidad_almacenada = 0;
	prueba_cantidad_almacenada(pila, &contador, cantidad_almacenada);
	printf("el tope es NULL:");
	prueba_tope_null(pila, &contador);
	printf("Prueba desapilar pila vacia:");
	prueba_desapilar(pila, &contador, NO_PUDO);
	pila_destruir(pila);
	if (contador == cantidad_pruebas) {
		printf("Prueba 3: OK\n\n");
		return 1;
	}
	return 0;
}

int DadaUnaPilaConMasivosElementos_CuandoApileYDesapile_EntoncesDebeFuncionarBien(){
	int elemento[300000];
	int contador = 0;
	int cantidad_almacenada, tamanio_esperado;
	int cantidad_pruebas = 6;
	
	pila_t* pila = pila_crear();

	cantidad_almacenada = 300000;
	tamanio_esperado = 524288;
	for (int i = 0; i < cantidad_almacenada; i++) {
		elemento[i] = i;
		pila_apilar(pila, &elemento[i]);
	}
	printf("Prueba apilar 300k:");
	prueba_masiva_apilar(pila, &contador, cantidad_almacenada, tamanio_esperado);
	for (int i = cantidad_almacenada; i > 0; i--) {
		pila_desapilar(pila);
	}
	tamanio_esperado = 2;
	printf("Prueba desapilar 300k:");
	prueba_masiva_desapilar(pila, &contador, tamanio_esperado);
	
	cantidad_almacenada = 200000;
	tamanio_esperado = 262144;
	for (int i = 0; i < cantidad_almacenada; i++) {
		elemento[i] = i;
		pila_apilar(pila, &elemento[i]);
	}
	printf("Prueba apilar 200k:");
	prueba_masiva_apilar(pila, &contador, cantidad_almacenada, tamanio_esperado);
	for (int i = cantidad_almacenada; i > 0; i--) {
		pila_desapilar(pila);
	}
	tamanio_esperado = 2;
	printf("Prueba desapilar 200k:");
	prueba_masiva_desapilar(pila, &contador, tamanio_esperado);

	cantidad_almacenada = 100000;
	tamanio_esperado = 131072;
	for (int i = 0; i < cantidad_almacenada; i++) {
		elemento[i] = i;
		pila_apilar(pila, &elemento[i]);
	}
	printf("Prueba con apilar 100k:");
	prueba_masiva_apilar(pila, &contador, cantidad_almacenada, tamanio_esperado);
	for (int i = cantidad_almacenada; i > 0; i--) {
		pila_desapilar(pila);
	}
	tamanio_esperado = 2;
	printf("Prueba desapilar 100k:");
	prueba_masiva_desapilar(pila, &contador, tamanio_esperado);

	pila_destruir(pila);

	if (contador == cantidad_pruebas) {
		printf("prueba 4: OK\n\n");
		return 1;
	}
	return 0;	
}

int DadaUnaPilaNULL_CuandoLaPasoALasFunciones_DebenDevolverSusValoresPredeterminados () {
	int contador = 0;
	int elemento = 32, cantidad_nula = 0;
	int cantidad_pruebas = 5;

	pila_t* pila = NULL;
	printf("Prueba apilar pila NULL:");
	prueba_apilar(pila, &contador, &elemento, NO_PUDO);
	printf("Prueba desapilar pila NULL:");
	prueba_desapilar(pila, &contador, NO_PUDO);
	printf("Prueba pila vacia:");
	prueba_pila_estado(pila, &contador, VACIA);
	printf("Prueba cantidad en pila NULL:");
	prueba_cantidad_almacenada(pila, &contador, cantidad_nula);
	printf("El tope es NULL:");
	prueba_tope_null(pila, &contador);
	pila_destruir(pila);

	if (contador == cantidad_pruebas) {
		printf("prueba 5: OK\n\n");
		return 1;
	}
	return 0;
}

int main(){
 	int pruebas_aprobadas = 0, cantidad_pruebas = 6;
	pruebas_aprobadas += mini_prueba();
	printf("\n\n\n\n");
	pruebas_aprobadas += DadaUnaCantidadVaridadDeElemento_CuandoApileYDesapile_EntoncesVeremosSiFuncionaComoLosEsperabamos();
	printf("\n\n\n\n");
	pruebas_aprobadas += DadaUnaPilaVacia_CuandoDesapile_EntoncesDevolveraNULL();
	printf("\n\n\n\n");
	pruebas_aprobadas += DadaUnaCantidadPequeniaDeElementos_CuandoApileYDesapile_EntoncesDevolveraLosValoresEsperados();
	printf("\n\n\n\n");
	pruebas_aprobadas += DadaUnaPilaConMasivosElementos_CuandoApileYDesapile_EntoncesDebeFuncionarBien();
	printf("\n\n\n\n");
	pruebas_aprobadas += DadaUnaPilaNULL_CuandoLaPasoALasFunciones_DebenDevolverSusValoresPredeterminados();
	printf("\nPruebas pasadas %i/%i \n", pruebas_aprobadas, cantidad_pruebas);
	return 0;
}

/**************************************************************************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
***************************************************************************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
**************************************************************************************************************************************************************/

void prueba_masiva_apilar(pila_t* pila, int* contador, int cantidad, int tamanio) {
	if(pila_tope(pila) == pila->elementos[pila->tope-1] && !pila_vacia(pila) && pila_cantidad(pila) == cantidad && pila->tamanio == tamanio) {
		printf(" APROBADA\n");
		(*contador)++;
	} else {
		printf(" DESAPROBADA\n");
	}
}

void prueba_masiva_desapilar(pila_t* pila, int* contador, int tamanio) {
	if(pila_tope(pila) == NULL && pila->tamanio == tamanio) {
		printf(" APROBADA\n");
		(*contador)++;
	} else {
		printf(" DESAPROBADA\n");
	}
}

void prueba_pila_estado(pila_t* pila, int* contador, int estado) {
	if(pila_vacia(pila) == estado) {
		printf(" APROBADA\n");
		(*contador)++;
	} else {
		printf(" DESAPROBADA\n");
	}
}

void prueba_apilar(pila_t* pila, int* contador, void* elemento, int apilar) {
	if (pila_apilar(pila, elemento) == apilar){
		printf(" APROBADA\n");
		(*contador)++;
	} else {
		printf(" DESAPROBADA\n");
	}
}

void prueba_cantidad_almacenada(pila_t* pila, int* contador, int cantidad){
	if(pila_cantidad(pila) == cantidad) {
		printf(" APROBADA\n");
		(*contador)++;
	} else {
		printf(" DESAPROBADA\n");
	}
}

void prueba_tope_almacenado(pila_t* pila, int* contador) {
	if(pila_tope(pila) == pila->elementos[pila->tope-1]) {
		printf(" APROBADA\n");
		(*contador)++;
	} else {
		printf(" DESAPROBADA\n");
	}
}

void prueba_desapilar(pila_t* pila, int* contador, int desapilar) {
	if(pila_desapilar(pila) == desapilar) {
		printf(" APROBADA\n");
		(*contador)++;
	} else {
		printf(" DESAPROBADA\n");
	}
}

void prueba_tope_null(pila_t* pila, int* contador) {
	if(pila_tope(pila) == NULL) {
		printf(" APROBADA\n");
		(*contador)++;
	} else {
		printf(" DESAPROBADA\n");
	}
}

void prueba_pila_tamanio(pila_t* pila, int* contador, int tamanio) {
	if(pila->tamanio == tamanio) {
		printf(" APROBADA\n");
		(*contador)++;
	} else {
		printf(" DESAPROBADA\n");
	}	
}