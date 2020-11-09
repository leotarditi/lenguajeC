#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "laberinto.h"
#include "copa.h"

#define TAMANIO 15
#define PARED '#'
#define VACIO ' '
#define TOTAL_AYUDAS 10
#define TOTAL_OBSTACULOS 10
#define DERECHA 'd'
#define IZQUIERDA 'a'
#define ARRIBA 'w'
#define ABAJO 's'

#define JUGADOR 'J'
#define RIVAL 'G'
#define COPA 'C'
#define POCIONES 'P'
#define IMPEDIMENTA 'I'
#define RIDDIKULUS 'R'
#define ESCREGUTO 'E'
#define ACROMANTULA 'A'
#define BOGGART 'B'
#define ESFINGE 'F'

#define MUERTO 0
#define GANE 1
#define PERDI -1
#define VIDA_MAXIMA 50
#define POSICION_PERMITIDA 10
#define POSICION_INVALIDA -1
#define DANIO_ESCREGUTO 20
#define DANIO_ACROMANTULA 10 
#define DANIO_BOGGART 15
#define AUMENTA_POCIONES 15
#define CANTIDAD_OBSTACULOS 3
#define CANTIDAD_AYUDAS 6

/*
 * Inicializará todas las estructuras con los valores correspondientes,
 * creará el laberinto, posicionará todos los elementos, etc.
 */
void inicializar_laberinto(juego_t* juego);

/*
 * Determinará si el caracter ingresado es válido, esto es, es el caracter ‘a’ o 
 * ‘s’ o ‘d’ o ‘w’ y además el jugador puede moverse en esa dirección, o sea, 
 * hay pasillo.
 */
bool es_movimiento_valido(juego_t* juego, char tecla);

/*
 * Moverá el jugador hacia la dirección especificada.
 * Dicho movimiento es válido.
 */
void mover_jugador(jugador_t* jugador, char direccion);

/*
 * Moverá el rival a la próxima posición.
 */
void mover_rival(juego_t* juego);

/*
 * Actualizará el juego. Restará vida si el jugador está sobre un obstáculo 
 * o lo eliminará si cuenta con el hechizo, aprenderá hechizos y todo lo 
 * que pueda suceder luego de un turno.
 */
void actualizar_juego(juego_t* juego);

/*
 * Devolverá el estado del juego, 1 ganado, 0 en curso, -1 perdido.
 */
int estado_juego(juego_t juego);

/*
 * Devolverá una coordenada aleatoria dentro del rango TAMANIOxTAMANIO.
 * No valida que dicha coordenada coincida con un pasillo ni que exista 
 * otro objeto en esa posición.
 */
coordenada_t posicion_aleatoria();

/*
 * Actualizará la matriz mostrada al usuario, con los elementos presentes 
 * en el juego.
 */
void actualizar_laberinto(juego_t juego, char laberinto[TAMANIO][TAMANIO]);

/*
 * Mostrará el laberinto por pantalla.
 */
void mostrar_laberinto(char laberinto[TAMANIO][TAMANIO]);

/*
 * Mostrará la copa por pantalla.
 */
void mostrar_copa (juego_t juego, char laberinto[TAMANIO][TAMANIO]);


//PRE: el laberinto venga lleno de espacios vacios.
void inicializar_paredes_laberinto(char laberinto[TAMANIO][TAMANIO]);
//POS: llena los espacios vacios con al azar # que simbolizan paredes.


//PRE: el laberinto original con sus paredes correspondientes y el laberinto auxiliar este vacio.
void inicializar_copa (juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]);
/*
 *	POS: teniendo en cuenta los lugares donde hay paredes del laberinto original,
 *	crea una posicion aleatoria de la copa y la ubica en el laberinto auxiliar.
*/


//PRE:  el laberinto original con sus paredes correspondientes y el laberinto auxiliar tenga la copa. 
void inicializar_obstaculos (juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]);
/*
 *	POS: teniendo en cuenta los lugares donde hay paredes del laberinto original y
 *	los espacios vacios que tiene el laberinto auxiliar,
 *	crea una posicion aleatoria para uno de los obstaculos ,lo ubica en el laberinto auxiliar
 *	y vuelve a controlar el laberinto original y el auxiliar.
*/

/*
 *	PRE:  el laberinto original con sus paredes correspondientes,
 *	y el laberinto auxiliar posea la copa y los obstaculos.
*/ 
void inicializar_ayudas (juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]);
/*
 *	POS: teniendo en cuenta los lugares donde hay paredes del laberinto original y
 *	los espacios vacios que tiene el laberinto auxiliar,
 *	crea una posicion aleatoria para una de las ayudas, la ubica en el laberinto auxiliar
 *	y vuelve a controlar el laberinto original y el auxiliar.
*/

