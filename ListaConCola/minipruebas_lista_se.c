#include "lista.h"
#include "mis_pruebas.h"
#include <stdio.h>

const int VACIA = 1;
const int NO_VACIA = 0;
const int PUDO = 0;
const int NO_PUDO = -1;
const int TIENE = 1;
const int NO_TIENE = 0;

void mostrar_elemento(void* elemento){
  if(elemento)
    printf("%c ", *(char*)elemento);
}

int mini_pruebas() {
  lista_t* lista = lista_crear();
  
  char a='a', b='b', c='c', d='d', w='w';
  
  lista_insertar(lista, &a);
  lista_insertar(lista, &c);
  lista_insertar_en_posicion(lista, &d, 100);
  lista_insertar_en_posicion(lista, &b, 1);
  lista_insertar_en_posicion(lista, &w, 4);
  
  lista_borrar_de_posicion(lista, 4);

  printf("Elementos en la lista: ");
  for(size_t i=0;i<lista_elementos(lista);i++)
    printf("%c ", *(char*)lista_elemento_en_posicion(lista, i));

  printf("\n");

  lista_iterador_t* it = lista_iterador_crear(lista);
  while(lista_iterador_tiene_siguiente(it))
    printf("%c ", *(char*)lista_iterador_siguiente(it));
  printf("\n");

  lista_iterador_destruir(it);

  printf("Imprimo la lista usando el iterador interno: ");
  lista_con_cada_elemento(lista, mostrar_elemento);
  printf("\n");
  
  lista_destruir(lista);
  return 1;
}

int DadaUnaCantidadVaridadDeElementos_CuandoInserteYBorre_EntoncesVeremosSiFuncionaComoLosEsperabamos() {
  int elemento[100];
  int contador = 0;
  int cantidad_almacenada;
  int cantidad_a_probar = 100;
  int cantidad_pruebas = 8;
  void* ultimo_elemento;

  lista_t* lista = lista_crear();
  printf("Prueba de lista vacia:");
  prueba_lista_estado(lista, &contador, VACIA);
  printf("cola sin elementos:");
  cantidad_almacenada = 0;
  prueba_cantidad_almacenada(lista, &contador, cantidad_almacenada);
  printf("El ultimo elemento es NULL:");
  ultimo_elemento = NULL;
  prueba_ultimo_almacenado(lista, &contador, ultimo_elemento);
  printf("Prueba de borrar en lista vacia:");
  prueba_borrar(lista, &contador, NO_PUDO);
  for (int i = 0; i < cantidad_a_probar; i++) {
    elemento[i] = i;
    lista_insertar(lista, &elemento[i]);
  }
  printf("El ultimo elemento es el esperado:");
  ultimo_elemento = &elemento[99];
  prueba_ultimo_almacenado(lista, &contador, ultimo_elemento);
  printf("Prueba lista no vacia:");
  prueba_lista_estado(lista, &contador, NO_VACIA);
  printf("Prueba 100 elementos insertados:");
  prueba_cantidad_almacenada(lista, &contador, cantidad_a_probar);
  for (int i = 100; i > 0; i--) {
    lista_borrar(lista);
  }
  printf("El ultimo elemento es NULL:");
  ultimo_elemento = NULL;
  prueba_ultimo_almacenado(lista, &contador, ultimo_elemento);
  lista_destruir(lista);
  if (contador == cantidad_pruebas) {
    printf("Prueba 1: OK\n\n");
    return 1;
  }
  return 0;
}

