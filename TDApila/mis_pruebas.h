#ifndef __MIS_PRUEBAS_H__
#define __MIS_PRUEBAS_H__

// La descripcion de las pruebas esta explicito en sus nombres
int mini_prueba();
int DadaUnaCantidadVaridadDeElemento_CuandoApileYDesapile_EntoncesVeremosSiFuncionaComoLosEsperabamos();
int DadaUnaPilaVacia_CuandoDesapile_EntoncesDevolveraNULL();
int DadaUnaCantidadPequeniaDeElementos_CuandoApileYDesapile_EntoncesDevolveraLosValoresEsperados();
int DadaUnaPilaConMasivosElementos_CuandoApileYDesapile_EntoncesDebeFuncionarBien();
int DadaUnaPilaNULL_CuandoLaPasoALasFunciones_DebenDevolverSusValoresPredeterminados();

//PRE:	recibir un contador inicializado
void prueba_pila_estado(pila_t* pila, int* contador, int estado);
/*	POS: esta funcion de encarga de probar si las funcion pila_vacia
 *	devuelve el estado pasado por parametro
*/

//PRE:	recibir un contador inicializado
void prueba_apilar(pila_t* pila, int* contador, void* elemento, int apilar);
/*	POS: esta funcion de encarga de probar si las funcion pila_apilar
 *	devuelve el que pudo o no apilar segun en el entero que le pasamos por parametro
*/

//PRE:	recibir un contador inicializado
void prueba_cantidad_almacenada(pila_t* pila, int* contador, int cantidad);
/*	POS: esta funcion de encarga de probar si las funcion pila_cantidad
 *	devuelve el valor que deberia pasado como parametro
*/

//PRE:	recibir un contador inicializado
void prueba_tope_almacenado(pila_t* pila, int* contador);
/*	POS: esta funcion de encarga de probar si las funcion pila_tope
 *	devuelve el elemento almacenado en el tope
*/

//PRE:	recibir un contador inicializado
void prueba_desapilar(pila_t* pila, int* contador, int desapilar);
/*	POS: esta funcion de encarga de probar si las funcion pila_desapilar
 *	devuelve el que pudo o no desapilar segun en el entero que le pasamos por parametro
*/

//PRE:	recibir un contador inicializado
void prueba_tope_null(pila_t* pila, int* contador);
/*	POS: esta funcion de encarga de probar si las funcion pila_tope
 *	devuelve el NULL
*/

//PRE:	recibir un contador inicializado
void prueba_pila_tamanio(pila_t* pila, int* contador, int tamanio);
/*	POS: esta funcion de encarga de probar si el tamanio de la pila
 *	es el esperado segun la funcion redimensionar_pila
*/

//PRE:	recibir un contador inicializado
void prueba_masiva_apilar(pila_t* pila, int* contador, int cantidad, int tamanio);
//POS:	controla se la carga masiva de elemento devuelve los valores esperados

//PRE:	recibir un contador inicializado
void prueba_masiva_desapilar(pila_t* pila, int* contador, int tamanio);
//POS:	controla se la descarga masiva de elemento devuelve los valores esperados

#endif /* __MIS_PRUEBAS_H__ */