/*
 *	PRE:  el laberinto original con sus paredes correspondientes,
 *	el laberinto auxiliar tenga la copa, los obstaculos y las ayudas,
 *	y la funcion de posicion absoluta para el jugador funcione correctamente.
*/ 
void inicializar_jugador (juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]);
/*
 *	POS: teniendo en cuenta los lugares donde hay paredes del laberinto original y
 *	los espacios vacios que tiene el laberinto auxiliar,
 *	y que la posicion absoluta entre la copa y el jugador sea mayor a 10,
 *	crea una posicion aleatoria para el jugador ,lo ubica en el laberinto auxiliar.
*/ 


//PRE: la posicion de la copa y el jugador esten inicializadas.
int posicion_absoluta_jugador (juego_t* juego, jugador_t jugador);
//POS: devuelve la distancia absoluta entre el jugador y la copa.


/*
 *	PRE:  el laberinto original con sus paredes correspondientes,
 *	el laberinto auxiliar tenga la copa, los obstaculos y las ayudas,
 *	y la funcion de posicion absoluta para el rival funcione correctamente.
*/ 
void inicializar_rival (juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]);
/*
 *	POS: teniendo en cuenta los lugares donde hay paredes del laberinto original y
 *	los espacios vacios que tiene el laberinto auxiliar,
 *	y que la posicion absoluta entre la copa y el rival sea mayor a 10,
 *	crea una posicion aleatoria para el rival ,lo ubica en el laberinto auxiliar.
*/


//PRE: la posicion de la copa y el rival esten inicializadas.
int posicion_absoluta_rival (juego_t* juego, rival_t rival);
//POS: devuelve la distancia absoluta entre el rival y la copa.


//PRE: la columna debe tenes un valor correspondiente y el laberinto original tengas sus paredes
bool puede_moverse_jugador_derecha (int columna, juego_t* juego);
/*
 *	POS: teniendo en cuenta la columna y las paredes del laberinto original,
 *	devuelve verdadero si el jugador puede moverse hacia la derecha y 
 *	falso si no puede moverse hacia esa direccion.
*/


//PRE: la columna debe tenes un valor correspondiente y el laberinto original tengas sus paredes
bool puede_moverse_jugador_izquierda (int columna, juego_t* juego);
/*
 *	POS: teniendo en cuenta la columna y las paredes del laberinto original,
 *	devuelve verdadero si el jugador puede moverse hacia la izquierda y 
 *	falso si no puede moverse hacia esa direccion.
*/


//PRE: la columna debe tenes un valor correspondiente y el laberinto original tengas sus paredes
bool puede_moverse_jugador_arriba (int fila, juego_t* juego);
/*
 *	POS: teniendo en cuenta la columna y las paredes del laberinto original,
 *	devuelve verdadero si el jugador puede moverse hacia arriba y 
 *	falso si no puede moverse hacia esa direccion.
*/


//PRE: la columna debe tenes un valor correspondiente y el laberinto original tengas sus paredes
bool puede_moverse_jugador_abajo (int fila, juego_t* juego);
/*
 *	POS: teniendo en cuenta la columna y las paredes del laberinto original,
 *	devuelve verdadero si el jugador puede moverse hacia abajo y 
 *	falso si no puede moverse hacia esa direccion.
*/


//PRE: la columna debe tenes un valor correspondiente y el laberinto original tengas sus paredes
bool puede_moverse_rival_derecha (int columna, juego_t* juego);
/*
 *	POS: teniendo en cuenta la columna y las paredes del laberinto original,
 *	devuelve verdadero si el rival puede moverse hacia la derecha y 
 *	falso si no puede moverse hacia esa direccion.
*/


//PRE: la columna debe tenes un valor correspondiente y el laberinto original tengas sus paredes
bool puede_moverse_rival_izquierda (int columna, juego_t* juego);
/*
 *	POS: teniendo en cuenta la columna y las paredes del laberinto original,
 *	devuelve verdadero si el rival puede moverse hacia la izquierda y 
 *	falso si no puede moverse hacia esa direccion.
*/


//PRE: la columna debe tenes un valor correspondiente y el laberinto original tengas sus paredes
bool puede_moverse_rival_arriba (int fila, juego_t* juego);
/*
 *	POS: teniendo en cuenta la columna y las paredes del laberinto original,
 *	devuelve verdadero si el rival puede moverse hacia arriba y 
 *	falso si no puede moverse hacia esa direccion.
*/


