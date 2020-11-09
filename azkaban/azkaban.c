#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NOMBRE 200
#define MAX_FECHA 7
const char BUENA = 'B';
const char REGULAR = 'R';
const char MALA = 'M';
#define ERROR -1
#define ARCHIVO_CRUCIO "crucio.dat"
#define ARCHIVO_CRUCIO_AUXILIAR "crucio_aux.dat"
#define ARCHIVO_IMPERIUS "imperius.dat"
#define ARCHIVO_IMPERIUS_AUXILIAR "imperius_aux.dat"

typedef struct preso {
	char nombre[MAX_NOMBRE];
	unsigned int edad;
	char conducta; // B buena, R regular o M mala
	unsigned int pabellon;
	unsigned int celda;
	char fecha[MAX_FECHA]; //formato aaaamm
	int maldicion_realizada; //1 crucio, 2 imperius
} preso_t;

//	PRE:	se debe haber cargado bien el nombre del archivo perdonables.
size_t perdonables(char nombre_archivo[MAX_NOMBRE]);
/*	
*	POS:	esta funcion se encarga de recibir dos archivos (crucio.dat e imperius.dat)
*	y con estos dos generar un tercer vector con los presos que esten en unos de los dos archivos
*	si este archivo que se genera existe, lo sobreescribe.
*/	

/*
*	PRE:	el nombre del archivo sea el mismo que se genero con el comando perdonables
*	que la fecha contenga año y mes con el formato (aaaamm) y que la conducta sea B (buena),
*	R (regular) o M (mala); otro carecter no servira.
*/
int liberar(char nombre_archivo[MAX_NOMBRE], char fecha[MAX_FECHA], char conducta);
/*
*	POS:	esta funcion recibe el archivo de perdonados (generado en el comando perdonadbles)
*	y genera otro archivo teniendo en cuenta la fecha y la conducta, si la conducta esta dentro
*	de los pedidos y su fecha es igual o anterior a la pedida el preso estara en el archivo de
*	texto de presos a liberar.
*/

/*
*	PRE:	que la fecha sea bien ingresada (explicado en la POS de liberar), y
*	que esta fecha sea la misma que usaron en el comando de liberar.
*/
size_t actualizar(char fecha[MAX_FECHA], char nombre_liberados[MAX_NOMBRE]);
/*
*	POS:	esta funcion lo que hace es actualizar los archivos crucio.dat e 
*	imperius.dat, sacando los registros de los nombres que coincidan con los de
*	la lista de liberados.
*/

/*
*	PRE:	que la fecha y el nombre de liberados sea el mismo que se utilizaron
*	en las funciones anteriores.
*/
int mostrar_liberados(char fecha[MAX_FECHA], char nombre_liberados[MAX_NOMBRE]);
/*
*	POS:	esta funcion imprime por pantalla los nombre que se encuentan en el
*	archivo de texto de liberados.
*/

//	PRE:	exista el archivo ayuda.txt
void ayuda();
//	POS:	esta funcion mostrara un serie de instrucciones para usar este programa.

//	PRE:	que el achivo halla sido inicializado al igual que el preso.
size_t leer_archivo_binario(FILE* archivo, preso_t* preso);
//	POS:	esta funcion lee archivos binario y devuelve 1 si leyo un registro o 0 si llego al final o no pudo leer.

//	PRE:	que el achivo halla sido inicializado al igual que el nombre.
int leer_archivo_texto(FILE* archivo, char nombre[MAX_NOMBRE]);
/*	
*	POS:	esta funcion de encarga de leer archivo de texto con strings separados por enter.
*	devuelve 1 si leyo el nombre o 0 si llego al final o no pudo leer.
*/

//	PRE:	que el achivo halla sido inicializado al igual que el preso.
size_t escribir_archivo_binario(FILE* archivo, preso_t preso);
//	POS:	esta funcion escribe archivos binario y devuelve 1 si escribio un registro o 0 si no tenia espacio para escribir.

//	PRE:	que el achivo halla sido inicializado al igual que el nombre.
int escribir_archivo_texto(FILE* archivo, char nombre[MAX_NOMBRE]);
/*	
*	POS:	esta funcion de encarga de escribir archivo de texto con strings separados por enter.
*	devuelve 1 si escribio el nombre o 0 si no tenia espacio en la memoria para escribir.
*/

