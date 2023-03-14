#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include "servicios.h"
#define MAX_MSG_SIZE 1024

int init() {
	DIR* dir = opendir("FilesPractice1");
	struct dirent *nextFile;
	char filePath[1024];

	// Search for the directory.
	if(dir) {
		// If directory exists, we proceed to delete all the files within it.
		while((nextFile = readdir(dir)) != NULL){
			sprintf(filePath, "%s/%s", "FilesPractice1", nextFile->d_name);
			remove(filePath);
		}
		
		// Close the directory.
		if((closedir(dir)) == -1){
			perror("Error while closing the directory.\n");
			exit(-1);
		}

	} else if (ENOENT == errno){
		// If the directory doesnt exist, we create it. 
		mkdir("FilesPractice1", 0700);
	} else {
		perror("Error while opening the directory.\n");
		exit(-1);
	}

	return 0;
}

// int set_value(int key, char *value1, int value2, double value3){

    
// }

// int get_value(int key, char *value1, int *value2, double *value3){


// }

// int modify_value(int key, char, *value1, int value2, double value3){

// }

// int delete_key(int key){

// }

// int copy_key(int key1, int key2){

// }