//PRE: la columna debe tenes un valor correspondiente y el laberinto original tengas sus paredes
bool puede_moverse_rival_abajo (int fila, juego_t* juego);
/*
 *	POS: teniendo en cuenta la columna y las paredes del laberinto original,
 *	devuelve verdadero si el rival puede moverse hacia abajo y 
 *	falso si no puede moverse hacia esa direccion.
*/

/*
 *	PRE: que la funcion de moverse hacia abajo del rival funciona correctamente
 *	y la cantidad de pasos este inicializada al igual que la varible se movio
*/
void mover_rival_abajo (juego_t* juego, rival_t* rival, int* cantidad_pasos, bool* se_movio);
/*
 *	POS: teniendo en cuenta lo que devuelve la funcion de moverse rival hacia abajo
 *	y la cantidad de pasos, movera al rival hacia la direccion especificada,
 *	modificara las variables pasadas por referencias y la direccion de este,
 *	utilizando las instrucciones dadas por la catedra.
*/

/*
 *	PRE: que la funcion de moverse hacia arriba del rival funciona correctamente
 *	y la cantidad de pasos este inicializada al igual que la varible se movio
*/
void mover_rival_arriba (juego_t* juego, rival_t* rival, int* cantidad_pasos, bool* se_movio);
/*
 *	POS: teniendo en cuenta lo que devuelve la funcion de moverse rival hacia abajo
 *	y la cantidad de pasos, movera al rival hacia la direccion especificada,
 *	modificara las variables pasadas por referencias y la direccion de este,
 *	utilizando las instrucciones dadas por la catedra.
*/

/*
 *	PRE: que la funcion de moverse hacia la derecha del rival funciona correctamente
 *	y la cantidad de pasos este inicializada al igual que la varible se movio
*/
void mover_rival_derecha (juego_t* juego, rival_t* rival, int* cantidad_pasos, bool* se_movio);
/*
 *	POS: teniendo en cuenta lo que devuelve la funcion de moverse rival hacia abajo
 *	y la cantidad de pasos, movera al rival hacia la direccion especificada,
 *	modificara las variables pasadas por referencias y la direccion de este,
 *	utilizando las instrucciones dadas por la catedra.
*/

/*
 *	PRE: que la funcion de moverse hacia la izquierda del rival funciona correctamente
 *	y la cantidad de pasos este inicializada al igual que la varible se movio
*/
void mover_rival_izquierda (juego_t* juego, rival_t* rival, int* cantidad_pasos, bool* se_movio);
/*
 *	POS: teniendo en cuenta lo que devuelve la funcion de moverse rival hacia abajo
 *	y la cantidad de pasos, movera al rival hacia la direccion especificada,
 *	modificara las variables pasadas por referencias y la direccion de este,
 *	utilizando las instrucciones dadas por la catedra.
*/

//PRE: las ayudas, el elemento a borrar y el tope, tengas valores incializados
void eliminar_ayudas (ayuda_t ayudas[TOTAL_AYUDAS], int elemento_a_borrar, int* tope);
/* 
 *	POS: utilizando la funcion que nos enseño la catedra, esta funcion lo que hace es:
 *	buscar donde se localiza la posicion del elemento a borrar,
 *	y a partir de ahi comenzar a correr todos los elementos siguientes en un lugar anterior,
 *	para luego disminuir en uno el tope.
*/

//PRE: los obstaculos, el elemento a borrar y el tope, tengan valores inicilizados
void eliminar_obstaculos (obstaculo_t obstaculos[TOTAL_OBSTACULOS], int elemento_a_borrar, int* tope);
/* 
 *	no es posible utilizar una misma funcion para eliminar obstaculos y ayudas porque sus
 *	estucturas son diferentes.
 *	POS: utilizando la funcion que nos enseño la catedra, esta funcion lo que hace es:
 *	buscar donde se localiza la posicion del elemento a borrar,
 *	y a partir de ahi comenzar a correr todos los elementos siguientes en un lugar anterior,
 *	para luego disminuir en uno el tope.
*/

/*
 *	PRE: la posicion y las variables requeridas de la estructura juego esten inicilizadas
 *	la funcion eliminar obstaculo funcione correctamente.
*/
void actualizar_obstaculos (juego_t* juego, int posicion);
/*
 *	POS: respetando las instrucciones que nos dio la catedra y utlizando la posicion
 *	esta funcion nos permite restar vida al jugador segun que obstaculo pise
 *	el jugador, o no, si este no tiene efecto y luego eliminarlo.
*/ 