//	PRE:	que los file sea inicilizados en la funcion y que el nombre del archivo sea bien cargado.
int abrir_archivos_de_perdonables(FILE** crucio_file, FILE** imperius_file, FILE** perdonables_file, char nombre_archivo[MAX_NOMBRE]);
/*
*	POS:	esta funcion de encarga de abrir todos los archivos necesario para la funcion perdonables
*	y a su vez revisa si estos archivos pueden abrirse, sino tira un mensaje de alerta y cierra los archivos
*	anteriormente abiertos.
*/


//	PRE:	que los archivos sean previamente abiertos segun lo requerido. Y que funcione correctamente la funcion de leer y escribir necesaria.
size_t llenar_archivo_perdonables (FILE* crucio_file, FILE* imperius_file, FILE* perdonables_file);
/*
*	POS:	esta funcion se encarga de llenar el archivo de perdonables con los datos de los
*	presos que se encuentran en tan solo uno de los archivos, es decir es una diferencia
*	simetrica entre los archivos crucio.dat e imperius.dat que estan ordenados por nombre.
*/

//	PRE:	que los archivos esten abiertos.
void cerrar_archivos_de_perdonables(FILE* crucio_file, FILE* imperius_file, FILE* perdonables_file);
//	POS:	esta funcion se encarga de cerra todos los archivos usados, no se revisa si cerro bien porque desde la catedra se nos dio esa indicacion.


//	PRE:	que el nombre del archivo y la fecha este bien cargados.
void armar_nombre_liberados(char nombre_liberados[MAX_NOMBRE], char fecha[MAX_FECHA]);
//	POS:	esta funcion se encarga de crear el nombre del archivo liberados asi, liberados_<fecha>.txt.

//	PRE:	que los file sea inicilizados en la funcion y que el nombre del archivo sea bien cargado.
bool existe_liberado(FILE* liberados_file, char nombre_liberados[MAX_NOMBRE]);
//	POS:	esta funcion se encarga de chequear si existe archivo liberados para evitar sobreescribir.

//	PRE:	que los file sea inicilizados en la funcion y que el nombre de los archivos sea bien cargado.
int abrir_archivos_de_liberados(FILE** perdonables_file, FILE** liberados_file, char nombre_archivo[MAX_NOMBRE], char nombre_liberados[MAX_NOMBRE]);
/*
*	POS:	esta funcion de encarga de abrir todos los archivos necesario para la funcion liberar
*	y a su vez revisa si estos archivos pueden abrirse, sino tira un mensaje de alerta y cierra los archivos
*	anteriormente abiertos.
*/

/*
*	PRE:	que los archivos sea previamente inicializados, esten abiertos segun el uso que le va a dar el usuario,
*	la fecha y la conducta esten bien ingresadas.  Y que funcione correctamente la funcion de leer y escribir necesaria.
*/
int llenar_archivo_liberados(FILE* perdonables_file, FILE* liberados_file, char fecha[MAX_FECHA], char conducta);
/*
*	POS:	esta funcion compara cada uno de los presos perdonables con la fecha y conducta cargada
*	y va llenando el archivo de liberados con los que cumplen las condiciones.
*/

//	PRE:	que la conducta sea bien ingresada
bool conducta_valida (char conducta_a_perdonar, char conducta);
//	POS:	esta funcion revisa este mecanismo B mejor que R mejor que M.

//	PRE:	que los archivos esten abiertos.
void cerrar_archivos_de_liberados(FILE* perdonables_file, FILE* liberados_file);
//	POS:	esta funcion se encarga de cerra todos los archivos usados, no se revisa si cerro bien porque desde la catedra se nos dio esa indicacion.


//	PRE:	que los file sea inicilizados en la funcion y que el nombre del archivo sea bien armado.
int abrir_archivos_de_actualizar(FILE** liberados_file, FILE** crucio_file, FILE** crucio_aux_file, 
	FILE** imperius_file, FILE** imperius_aux_file, char nombre_liberados[MAX_NOMBRE]);
