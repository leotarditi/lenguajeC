#include <stdio.h>
#define MAX_NOMBRE 200
#define MAX_FECHA 7
#define CRUCIO 1
#define IMPERIUS 2

typedef struct preso {
	char nombre[MAX_NOMBRE];
	unsigned int edad;
	char conducta; // B buena, R regular o M mala
	unsigned int pabellon;
	unsigned int celda;
	char fecha[MAX_FECHA]; //formato aaaamm
	int maldicion_realizada; //1 crucio, 2 imperius
} preso_t;

int leer_archivo_texto(FILE* archivo, preso_t* actual){
  return fscanf(archivo, "%[^\n]\n%u\n%c\n%u\n%u\n%s\n%i\n\n", actual->nombre, &actual->edad, &actual->conducta,
		&actual->pabellon, &actual->celda, actual->fecha, &actual->maldicion_realizada);
}
void escribir_archivo_binario(FILE* archivo, preso_t preso){
  fwrite(&preso, sizeof(preso_t), 1, archivo);
}

void crear_archivos(FILE* archivo_bin1, FILE* archivo_bin2, FILE* archivo_txt) {
	preso_t actual;
	int leidos = leer_archivo_texto(archivo_txt, &actual);
	while(leidos == 7) {
		if(actual.maldicion_realizada == CRUCIO) {
			escribir_archivo_binario(archivo_bin1, actual);
		} else if(actual.maldicion_realizada == IMPERIUS) {
			escribir_archivo_binario(archivo_bin2, actual);
		}
		leidos = leer_archivo_texto(archivo_txt, &actual);
	}
}


int main(){
	FILE* archivo = fopen("archivo.txt", "r");
	if (!archivo){
		printf("el archivo no puedo abrirse\n");
		return -1;
	}
	FILE* crucio = fopen("crucio.dat", "w");
	FILE* imperius = fopen("imperius.dat", "w");
	crear_archivos(crucio, imperius, archivo);
	fclose(crucio);
	fclose(imperius);
	fclose(archivo);
	return 0;	
}