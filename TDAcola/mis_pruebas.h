#ifndef __MIS_PRUEBAS_H__
#define __MIS_PRUEBAS_H__

// La descripcion de las pruebas esta explicito en sus nombres
int mini_prueba();
int DadaUnaCantidadVaridadDeElemento_CuandoEncoleYDesencole_EntoncesVeremosSiFuncionaComoLosEsperabamos ();
int DadaUnaColaVacia_CuandoDesencole_EntoncesDevolveraNULL();
int DadaUnaCantidadPequeniaDeElementos_CuandoEncoleYDesencole_EntoncesDevolveraLosValoresEsperados();
int DadaUnaColaConMasivosElementos_CuandoEncolerYDesencole_EntoncesDebeFuncionarBien();
int DadaUnaColaNULL_CuandoLaPasoALasFunciones_DebenDevolverSusValoresPredeterminados ();

//PRE:	recibir un contador inicializado
void prueba_cola_estado(cola_t* cola, int* contador, int estado);
/*	POS: esta funcion de encarga de probar si las funcion cola_vacia
 *	devuelve el estado pasado por parametro
*/

//PRE:	recibir un contador inicializado
void prueba_encolar(cola_t* cola, int* contador, void* elemento, int encolar);
/*	POS: esta funcion de encarga de probar si las funcion cola_encolar
 *	devuelve el pudo o no encolar segun en el entero que le pasamos por parametro
*/

//PRE:	recibir un contador inicializado
void prueba_cantidad_almacenada(cola_t* cola, int* contador, int cantidad);
/*	POS: esta funcion de encarga de probar si las funcion cola_cantidad
 *	devuelve el valor que deberia pasado como parametro
*/

//PRE:	recibir un contador inicializado
void prueba_primero_almacenado(cola_t* cola, int* contador);
/*	POS: esta funcion de encarga de probar si las funcion cola_primero
 *	devuelve el elemento almacenado en el inicio
*/

//PRE:	recibir un contador inicializado
void prueba_desencolar(cola_t* cola, int* contador, int desencolar);
/*	POS: esta funcion de encarga de probar si las funcion cola_desencolar
 *	devuelve el pudo o no desencolar segun en el entero que le pasamos por parametro
*/

//PRE:	recibir un contador inicializado
void prueba_primero_null(cola_t* cola, int* contador);
/*	POS: esta funcion de encarga de probar si las funcion cola_primero
 *	devuelve el NULL esperado
*/

//PRE:	recibir un contador inicializado
void prueba_masiva_encolar(cola_t* cola, int* contador, int cantidad);
//POS:	controla si la carga masiva de elemento devuelve los valores esperados

//OBSERVACION: no use un desencolar masivo porque solo devia comprobar si el valor de cola_primero era NULL

#endif /* __MIS_PRUEBAS_H__ */