/*
*	POS:	esta funcion de encarga de abrir todos los archivos necesario para la funcion actualizar
*	y a su vez revisa si estos archivos pueden abrirse, sino tira un mensaje de alerta y cierra los archivos
*	anteriormente abiertos.
*/

//	PRE:	que los archivos sea previamente inicializados, esten abiertos segun el uso que le va a dar el usuario,
size_t actualizar_archivos(FILE* file_liberados, FILE* file_crucio, FILE* file_imperius, FILE* archivo_actualizado_crucio, FILE* archivo_actualizado_imperius);
/*	
*	POS:	esta funcion lo que hace es actualizar los archivos de crcio e imperius, generando un archivo actualizado para ambos
*	el funcionamiento se basa en una diferencia entre tres archivos, donde los nombre que aparecen en el archivos de liberados
*	no deberan existir en el nuevo archivo actualizado.
*/

//	PRE:	que los archivos esten abiertos.
void cerrar_archivos_de_actualizar(FILE* liberados_file, FILE* crucio_file, FILE* crucio_aux_file, FILE* imperius_file, FILE* imperius_aux_file);
/*
*	POS:	esta funcion se encarga de cerra todos los archivos usados, no se revisa si cerro bien porque desde la catedra se nos dio esa indicacion.
*	para luego eliminar el archivo de crucio.dat e imperius.dat antiguos y cambiarle el nombre de los crucio e imperius auxiliares,
*	que son donde aparecen solo los presos que no estan en el archivo de liberados, por los de crucio.dat e imperius.dat.
*/


//	PRE:	que el file sea inicilizado en la funcion y que el nombre del archivo sea bien armado.
int abrir_archivo_liberados(FILE** liberados_file, char nombre_liberados[MAX_NOMBRE]);
//	POS:	abre el archivo de liberados para lectura y revisa si fue bien abierto.

//	PRE:	que el archivo este abierto.
void mostrar_liberados_por_pantalla(FILE* liberados_file);
//	POS:	se encarga de mostrar por pantalla los nombre del archivo de liberados.

//	PRE:	que el archivo este abierto.
void cerrar_archivos_liberados(FILE* liberados_file);
//	POS:	esta funcion se encarga de cerra todos los archivos usados, no se revisa si cerro bien porque desde la catedra se nos dio esa indicacion.


size_t perdonables(char nombre_archivo[MAX_NOMBRE]) {
	FILE* crucio_file;
	FILE* imperius_file;
	FILE* perdonables_file;
	int pudo_abrir;
	size_t pudo_llenar;
	pudo_abrir = abrir_archivos_de_perdonables(&crucio_file, &imperius_file, &perdonables_file, nombre_archivo);
	if(pudo_abrir == ERROR) {
		printf("no se pudo abrir todos los archivos\n");
		return 0;
	}
	pudo_llenar = llenar_archivo_perdonables(crucio_file, imperius_file, perdonables_file);
	cerrar_archivos_de_perdonables(crucio_file, imperius_file, perdonables_file);
	return pudo_llenar;
}

int liberar(char nombre_archivo[MAX_NOMBRE], char fecha[MAX_FECHA], char conducta) {
	char nombre_liberados[MAX_NOMBRE];
	armar_nombre_liberados(nombre_liberados, fecha);
	FILE* perdonables_file;
	FILE* liberados_file;
	int pudo_abrir, pudo_llenar;
	bool existe = false;
	existe = existe_liberado(liberados_file, nombre_liberados);
	if(existe) {
		printf("ya existe ese archivo\n");
		return 0;
	}
	pudo_abrir = abrir_archivos_de_liberados(&perdonables_file, &liberados_file, nombre_archivo, nombre_liberados);
	if(pudo_abrir == ERROR) {
		printf("no se pudo abrir todos los archivos\n");
		return 0;
	}
	pudo_llenar = llenar_archivo_liberados(perdonables_file, liberados_file, fecha, conducta);
	cerrar_archivos_de_liberados(perdonables_file, liberados_file);
	return pudo_llenar;
}