int DadaUnaListaVacia_CuandoBorre_EntoncesDevolveraNULL() {
  lista_t* lista = lista_crear();
  int contador = 0;
  int cantidad_almacenada;
  int cantidad_pruebas = 5;
  void* ultimo_elemento;
  size_t posicion1 = 1;

  printf("Prueba lista vacia:");
  prueba_lista_estado(lista, &contador, VACIA);
  printf("Lista sin elementos:");
  cantidad_almacenada = 0;
  prueba_cantidad_almacenada(lista, &contador, cantidad_almacenada);
  printf("El ultimo elemento es NULL:");
  ultimo_elemento = NULL;
  prueba_ultimo_almacenado(lista, &contador, ultimo_elemento);
  printf("Prueba de borrar lista vacia:");
  prueba_borrar(lista, &contador, NO_PUDO);
  printf("Prueba de borrar en posicion lista vacia:");
  prueba_borrar_en_posicion(lista, &contador, NO_PUDO, posicion1);
  lista_destruir(lista);
  if (contador == cantidad_pruebas) {
    printf("Prueba 2: OK\n\n");
    return 1;
  }
  return 0;
}

int DadaUnaCantidadPequeniaDeElementos_CuandoInsertoEnPosicionYBorroEnPosicion_EntoncesDevolveraLosValoresEsperados() {
  lista_t* lista = lista_crear();
  int contador = 0;
  int elemento3 = 0, elemento4 = 32;
  char elemento2 = 'e', elemento1 = 'L', elemento5 = 'p';
  size_t posicion2 = 2, posicion0 = 0;
  int cantidad_almacenada;
  int cantidad_pruebas = 21;
  void* ultimo_elemento;

  printf("Prueba lista vacia:");
  prueba_lista_estado(lista, &contador, VACIA);
  printf("Prueba insertar un elemento:");
  prueba_insertar(lista, &contador, &elemento1, PUDO);
  printf("Prueba lista con un elemento:");
  prueba_lista_estado(lista, &contador, NO_VACIA);
  printf("Prueba cantidad con un elemento insertado:");
  cantidad_almacenada = 1;
  prueba_cantidad_almacenada(lista, &contador, cantidad_almacenada);
  printf("El ultimo es el elemento insertado:");
  ultimo_elemento = &elemento1;
  prueba_ultimo_almacenado(lista, &contador, ultimo_elemento);
  printf("Prueba insertar un elemento:");
  prueba_insertar(lista, &contador, &elemento5, PUDO);
  printf("Prueba insertar un elemento:");
  prueba_insertar(lista, &contador, &elemento3, PUDO);
  printf("Prueba insertar en posicion un elemento:");
  prueba_insertar_en_posicion(lista, &contador, &elemento2, PUDO, posicion2);
  printf("Prueba insertar en posicion un elemento:");
  prueba_insertar_en_posicion(lista, &contador, &elemento4, PUDO, posicion0);
  printf("Prueba lista con elementos:");
  prueba_lista_estado(lista, &contador, NO_VACIA);
  printf("Prueba cantidad de elementos esperados:");
  cantidad_almacenada = 5;
  prueba_cantidad_almacenada(lista, &contador, cantidad_almacenada);
  printf("Prueba borrar en posicion un elemento:");
  prueba_borrar_en_posicion(lista, &contador, PUDO, posicion2);
  printf("Prueba borrar en posicion un elemento:");
  prueba_borrar_en_posicion(lista, &contador, PUDO, posicion0);
  printf("Prueba borrar un elemento:");
  prueba_borrar(lista, &contador, PUDO);
  printf("Prueba borrar un elemento:");
  prueba_borrar(lista, &contador, PUDO);
  printf("Se borra el ultimo elemento de la lista:");
  prueba_borrar(lista, &contador, PUDO);
  printf("Prueba lista vacia:");
  prueba_lista_estado(lista, &contador, VACIA);
  printf("Lista sin elementos:");
  cantidad_almacenada = 0;
  prueba_cantidad_almacenada(lista, &contador, cantidad_almacenada);
  printf("El ultimo elemento es NULL:");
  ultimo_elemento = NULL;
  prueba_ultimo_almacenado(lista, &contador, ultimo_elemento);
  printf("Prueba borrar lista vacia:");
  prueba_borrar(lista, &contador, NO_PUDO);
  printf("Prueba de borrar en posicion lista vacia:");
  prueba_borrar_en_posicion(lista, &contador, NO_PUDO, posicion2);
  lista_destruir(lista);
  if (contador == cantidad_pruebas) {
    printf("Prueba 3: OK\n\n");
    return 1;
  }
  return 0;
}

