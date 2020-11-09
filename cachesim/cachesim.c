#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define FORMATO_LECTURA_TRAZAS "%x: %c %x %i %x\n"
#define ERROR -1
#define PENALTY 100

typedef struct Metricas {
	unsigned loads;
	unsigned stores;
	double totalAccess;
	unsigned readMiss;
	unsigned writeMiss;
	double totalMiss;
	unsigned dirtyReadMisses;
	unsigned dirtyWriteMisses;
	unsigned long bytesRead;
	unsigned long bytesWritten;
	unsigned long ciclesRead;
	unsigned long ciclesWrite;
	double missRateTotal;
} Metricas;

typedef struct Line {
	short dirtyBit;
	short valid;
	unsigned tag;
	// For LRU polity
	unsigned long lastUsed;
} Line;

typedef struct Set {
	Line *lines;
} Set;


typedef struct Cache {
	Metricas metricas;
	unsigned size;
    unsigned setSize;
	unsigned linesPerSet;
	unsigned bytesPerBlock;
	Set *sets;
	unsigned long cicles;
} Cache;

// Creo e iniciliazo la cache
Cache* cacheCreate(unsigned C, unsigned E, unsigned S, unsigned B) {
	Cache *cache;
	cache = (Cache*)calloc(1, sizeof(Cache));
	if(cache == NULL) return NULL;

	cache->size = C;
	cache->linesPerSet = E;
	cache->setSize = S;
	cache->bytesPerBlock = B;
	
	cache->sets = (Set*)calloc(1, sizeof(Set)*(size_t)cache->setSize);
	if (cache->sets == NULL) return NULL;
	
	for(unsigned i=0; i < cache->setSize; i++) {
		cache->sets[i].lines = (Line*)calloc(1, sizeof(Line)*(size_t)cache->linesPerSet);
		if (cache->sets[i].lines == NULL) return NULL;		
	}

	return cache;
}

// Libero la memoria pedida para la cache
void deallocate(Cache *cache) {
	for(unsigned i=0; i < cache->setSize; i++) {
		free(cache->sets[i].lines);
	}
	free(cache->sets);
	free(cache);
}

// La funcion log2 para ints
unsigned log2u(unsigned n) {
    unsigned r=0;
    while (n>>=1) r++;
        return r;
}

// Se fija si un numero es potencia de dos
bool isPowerTwo(unsigned x) {
    return (x != 0) && ((x & (x - 1)) == 0);
}

// Se fija si tres numeros son potencia de dos
bool arePowerTwo(unsigned n1, unsigned n2, unsigned n3) {
	return (isPowerTwo(n1) && isPowerTwo(n2) && isPowerTwo(n3));
}

// Calcula el tag y el set
void calculateTagAndSetValues(uint32_t address, Cache* cache, unsigned *tag, unsigned *set) {
	// Saca cuando ocupa el set, tag y offset en una linea
	unsigned bitSet = log2u(cache->setSize);
	unsigned bitOffset = log2u(cache->bytesPerBlock);
	unsigned bitTag = 32 - bitSet - bitOffset;
	// Crea mascaras para hallar el set y tag
	uint32_t maskTag = (uint32_t)((1 << 31) >> (bitTag - 1));
	uint32_t maskOffset = (uint32_t)(~ ( ((1 << 31) ^ (~0)) << bitOffset));
	uint32_t maskSet = (uint32_t)((~ (maskTag | maskOffset)) >> bitOffset);
	// Saca el tag y set
	*set = (uint32_t)((address >> bitOffset) & maskSet);
	*tag = (uint32_t)(address >> (bitSet + bitOffset));
}