/*
 *	PRE: la posicion y las variables requeridas de la estructura juego esten inicilizadas
 *	la funcion eliminar ayuda funcione correctamente.
*/
void actualizar_ayudas (juego_t* juego, int posicion, int* tope);
/*
 *	POS: respetando las instrucciones que nos dio la catedra y utlizando la posicion
 *	esta funcion nos permite sumar vida al jugador segun que ayuda pise
 *	el jugador, o guardarla en su vector de ayudas y luego eliminarlo.
*/ 

//PRE: el laberinto debe tenes todos los elementos correspondientes
void limpiar_laberinto (char laberinto[TAMANIO][TAMANIO]); 
/*
 *	POS: lo que hace esta funcion es limpiar el laberinto para que no queden rastros
 *	de movimientos anteriores para que luego la funcion actualizar pueda colocarlos
 *	nuevamente, teniendo en cuenta sus nuevas posiciones
*/

//PRE: ambas posiciones deben estar inicializadas.
bool coincide_posicion (coordenada_t posicion_1, coordenada_t poscion_2);
/*
 *	POS: compara las filas y columnas de dos posiciones para luego
 *	devolver verdadero si estas coincides y falso sino.
*/

//PRE: el laberinto original tenga las paredes
void copiar_paredes(juego_t juego, char laberinto[TAMANIO][TAMANIO]);
//POS: lo que hace esta funcion es llenar de paredes el laberinto.


void inicializar_laberinto(juego_t* juego) {
	juego->jugador.codigo = JUGADOR;
	juego->jugador.vida = VIDA_MAXIMA;
	juego->jugador.tope_ayudas = 0;
	juego->rival.codigo = RIVAL;
	juego->rival.direccion = DERECHA;
	juego->rival.cantidad_pasos = 0;
	juego->copa.codigo = COPA;
	juego->obstaculos[0].codigo = ESCREGUTO;
	juego->obstaculos[0].danio = DANIO_ESCREGUTO;
	juego->obstaculos[1].codigo = ACROMANTULA;
	juego->obstaculos[1].danio = DANIO_ACROMANTULA;
	juego->obstaculos[2].codigo = BOGGART;
	juego->obstaculos[2].danio = DANIO_BOGGART;
	juego->tope_obstaculos = CANTIDAD_OBSTACULOS;
	juego->ayudas[0].codigo = IMPEDIMENTA;
	juego->ayudas[0].vida_a_recuperar = 0;
	juego->ayudas[1].codigo = RIDDIKULUS;
	juego->ayudas[1].vida_a_recuperar = 0;
	juego->ayudas[2].codigo = POCIONES;
	juego->ayudas[2].vida_a_recuperar = AUMENTA_POCIONES;
	juego->ayudas[3].codigo = POCIONES;
	juego->ayudas[3].vida_a_recuperar = AUMENTA_POCIONES;
	juego->ayudas[4].codigo = POCIONES;
	juego->ayudas[4].vida_a_recuperar = AUMENTA_POCIONES;
	juego->ayudas[5].codigo = ESFINGE;
	juego->ayudas[5].vida_a_recuperar = 0;
	juego->tope_ayudas = CANTIDAD_AYUDAS;
	char laberinto[TAMANIO][TAMANIO];
	char laberinto_auxiliar[TAMANIO][TAMANIO];
	limpiar_laberinto(laberinto_auxiliar);

	inicializar_paredes_laberinto(laberinto);
	for (int i = 0; i < TAMANIO; i ++) {
		for (int j = 0; j < TAMANIO; j++) {
			juego->laberinto_original[i][j] = laberinto[i][j];
		}
	}
	inicializar_copa(juego, laberinto_auxiliar);
	inicializar_obstaculos(juego, laberinto_auxiliar);
	inicializar_ayudas(juego, laberinto_auxiliar);
	inicializar_jugador(juego, laberinto_auxiliar);
	inicializar_rival(juego, laberinto_auxiliar);
}


bool es_movimiento_valido(juego_t* juego, char tecla) {
	
	if ((tecla == DERECHA) && (puede_moverse_jugador_derecha(juego->jugador.posicion.col+1, juego))) {
		return true;
	} else if ((tecla == IZQUIERDA) && (puede_moverse_jugador_izquierda(juego->jugador.posicion.col-1, juego))) {
		return true;
	} else if ((tecla == ARRIBA) && (puede_moverse_jugador_arriba(juego->jugador.posicion.fil-1, juego))) {
		return true;
	} else if ((tecla == ABAJO) && (puede_moverse_jugador_abajo(juego->jugador.posicion.fil+1, juego))) {
		return true;
	} 
	return false;
}