size_t actualizar(char fecha[MAX_FECHA], char nombre_liberados[MAX_NOMBRE]) {
	FILE* liberados_file;
	FILE* crucio_file;
	FILE* crucio_aux_file;
	FILE* imperius_file;
	FILE* imperius_aux_file;
	int pudo_abrir;
	size_t pudo_actualizar;
	pudo_abrir = abrir_archivos_de_actualizar(&liberados_file, &crucio_file, &crucio_aux_file, &imperius_file, &imperius_aux_file, nombre_liberados);
	if(pudo_abrir == ERROR) {
		printf("no se pudo abrir todos los archivos\n");
		return 0;
	}
	pudo_actualizar = actualizar_archivos(liberados_file, crucio_file, imperius_file, crucio_aux_file, imperius_aux_file);
	cerrar_archivos_de_actualizar(liberados_file, crucio_file, crucio_aux_file, imperius_file, imperius_aux_file);
	remove("crucio.dat");
	rename("crucio_aux.dat", "crucio.dat");
	remove("imperius.dat");
	rename("imperius_aux.dat", "imperius.dat");
	return pudo_actualizar;
}

int mostrar_liberados(char fecha[MAX_FECHA], char nombre_liberados[MAX_NOMBRE]) {
	FILE* liberados_file;
	int pudo_abrir;
	pudo_abrir = abrir_archivo_liberados(&liberados_file, nombre_liberados);
	if(pudo_abrir == ERROR) {
		printf("no se pudo abrir todos los archivos\n");
		return 0;
	}
	mostrar_liberados_por_pantalla(liberados_file);
	cerrar_archivos_liberados(liberados_file);
	return pudo_abrir;
}

void ayuda() {
	FILE* ayuda_file;
	char oracion[MAX_NOMBRE];
	int leidos;
	ayuda_file = fopen("ayuda.txt", "r");
	leidos = leer_archivo_texto(ayuda_file, oracion);
	while(leidos == 1) {
		printf("%s\n", oracion);
		leidos = leer_archivo_texto(ayuda_file, oracion);
	}
	fclose(ayuda_file);
}


int main(int argc, char *argv[]) {
	if (strcmp(argv[1],"perdonables") == 0 && argc == 3) {
		perdonables(argv[2]);
	} else if (strcmp(argv[1],"liberar") == 0 && argc == 5) {
		liberar(argv[2], argv[3], *argv[4]);
	} else if(strcmp(argv[1], "actualizar") == 0 && argc == 3) {
		char archivo_liberados[MAX_NOMBRE];
		armar_nombre_liberados(archivo_liberados, argv[2]);
		actualizar(argv[2], archivo_liberados);
	} else if(strcmp(argv[1], "mostrar_liberados") == 0 && argc == 3) {
		char archivo_liberados[MAX_NOMBRE];
		armar_nombre_liberados(archivo_liberados, argv[2]);
		mostrar_liberados(argv[2], archivo_liberados);
	} else if (strcmp(argv[1], "ayuda") == 0 && argc == 2) {
		ayuda();
	}
	return 0;
}


/***************************************************************************************************************************************************************
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
***************************************************************************************************************************************************************/


size_t leer_archivo_binario(FILE* archivo, preso_t* preso){
  return fread(preso, sizeof(preso_t), 1, archivo);
}
int leer_archivo_texto(FILE* archivo, char nombre[MAX_NOMBRE]){
  return fscanf(archivo, "%[^\n]\n", nombre);
}
size_t escribir_archivo_binario(FILE* archivo, preso_t preso){
  return fwrite(&preso, sizeof(preso_t), 1, archivo);
}
int escribir_archivo_texto(FILE* archivo, char nombre[MAX_NOMBRE]){
	return fprintf(archivo, "%s\n", nombre);
}



int abrir_archivos_de_perdonables(FILE** crucio_file, FILE** imperius_file, FILE** perdonables_file, char nombre_archivo[MAX_NOMBRE]) {
	(*crucio_file) = fopen(ARCHIVO_CRUCIO, "r");
	if(crucio_file == NULL) {
		printf("no se pudo abrir el archivo crucio \n");
		return -1;
	}
	(*imperius_file) = fopen(ARCHIVO_IMPERIUS, "r");
	if(imperius_file == NULL) {
		printf("no se pudo abrir el archivo imperius \n");
		fclose(*crucio_file);
		return -1;
	}
	(*perdonables_file) = fopen(nombre_archivo, "w");
	if(perdonables_file == NULL) {
		printf("no se pudo abrir el archivo de perdonables \n");
		fclose(*crucio_file);
		fclose(*imperius_file);
		return -1;
	}
	return 1;
}

