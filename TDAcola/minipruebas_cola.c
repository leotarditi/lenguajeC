#include "cola.h"
#include "mis_pruebas.h"
#include <stdio.h>

const int VACIA = 1;
const int NO_VACIA = 0;
const int PUDO = 0;
const int NO_PUDO = -1;

int mini_prueba() {
  cola_t* cola = cola_crear();

  int a=1, b=2, c=3, d=4;

  printf("Encolo el elemento %i\n", a);
  cola_encolar(cola, (void*)&a);

  printf("Encolo el elemento %i\n", b);
  cola_encolar(cola, (void*)&b);

  printf("Encolo el elemento %i\n", c);
  cola_encolar(cola, (void*)&c);

  printf("Encolo el elemento %i\n", d);
  cola_encolar(cola, (void*)&d);

  printf("La cola tiene %i elementos\n", cola_cantidad(cola));
    
  printf("Desencolo un elemento\n");
  cola_desencolar(cola);

  printf("¿La cola está vacía?: %s\n", cola_vacia(cola)?"SI":"NO");

  cola_primero(cola);
  printf("El primer elemento de la cola es: %i\n", *(int*)cola_primero(cola));

  cola_destruir(cola);
  return 1;
}

int DadaUnaCantidadVaridadDeElemento_CuandoEncoleYDesencole_EntoncesVeremosSiFuncionaComoLosEsperabamos() {
  int elemento[100];
  int contador = 0;
  int cantidad_almacenada;
  int cantidad_a_probar = 100;
  char letra = 'N';
  int cantidad_pruebas = 14;

  cola_t* cola = cola_crear();

  printf("Prueba de cola vacia:");
  prueba_cola_estado(cola, &contador, VACIA);
  printf("Prueba de encolar una letra:");
  prueba_encolar(cola, &contador, &letra, PUDO);
  printf("Prueba de cola no vacia:");
  prueba_cola_estado(cola, &contador, NO_VACIA);
  printf("Prueba de cantidad con un elemento apilado:");
  cantidad_almacenada = 1;
  prueba_cantidad_almacenada(cola, &contador, cantidad_almacenada);
  printf("El primer elemento de la cola es el esperado:");
  prueba_primero_almacenado(cola, &contador);
  printf("Prueba desencola un elemento:");
  prueba_desencolar(cola, &contador, PUDO);
  printf("Prueba cola vacia:");
  prueba_cola_estado(cola, &contador, VACIA);
  printf("cola sin elementos:");
  cantidad_almacenada = 0;
  prueba_cantidad_almacenada(cola, &contador, cantidad_almacenada);
  printf("El primer elemento es NULL:");
  prueba_primero_null(cola, &contador);
  printf("Prueba de desencolar cola vacia:");
  prueba_desencolar(cola, &contador, NO_PUDO);
  printf("\n");
  for (int i = 0; i < cantidad_a_probar; i++) {
    elemento[i] = i;
    cola_encolar(cola, &elemento[i]);
  }
  printf("El primer elemento es el esperado:");
  prueba_primero_almacenado(cola, &contador);
  printf("Prueba cola no vacia:");
  prueba_cola_estado(cola, &contador, NO_VACIA);
  printf("Prueba 100 elementos encolados:");
  prueba_cantidad_almacenada(cola, &contador, cantidad_a_probar);
  printf("\n");
  for (int i = 100; i > 0; i--) {
    cola_desencolar(cola);
  }
  printf("\n");
  printf("El primer elemento es NULL:");
  prueba_primero_null(cola, &contador);
  cola_destruir(cola);
  if (contador == cantidad_pruebas) {
    printf("Prueba 1: OK\n\n");
    return 1;
  }
  return 0;
}

int DadaUnaColaVacia_CuandoDesencole_EntoncesDevolveraNULL() {
  cola_t* cola = cola_crear();
  int contador = 0;
  int cantidad_almacenada;
  int cantidad_pruebas = 4;

  printf("Prueba cola vacia:");
  prueba_cola_estado(cola, &contador, VACIA);
  printf("Cola sin elementos:");
  cantidad_almacenada = 0;
  prueba_cantidad_almacenada(cola, &contador, cantidad_almacenada);
  printf("El primero es NULL:");
  prueba_primero_null(cola, &contador);
  printf("Prueba de desencolar cola vacia:");
  prueba_desencolar(cola, &contador, NO_PUDO);
  cola_destruir(cola);
  if (contador == cantidad_pruebas) {
    printf("Prueba 2: OK\n\n");
    return 1;
  }
  return 0;
}