int DadaUnaListaConMasivosElementos_CuandoInserteYBorre_EntoncesDebeFuncionarBien(){
  int elemento[300000];
  int contador = 0;
  int cantidad_almacenada;
  int cantidad_pruebas = 6;
  void* ultimo_elemento;

  lista_t* lista = lista_crear();

  cantidad_almacenada = 1000;
  for (int i = 0; i < cantidad_almacenada; i++) {
    elemento[i] = i;
    lista_insertar(lista, &elemento[i]);
  }
  printf("Prueba insertar 1000 elementos:");
  ultimo_elemento = &elemento[999];
  prueba_masiva_insertar(lista, &contador, cantidad_almacenada, ultimo_elemento);
  for (int i = cantidad_almacenada; i > 0; i--) {
    lista_borrar(lista);
  }
  printf("Prueba borrar 1000 elementos:");
  ultimo_elemento = NULL;
  prueba_ultimo_almacenado(lista, &contador, ultimo_elemento);
  
  lista_destruir(lista);
  lista = lista_crear();

  cantidad_almacenada = 700;
  for (int i = 0; i < cantidad_almacenada; i++) {
    elemento[i] = i;
    lista_insertar(lista, &elemento[i]);
  }
  printf("Prueba insertar 700 elementos:");
  ultimo_elemento = &elemento[699];
  prueba_masiva_insertar(lista, &contador, cantidad_almacenada, ultimo_elemento);
  for (int i = cantidad_almacenada; i > 0; i--) {
    lista_borrar(lista);
  }
  printf("Prueba borrar 700 elementos:");
  ultimo_elemento = NULL;
  prueba_ultimo_almacenado(lista, &contador, ultimo_elemento);

  lista_destruir(lista);
  lista = lista_crear();

  cantidad_almacenada = 500;
  for (int i = 0; i < cantidad_almacenada; i++) {
    elemento[i] = i;
    lista_insertar(lista, &elemento[i]);
  }
  printf("Prueba insertar 500 elementos:");
  ultimo_elemento = &elemento[499];
  prueba_masiva_insertar(lista, &contador, cantidad_almacenada, ultimo_elemento);
  for (int i = cantidad_almacenada; i > 0; i--) {
    lista_borrar(lista);
  }
  printf("Prueba borrar 500 elementos:");
  ultimo_elemento = NULL;
  prueba_ultimo_almacenado(lista, &contador, ultimo_elemento);

  lista_destruir(lista);

  if (contador == cantidad_pruebas) {
    printf("prueba 4: OK\n\n");
    return 1;
  }
  return 0; 
}

int DadaUnaListaNULL_CuandoLaPasoALasFunciones_DebenDevolverSusValoresPredeterminados() {
  int contador = 0;
  int elemento = 21, cantidad_nula = 0;
  size_t posicion = 3;
  void* ultimo_elemento = NULL;
  int cantidad_pruebas = 7;

  lista_t* lista = NULL;
  printf("Prueba insertar en lista NULL:");
  prueba_insertar(lista, &contador, &elemento, NO_PUDO);
  printf("Prueba insertar en posicion lista NULL:");
  prueba_insertar_en_posicion(lista, &contador, &elemento, NO_PUDO, posicion);
  printf("Prueba borrar en lista NULL:");
  prueba_borrar(lista, &contador, NO_PUDO);
  printf("Prueba borrar de posicion en lista NULL:");
  prueba_borrar_en_posicion(lista, &contador, NO_PUDO, posicion);
  printf("Prueba lista vacia:");
  prueba_lista_estado(lista, &contador, VACIA);
  printf("Prueba cantidad en lista NULL:");
  prueba_cantidad_almacenada(lista, &contador, cantidad_nula);
  printf("El ultimo elemento de la lista es NULL:");
  prueba_ultimo_almacenado(lista, &contador, ultimo_elemento);
  lista_destruir(lista);

  if (contador == cantidad_pruebas) {
    printf("prueba 5: OK\n\n");
    return 1;
  }
  return 0;
}

