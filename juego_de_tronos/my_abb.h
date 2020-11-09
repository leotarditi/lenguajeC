#ifndef __MY_ABB_H__
#define __MY_ABB_H__

//PRE:	el arbol, la raiz y el nuevo no sean NULL
void insertar_nodo(abb_t* arbol, nodo_abb_t* raiz, nodo_abb_t* nuevo);
//POS:	esta funcion de encarga de insertar un nuevo nodo de manera recursiva en el lugar que le corresponde

//PRE:	el arbol no sea NULL
int borrar_nodo(abb_t* arbol, nodo_abb_t* nodo);
//POS:	esta funcion de encarga de borrar el nodo pasado como parametro de manera recursiva y devolvera si pudo o no borrar 

//PRE:	el nodo no sea NULL
nodo_abb_t* obtener_padre(nodo_abb_t* raiz, nodo_abb_t* nodo);
//POS:	esta funcion recursiva se encarga de obtener el padre del nodo pasado por parametro y devolvera el padre obtenido

//PRE:	el nodo no sea NULL
nodo_abb_t* obtener_mayor(nodo_abb_t* nodo);
//POS:	esta funcion se encarga de obtener el mayor del subarbol menor, y devolvera el obtenido

//PRE:	el arbol y el elemento no sean NULL
nodo_abb_t* buscar_nodo(abb_t* arbol, nodo_abb_t* raiz, void* elemento);
//POS:	se encarga de buscar un nodo determinado en el arbol, y devolvera el nodo encontrado

//PRE:	ninguno de los elementos pasado como parametros sean NULL
void recorrido_inorden(nodo_abb_t* nodo, void** array, int tamanio_array, int* tamanio_usado);
//POS:	se encarga de llenar el array con lo elementos de manera recursiva e inorden, es decir siguiendo el procedimiento izquierda, nodo, derecha

//PRE:	ninguno de los elementos pasado como parametros sean NULL
void recorrido_preorden(nodo_abb_t* nodo, void** array, int tamanio_array, int* tamanio_usado);
//POS:	se encarga de llenar el array con lo elementos de manera recursiva y preorden, es decir siguiendo el procedimiento nodo, izquierda, derecha

//PRE:	ninguno de los elementos pasado como parametros sean NULL
void recorrido_postorden(nodo_abb_t* nodo, void** array, int tamanio_array, int* tamanio_usado);
//POS:	se encarga de llenar el array con lo elementos de manera recursiva y postorden, es decir siguiendo el procedimiento izquierda, derecha, nodo

//PRE:	el arbol sea distinto de NULL
void destruir(abb_t* arbol, nodo_abb_t* raiz);
//POS:	se encarga de destruir cada uno de los nodos del arbol y luego el arbol

//PRE:	ninguno de los elementos pasado como parametros sean NULL
void recorrido_interno_inorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra, bool* no_sigo);
//POS:	se encarga de realizar el recorrido inorden especificado anteriormente y comprobar en cada caso que la funcion no devuelva true porque habria que cortar el recorrido

//PRE:	ninguno de los elementos pasado como parametros sean NULL
void recorrido_interno_preorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra, bool* no_sigo);
//POS:	se encarga de realizar el recorrido preorden especificado anteriormente y comprobar en cada caso que la funcion no devuelva true porque habria que cortar el recorrido

//PRE:	ninguno de los elementos pasado como parametros sean NULL
void recorrido_interno_postorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra, bool* no_sigo);
//POS:	se encarga de realizar el recorrido postorden especificado anteriormente y comprobar en cada caso que la funcion no devuelva true porque habria que cortar el recorrido

#endif /* __MY_ABB_H__ */