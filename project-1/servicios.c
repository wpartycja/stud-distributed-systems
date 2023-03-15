#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <math.h>

#include "servicios.h"

#define MAX_MSG_SIZE 1024
#define DIR_NAME "FilesPractice1"
#define FILE_TYPE ".txt"


int init() {
	DIR* dir = opendir(DIR_NAME);
	struct dirent *nextFile;
	char filePath[1024];

	// Search for the directory.
	if(dir) {
		// If directory exists, we proceed to delete all the files within it.
		while((nextFile = readdir(dir)) != NULL){
			sprintf(filePath, "%s/%s", DIR_NAME, nextFile->d_name);
			remove(filePath);
		}
		
		// Close the directory.
		if((closedir(dir)) == -1){
			perror("Error while closing the directory.\n");
			exit(-1);
		}

	} else if (ENOENT == errno){
		// If the directory doesnt exist, we create it. 
		mkdir(DIR_NAME, 0700);
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

int modify_value(int key, char* value1, int value2, double value3){
	// initializing variables
	// + adding variables of type char[] for values
	FILE* fptr;

	char key_str[(int)((ceil(log10(key))+1)*sizeof(char))]; // inside fancy way to calculate dynamically size of 
	char value2_str[(int)((ceil(log10(value2))+1)*sizeof(char))];
	char value3_str[(int)((ceil(log10(value3))+1)*sizeof(char))];

	sprintf(key_str, "%d", key);
	sprintf(value2_str, "%d", value2);
	sprintf(value3_str, "%f", value3);

    // creating a path to file
	char path[strlen(DIR_NAME) + strlen(key_str) + strlen(FILE_TYPE) + 2]; // 2 becuase of "/" and EOF
	snprintf(path, sizeof(path), "%s/%s%s", DIR_NAME, key_str, FILE_TYPE);

	// creating new file content
	int size = strlen(key_str) + strlen(value1) + strlen(value2_str) + strlen(value3_str) + 3; // "3" for separating commas
	char new_line[size];
	snprintf(new_line, sizeof(new_line), "%s,%s,%s,%s", key_str, value1, value2_str, value3_str);

	//saving to file
	fptr = fopen(path, "r+");
	 
    if (NULL == fptr) {
        printf("Error: File can't be opened - file with this key doesn't exist\n");
		return -1;
    }

	fprintf(fptr, "%s", new_line);
    fclose(fptr);

    return 0;
}

// int delete_key(int key){

// }

// int copy_key(int key1, int key2){

// }