int DadaUnaCantidadPequeniaDeElementos_CuandoEncoleYDesencole_EntoncesDevolveraLosValoresEsperados() {
  cola_t* cola = cola_crear();
  int contador = 0;
  char elemento1 = 'o', elemento2 = 'e', elemento3 = 'L';
  int cantidad_almacenada;
  int cantidad_pruebas = 16;

  printf("Prueba cola vacia:");
  prueba_cola_estado(cola, &contador, VACIA);
  printf("Prueba encola un elemento:");
  prueba_encolar(cola, &contador, &elemento1, PUDO);
  printf("Prueba cola con un elemento:");
  prueba_cola_estado(cola, &contador, NO_VACIA);
  printf("Prueba cantidad con un elemento apilado:");
  cantidad_almacenada = 1;
  prueba_cantidad_almacenada(cola, &contador, cantidad_almacenada);
  printf("El primer es el elemento apilado:");
  prueba_primero_almacenado(cola, &contador);
  printf("Prueba encolar un elemento:");
  prueba_encolar(cola, &contador, &elemento2, PUDO);
  printf("Prueba encolar un elemento:");
  prueba_encolar(cola, &contador, &elemento3, PUDO);
  printf("Prueba cola con elementos:");
  prueba_cola_estado(cola, &contador, NO_VACIA);
  printf("Prueba cantidad de elementos esperados:");
  cantidad_almacenada = 3;
  prueba_cantidad_almacenada(cola, &contador, cantidad_almacenada);
  printf("Prueba desencolar un elemento:");
  prueba_desencolar(cola, &contador, PUDO);
  printf("Prueba desencolar un elemento:");
  prueba_desencolar(cola, &contador, PUDO);
  printf("Se desencolar el ultimo elemento de la cola:");
  prueba_desencolar(cola, &contador, PUDO);
  printf("Prueba cola vacia:");
  prueba_cola_estado(cola, &contador, VACIA);
  printf("Cola sin elementos:");
  cantidad_almacenada = 0;
  prueba_cantidad_almacenada(cola, &contador, cantidad_almacenada);
  printf("el primer elemento es NULL:");
  prueba_primero_null(cola, &contador);
  printf("Prueba desencolar pila vacia:");
  prueba_desencolar(cola, &contador, NO_PUDO);
  cola_destruir(cola);
  if (contador == cantidad_pruebas) {
    printf("Prueba 3: OK\n\n");
    return 1;
  }
  return 0;
}


int DadaUnaColaConMasivosElementos_CuandoEncolerYDesencole_EntoncesDebeFuncionarBien(){
  int elemento[300000];
  int contador = 0;
  int cantidad_almacenada;
  int cantidad_pruebas = 6;
  
  cola_t* cola = cola_crear();

  cantidad_almacenada = 300000;
  for (int i = 0; i < cantidad_almacenada; i++) {
    elemento[i] = i;
    cola_encolar(cola, &elemento[i]);
  }
  printf("Prueba encolar 300k:");
  prueba_masiva_encolar(cola, &contador, cantidad_almacenada);
  for (int i = cantidad_almacenada; i > 0; i--) {
    cola_desencolar(cola);
  }
  printf("Prueba desencolar 300k:");
  prueba_primero_null(cola, &contador);
  
  cantidad_almacenada = 200000;
  for (int i = 0; i < cantidad_almacenada; i++) {
    elemento[i] = i;
    cola_encolar(cola, &elemento[i]);
  }
  printf("Prueba encolar 200k:");
  prueba_masiva_encolar(cola, &contador, cantidad_almacenada);
  for (int i = cantidad_almacenada; i > 0; i--) {
    cola_desencolar(cola);
  }
  printf("Prueba desencolar 200k:");
  prueba_primero_null(cola, &contador);

  cantidad_almacenada = 100000;
  for (int i = 0; i < cantidad_almacenada; i++) {
    elemento[i] = i;
    cola_encolar(cola, &elemento[i]);
  }
  printf("Prueba con encolar 100k:");
  prueba_masiva_encolar(cola, &contador, cantidad_almacenada);
  for (int i = cantidad_almacenada; i > 0; i--) {
    cola_desencolar(cola);
  }
  printf("Prueba desencolar 100k:");
  prueba_primero_null(cola, &contador);

  cola_destruir(cola);

  if (contador == cantidad_pruebas) {
    printf("prueba 4: OK\n\n");
    return 1;
  }
  return 0; 
}