void mover_jugador(jugador_t* jugador, char direccion) {
	
	if (direccion == DERECHA) {
		jugador->posicion.col = (jugador->posicion.col + 1);
	} else if (direccion == IZQUIERDA) {
		jugador->posicion.col = (jugador->posicion.col - 1);
	} else if (direccion == ARRIBA) {
		jugador->posicion.fil = (jugador->posicion.fil - 1);
	} else if (direccion == ABAJO) {
		jugador->posicion.fil = (jugador->posicion.fil + 1);
	}
}


void mover_rival(juego_t* juego) {
	bool se_movio = false;

	while (!se_movio) {
		if (juego->rival.direccion == DERECHA) {
			mover_rival_derecha(juego, &juego->rival, &juego->rival.cantidad_pasos, &se_movio);
		} else if (juego->rival.direccion == ABAJO) {
			mover_rival_abajo(juego, &juego->rival, &juego->rival.cantidad_pasos, &se_movio);
		} else if (juego->rival.direccion == IZQUIERDA) {
			mover_rival_izquierda(juego, &juego->rival, &juego->rival.cantidad_pasos, &se_movio);
		} else if (juego->rival.direccion == ARRIBA) {
			mover_rival_arriba(juego, &juego->rival, &juego->rival.cantidad_pasos, &se_movio);
		}
	}
}


void actualizar_juego(juego_t* juego) {
	int posicion_obstaculos;
	int posicion_ayudas;
		
	juego->jugador.vida = (juego->jugador.vida - 3);
	for (int i = 0; i < juego->tope_obstaculos; i ++) {
		if (coincide_posicion(juego->jugador.posicion, juego->ayudas[i].posicion)) {
			posicion_ayudas = i;
			actualizar_ayudas (juego,posicion_ayudas,&juego->jugador.tope_ayudas);
		}
	}

	for (int j = 0; j < juego->tope_ayudas; j ++) {
		if (coincide_posicion(juego->jugador.posicion, juego->obstaculos[j].posicion)) {
			posicion_obstaculos = j;
			actualizar_obstaculos (juego,posicion_obstaculos);
		}
	}
}


int estado_juego(juego_t juego) {
	if (coincide_posicion(juego.jugador.posicion, juego.copa.posicion)) {
		return GANE;
	} else if (coincide_posicion(juego.rival.posicion, juego.copa.posicion)) {
		return PERDI;
	} else if (juego.jugador.vida < MUERTO) {
		return PERDI;
	}
	return 0;
}


coordenada_t posicion_aleatoria() {
	coordenada_t posicion;
	posicion.fil = rand() % TAMANIO;
	posicion.col = rand() % TAMANIO;
	return posicion;
}


void actualizar_laberinto(juego_t juego, char laberinto[TAMANIO][TAMANIO]) {
	limpiar_laberinto (laberinto);
	copiar_paredes (juego, laberinto);
	for (int i = 0; i < juego.tope_obstaculos; i ++) {
		laberinto[juego.obstaculos[i].posicion.fil][juego.obstaculos[i].posicion.col] = juego.obstaculos[i].codigo;
	}
	for (int i = 0; i < juego.tope_ayudas; i ++) {
		laberinto[juego.ayudas[i].posicion.fil][juego.ayudas[i].posicion.col] = juego.ayudas[i].codigo;
	}
	laberinto[juego.rival.posicion.fil][juego.rival.posicion.col] = juego.rival.codigo;
	laberinto[juego.jugador.posicion.fil][juego.jugador.posicion.col] = juego.jugador.codigo;
}


void mostrar_laberinto(char laberinto[TAMANIO][TAMANIO]) {
	for (int i = 0; i < TAMANIO; i ++) {
		for (int j = 0; j < TAMANIO; j ++) {
			printf("%c", laberinto[i][j]);
		}
		printf("\n");
	}
}


void mostrar_copa (juego_t juego, char laberinto[TAMANIO][TAMANIO]) {
	laberinto[juego.copa.posicion.fil][juego.copa.posicion.col] = juego.copa.codigo;
}

//************************************************************************************************************************************************************//
//############################################################################################################################################################//
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//

