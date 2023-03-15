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
#include "servicios_help.h"

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
	FILE* fptr;

	// getting the key as string and a path
	const char* key_str = get_key_str(key);
	const char* path = get_path(key_str);
 
	// chainging the type to string
	char value2_str[(int)((ceil(log10(value2))+1)*sizeof(char))];
	char value3_str[(int)((ceil(log10(value3))+1)*sizeof(char))];

	sprintf(value2_str, "%d", value2);
	sprintf(value3_str, "%f", value3);

	// creating new file content
	int size = strlen(key_str) + strlen(value1) + strlen(value2_str) + strlen(value3_str) + 6; // "6" for separating commas and spaces
	char new_line[size];
	snprintf(new_line, sizeof(new_line), "%s, %s, %s, %s", key_str, value1, value2_str, value3_str);

	//saving to file
	fptr = fopen(path, "r+");
	 
    if (NULL == fptr) {
        printf("Error: File can't be opened - file with this key doesn't exist\n");
		return -1;
    } else {
		printf("New values: %s\nHave beed succesfully modified to %s%s file.\n", new_line, key_str, FILE_TYPE);
	}

	fprintf(fptr, "%s", new_line);
    fclose(fptr);

    return 0;
}

int delete_key(int key){
	// add variable key in char[] type
	const char* key_str = get_key_str(key);
	const char* path = get_path(key_str);

	// try to delete the file
	if(remove(path) == 0) {
		printf("File %s%s deleted successfully!\n", key_str, FILE_TYPE);
	} else {
		printf("Error: Unable to delete file %s%s\n", key_str, FILE_TYPE);
		return -1;
	}
	
	return 0;
}

int exist(int key){
	// get key as a string and a path to file
	const char* key_str = get_key_str(key);
	const char* path = get_path(key_str);
	
	if (access(path, F_OK) == 0) { // F_OK - test for the existence of the file
		printf("Succesfully checked the existence of %s%s file.\n", key_str, FILE_TYPE);
		return 1; // file exist
	} else {
		printf("File named %s%s doesn't exist.\n", key_str, FILE_TYPE);
		return 0; // file doesn't exist
	}
}
