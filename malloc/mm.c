/* 
 * Los bloques están alineados con límites de palabras dobles.
 * Esto produce bloques alineados de 8 bytes en un procesador de 32 bits y 
 * bloques alineados de 16 bytes en un procesador de 64 bits.
 * Sin embargo, la alineación de 16 bytes es más estricta de lo necesario; 
 * la asignación solo requiere una alineación de 8 bytes. 
 * El tamaño mínimo de bloque tomado es de 4 palabras.
 * Este asignador utiliza el tamaño de un puntero, por ejemplo, sizeof(void *), 
 * para definir el tamaño de una palabra.
 * Este asignador también utiliza el tipo estándar uintptr_t para 
 * definir enteros sin signo que tienen el mismo tamaño que un puntero, 
 * es decir, sizeof(uintptr_t) == sizeof(void *).
 * 
 * 
 * Blocks are aligned to double-word boundaries.  
 * This yields 8-byte aligned blocks on a 32-bit processor, 
 * and 16-byte aligned blocks on a 64-bit processor.  
 * However, 16-byte alignment is stricter than necessary; 
 * the assignment only requires 8-byte alignment. 
 * The minimum block size taken is 4 words.
 * This allocator uses the size of a pointer, e.g., sizeof(void *),
 * to define the size of a word.  
 * This allocator also uses the standard type uintptr_t to 
 * define unsigned integers that are the same size as a pointer, 
 * i.e., sizeof(uintptr_t) == sizeof(void *).
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "memlib.h"
#include "mm.h"

team_t team = {
    " g10",                     // Número de grupo,
    " Leo Tarditi",             // Nombre integrante 1
    " ltarditi@fi.uba.ar",     // E-mail integrante 1
    "",     // Nombre integrante 2 (si lo hay)
    ""      // E-mail integrante 2 (si lo hay)
};

#define EXITO 0
#define ERROR -1

// Constantes y macros básicas: 
// Basic constants and macros: 

// Tamaño de palabra y encabezado/pie de página (bytes)
// Word and header/footer size (bytes)
#define WSIZE      sizeof(void *) 
// Tamaño de palabra doble (bytes)
// Doubleword size (bytes) 
#define DSIZE      (2 * WSIZE)    
// Extiende el heap por esta cantidad (bytes)
// Extend heap by this amount (bytes)
#define CHUNKSIZE  (1 << 12)      

// Valor máximo entre 2 valores
// Max value of 2 values
#define MAX(x, y) ((x) > (y) ? (x) : (y))

// Empaqueta un tamaño y un bit asignado en una palabra
// Pack a size and allocated bit into a word
#define PACK(size, alloc)  ((size) | (alloc))

// Lee y escribe una palabra en la dirección p.
// Read and write a word at address p.
#define GET(p)       (*(uintptr_t *)(p))
#define PUT(p, val)  (*(uintptr_t *)(p) = (val))

// Lee el tamaño y los campos asignados de la dirección p
// Read the size and allocated fields from address p 
#define GET_SIZE(p)   (GET(p) & ~(DSIZE - 1))
#define GET_ALLOC(p)  (GET(p) & 0x1)


// Dado el bloque void* bp, calcular la dirección de su encabezado y pie de página
// Given block ptr bp, compute address of its header and footer
#define HDRP(bp)  ((void *)(bp) - WSIZE)
#define FTRP(bp)  ((void *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

// Dado el bloque void* bp, calcular la dirección de los bloques siguientes y anteriores
// Given block ptr bp, compute address of next and previous blocks
#define NEXT_BLK(bp)  ((void *)(bp) + GET_SIZE(HDRP(bp)))
#define PREV_BLK(bp)  ((void *)(bp) - GET_SIZE((void *)(bp) - DSIZE)) 

/* 
 * bp es la dirección del bloque libre. Dado que el tamaño mínimo del bloque es de 16 bytes, 
 * utilizo para almacenar la dirección del puntero del bloque anterior y el siguiente.
 * 
 * bp is address of the free block. Since minimum Block size is 16 bytes, 
 * we utilize to store the address of previous block pointer and next block pointer.
*/

// Dado el ptr en la free list, obtiene el puntero siguiente y anterior en la lista
// Given ptr in free list, get next and previous ptr in the list
#define GET_NEXT_PTR(bp)  (*(char **)(bp + WSIZE))
#define GET_PREV_PTR(bp)  (*(char **)(bp))

// Pone punteros en los elementos siguientes y anteriores de la free list
// Puts pointers in the next and previous elements of free list
#define SET_NEXT_PTR(bp, qp) (GET_NEXT_PTR(bp) = qp)
#define SET_PREV_PTR(bp, qp) (GET_PREV_PTR(bp) = qp)

