#ifndef __LISTA_CON_COLA_H__
#define __LISTA_CON_COLA_H__

//PRE:	que el elemento no sea null (no se fija si la cola es null porque ya lo verifica el encolar)
int insertar_al_final(cola_t* cola, void* elemento);
//POS:	se encarga de insertar un elemento al final de la lista

//PRE:	aclaro que no es necesario que las colas no sea null ya que es lo verifica el encolar
int cola_copiar(cola_t* original, cola_t* copia);
int copiar_en_dos_colas(cola_t* original, cola_t* copia1, cola_t* copia2);
//POS:	la primera se encarga de copiar los elementos de una cola a otra y la segunda de una cola a ortas dos

#endif /* __LISTA_CON_COLA_H__ */