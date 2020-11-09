#include "abb.h"
#include "my_abb.h"
#include "cola.h"
#include "lista.h"
#include "trono.h"
#include "simulacion.h"
#include <stdio.h>

const char SIMULACION = 'S';
const char AGREGAR = 'A';
const char LISTAR = 'L';
const char EXTINTAS = 'E';
const char FINALIZAR = 'Q';

char mensaje_comienzo(char* letras_comienzo) {
	printf("Presiona S si desea iniciar la simulación, A si desea agregar una casa al arbol, L si desear ver las casas ordenadas \n"); 
	printf("por cantidad de integrantes, E si desea ver las casas extintas o Q si desea finalizar la ejecucion: ");
	scanf (" %c", letras_comienzo);
	printf("\n");
	return (*letras_comienzo);
}

int main() {
	char letras_comienzo;
	int anios_a_transcurrir;
	char nombre_archivo[50];

	letras_comienzo = mensaje_comienzo(&letras_comienzo);
	while(letras_comienzo != SIMULACION && letras_comienzo != AGREGAR && letras_comienzo != LISTAR && 
		letras_comienzo != EXTINTAS && letras_comienzo != FINALIZAR) {
		letras_comienzo = mensaje_comienzo(&letras_comienzo);
	}

	strcpy(nombre_archivo, "casa.txt");
	reino_t* reino = crear_reino(nombre_archivo);
	
	while(letras_comienzo != FINALIZAR) {	
		if(letras_comienzo == SIMULACION) {
			printf("Cuantos anios desea transcurrir: ");
			scanf(" %i", &anios_a_transcurrir);
			printf("\n");
			char* casa_ganadora = simulacion(anios_a_transcurrir, reino);
			if(casa_ganadora == NULL) {
				printf("No hay mas casas. \n\n");
			} else {
				printf("La casa que esta en el trono es: %s \n\n", casa_ganadora);
			}
		} else if (letras_comienzo == AGREGAR) {
			printf("Por favor ingrese el nombre del archivo donde se encuentra la nueva casa: ");
			scanf(" %s", nombre_archivo);
			printf("\n");
			agregar_nueva_casa(nombre_archivo, reino);
		} else if (letras_comienzo == LISTAR) {
			mostrar_casas_por_integrantes(reino);
			printf("\n");
		} else if (letras_comienzo == EXTINTAS) {
			mostrar_casas_extintas(reino);
			printf("\n");
		}	
		letras_comienzo = mensaje_comienzo(&letras_comienzo);
	}
	destruir_reino(reino);
	return 0;
}