// Declaraciones globales
// Global declarations
static char *heap_listp = 0; 
static char *free_list_start = 0;

// Prototipos de funciones para rutinas de ayuda interna
// Function prototypes for internal helper routines
static void *coalesce(void *bp);
static void *extend_heap(size_t words);
static void *find_fit(size_t asize);
static void place(void *bp, size_t asize);

// Prototipos de funciones para el mantenimiento de la free list
// Function prototypes for maintaining free list
static void insert_in_free_list(void *bp); 
static void remove_from_free_list(void *bp); 

// Prototipos de funciones para las rutinas del verificador de consistencia del heap
// Function prototypes for heap consistency checker routines
static void checkblock(void *bp);
static void checkheap(bool verbose);
static void printblock(void *bp); 

/*
 * Inicialice el administrador de memoria.
 * @param - void ningún parámetro pasado
 * @return - int 0 para éxito o -1 para fracaso
 * 
 * Initialize the memory manager.
 * @param - void no parameter passed in
 * @return - int 0 for success or -1 for failure
 */
int mm_init(void) {
  
    // Crea el heap vacío inicial.
    // Create the initial empty heap.
    if ((heap_listp = mem_sbrk(8*WSIZE)) == NULL) return ERROR;

    // Alineamiento del padding
    // Alignment padding
    PUT(heap_listp, 0);
    // Encabezado del prólogo
    // Prologue header
    PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1)); 
    // Pie del prólogo
    // Prologue footer
    PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1)); 
    // Encabezado del epílogo
    // Epilogue header
    PUT(heap_listp + (3 * WSIZE), PACK(0, 1));     
    free_list_start = heap_listp + 2*WSIZE; 

    // Extiende el heap vacío con un bloque libre del tamaño de bloque mínimo posible
    // Extend the empty heap with a free block of minimum possible block size
    if (extend_heap(4) == NULL) return ERROR;
    
    return EXITO;
}

/* 
 * PRE:
 *   Tamaño de memoria solicitado por el programador.
 * POS:
 *   Asigna un bloque con al menos "tamaño" bytes de carga útil, a menos que "tamaño" sea cero. 
 *   Devuelve la dirección de este bloque si la asignación fue exitosa y NULL en caso contrario.
 * 
 * Requires:
 *   Size of memory asked by the programmer.
 * Effects:
 *   Allocate a block with at least "size" bytes of payload, unless "size" is zero.  
 *   Returns the address of this block if the allocation was successful and NULL otherwise.
 */
void *mm_malloc(size_t size) {

    // Tamaño de bloque ajustado
    // Adjusted block size
    size_t asize;      
    // Cantidad para extender el heap si no entra
    // Amount to extend heap if no fit
    size_t extendsize; 
    void *ptr;

    // Ignora las solicitudes falsas.
    // Ignore spurious requests.
    if (size == 0) return NULL;

    // Ajusta el tamaño del bloque para incluir los requisitos generales y de alineación.
    // Adjust block size to include overhead and alignment reqs.
    if (size <= DSIZE) asize = 2 * DSIZE;
    else               asize = DSIZE * ((size + DSIZE + (DSIZE - 1)) / DSIZE);

    // Busca en la free list lugar para un fit.
    // Search the free list for a fit.
    if ((ptr = find_fit(asize)) != NULL) {
        place(ptr, asize);
        return ptr;
    }

    // No se encontró ningún fit. Pide más memoria y coloca el bloque.
    // No fit found.  Get more memory and place the block.
    extendsize = MAX(asize, CHUNKSIZE);
    if ((ptr = extend_heap(extendsize / WSIZE)) == NULL) return NULL;
    
    place(ptr, asize);
    return ptr;
} 

/* 
 * PRE:
 *   "ptr" es la dirección de un bloque asignado o NULL.
 * POS:
 *   Libera un bloque.
 * 
 * Requires:
 *   "ptr" is either the address of an allocated block or NULL.
 * Effects:
 *   Free a block.
 */
void mm_free(void *ptr){
    size_t size;
    // Ignora solicitudes falsas.
    // Ignore spurious requests.
    if (ptr == NULL) return;
    // Libera y fusiona el bloque.
    // Free and coalesce the block.
    size = GET_SIZE(HDRP(ptr));
    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));
    coalesce(ptr);
}

