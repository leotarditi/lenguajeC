#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "cp57.h"

#define ERROR -1
#define SUCCESS 0

size_t writeall(int fd, const void *buf, size_t count) {
	
	ssize_t bytes_written = 0;
	size_t current = 0;
	
	do {
		bytes_written = write(fd, (buf + current), (count - current));
		if(bytes_written == ERROR) {
			if(errno != EINTR) {
				return current;	
			}
		} else {
			current += bytes_written;
		}
	} while (current < count);

	return SUCCESS;
}

size_t copyfd(int fdin, int fdout, void *buf, size_t size) {

	ssize_t bytes_read, bytes_written;
	size_t count = 0;
	
	do {
		bytes_read = read(fdin, buf, size);
		if (bytes_read == ERROR) {
			if(errno != EINTR) {
				return count;	
			} else {
				continue;
			}
		}
		bytes_written = writeall(fdout, buf, bytes_read);
		if(bytes_written == SUCCESS) {
			count += bytes_read;
		} else {
			count += bytes_written;
			return bytes_written;
		}
				
	} while (bytes_read != SUCCESS);

	return SUCCESS;
}

int main(int argc, char const *argv[]) {
	
	uint8_t buf[512];
	int fdin, fdout;
	size_t copy;

	if(argc != 3) {
		perror("No escribiste 3 argumentos como lo pedido");
		return ERROR;
	}

	//Opcional 2
	ssize_t link = readlink(argv[1], (char*)buf, sizeof(buf));
	if(link > ERROR) {
		printf("El archivo origen es un enlace simbolico \n");
		buf[link] = '\0';
		int copy_link = symlink((char*)buf, argv[2]);
		if(copy_link == 0) {
			printf("Se copio el enlace correctamente \n");
		} else {
			perror("No se pudo copiar el enlace \n");
		}
		return copy_link;
	}
 
	fdin = open(argv[1], O_RDONLY);
	if(fdin == -1) {
		fprintf(stderr, "Error al abrir '%s': %m \n", argv[0]);
		return ERROR;
	}
	

	fdout = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if(fdout == -1 && errno != EISDIR) {
		fprintf(stderr, "Error al abrir '%s': %m \n", argv[1]);
		close(fdin);
		return ERROR;
	}

	//Opcional 1
	if(fdout == ERROR) {
		if(errno == EISDIR) {
			printf("El archivo de destino es un directorio \n");
			int fd_dir;
			fd_dir = open(argv[2], O_RDONLY | O_DIRECTORY);
			if(fd_dir == ERROR) {
				perror("El directorio no se pudo abrir \n");
			}

			char *out;
			out = strrchr(argv[1], '/');

			if(out != NULL) {
				out++;
			} else {
				out = (char*)argv[1];
			}

			fdout = openat(fd_dir, out, O_CREAT | O_WRONLY | O_TRUNC, 0666);
			if(fdout == ERROR) {
				perror("No se pudo copiar en el directorio \n");
			}	

			close(fd_dir);
		}
	}

	copy = copyfd(fdin, fdout, buf, sizeof(buf));
	if(copy == SUCCESS) {
		printf("Se copio con exito \n");
	} else {
		printf("Hubo un error o llegaste a copiar %zu bytes \n", copy);
		return ERROR;
	}

	close(fdin);
	close(fdout);
    return SUCCESS;
}