// Evita conflico con la politica LRU
void evictVerbose(uint32_t address, Cache *cache, char operation, unsigned n, unsigned m) {
	unsigned index = 0;
	// Calculo set y tag
	unsigned tag = 0, set = 0;
	calculateTagAndSetValues(address, cache, &tag, &set);
	
	// Busco la ultima linea usada
	unsigned long min = cache->sets[set].lines[0].lastUsed;
	for(unsigned i=1; i < cache->linesPerSet; i++) {
		unsigned long value = cache->sets[set].lines[i].lastUsed;
		if(min > value) {
			min = value;
			index = i;
		}
	}
	
	// Hay un clean miss
	if(cache->sets[set].lines[index].dirtyBit == 0) {
		
		// Actualizo los ciclos aplicando penalidad segun la operacion
		if(operation == 'R') {
			cache->metricas.ciclesRead += PENALTY + 1;
		} else {
			cache->metricas.ciclesWrite += PENALTY + 1;
		}
				
		// Imprimo por pantalla
		short valid = cache->sets[set].lines[index].valid;
		short dirty = cache->sets[set].lines[index].dirtyBit;
		unsigned long lastUsed = cache->sets[set].lines[index].lastUsed;
		unsigned tagAnt = cache->sets[set].lines[index].tag;
		if(n == (unsigned)cache->cicles && n <= m) {
			printf("%i 2a %x %x %i %x %i %i", n, set, tag, index, tagAnt, valid, dirty);
			if(cache->linesPerSet > 1) {
				printf(" %li", lastUsed);
			}
			printf("\n");
		}
		
		// Cambio el dirty en la escritura
		if(operation == 'W') {	
			cache->sets[set].lines[index].dirtyBit = 1;
		}
	
	// Hay un dirty miss
	} else {
		
		// Actualizo los ciclos aplicando penalidad segun la operacion
		if(operation == 'R') {
			cache->metricas.ciclesRead += PENALTY * 2 + 1;
		} else {
			cache->metricas.ciclesWrite += PENALTY * 2 + 1;
		}
			
		// Actualizo los dirty misses segun la operacion
		if(operation == 'R') {
			cache->metricas.dirtyReadMisses++;
		} else {
			cache->metricas.dirtyWriteMisses++;
		}
			
		// Imprimo por pantalla
		short valid = cache->sets[set].lines[index].valid;
		short dirty = cache->sets[set].lines[index].dirtyBit;
		unsigned long lastUsed = cache->sets[set].lines[index].lastUsed;
		unsigned tagAnt = cache->sets[set].lines[index].tag;
		if(n == (unsigned)cache->cicles && n <= m) {
			printf("%i 2b %x %x %i %x %i %i", n, set, tag, index, tagAnt, valid, dirty);
			if(cache->linesPerSet > 1) {
				printf(" %li", lastUsed);
			}
			printf("\n");
		}
		
		// Cambio el dirty en la lectura
		if(operation == 'R') {	
			cache->sets[set].lines[index].dirtyBit = 0;
		}

		// Actualizo los bytes escritos si hay un dirty miss
		cache->metricas.bytesWritten += cache->bytesPerBlock;
	}	
				
	// Cambio tag, valid y lastUsed
	cache->sets[set].lines[index].tag = tag;
	cache->sets[set].lines[index].valid = 1;
	cache->sets[set].lines[index].lastUsed = cache->cicles;
}

void checkCacheVerbose(uint32_t address, Cache *cache, char operation, unsigned n, unsigned m){
	
	// Actualizo la metricas de acceso segun la operacion	
	cache->metricas.totalAccess++;
	if(operation == 'R') {
		cache->metricas.loads++;
	} else {
		cache->metricas.stores++;
	}

	// Calculo set y tag
	unsigned tag = 0, set = 0;
	calculateTagAndSetValues(address, cache, &tag, &set);
	
	for(unsigned i=0; i < cache->linesPerSet; i++) {		
		
		// Si hay un hit
		if(cache->sets[set].lines[i].valid && cache->sets[set].lines[i].tag == tag) {
			
			// Imprimo por pantalla
			short valid = cache->sets[set].lines[i].valid;
			short dirty = cache->sets[set].lines[i].dirtyBit;
			unsigned long lastUsed = cache->sets[set].lines[i].lastUsed;
			if(n == (unsigned)cache->cicles && n <= m) {
				printf("%i 1 %x %x %i %x %i %i", n, set, tag, i, tag, valid, dirty);
				if(cache->linesPerSet > 1) {
					printf(" %li", lastUsed);
				}
				printf("\n");
			}

			// Actualizo ciclos segun operacion
			if(operation == 'R') {
				cache->metricas.ciclesRead++;
			} else {
				cache->metricas.ciclesWrite++;
			}

			// Cambio el dirty cuando escribo
			if(operation == 'W') {	
				cache->sets[set].lines[i].dirtyBit = 1;
			}

			// Actualizo la ultima linea usada
			cache->sets[set].lines[i].lastUsed = cache->cicles;
			return;
		}
	}

	// Actualizo los misses y escribo
	cache->metricas.totalMiss++;
	cache->metricas.bytesRead += cache->bytesPerBlock;
	if(operation == 'R') {
		cache->metricas.readMiss++;	
	} else {
		cache->metricas.writeMiss++;
	}

	for(unsigned i=0; i < cache->linesPerSet; i++) {
		
		// Hay un clean miss
		if(!(cache->sets[set].lines[i].valid)) {
			
			// Actualizo los ciclos aplicando penalidad segun la operacion
			if(operation == 'R') {
				cache->metricas.ciclesRead += PENALTY + 1;
			} else {
				cache->metricas.ciclesWrite += PENALTY + 1;
			}

			// Imprimo por pantalla
			short valid = cache->sets[set].lines[i].valid;
			short dirty = cache->sets[set].lines[i].dirtyBit;
			unsigned long lastUsed = cache->sets[set].lines[i].lastUsed;
			if(n == (unsigned)cache->cicles && n <= m) {
				printf("%i 2a %x %x %i -1 %i %i", n, set, tag, i, valid, dirty);
				if(cache->linesPerSet > 1) {
					printf(" %li", lastUsed);
				}
				printf("\n");
			}
				
			// Cambio tag, valid y lastUsed
			cache->sets[set].lines[i].tag = tag;
			cache->sets[set].lines[i].valid = 1;
			cache->sets[set].lines[i].lastUsed = cache->cicles;
				
			// Cambio el dirty cuando escribo
			if(operation == 'W') {
				cache->sets[set].lines[i].dirtyBit = 1;
			}
			return;
		} 
	}

	// Resuelvo conflicto con LRU
	evictVerbose(address, cache, operation, n, m);
}

