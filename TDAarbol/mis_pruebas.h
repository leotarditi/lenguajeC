#ifndef __MIS_PRUEBAS_H__
#define __MIS_PRUEBAS_H__

//El nombre de las funciones es descriptivo para saber lo que hace
int miniprueba();
int DadoUnArbolNULLCuandoRealiceLasFuncionesDevolveraLosValoresPreestablecidos();
int DadoUnArbolVacioCuandoRealiceLasFuncionesDevolveraLosValoresPreestablecidos();
int DadoUnArbolDeEnterosCuandoRealiceLasFuncionesDevolveraLosValoresPreestablecidos();
int DadoUnArbolDeLetrasCuandoRealiceLasFuncionesDevolveraLosValoresPreestablecidos();
int DadoUnArbolLlenoDeAlumnosCuandoRealiceLasDiferentesFuncionesDevolveraLosValoresEsperados();
int DadoUnArbolDegeneraCuandoRealiceLasDiferentesFuncionesDevolveraLoPreestablecido();
int DadaUnaCantidadMasivaDeNumerosCuandoLosInserteYBorreDelArbolDevolveraLosValoresEstablecidos();


void prueba_insertar(abb_t* arbol, void* elemento, int inserto, int* contador);
//POS:	se encarga de ver si la funcion arbol_insertar devuelve el valor esperado segun se pase si pudo o no insertar

void prueba_borrar(abb_t* arbol, void* elemento, int borro, int* contador);
//POS:	se encarga de ver si la funcion arbol_borrar devuelve el valor esperado segun se pase si pudo o no borrar

void prueba_buscar(abb_t* arbol, void* elemento, int encontro, int* contador);
//POS:	se encarga de ver si la funcion arbol_buscar devuelve el valor esperado segun se pase si pudo o no encontrar

void prueba_raiz(abb_t* arbol, void* elemento_raiz, int* contador);
//POS:	se encarga de ver si la funcion arbol_raiz devuelve el elemento de la raiz pasado

void prueba_estado(abb_t* arbol, int estado, int* contador);
//POS:	se encarga de ver si el arbol esta vacio o no

void imprimir_recorridos(abb_t* arbol, void** array, int tamanio_array, int (*funcion_recorrido)(abb_t*,void**,int), int tipo_dato);
//POS:	imprime el recorrido segun la funcion de recorrido pasada y el tipo de dato que se le ingrese

#endif /* __MIS_PRUEBAS_H__ */