size_t llenar_archivo_perdonables (FILE* crucio_file, FILE* imperius_file, FILE* perdonables_file) {
	preso_t imperius, crucio;
	size_t crucio_leido, imperius_leido;
	size_t pudo_escribir;
	crucio_leido = leer_archivo_binario(crucio_file, &crucio);
	imperius_leido = leer_archivo_binario(imperius_file, &imperius);
	pudo_escribir = 1;
	while((crucio_leido > 0) && (imperius_leido > 0) && (pudo_escribir)) {
		int comparacion = strcmp(crucio.nombre, imperius.nombre);
		if (comparacion == 0) {
			crucio_leido = leer_archivo_binario(crucio_file, &imperius);
			imperius_leido = leer_archivo_binario(crucio_file, &crucio);
		} else if (comparacion < 0) {
			pudo_escribir = escribir_archivo_binario(perdonables_file, crucio);
			crucio_leido = leer_archivo_binario(crucio_file, &crucio);
		} else {
			pudo_escribir = escribir_archivo_binario(perdonables_file, imperius);
			imperius_leido = leer_archivo_binario(imperius_file, &imperius);
		}
	}
	while((crucio_leido > 0) && (pudo_escribir)) {
		pudo_escribir = escribir_archivo_binario(perdonables_file, crucio);
		crucio_leido = leer_archivo_binario(crucio_file, &crucio);
	}
	while((imperius_leido > 0) && (pudo_escribir)) {
		pudo_escribir = escribir_archivo_binario(perdonables_file, imperius);
		imperius_leido = leer_archivo_binario(imperius_file, &imperius);
	}
	return pudo_escribir;
}

void cerrar_archivos_de_perdonables(FILE* crucio_file, FILE* imperius_file, FILE* perdonables_file) {
	fclose(imperius_file);
	fclose(crucio_file);
	fclose(perdonables_file);
}



void armar_nombre_liberados(char nombre_liberados[MAX_NOMBRE], char fecha[MAX_FECHA]) {
	strcpy(nombre_liberados, "liberados_");
	strcat(nombre_liberados, fecha);
	strcat(nombre_liberados, ".txt");
}

bool existe_liberado(FILE* liberados_file, char nombre_liberados[MAX_NOMBRE]) {
	(liberados_file) = fopen(nombre_liberados, "r");
	if(liberados_file == NULL) {
		return false;
	}
	fclose(liberados_file);
	return true;
}

int abrir_archivos_de_liberados(FILE** perdonables_file, FILE** liberados_file, char nombre_archivo[MAX_NOMBRE], char nombre_liberados[MAX_NOMBRE]) {
	(*perdonables_file) = fopen(nombre_archivo, "r");
	if(perdonables_file == NULL) {
		printf("no se pudo abrir el archivo de perdonables\n");
		return -1;
	}
	(*liberados_file) = fopen(nombre_liberados, "w");
	if(liberados_file == NULL) {
		printf("no se pudo abrir el archivo de liberados\n");
		fclose(*perdonables_file);
		return -1;
	}
	return 1;
}

int llenar_archivo_liberados(FILE* perdonables_file, FILE* liberados_file, char fecha[MAX_FECHA], char conducta) {
	preso_t perdonables;
	size_t leidos = leer_archivo_binario(perdonables_file, &perdonables);
	int pudo_escribir = 1;
	while(leidos > 0 && pudo_escribir) {
		int comparacion_fechas = strcmp (fecha, perdonables.fecha);
		if((comparacion_fechas >= 0) && (conducta_valida(perdonables.conducta, conducta))) {
			pudo_escribir = escribir_archivo_texto(liberados_file, perdonables.nombre);
		}
		leidos = leer_archivo_binario(perdonables_file, &perdonables);
	}
	return pudo_escribir;
}

