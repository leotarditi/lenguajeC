#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include "ls57.h"

#define ERROR -1
#define SUCCESS 0

ssize_t getsize(int atdirfd, const char *filename) {
	
	struct stat st;
	fstatat(atdirfd, filename, &st, AT_SYMLINK_NOFOLLOW);
	lstat(filename, &st);

	if((st.st_mode & S_IFMT) == S_IFREG) {
		return st.st_size;
	}
	return ERROR;
}

void lsdir(DIR *dir) {
	
	int fdout;
	struct dirent* file;
	ssize_t size;

	file = readdir(dir);
	fdout = dirfd(dir);

	while(file != NULL) {
		size = getsize(fdout, file->d_name);
		
		if(file->d_name[0] != '.') {
			
			if(size > -1) {
				printf("%s\t%zu\n", file->d_name, size);
			} else {
				printf("%s\n", file->d_name);
			}
		}
		file = readdir(dir);
	}
}

int main(int argc, char const *argv[]) {
	
	DIR* dir;
	
	if(argc == 1){
		dir = opendir(".");
	} else {
		dir = opendir(argv[1]);
	}

	if(dir == NULL) {
		perror("Error al abrir el directorio \n");
		return ERROR;
	}

	if(errno == ENOTDIR) {
		perror("Solo se pueden listar directorios \n");
		return ERROR;
	}

	lsdir(dir);

	closedir(dir);
	return SUCCESS;
}