void inicializar_copa (juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]) {
	
	do {
		juego->copa.posicion = posicion_aleatoria();
	} while(juego->laberinto_original[juego->copa.posicion.fil][juego->copa.posicion.col] == PARED);
	
	laberinto_auxiliar[juego->copa.posicion.fil][juego->copa.posicion.col] = juego->copa.codigo;
}
void inicializar_obstaculos (juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]) {
	
	for (int i=0; i < juego->tope_obstaculos; i++) {
		do {
			juego->obstaculos[i].posicion = posicion_aleatoria();
		} while((juego->laberinto_original[juego->obstaculos[i].posicion.fil][juego->obstaculos[i].posicion.col] == PARED)
			|| (laberinto_auxiliar[juego->obstaculos[i].posicion.fil][juego->obstaculos[i].posicion.col] != VACIO)); 
		
		laberinto_auxiliar[juego->obstaculos[i].posicion.fil][juego->obstaculos[i].posicion.col] = juego->obstaculos[i].codigo;
	}
}
void inicializar_ayudas (juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]) {
	
	for (int i=0; i < juego->tope_ayudas; i++) {
		do {
			juego->ayudas[i].posicion = posicion_aleatoria();
		} while((juego->laberinto_original[juego->ayudas[i].posicion.fil][juego->ayudas[i].posicion.col] == PARED)
			|| (laberinto_auxiliar[juego->ayudas[i].posicion.fil][juego->ayudas[i].posicion.col] != VACIO));

		(laberinto_auxiliar)[juego->ayudas[i].posicion.fil][juego->ayudas[i].posicion.col] = juego->ayudas[i].codigo;
	}
}
void inicializar_jugador (juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]) {
	
	do {
		juego->jugador.posicion = posicion_aleatoria();
	} while((juego->laberinto_original[juego->jugador.posicion.fil][juego->jugador.posicion.col] == PARED)
		|| (laberinto_auxiliar[juego->jugador.posicion.fil][juego->jugador.posicion.col] != VACIO)
		|| (posicion_absoluta_jugador (juego, juego->jugador) <= POSICION_PERMITIDA));
	
	(laberinto_auxiliar)[juego->jugador.posicion.fil][juego->jugador.posicion.col] = juego->jugador.codigo;
}
int posicion_absoluta_jugador (juego_t* juego, jugador_t jugador) {
	
	int diferencia_posicion = abs(juego->copa.posicion.col - jugador.posicion.col) + abs(juego->copa.posicion.fil - jugador.posicion.fil);
	return diferencia_posicion;
}
void inicializar_rival (juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]) {
	
	do {
		juego->rival.posicion = posicion_aleatoria();
	} while((juego->laberinto_original[juego->rival.posicion.fil][juego->rival.posicion.col] == PARED)
		|| (laberinto_auxiliar[juego->rival.posicion.fil][juego->rival.posicion.col] != VACIO)
		|| (posicion_absoluta_rival (juego, juego->rival) <= POSICION_PERMITIDA));
	
	(laberinto_auxiliar)[juego->rival.posicion.fil][juego->rival.posicion.col] = juego->rival.codigo;
}
int posicion_absoluta_rival (juego_t* juego, rival_t rival) {
	
	int diferencia_posicion = abs(juego->copa.posicion.col - rival.posicion.col) + abs(juego->copa.posicion.fil - rival.posicion.fil);
	return diferencia_posicion;
}



bool coincide_posicion (coordenada_t posicion_1, coordenada_t posicion_2) {
	if ((posicion_1.col == posicion_2.col) && (posicion_1.fil == posicion_2.fil)) {
		return true;
	}
	return false;
}



bool puede_moverse_jugador_abajo(int fila, juego_t* juego) {
	
	if ((fila < TAMANIO) && (juego->laberinto_original[juego->jugador.posicion.fil+1][juego->jugador.posicion.col] != PARED)) {
		return true;
	}
	return false;
}
bool puede_moverse_jugador_arriba(int fila, juego_t* juego) {
	
	if ((fila > POSICION_INVALIDA) && (juego->laberinto_original[juego->jugador.posicion.fil-1][juego->jugador.posicion.col] != PARED)) {
		return true;
	} 
	return false;
}
bool puede_moverse_jugador_derecha(int columna, juego_t* juego) {
	
	if ((columna < TAMANIO)  && (juego->laberinto_original[juego->jugador.posicion.fil][juego->jugador.posicion.col+1] != PARED)) {
		return true;
	} 
	return false;
}
bool puede_moverse_jugador_izquierda(int columna, juego_t* juego) {
	
	if (columna > POSICION_INVALIDA  && (juego->laberinto_original[juego->jugador.posicion.fil][juego->jugador.posicion.col-1] != PARED)) {
		return true;
	}
	return false;
}