bool conducta_valida (char conducta_a_perdonar, char conducta) {
	if (conducta == BUENA) {
		if (conducta_a_perdonar == BUENA) {
			return true;
		}
		return false;
	} else if (conducta == REGULAR) {
		if (conducta_a_perdonar == MALA) {
			return false;
		}
		return true;
	}
	return true;
}

void cerrar_archivos_de_liberados(FILE* perdonables_file, FILE* liberados_file) {
	fclose(perdonables_file);
	fclose(liberados_file);
}



int abrir_archivos_de_actualizar(FILE** liberados_file, FILE** crucio_file, FILE** crucio_aux_file, 
	FILE** imperius_file, FILE** imperius_aux_file, char nombre_liberados[MAX_NOMBRE]) {
	(*liberados_file) = fopen(nombre_liberados, "r");
	if(liberados_file == NULL) {
		printf("no se pudo abrir el archivo de liberados\n");
		return 0;
	}
	(*crucio_file) = fopen(ARCHIVO_CRUCIO, "r");
	if(crucio_file == NULL) {
		printf("no se pudo abrir el archivo crucio\n");
		fclose(*liberados_file);
		return 0;
	}
	(*crucio_aux_file) = fopen(ARCHIVO_CRUCIO_AUXILIAR, "w");
	if(crucio_aux_file == NULL) {
		printf("no se pudo abrir el archivo crucio auxiliar\n");
		fclose(*liberados_file);
		fclose(*crucio_file);
		return 0;
	}
	(*imperius_file) = fopen(ARCHIVO_IMPERIUS, "r");
	if(imperius_file == NULL) {
		printf("no se pudo abrir el archivo imperius\n");
		fclose(*liberados_file);
		fclose(*crucio_file);
		fclose(*crucio_aux_file);
		return 0;
	}
	(*imperius_aux_file) = fopen(ARCHIVO_IMPERIUS_AUXILIAR, "w");
	if(imperius_aux_file == NULL) {
		printf("no se pudo abrir el archivo imperius auxiliar\n");
		fclose(*liberados_file);
		fclose(*crucio_file);
		fclose(*crucio_aux_file);
		fclose(*imperius_file);
		return -1;
	}
	return 1;
}