int DadaUnaColaNULL_CuandoLaPasoALasFunciones_DebenDevolverSusValoresPredeterminados () {
  int contador = 0;
  int elemento = 21, cantidad_nula = 0;
  int cantidad_pruebas = 5;

  cola_t* cola = NULL;
  printf("Prueba encolar cola NULL:");
  prueba_encolar(cola, &contador, &elemento, NO_PUDO);
  printf("Prueba desencolar cola NULL:");
  prueba_desencolar(cola, &contador, NO_PUDO);
  printf("Prueba cola vacia:");
  prueba_cola_estado(cola, &contador, VACIA);
  printf("Prueba cantidad en cola NULL:");
  prueba_cantidad_almacenada(cola, &contador, cantidad_nula);
  printf("El primer elemento es NULL:");
  prueba_primero_null(cola, &contador);
  cola_destruir(cola);

  if (contador == cantidad_pruebas) {
    printf("prueba 5: OK\n\n");
    return 1;
  }
  return 0;
}

int main(){
  int pruebas_aprobadas = 0;
  int cantidad_pruebas = 6;

  pruebas_aprobadas += mini_prueba();
  printf("\n\n\n\n");
  pruebas_aprobadas += DadaUnaCantidadVaridadDeElemento_CuandoEncoleYDesencole_EntoncesVeremosSiFuncionaComoLosEsperabamos();
  printf("\n\n\n\n");
  pruebas_aprobadas += DadaUnaColaVacia_CuandoDesencole_EntoncesDevolveraNULL();
  printf("\n\n\n\n");
  pruebas_aprobadas += DadaUnaCantidadPequeniaDeElementos_CuandoEncoleYDesencole_EntoncesDevolveraLosValoresEsperados();
  printf("\n\n\n\n");
  pruebas_aprobadas += DadaUnaColaConMasivosElementos_CuandoEncolerYDesencole_EntoncesDebeFuncionarBien();
  printf("\n\n\n\n");
  pruebas_aprobadas += DadaUnaColaNULL_CuandoLaPasoALasFunciones_DebenDevolverSusValoresPredeterminados();
  printf("\n\n\n\n");

  printf("\nPruebas pasadas %i/%i \n", pruebas_aprobadas, cantidad_pruebas);
  return 0;
}

/**************************************************************************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
***************************************************************************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
**************************************************************************************************************************************************************/


void prueba_masiva_encolar(cola_t* cola, int* contador, int cantidad) {
  if(cola_primero(cola) == cola->nodo_inicio->elemento && !cola_vacia(cola) && cola_cantidad(cola) == cantidad) {
    printf(" APROBADA\n");
    (*contador)++;
  } else {
    printf(" DESAPROBADA\n");
  }
}

void prueba_cola_estado(cola_t* cola, int* contador, int estado) {
  if(cola_vacia(cola) == estado) {
    printf(" APROBADA\n");
    (*contador)++;
  } else {
    printf(" DESAPROBADA\n");
  }
}

void prueba_encolar(cola_t* cola, int* contador, void* elemento, int encolar) {
  if (cola_encolar(cola, elemento) == encolar){
    printf(" APROBADA\n");
    (*contador)++;
  } else {
    printf(" DESAPROBADA\n");
  }
}

void prueba_cantidad_almacenada(cola_t* cola, int* contador, int cantidad){
  if(cola_cantidad(cola) == cantidad) {
    printf(" APROBADA\n");
    (*contador)++;
  } else {
    printf(" DESAPROBADA\n");
  }
}

void prueba_primero_almacenado(cola_t* cola, int* contador) {
  if(cola_primero(cola) == cola->nodo_inicio->elemento) {
    printf(" APROBADA\n");
    (*contador)++;
  } else {
    printf(" DESAPROBADA\n");
  }
}

void prueba_desencolar(cola_t* cola, int* contador, int desencolar) {
  if(cola_desencolar(cola) == desencolar) {
    printf(" APROBADA\n");
    (*contador)++;
  } else {
    printf(" DESAPROBADA\n");
  }
}

void prueba_primero_null(cola_t* cola, int* contador) {
  if(cola_primero(cola) == NULL) {
    printf(" APROBADA\n");
    (*contador)++;
  } else {
    printf(" DESAPROBADA\n");
  }
}