int DadaUnaLista_CuandoUseElIteradorExterno_EntoncesDevolveraLoEsperado() {
  int contador = 0;
  int cantidad_pruebas = 9;  

  lista_t* lista = lista_crear();
  
  char a='a', b='b', c='c', d='d', w='w';
  
  lista_insertar(lista, &a);
  lista_insertar(lista, &c);
  lista_insertar_en_posicion(lista, &d, 100);
  lista_insertar_en_posicion(lista, &b, 1);
  lista_insertar_en_posicion(lista, &w, 4);
  
  lista_borrar_de_posicion(lista, 4);

  lista_iterador_t* iterador = lista_iterador_crear(lista);
  printf("Prueba de iterador siguiente:");
  prueba_tiene_iterador_siguiente(iterador, &contador, TIENE);
  printf("Prueba iterador siguiente esperado:");
  prueba_iterador_siguiente(iterador, &contador, &a);
  printf("Prueba de iterador siguiente:");
  prueba_tiene_iterador_siguiente(iterador, &contador, TIENE);
  printf("Prueba iterador siguiente esperado:");
  prueba_iterador_siguiente(iterador, &contador, &b);
  printf("Prueba de iterador siguiente:");
  prueba_tiene_iterador_siguiente(iterador, &contador, TIENE);
  printf("Prueba iterador siguiente esperado:");
  prueba_iterador_siguiente(iterador, &contador, &c);
  printf("Prueba de iterador siguiente:");
  prueba_tiene_iterador_siguiente(iterador, &contador, TIENE);
  printf("Prueba iterador siguiente esperado:");
  prueba_iterador_siguiente(iterador, &contador, &d);
  printf("Prueba de iterador siguiente:");
  prueba_tiene_iterador_siguiente(iterador, &contador, NO_TIENE);

  lista_iterador_destruir(iterador);
  lista_destruir(lista);

  if (contador == cantidad_pruebas) {
    printf("prueba 6: OK\n\n");
    return 1;
  }
  return 0;
}

int DadaUnaListaYUnIteradorNULL_CuandoLosPasoALasFunciones_DebenDevolverLosValoresPredeterminados() {
  int contador = 0;
  int cantidad_pruebas = 3;
  void* elemento_esperado = NULL;

  lista_t* lista = NULL;
  lista_iterador_t* iterador = lista_iterador_crear(lista);

  printf("Prueba de crear iterador con lista NULL:");
  prueba_iterador_NULL(iterador, &contador);
  printf("Prueba con iterador NULL tiene siguiente:");
  prueba_tiene_iterador_siguiente(iterador, &contador, NO_TIENE);
  printf("Prueba con iterador NULL elemento siguiente esperado:");
  prueba_iterador_siguiente(iterador, &contador, elemento_esperado);
  lista_iterador_destruir(iterador);

  if (contador == cantidad_pruebas) {
    printf("prueba 7: OK\n\n");
    return 1;
  }
  return 0;
}

int main(){
  int pruebas_aprobadas = 0, cantidad_prueba = 8;

  pruebas_aprobadas += mini_pruebas();
  printf("\n\n\n\n");
  pruebas_aprobadas += DadaUnaCantidadVaridadDeElementos_CuandoInserteYBorre_EntoncesVeremosSiFuncionaComoLosEsperabamos();
  printf("\n\n\n\n");
  pruebas_aprobadas += DadaUnaListaVacia_CuandoBorre_EntoncesDevolveraNULL();
  printf("\n\n\n\n");
  pruebas_aprobadas += DadaUnaCantidadPequeniaDeElementos_CuandoInsertoEnPosicionYBorroEnPosicion_EntoncesDevolveraLosValoresEsperados();
  printf("\n\n\n\n");
  pruebas_aprobadas += DadaUnaListaConMasivosElementos_CuandoInserteYBorre_EntoncesDebeFuncionarBien();
  printf("\n\n\n\n");
  pruebas_aprobadas += DadaUnaListaNULL_CuandoLaPasoALasFunciones_DebenDevolverSusValoresPredeterminados();
  printf("\n\n\n\n");
  pruebas_aprobadas += DadaUnaLista_CuandoUseElIteradorExterno_EntoncesDevolveraLoEsperado();
  printf("\n\n\n\n");
  pruebas_aprobadas += DadaUnaListaYUnIteradorNULL_CuandoLosPasoALasFunciones_DebenDevolverLosValoresPredeterminados();
  printf("\n\n\n\n");
  if(pruebas_aprobadas == cantidad_prueba) {
    printf("Pasaste %i/%i pruebas\n", pruebas_aprobadas, cantidad_prueba);
  } else {
    printf("No aprobaste la totalidad de las pruebas, Pasaste %i/%i pruebas\n", pruebas_aprobadas, cantidad_prueba);
  }
  return 0;
}

