#ifndef __MIS_PRUEBAS_H__
#define __MIS_PRUEBAS_H__

// La descripcion de las pruebas esta explicito en sus nombres
int mini_prueba();
int DadaUnaCantidadVaridadDeElementos_CuandoInserteYBorre_EntoncesVeremosSiFuncionaComoLosEsperabamos();
int DadaUnaListaVacia_CuandoBorre_EntoncesDevolveraNULL();
int DadaUnaCantidadPequeniaDeElementos_CuandoInsertoEnPosicionYBorroEnPosicion_EntoncesDevolveraLosValoresEsperados();
int DadaUnaListaConMasivosElementos_CuandoInserteYBorre_EntoncesDebeFuncionarBien();
int DadaUnaListaNULL_CuandoLaPasoALasFunciones_DebenDevolverSusValoresPredeterminados();
int DadaUnaLista_CuandoUseElIteradorExterno_EntoncesDevolveraLoEsperado();
int DadaUnaListaYUnIteradorNULL_CuandoLosPasoALasFunciones_DebenDevolverLosValoresPredeterminados();


//PRE:	recibir un contador inicializado
void prueba_lista_estado(lista_t* lista, int* contador, int estado);
/*	POS: esta funcion de encarga de probar si las funcion lista_vacia
 *	devuelve el estado pasado por parametro.
*/

//PRE:	recibir un contador inicializado
void prueba_insertar(lista_t* lista, int* contador, void* elemento, int insertar);
/*	POS: esta funcion de encarga de probar si las funcion lista_insertar
 *	devuelve el pudo o no insertar segun el entero que le pasamos por parametro
*/

//PRE:	recibir un contador inicializado y un elemento valido
void prueba_insertar_en_posicion(lista_t* lista, int* contador, void* elemento, int insertar, size_t posicion);
/*	POS: esta funcion de encarga de probar si las funcion lista_insertar_en_posicion
 *	devuelve el pudo o no insertar en la posicion correspondiente segun el entero que le pasamos por parametro
*/

//PRE:	recibir un contador inicializado
void prueba_cantidad_almacenada(lista_t* lista, int* contador, int cantidad);
/*	POS: esta funcion de encarga de probar si las funcion lista_elementos
 *	devuelve el valor que deberia pasado como parametro
*/

//PRE:	recibir un contador inicializado
void prueba_ultimo_almacenado(lista_t* lista, int* contador, void* elemento);
/*	POS: esta funcion de encarga de probar si las funcion lista_ultimo
 *	devuelve el elemento almacenado en el ultimo nodo
*/

//PRE:	recibir un contador inicializado
void prueba_borrar(lista_t* lista, int* contador, int borrar);
/*	POS: esta funcion de encarga de probar si las funcion lista_borrar
 *	devuelve el pudo o no borrar segun en el entero que le pasamos por parametro
*/

//PRE:	recibir un contador inicializado
void prueba_borrar_en_posicion(lista_t* lista, int* contador, int borrar, size_t posicion);
/*	POS: esta funcion de encarga de probar si las funcion lista_borrar_de_posicion
 *	devuelve el pudo o no borrar en la posicion pasada segun en el entero que le pasamos por parametro
*/

//PRE:	recibir un contador inicializado
void prueba_masiva_insertar(lista_t* lista, int* contador, int cantidad, void* elemento);
//POS:	controla si la carga masiva de elemento devuelve los valores esperados

//PRE:	recibir un contador inicializado
void prueba_tiene_iterador_siguiente(lista_iterador_t* iterador, int* contador, int itero);
/*	POS: esta funcion se encarga de ver si la funcion lista_iterador_tiene_siguiente
 *	pudo hacerlo o no segun correponde el valor de itero pasado como parametro
*/

//PRE:	recibir un contador inicializado
void prueba_iterador_siguiente(lista_iterador_t* iterador, int* contador, void* elemento);
/*	POS: esta funcion se encarga de ver si la funcion lista_iterador_siguiente
 *	devuelve el elemento esperado segun lo pasado por parametro
*/

//PRE:	recibir un contador inicializado
void prueba_iterador_NULL(lista_iterador_t* iterador, int* contador);
// se encarga de ver si el iterador es NULL

//OBSERVACION: no use un borrar masivo porque solo devia comprobar si el valor de lista_ultimo era NULL

#endif /* __MIS_PRUEBAS_H__ */