void mover_rival_derecha(juego_t* juego, rival_t* rival, int* cantidad_pasos, bool* se_movio) {
	
	if (puede_moverse_rival_derecha(juego->rival.posicion.col+1, juego)) {
		rival->posicion.col = (rival->posicion.col + 1);
		(*se_movio) = true;
		(*cantidad_pasos) ++;
	} else {
		juego->rival.direccion = ABAJO;
		(*cantidad_pasos) = 0;
	}
	if ((*cantidad_pasos) == 4) {
		juego->rival.direccion = ABAJO;
		(*cantidad_pasos) = 0;
	}
}
void mover_rival_abajo(juego_t* juego, rival_t* rival, int* cantidad_pasos, bool* se_movio) {
	
	if (puede_moverse_rival_abajo(juego->rival.posicion.fil+1, juego)) {
		rival->posicion.fil = (rival->posicion.fil + 1);
		(*se_movio) = true;
		(*cantidad_pasos) ++;
	} else {
		juego->rival.direccion = IZQUIERDA;
		(*cantidad_pasos) = 0;
	}
	if ((*cantidad_pasos) == 4) {
		juego->rival.direccion = IZQUIERDA;
		(*cantidad_pasos) = 0;
	}
}
void mover_rival_izquierda(juego_t* juego, rival_t* rival, int* cantidad_pasos, bool* se_movio) {
	
	if (puede_moverse_rival_izquierda(juego->rival.posicion.col-1, juego)) {
		rival->posicion.col = (rival->posicion.col - 1);
		(*se_movio) = true;
		(*cantidad_pasos) ++;
	} else {
		juego->rival.direccion = ARRIBA;
		(*cantidad_pasos) = 0;
	}
	if ((*cantidad_pasos) == 4) {
		juego->rival.direccion = ARRIBA;
		(*cantidad_pasos) = 0;
	}
}
void mover_rival_arriba(juego_t* juego, rival_t* rival, int* cantidad_pasos, bool* se_movio) {
	if (puede_moverse_rival_arriba(juego->rival.posicion.fil-1, juego)) {
		rival->posicion.fil = (rival->posicion.fil - 1);
		(*se_movio) = true;
		(*cantidad_pasos) ++;
	} else {
		juego->rival.direccion = DERECHA;
		(*cantidad_pasos) = 0;
	}
	if ((*cantidad_pasos) == 4) {
		juego->rival.direccion = DERECHA;
		(*cantidad_pasos) = 0;
	}
}
bool puede_moverse_rival_abajo(int fila, juego_t* juego) {
	
	if ((fila < TAMANIO) && (juego->laberinto_original[juego->rival.posicion.fil+1][juego->rival.posicion.col] != PARED)) {
		return true;
	}
	return false;
}
bool puede_moverse_rival_arriba(int fila, juego_t* juego) {
	
	if ((fila > POSICION_INVALIDA) && (juego->laberinto_original[juego->rival.posicion.fil-1][juego->rival.posicion.col] != PARED)) {
		return true;
	} 
	return false;
}
bool puede_moverse_rival_derecha(int columna, juego_t* juego) {
	
	if ((columna < TAMANIO)  && (juego->laberinto_original[juego->rival.posicion.fil][juego->rival.posicion.col+1] != PARED)) {
		return true;
	} 
	return false;
}
bool puede_moverse_rival_izquierda(int columna, juego_t* juego) {
	
	if (columna > POSICION_INVALIDA  && (juego->laberinto_original[juego->rival.posicion.fil][juego->rival.posicion.col-1] != PARED)) {
		return true;
	}
	return false;
}