/**************************************************************************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
***************************************************************************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
**************************************************************************************************************************************************************/


void prueba_masiva_insertar(lista_t* lista, int* contador, int cantidad, void* elemento) {
  if(lista_ultimo(lista) == elemento && !lista_vacia(lista) && lista_elementos(lista) == cantidad) {
    printf(" APROBADA\n");
    (*contador)++;
  } else {
    printf(" DESAPROBADA\n");
  }
}

void prueba_lista_estado(lista_t* lista, int* contador, int estado) {
  if(lista_vacia(lista) == estado) {
    printf(" APROBADA\n");
    (*contador)++;
  } else {
    printf(" DESAPROBADA\n");
  }
}

void prueba_insertar(lista_t* lista, int* contador, void* elemento, int insertar) {
  if (lista_insertar(lista, elemento) == insertar){
    printf(" APROBADA\n");
    (*contador)++;
  } else {
    printf(" DESAPROBADA\n");
  }
}

void prueba_insertar_en_posicion (lista_t* lista, int* contador, void* elemento, int insertar, size_t posicion) {
  if (lista_insertar_en_posicion(lista, elemento, posicion) == insertar){
    printf(" APROBADA\n");
    (*contador)++;
  } else {
    printf(" DESAPROBADA\n");
  }
}

void prueba_cantidad_almacenada(lista_t* lista, int* contador, int cantidad){
  if(lista_elementos(lista) == cantidad) {
    printf(" APROBADA\n");
    (*contador)++;
  } else {
    printf(" DESAPROBADA\n");
  }
}

void prueba_ultimo_almacenado(lista_t* lista, int* contador, void* elemento) {
  if(lista_ultimo(lista) == elemento) {
    printf(" APROBADA\n");
    (*contador)++;
  } else {
    printf(" DESAPROBADA\n");
  }
}

void prueba_borrar(lista_t* lista, int* contador, int borrar) {
  if(lista_borrar(lista) == borrar) {
    printf(" APROBADA\n");
    (*contador)++;
  } else {
    printf(" DESAPROBADA\n");
  }
}

void prueba_borrar_en_posicion(lista_t* lista, int* contador, int borrar, size_t posicion) {
  if(lista_borrar_de_posicion(lista, posicion) == borrar) {
    printf(" APROBADA\n");
    (*contador)++;
  } else {
    printf(" DESAPROBADA\n");
  }
}

void prueba_tiene_iterador_siguiente(lista_iterador_t* iterador, int* contador, int itero) {
  if(lista_iterador_tiene_siguiente(iterador) == itero) {
    printf(" APROBADA\n");
    (*contador)++;
  } else {
    printf(" DESAPROBADA\n");
  }
}

void prueba_iterador_siguiente(lista_iterador_t* iterador, int* contador, void* elemento) {
  if(lista_iterador_siguiente(iterador) == elemento) {
    printf(" APROBADA\n");
    (*contador)++;
  } else {
    printf(" DESAPROBADA\n");
  } 
}

void prueba_iterador_NULL(lista_iterador_t* iterador, int* contador) {
  if(iterador == NULL) {
    printf(" APROBADA\n");
    (*contador)++;
  } else {
    printf(" DESAPROBADA\n");
  } 
}