/*
 * PRE:
 *   "ptr" es la dirección de un bloque asignado o NULL.
 * POS:
 *   Reasigna el bloque "ptr" a un bloque con al menos tamaño bytes de carga útil, a menos que tamaño sea cero.
 *   Si "tamaño" es cero, libera el bloque "ptr" y devuelve NULL.
 *   Si el bloque "ptr" ya es un bloque con bytes de carga útil de tamaño mínimo, 
 *   entonces "ptr" puede devolverse opcionalmente.
 *   Además, si el tamaño solicitado es mayor que el tamaño del bloque actual en el puntero ptr
 *   y tenemos el siguiente bloque vacío con la suma del tamaño del bloque actual y el siguiente bloque (que está vacío)
 *   entonces no necesitamos llamar a malloc, solo combinamos el bloque actual y el bloque siguiente para 
 *   redimensionarlos para satisfacer el tamaño de reasignación solicitado.
 *   Si no se puede hacer nada, se asigna un nuevo bloque (usando malloc) y el contenido del bloque antiguo
 *   "ptr" se copian en ese nuevo bloque. Devuelve la dirección de este nuevo 
 *   bloque si la asignación fue exitosa y NULL en caso contrario.
 * 
 * Requires:
 *   "ptr" is either the address of an allocated block or NULL.
 * Effects:
 *   Reallocates the block "ptr" to a block with at least "size" bytes of payload, unless "size" is zero.  
 *   If "size" is zero, frees the block "ptr" and returns NULL.  
 *   If the block "ptr" is already a block with at least "size" bytes of payload, then "ptr" may optionally be returned.
 *   Further if requested size is greater than the current block size at pointer bp
 *   and we have the next block as empty with sum of current block size and next block (which happens to be empty)
 *   then we dont need call malloc but just combine current block and next block to resize them so as to 
 *   satisfy the requested realloc size. 
 *   If nothing can be done then a new block is allocated (using malloc) and the contents of the old block
 *   "ptr" are copied to that new block.  Returns the address of this new 
 *   block if the allocation was successful and NULL otherwise.
 */
void *mm_realloc(void *ptr, size_t size){
    if((int)size < 0) return NULL; 
    else if((int)size == 0){ 
        mm_free(ptr); 
        return NULL; 
    } 
    else if(size > 0){ 
        size_t oldsize = GET_SIZE(HDRP(ptr)); 
        // 2 palabras para encabezado y pie de página
        // 2 words for header and footer
        size_t newsize = size + 2 * WSIZE;         
      
        // si el nuevo tamaño es menor que el viejo tamaño, devuelvo ptr
        // if newsize is less than oldsize then we just return bp 
        if(newsize <= oldsize) return ptr; 
      
        // si el nuevo tamaño es mayor que el viejo tamaño
        // if newsize is greater than oldsize  
        else { 
            size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLK(ptr))); 
            size_t csize;
            /*
             * si el siguiente bloque esta libre y el tamaño de los dos bloques es mayor o 
             * igual que el nuevo tamaño entonces solo necesitamos combinar ambos bloques
             * 
             * if next block is free and the size of the two blocks is greater than or 
             * equal the new size then we only need to combine both the blocks  
            */ 
            if(!next_alloc && ((csize = oldsize + GET_SIZE(HDRP(NEXT_BLK(ptr))))) >= newsize){ 
                remove_from_free_list(NEXT_BLK(ptr)); 
                PUT(HDRP(ptr), PACK(csize, 1)); 
                PUT(FTRP(ptr), PACK(csize, 1)); 
                return ptr; 
            } else {  
                void *new_ptr = mm_malloc(newsize);  
                place(new_ptr, newsize);
                memcpy(new_ptr, ptr, newsize); 
                mm_free(ptr); 
                return new_ptr; 
            } 
        }
    } else return NULL;
} 

/*
 * PRE:
 *   "ptr" es la dirección de un bloque recién liberado.
 * POS:
 *   Realice la fusión de etiquetas de contorno.
 *   Elimina e inserta los punteros de bloques libres apropiados a la explicit free list
 *   Devuelve la dirección del bloque fusionado.
 * 
 * Requires:
 *   "ptr" is the address of a newly freed block.
 * Effects:
 *   Perform boundary tag coalescing. 
 *   Removes and inserts appropiate free block pointers to the explicit free list
 *   Returns the address of the coalesced block.
 */