void actualizar_obstaculos (juego_t* juego, int posicion) {
	
	if (juego->obstaculos[posicion].codigo == ESCREGUTO) {
		if(juego->jugador.tope_ayudas > 0) {
			for (int i = 0; i < juego->jugador.tope_ayudas; i ++) {
				if (juego->jugador.ayudas[i].codigo == IMPEDIMENTA) { 
					eliminar_obstaculos(&juego->obstaculos[posicion], juego->obstaculos[posicion].codigo, &juego->tope_obstaculos);
				}
			}
		} else {
			juego->jugador.vida = (juego->jugador.vida - juego->obstaculos[posicion].danio);
			eliminar_obstaculos(&juego->obstaculos[posicion], juego->obstaculos[posicion].codigo, &juego->tope_obstaculos);
		}
	} else if (juego->obstaculos[posicion].codigo == BOGGART) {
		if(juego->jugador.tope_ayudas > 0) {
			for (int i = 0; i < juego->jugador.tope_ayudas; i ++) {
				if (juego->jugador.ayudas[i].codigo == RIDDIKULUS) { 
					eliminar_obstaculos(&juego->obstaculos[posicion], juego->obstaculos[posicion].codigo, &juego->tope_obstaculos);
				}
			}
		} else {
			juego->jugador.vida = (juego->jugador.vida - juego->obstaculos[posicion].danio);
			eliminar_obstaculos(&juego->obstaculos[posicion], juego->obstaculos[posicion].codigo, &juego->tope_obstaculos);
		}
	} else if (juego->obstaculos[posicion].codigo == ACROMANTULA) {
		juego->jugador.vida = (juego->jugador.vida - juego->obstaculos[posicion].danio);
		eliminar_obstaculos(&juego->obstaculos[posicion], juego->obstaculos[posicion].codigo, &juego->tope_obstaculos);
	}
}
void actualizar_ayudas (juego_t* juego, int posicion, int* tope) {
	char laberinto[TAMANIO][TAMANIO];
	
	if (juego->ayudas[posicion].codigo == IMPEDIMENTA) {
		juego->jugador.vida = (juego->jugador.vida + juego->ayudas[posicion].vida_a_recuperar);
		juego->jugador.ayudas[juego->jugador.tope_ayudas] = juego->ayudas[posicion];
		(*tope) ++;
		eliminar_ayudas (&juego->ayudas[posicion], juego->ayudas[posicion].codigo, &juego->tope_ayudas);
	} else if (juego->ayudas[posicion].codigo == RIDDIKULUS) {
		juego->jugador.vida = (juego->jugador.vida + juego->ayudas[posicion].vida_a_recuperar);
		juego->jugador.ayudas[juego->jugador.tope_ayudas] = juego->ayudas[posicion];
		(*tope) ++;
		eliminar_ayudas (&juego->ayudas[posicion], juego->ayudas[posicion].codigo, &juego->tope_ayudas);
	} else if (juego->ayudas[posicion].codigo == POCIONES) {
		juego->jugador.vida = (juego->jugador.vida + juego->ayudas[posicion].vida_a_recuperar);
		if (juego->jugador.vida > VIDA_MAXIMA) {
			juego->jugador.vida = VIDA_MAXIMA;
		}
		eliminar_ayudas (&juego->ayudas[posicion], juego->ayudas[posicion].codigo, &juego->tope_ayudas);
	} else if (juego->ayudas[posicion].codigo == ESFINGE) {
		juego->jugador.vida = (juego->jugador.vida + juego->ayudas[posicion].vida_a_recuperar);
		mostrar_copa (*juego,laberinto);
		eliminar_ayudas (&juego->ayudas[posicion], juego->ayudas[posicion].codigo, &juego->tope_ayudas);
	}
}
void eliminar_ayudas (ayuda_t ayudas[TOTAL_AYUDAS], int elemento_a_borrar, int* tope) {
	bool esta = false;
	int i = 0;
	int posicion = 0;

	while ((i < *tope) && (!esta)) {
		if (ayudas[i].codigo == elemento_a_borrar) {
			esta = true;
			posicion = i;
		}
		i++;
	}
	if (esta) {
		for (int i = posicion; i < *tope-1; i++) {
			ayudas[i] = ayudas[i+1];
		}
		(*tope) --;
	}
}
void eliminar_obstaculos (obstaculo_t obstaculos[TOTAL_OBSTACULOS], int elemento_a_borrar, int* tope) {
	bool esta = false;
	int i = 0;
	int posicion = 0;

	while ((i < *tope) && (!esta)) {
		if (obstaculos[i].codigo == elemento_a_borrar) {
			esta = true;
			posicion = i;
		}
		i++;
	}
	if (esta) {
		for (int i = posicion; i < *tope-1; i++) {
			obstaculos[i] = obstaculos[i+1];
		}
		(*tope) --;
	}	
}



void limpiar_laberinto(char laberinto[TAMANIO][TAMANIO]) {
	for (int i = 0; i < TAMANIO; i ++) {
		for (int j = 0; j < TAMANIO; j ++) {
			if (laberinto[i][j] != COPA) {
				laberinto[i][j] = VACIO;
			}
		}
	}
}



void copiar_paredes(juego_t juego, char laberinto[TAMANIO][TAMANIO]) {
	for (int i = 0; i < TAMANIO; i ++) {
		for (int j = 0; j < TAMANIO; j++) {
			laberinto[i][j] = juego.laberinto_original[i][j];
		}
	}
}
