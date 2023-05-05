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
#define DIR_NAME "FilesPractice2"
#define FILE_TYPE ".txt"
#define MAX_SIZE 256

int init() {
	DIR* dir = opendir(DIR_NAME); // Open the directory.
	struct dirent *nextFile; // Pointer to the next file in the directory.
	char filePath[MAX_MSG_SIZE]; // Path to the file.

	// Search for the directory.
	if(dir) {
		// If directory exists, we proceed to delete all the files within it.
		while((nextFile = readdir(dir)) != NULL){
			sprintf(filePath, "%s/%s", DIR_NAME, nextFile->d_name); // Get the path to the file.
			remove(filePath);
		}
		
		// Close the directory.
		if((closedir(dir)) == -1){
			perror("Error init(): while closing the directory.\n");
			printf("----------------------------------------\n");

			return(-1);
		}

	} else if (ENOENT == errno){
		// If the directory doesnt exist, we create it. 
		mkdir(DIR_NAME, 0700);
	} else {
		perror("Error init(): while opening the directory.\n");
		printf("----------------------------------------\n");

		return(-1);
	}

	printf("Initialization completed successfully.\n");
	printf("----------------------------------------\n");

	return 0;
}
   
int set_value(int key, char *value1, int value2, double value3) {
	int status;
	char line[5000];
	char temp[1000];
	int n;

	// Verify if value1 is the right size.
	if(strlen(value1) > MAX_SIZE){
		printf("Error set_value(): size of value1 in file %d is bigger than 256 bytes.\n", key);
		printf("----------------------------------------\n");

		return -1;
	}

	// Get key as a string and a path to file.
	const char *keyStr = get_key_str(key);
	const char *path = get_path(keyStr);

	// Open the file.
	if((status = open(path, O_RDONLY)) == -1){
		// Since the file doesnt exist, we proceed to create it.
		if((status = open(path, O_WRONLY | O_CREAT, 0666)) == -1){
			perror("Error while creating the file.\n");
			printf("----------------------------------------\n");

			return -1;
		}
		// Format the key and values to write them into the file.
		snprintf(line, 5000, "%d, ", key);
		
		n = strlen(value1);
		strncat(line, value1, n);
		
		snprintf(temp, 1000, ", %d, ", value2); 
		n = strlen(temp);
		strncat(line, temp, n);
		
		snprintf(temp, 1000, "%lf\n", value3);
		n = strlen(temp);
		strncat(line, temp, n);

		// Write the values into the file.
		write(status, line, strlen(line));

		printf("Values for key %d: value1 =\"%s\", value2 = %d, value3 = %lf\n", key, value1, value2, value3);
		printf("Successfully set values for key %d\n", key);
	} else {
		// Since file already exists, it is considered an error.
		printf("Error set_value(): key %d value already exists.\n", key);
		printf("----------------------------------------\n");
		return -1;
	}

	// Close the file.
	if(close(status) == -1){
		perror("Error while closing the file.\n");
		printf("----------------------------------------\n");
		return -1;
	}

	printf("----------------------------------------\n");
	return 0;
}

int get_value(int key, char *value1, int *value2, double *value3){
	//char name[1000];
	char line[MAX_MSG_SIZE];
	char *token;
	char *ptr;
	int i = 0;
	int sz;

	// Verify if value1 is the right size.
	if((sz = check_size_v1(value1)) == -1){
		perror("Error get_value(): size of value1 is bigger than 256 bytes.\n");
		printf("----------------------------------------\n");

		return -1;
	}

	// Get the key as a string and a path to the file.
	const char *keyStr = get_key_str(key);
	const char *path = get_path(keyStr);

	// Opening the file
	FILE *f = fopen(path, "r");

	if(f == NULL){
		printf("Error get_value(): element with key %d value does not exist.\n", key);
		printf("----------------------------------------\n");

		return -1;
	}

	// Get values and store them.
	fgets(line, MAX_MSG_SIZE, f);	

	// Extract the first token
	token = strtok(line, ", ");

	// Loop through the string to extract all other tokens.
	while((token != NULL) && i < 3){
		token = strtok(NULL, ", ");
		switch(i){
			case 0: 
				strcpy(value1, token);
				break;
				
			case 1:
				*value2 = strtol(token, &ptr, 10);
				break;
			
			case 2:
				*value3 = strtod(token, &ptr);
				break;
		}
		i++;
	}

	printf("Succesfully got values: %s, %d, %lf from file %d\n", value1, *value2, *value3, key);
	
	// Close the file.
	if (fclose(f) == EOF) {
        perror("Error get_value(): while closing the file.\n");
		printf("----------------------------------------\n");

        	return -1;
    	}

	printf("----------------------------------------\n");
	return 0;
}

int modify_value(int key, char* value1, int value2, double value3){
	if (exist(key) == -1 || exist(key) == 0){
		printf("Error modify_value(): File can't be opened - file with key %d doesn't exist\n", key);
		printf("----------------------------------------\n");
		return -1;
	}
	if (delete_key(key) == -1){
		printf("Error modify_value(): while deleting the file %d.\n", key);
		return -1;
	}
	if (set_value(key, value1, value2, value3) == -1){
		printf("Error modify_value(): while changing the values in file %d.\n", key);
		return -1;
	}
	printf("----------------------------------------\n");
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
		printf("Error delete_key(): Unable to delete file %s%s\n", key_str, FILE_TYPE);
		printf("----------------------------------------\n");

		return -1;
	}
	
	printf("----------------------------------------\n");
	return 0;
}

int exist(int key){
	// get key as a string and a path to file
	const char* key_str = get_key_str(key);
	const char* path = get_path(key_str);
	
	if (access(path, F_OK) == 0) { // F_OK - test for the existence of the file
		printf("Succesfully checked the existence of %s%s file.\n", key_str, FILE_TYPE);
		printf("----------------------------------------\n");
		return 1; // file exist
	
	} else {
		printf("File named %s%s doesn't exist.\n", key_str, FILE_TYPE);
		printf("----------------------------------------\n");
		return 0; // file doesn't exist
	}
}

int copy_key(int key1, int key2){
	// get keys as a string and a path to file
	const char* key1_str = get_key_str(key1);
	const char* key2_str = get_key_str(key2);

	const char* path1 = get_path(key1_str);

	// opening the files
    FILE* fptr1 = fopen(path1, "r");

	// If file with key1 doesnt exist, information isnt copied.
	if (fptr1 == NULL){
        perror("Error copy_key(): File with key number 1 doesn't exist.\n");
        return -1;
    	}

	// Retrieve values from file with key1.
	char val1[256];
    int *val2 = malloc(sizeof(int));  
    double *val3 = malloc(sizeof(double)); 
	
	int res1 = get_value(key1, val1, val2, val3);
	if(res1 == -1){
		perror("Error copy_key(): while retrieving values from file with key number one.\n");
		return -1;
	}

	// Verifiy if a file with key2 exists.
	int res2 = exist(key2);
	if(res2 == 1){
		// If it exists, we just modify the values.
		int res3 = modify_value(key2, val1, *val2, *val3);
		if(res3 == -1){
			perror("Error copy_key(): while copying the values.\n");
			return -1;
		}
	} else {
		// If the file doesnt exist, we create it.
		int res4 = set_value(key2, val1, *val2, *val3);
		if(res4 == -1){
			perror("Error copy_key(): while copying the values.\n");
			return -1;
		}
	}

	// free memory
	free(val2); 
    free(val3);

  	printf("Key %s has been copied to %s\n", key1_str, key2_str);

  	return 0;
}