static void *coalesce(void *ptr) {

    // si el bloque anterior está asignado o su tamaño es cero, se establecerá PREV_ALLOC.
    // if previous block is allocated or its size is zero then PREV_ALLOC will be set.
    size_t NEXT_ALLOC = GET_ALLOC(HDRP(NEXT_BLK(ptr)));
    size_t PREV_ALLOC = GET_ALLOC(FTRP(PREV_BLK(ptr))) || PREV_BLK(ptr) == ptr;
    size_t size = GET_SIZE(HDRP(ptr));
  
    // Si el siguiente bloque esta libre
    // Next block is only free   
    if (PREV_ALLOC && !NEXT_ALLOC) {                  
        size += GET_SIZE(HDRP(NEXT_BLK(ptr)));
        remove_from_free_list(NEXT_BLK(ptr));
        PUT(HDRP(ptr), PACK(size, 0));
        PUT(FTRP(ptr), PACK(size, 0));
    }
    // Si el bloque anterior esta libre
    // Prev block is only free  
    else if (!PREV_ALLOC && NEXT_ALLOC) {               
        size += GET_SIZE(HDRP(PREV_BLK(ptr)));
        ptr = PREV_BLK(ptr);
        remove_from_free_list(ptr);
        PUT(HDRP(ptr), PACK(size, 0));
        PUT(FTRP(ptr), PACK(size, 0));
    }
    // Si ambos bloques estan libres
    // Both blocks are free
    else if (!PREV_ALLOC && !NEXT_ALLOC) {                
        size += GET_SIZE(HDRP(PREV_BLK(ptr))) + GET_SIZE(HDRP(NEXT_BLK(ptr)));
        remove_from_free_list(PREV_BLK(ptr));
        remove_from_free_list(NEXT_BLK(ptr));
        ptr = PREV_BLK(ptr);
        PUT(HDRP(ptr), PACK(size, 0));
        PUT(FTRP(ptr), PACK(size, 0));
    }
    // por último, inserto ptr en la free list y devuelvo ptr
    // lastly insert ptr into free list and return ptr
    insert_in_free_list(ptr);
    return ptr;
}

/* 
 * PRE:
 *   Ninguna.
 * POS:
 *   Extiende el heap con un bloque libre y devuelve la dirección de ese bloque.
 * 
 * Requires:
 *   None.
 * Effects:
 *   Extend the heap with a free block and return that block's address.
 */

static void *extend_heap(size_t words) {
    char *ptr;
    size_t size;

    // Asignar un número par de palabras para mantener la alineación
    // Allocate an even number of words to maintain alignment 
    size = (words % 2) ? (words+1) * WSIZE : words * WSIZE;
    // Dado que el tamaño mínimo de bloque que se nos da es de 4 palabras (es decir, 16 bytes)
    // Since minimum block size given to us is 4 words (ie 16 bytes)
    if (size < 16) size = 16;
    // pido más espacio en la memoria
    // call for more memory space 
    if ((ptr = mem_sbrk(size)) == NULL) return NULL;
    
    // Inicializo el encabezado/pie de página del bloque libre y el encabezado del epílogo
    // Initialize free block header/footer and the epilogue header 
  
    // encabezado de bloque libre
    // free block header
    PUT(HDRP(ptr), PACK(size, 0));         
    // pie de bloque libre
    // free block footer 
    PUT(FTRP(ptr), PACK(size, 0));        
    // nuevo encabezado de epílogo
    // new epilogue header  
    PUT(HDRP(NEXT_BLK(ptr)), PACK(0, 1)); 
  
    // fusiono ptr con los bloques siguientes y anteriores
    // coalesce ptr with next and previous blocks
    return coalesce(ptr);
}

/*
 * PRE:
 *   Tamaño de memoria para encontrar.
 * POS:
 *   Encuentra un fit para un bloque con bytes de tamaño en la free list.
 *   Extiende el heap en algunos casos especiales.
 *   Y devuelve la dirección de ese bloque o NULL si no se encontró un bloque adecuado.
 * 
 * Requires:
 *   Size of memory to find.
 * Effects:
 *   Finds a fit for a block with "asize" bytes from the free list.
 *   Extends the heap in some special cases.
 *   And Returns that block's address or NULL if no suitable block was found. 
 */

static void *find_fit(size_t asize){
    void *ptr;
    static int last_malloced_size = 0;
    static int repeat_counter = 0;
    if(last_malloced_size == (int)asize){
        if(repeat_counter>30){  
            int extendsize = MAX(asize, 4 * WSIZE);
            ptr = extend_heap(extendsize/4);
            return ptr;
        }
        else repeat_counter++;
    }
    else repeat_counter = 0;
    for (ptr = free_list_start; GET_ALLOC(HDRP(ptr)) == 0; ptr = GET_NEXT_PTR(ptr)){
        if (asize <= (size_t)GET_SIZE(HDRP(ptr))) {
            last_malloced_size = asize;
            return ptr;
        }
    }
    return NULL;
}

