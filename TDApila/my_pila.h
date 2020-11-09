#ifndef __MY_PILA_H__
#define __MY_PILA_H__

//PRE:	la pila debe existir y estar bien creada
int redimensionar_pila(pila_t** pila);
/*	POS: esta funcion se encarga de aumentar el vector de elementos,
 *	cuando esta llena aumenta al doble de su capacidad
 *	y cuando esta usando menos de la mitad de su capacidad disminuye su capacidad 
 *	a la mitad de su capacidad anterior
*/

#endif /* __MY_PILA_H__ */