void simulateModeVerbose(Cache *cache, FILE *traceFile, unsigned firstOp, unsigned secondOp) {
	unsigned instructionPointer = 0, address = 0, block = 0, size = 0;
    char operation = 0;
	
	// Leo del archivo
	int leidos = fscanf(traceFile, FORMATO_LECTURA_TRAZAS, &instructionPointer, &operation, &address, &size, &block);
    unsigned n = firstOp;
	
	while( leidos != EOF ){
		checkCacheVerbose(address, cache, operation, n, secondOp);
		if(n == (unsigned)cache->cicles) n++;
		cache->cicles++;
		leidos = fscanf(traceFile, FORMATO_LECTURA_TRAZAS, &instructionPointer, &operation, &address, &size, &block);
	}
}

void mostrarMetricas(Cache *cache) {
	
	if(cache->linesPerSet == 1) printf("direct-mapped, ");
	else printf("%i-way, ", cache->linesPerSet);
	
	printf("%i sets, size = %iKB\n", cache->setSize, cache->size);
	printf("loads %i stores %i total %li\n", cache->metricas.loads, cache->metricas.stores, (long)cache->metricas.totalAccess);
	printf("rmiss %i wmiss %i total %li\n", cache->metricas.readMiss, cache->metricas.writeMiss, (long)cache->metricas.totalMiss);
	printf("dirty rmiss %i dirty wmiss %i\n", cache->metricas.dirtyReadMisses, cache->metricas.dirtyWriteMisses);
	printf("bytes read %li bytes written %li\n", cache->metricas.bytesRead, cache->metricas.bytesWritten);
	printf("read time %li write time %li\n", cache->metricas.ciclesRead, cache->metricas.ciclesWrite);
	printf("miss rate %f\n", cache->metricas.missRateTotal);

}

int main(int argc, char *argv[]) {
	if(argc != 5 && argc != 8) {
		perror("Deberias tener 5 u 8 argumentos \n");
		return ERROR;
	}
        
    unsigned cacheSize = (unsigned)atoi(argv[2]);
	unsigned linesPerSet = (unsigned)atoi(argv[3]);
	unsigned setSize = (unsigned)atoi(argv[4]);

	if((cacheSize < (linesPerSet * setSize)) || (!arePowerTwo(cacheSize, linesPerSet, setSize))) {
		perror("Valores de C,E o S invalidos! \n");
		return ERROR;
	}

	unsigned bytesPerBlock = cacheSize/(linesPerSet*setSize);
	cacheSize /= 1024;

	FILE* archivo = fopen(argv[1], "r");
	if(!archivo) {
		perror("No se pudo abrir el archivo");
		return ERROR;
	}

	Cache *cacheSim = cacheCreate(cacheSize, linesPerSet, setSize, bytesPerBlock);
	if(!cacheSim) {
		perror("No se pudo crear la cache");
		fclose(archivo);
		return ERROR;
	}
	
	if(argc == 5) {
		simulateModeVerbose(cacheSim, archivo, 1, 0);
	} else {
		unsigned firstOperation = (unsigned)atoi(argv[6]);
		unsigned secondOperation = (unsigned)atoi(argv[7]);
		if (firstOperation > secondOperation) {
			perror("n debe ser mayo a m");
			return ERROR;
		}		
		simulateModeVerbose(cacheSim, archivo, firstOperation, secondOperation);
	}

	cacheSim->metricas.missRateTotal = (cacheSim->metricas.totalMiss / cacheSim->metricas.totalAccess);
	mostrarMetricas(cacheSim);

    deallocate(cacheSim);
	fclose(archivo);
	
    return 0;
}