/* 
 * POS:
 *   "ptr" es la dirección de un bloque libre que tiene al menos un tamaño de bytes.
 * PRE:
 *   Coloca un bloque con tamaño "asize" de bytes al comienzo del bloque libre "ptr" y
 *   dividie ese bloque si el resto fuera al menos el tamaño minimo del bloque.
 * 
 * Requires:
 *   "ptr" is the address of a free block that is at least "asize" bytes.
 * Effects:
 *   Place a block of "asize" bytes at the start of the free block "ptr" and
 *   split that block if the remainder would be at least the minimum block
 *   size. 
 */
static void place(void *ptr, size_t asize){
    size_t csize = GET_SIZE(HDRP(ptr));

    if ((csize - asize) >= 4 * WSIZE) {
        PUT(HDRP(ptr), PACK(asize, 1));
        PUT(FTRP(ptr), PACK(asize, 1));
        remove_from_free_list(ptr);
        ptr = NEXT_BLK(ptr);
        PUT(HDRP(ptr), PACK(csize-asize, 0));
        PUT(FTRP(ptr), PACK(csize-asize, 0));
        coalesce(ptr);
    } else {
        PUT(HDRP(ptr), PACK(csize, 1));
        PUT(FTRP(ptr), PACK(csize, 1));
        remove_from_free_list(ptr);
    }
}

// Inserta el puntero de bloque libre en la free list
// Inserts the free block pointer int the free list
static void insert_in_free_list(void *ptr){
    SET_NEXT_PTR(ptr, free_list_start); 
    SET_PREV_PTR(free_list_start, ptr); 
    SET_PREV_PTR(ptr, NULL); 
    free_list_start = ptr; 
}
// Elimina el puntero de bloque libre en la free list
// Removes the free block pointer int the free list
static void remove_from_free_list(void *ptr){
    if (GET_PREV_PTR(ptr)) SET_NEXT_PTR(GET_PREV_PTR(ptr), GET_NEXT_PTR(ptr));
    else                   free_list_start = GET_NEXT_PTR(ptr);
    SET_PREV_PTR(GET_NEXT_PTR(ptr), GET_PREV_PTR(ptr));
}


// Las funciones restantes son funciones de verificación de consistencia del heap.
// The remaining routines are heap consistency checker routines. 

/*
 * PRE:
 *   "ptr" es la dirección de un bloque.
 * POS:
 *   Realiza una verificación mínima en el bloque "ptr".
 * 
 * Requires:
 *   "ptr" is the address of a block.
 * Effects:
 *   Perform a minimal check on the block "ptr".
 */
static void checkblock(void *ptr) {

    if ((uintptr_t)ptr % DSIZE) printf("Error: %p is not doubleword aligned\n", ptr);
    if (GET(HDRP(ptr)) != GET(FTRP(ptr))) printf("Error: header does not match footer\n");
}

/* 
 * PRE:
 *   Ninguna.
 * POS:
 *   Realiza una comprobación mínima de la consistencia del heap.
 * 
 * Requires:
 *   None.
 * Effects:
 *   Perform a minimal check of the heap for consistency. 
 */
void checkheap(bool verbose) {
    void *ptr;

    if (verbose) printf("Heap (%p):\n", heap_listp);

    if (GET_SIZE(HDRP(heap_listp)) != DSIZE || !GET_ALLOC(HDRP(heap_listp))) printf("Bad prologue header\n");
    checkblock(heap_listp);

    for (ptr = heap_listp; GET_SIZE(HDRP(ptr)) > 0; ptr = (void *)NEXT_BLK(ptr)) {
        if (verbose) printblock(ptr);
        checkblock(ptr);
    }

    if (verbose) printblock(ptr);
    if (GET_SIZE(HDRP(ptr)) != 0 || !GET_ALLOC(HDRP(ptr))) printf("Bad epilogue header\n");
}

/*
 * PRE:
 *   "ptr" es la dirección de un bloque.
 * POS:
 *   Imprime el bloque "ptr".
 * 
 * Requires:
 *   "ptr" is the address of a block.
 * Effects:
 *   Print the block "ptr".
 */
static void printblock(void *ptr) {
    bool halloc, falloc;
    size_t hsize, fsize;

    checkheap(false);
    hsize = GET_SIZE(HDRP(ptr));
    halloc = GET_ALLOC(HDRP(ptr));  
    fsize = GET_SIZE(FTRP(ptr));
    falloc = GET_ALLOC(FTRP(ptr));  

    if (hsize == 0) {
        printf("%p: end of heap\n", ptr);
        return;
    }

    printf("%p: header: [%zu:%c] footer: [%zu:%c]\n", ptr, hsize, (halloc ? 'a' : 'f'), fsize, (falloc ? 'a' : 'f'));
}