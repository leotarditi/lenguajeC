#include <sys/types.h>

/*
 * writeall() es un wrapper de write(2) que se asegura (mediante un
 * ciclo) que se escriban todos los bytes.
 *
 * Devuelve 0 si se escribieron todos los bytes; en caso contrario
 * (esto es, si write devolvió en algún momento -1), se devuelve el
 * número de bytes que sí pudo escribir.
 *
 * Precondiciones: fd >= 0, buf != NULL, count > 0.
 */
size_t writeall(int fd, const void *buf, size_t count);


/*
 * copyfd() lee todo el contenido de un file descriptor para escribirlo
 * en otro, usando como almacenamiento temporal el buffer proporcionado.
 *
 * La función lee como máximo "size" bytes de "fdin" en "buf",
 * y escribe los bytes leidos en "fdout", usando writeall().
 *
 * La función devuelve 0 si se copió el archivo en su totalidad (esto es,
 * read llegó a devolver 0). En caso contrario, devuelve el número de bytes
 * escritos (esto es, si read devolvió en algún momento -1, o writeall
 * no pudo escribir todos los bytes).
 *
 * Precondiciones: fdin >= 0, fdout >= 0, buf != NULL, size > 0.
 */
size_t copyfd(int fdin, int fdout, void *buf, size_t size);