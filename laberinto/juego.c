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
#define MOSTRAME_LA_COPA 15
#define GANE 1
#define PERDI -1


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

int main () {
	juego_t juego;
	char laberinto[TAMANIO][TAMANIO];
	char direccion;
	srand((unsigned int) time(NULL));

	inicializar_laberinto(&juego);
	actualizar_laberinto(juego, laberinto);
	mostrar_laberinto(laberinto);
	while (juego.jugador.vida > MUERTO) {
		
		printf("presione d y enter, si desea moverse hacia la derecha,\n");
		printf("presione s y enter, si desea moverse hacia abajo,\n");
		printf("presione a y enter, si desea moverse hacia la izquierda,\n");
		printf("presione w y enter, si desea moverse hacia arriba,\n");
		do {

			printf("espero que presiones bien \n");
			scanf("%c", &direccion);
		} while (!es_movimiento_valido(&juego, direccion)); 
		mover_jugador(&juego.jugador, direccion);
		if (estado_juego(juego) == GANE) {
			
			printf("has ganado esta vez... \n");
			printf("has ganado esta vez... \n");
			printf("has ganado esta vez... \n");
			return estado_juego(juego);
		} else if (estado_juego(juego) == PERDI) {
			
			printf("te ha derrotado una maquina... ): \n");
			printf("eres un loser... ): \n");
			printf("vuelve a intentarlo pededor... ): \n");
			return estado_juego(juego);
		}
		actualizar_juego(&juego);
		mover_rival(&juego);
		actualizar_laberinto(juego, laberinto);
		system ("clear");
		if (juego.jugador.vida > MUERTO) {
			
			printf("la vida del jugador es : %i \n", juego.jugador.vida);
		}
		if (juego.jugador.vida <= MOSTRAME_LA_COPA) {
			mostrar_copa (juego,laberinto);
		}
		mostrar_laberinto(laberinto);
	}
	printf("no llegaste a la copa \n");
	printf("quieres volver a jugar? \n");
	printf("es totalmente gratis... \n");
	return estado_juego(juego);
}