size_t actualizar_archivos(FILE* file_liberados, FILE* file_crucio, FILE* file_imperius, FILE* archivo_actualizado_crucio, FILE* archivo_actualizado_imperius) {
	preso_t crucio, imperius;
	char nombre_liberados[MAX_NOMBRE];
	size_t crucio_leidos, imperius_leidos;
	int liberados_leidos;
	liberados_leidos = leer_archivo_texto(file_liberados, nombre_liberados);
	crucio_leidos = leer_archivo_binario(file_crucio, &crucio);
	imperius_leidos = leer_archivo_binario(file_imperius, &imperius);
	size_t pudo_escribir = 1;
	while((liberados_leidos > 0) && (crucio_leidos > 0) && (imperius_leidos == 1) && (pudo_escribir)) {
		int comparacion_crucio = strcmp(crucio.nombre, nombre_liberados);
		int comparacion_imperius = strcmp(imperius.nombre, nombre_liberados);
		if ((comparacion_crucio == 0) && (comparacion_imperius < 0)) {
			pudo_escribir = escribir_archivo_binario(archivo_actualizado_imperius, imperius);
			imperius_leidos = leer_archivo_binario(file_imperius, &imperius);
		} else if ((comparacion_crucio == 0) && (comparacion_imperius > 0)) {
			liberados_leidos = leer_archivo_texto(file_liberados, nombre_liberados);
			crucio_leidos = leer_archivo_binario(file_crucio, &crucio);
		} else if ((comparacion_crucio < 0) && (comparacion_imperius == 0)) {
			pudo_escribir = escribir_archivo_binario(archivo_actualizado_crucio, crucio);
			crucio_leidos = leer_archivo_binario(file_crucio, &crucio);
		} else if ((comparacion_crucio < 0) && (comparacion_imperius < 0)) {
			pudo_escribir = escribir_archivo_binario(archivo_actualizado_imperius, imperius);
			pudo_escribir = escribir_archivo_binario(archivo_actualizado_crucio, crucio);
			crucio_leidos = leer_archivo_binario(file_crucio, &crucio);
			imperius_leidos = leer_archivo_binario(file_imperius, &imperius);
		}	else if ((comparacion_crucio < 0 && comparacion_imperius > 0)) {
			pudo_escribir = escribir_archivo_binario(archivo_actualizado_crucio, crucio);
			crucio_leidos = leer_archivo_binario(file_crucio, &crucio);
		} else if ((comparacion_crucio > 0) && (comparacion_imperius == 0)) {
			liberados_leidos = leer_archivo_texto(file_liberados, nombre_liberados);
			imperius_leidos = leer_archivo_binario(file_imperius, &imperius);
		} else if ((comparacion_crucio > 0) && (comparacion_imperius > 0)) {
			liberados_leidos = leer_archivo_texto(file_liberados, nombre_liberados);
		} else {
			pudo_escribir = escribir_archivo_binario(archivo_actualizado_imperius, imperius);
			imperius_leidos = leer_archivo_binario(file_imperius, &imperius);
		}
	}
	while((liberados_leidos == 1) && (crucio_leidos > 0) && (pudo_escribir)) {
		int comparacion_crucio = strcmp(crucio.nombre, nombre_liberados);
		if (comparacion_crucio == 0) {
			liberados_leidos = leer_archivo_texto(file_liberados, nombre_liberados);
			crucio_leidos = leer_archivo_binario(file_crucio, &crucio);
		} else if (comparacion_crucio < 0) {
			pudo_escribir = escribir_archivo_binario(archivo_actualizado_crucio, crucio);
			crucio_leidos = leer_archivo_binario(file_crucio, &crucio);
		} else {
			liberados_leidos = leer_archivo_texto(file_liberados, nombre_liberados);
		}
	}
	while((liberados_leidos == 1) && (imperius_leidos > 0) && (pudo_escribir)) {
		int comparacion_imperius = strcmp(imperius.nombre, nombre_liberados);
		if (comparacion_imperius == 0) {
			liberados_leidos = leer_archivo_texto(file_liberados, nombre_liberados);
			imperius_leidos = leer_archivo_binario(file_imperius, &imperius);
		} else if (comparacion_imperius < 0) {
			pudo_escribir = escribir_archivo_binario(archivo_actualizado_imperius, imperius);
			imperius_leidos = leer_archivo_binario(file_imperius, &imperius);
		} else {
			liberados_leidos = leer_archivo_texto(file_liberados, nombre_liberados);
		}
	}
	while((crucio_leidos > 0) && (pudo_escribir)) {
		pudo_escribir = escribir_archivo_binario(archivo_actualizado_crucio, crucio);
		crucio_leidos = leer_archivo_binario(file_crucio, &crucio);
	}
	while((imperius_leidos > 0) && (pudo_escribir)) {
		pudo_escribir = escribir_archivo_binario(archivo_actualizado_imperius, imperius);
		imperius_leidos = leer_archivo_binario(file_imperius, &imperius);
	}
	return pudo_escribir;
}

void cerrar_archivos_de_actualizar(FILE* liberados_file, FILE* crucio_file, FILE* crucio_aux_file, FILE* imperius_file, FILE* imperius_aux_file) {
	fclose(liberados_file);
	fclose(crucio_file);
	fclose(crucio_aux_file);
	fclose(imperius_file);
	fclose(imperius_aux_file);
}



int abrir_archivo_liberados(FILE** liberados_file, char nombre_liberados[MAX_NOMBRE]) {
	*liberados_file = fopen(nombre_liberados, "r");
	if(liberados_file == NULL) {
		printf("no pudo abrir el archivo de liberados\n");
		return -1;
	}
	return 1;
}

void mostrar_liberados_por_pantalla(FILE* liberados_file) {	
	preso_t actual;
	int leidos = leer_archivo_texto(liberados_file, actual.nombre);
	while (leidos == 1) {
		printf("%s\n", actual.nombre);
		leidos = fscanf(liberados_file, "%[^\n]\n", actual.nombre);
	}
}

void cerrar_archivos_liberados(FILE* liberados_file) {
	fclose(liberados_file);
}