#include "hash.h"
#include "hash_iterador.h"
#include "lista_modificada.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void prueba_insertar(hash_t* hash, const char* clave, void* elemento, int inserto, int* contador);
/*
 *	POS: se encarga de ver si la funcion hash_insertar devuelve el valor esperado segun se pase si pudo o no insertar
 *	y aumenta en contador en caso de pasar la prueba correctamente
*/


void prueba_quitar(hash_t* hash, const char* clave, int quito, int* contador);
/*
 *	POS: se encarga de ver si la funcion hash_quitar devuelve el valor esperado segun se pase si pudo o no borrar
 *	y aumenta en contador en caso de pasar la prueba correctamente
*/

void prueba_obtener(hash_t* hash, const char* clave, void* elemento, int* contador);
/*
 *	POS: se encarga de ver si la funcion hash_obtener devuelve el elemento esperado segun el elemento pasado por parametro
 *	y aumenta en contador en caso de pasar la prueba correctamente
*/

void prueba_contiene(hash_t* hash, const char* clave, bool contiene, int* contador);
/*
 *	POS: se encarga de ver si la funcion hash_contiene devuelve el valor esperado segun este o no este esa clave
 *	y aumenta en contador en caso de pasar la prueba correctamente
*/

void prueba_cantidad(hash_t* hash, int cantidad, int* contador);
/*
 *	POS: se encarga de ver si la funcion hash_cantida devuelve la cantidad esperada
 *	y aumenta en contador en caso de pasar la prueba correctamente
*/

void prueba_iterador_crear(hash_t* hash, hash_iterador_t* iterador, int* contador);
/*
 *	POS: se encarga de ver si la funcion hash_iterador_crear devuelve el iterador esperado
 *	y aumenta en contador en caso de pasar la prueba correctamente
*/

void prueba_iterador_siguiente(hash_iterador_t* iterador, const char* clave, int* contador);
/*
 *	POS: se encarga de ver si la funcion hash_iterador_siguiente devuelve la clave esperada
 *	y aumenta en contador en caso de pasar la prueba correctamente
*/

void prueba_iterador_tiene_siguiente(hash_iterador_t* iterador, bool tiene, int* contador);
/*
 *	POS: se encarga de ver si la funcion hash_iterador_tiene_siguiente devuelve si el iterador tiene o no siguiente
 *	y aumenta en contador en caso de pasar la prueba correctamente
*/

void prueba_masiva(int contador_errores, int cantidad_errores_esperados, int* contador);
/*
 *	POS: se encarga de ver si las primitivas del hash no tienen errores al aplicarle muchos elementos
 *	y aumenta en contador en caso de pasar la prueba correctamente
*/

//El nombre de las funciones es descriptivo para saber lo que hace
int DadoUnHashVacioCuandoRealiceLasDiferentesFuncionesDevolveraLoPreestablecidoEnElContrato();
int DadoUnHashVacioCuandoItereEseHashDevolveraLoPreestablecidoEnElContrato();
int DadaUnaCantidadDeClavesYElementosCuandoInserteDevolveraLosValoresEsperados();
int DadaUnaCantidadDeClavesConElmentosCuandoQuieraInsertarLaMismaClaveConDistintoElementoDevolveraLaClaveConElUltimoElementoIngresado();
int DadoUnaCantidadDeClavesConElementosAlmacenadosEnMemoriaDinamicaCuandoLosReemplazeYDestruyanDevolveranLosValoresEsperados();
int DadaUnaCantidadDeClavesYElementosCuandoBorreDevolveraLosValoresEsperados();
int DadaUnaGranCantidadDeElementosCuandoLosInsertoyBorroDeUnHashDevolveraLosValoresEsperados(size_t largo);
int DadoUnHashCuandoUseElIteradorDevolveraLosValoresEsperados();
int DadoUnHashConMuchosElementosCuandoUseElIteradorDevolveraLosValoresEsperados(size_t largo);
int DadoUnHashNULLCuandoRealiceLasDiferentesFuncionesDevolveraLoPreestablecidoEnElContrato();