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
	char filePath[MAX_MSG_SIZE];

	// Search for the directory.
	if(dir) {
		// If directory exists, we proceed to delete all the files within it.
        printf("Directory %s found. Deleting all files within it.\n", DIR_NAME);
		while((nextFile = readdir(dir)) != NULL){
			sprintf(filePath, "%s/%s", DIR_NAME, nextFile->d_name);
			remove(filePath);
            printf("Deleted file: %s\n", filePath);
		}
		
		// Close the directory.
		if((closedir(dir)) == -1){
			perror("Error while closing the directory.\n");
			return(-1);
		} else {
			printf("Directory %s closed successfully.\n", DIR_NAME);
		}

	} else if (ENOENT == errno){
		// If the directory doesnt exist, we create it. 
		mkdir(DIR_NAME, 0700);
        printf("Directory %s not found. Creating directory.\n", DIR_NAME);
	} else {
		perror("Error while opening the directory.\n");
		return(-1);
	}
    
    printf("Initialization completed successfully\n");
	return 0;
}
   

int set_value(int key, char *value1, int value2, double value3) {
	char name[1000];
	int status;
	char line[5000];
	char temp[1000];
	int n;

	// Change directory where we work.
	if(chdir("FilesPractice1") == -1){
		perror("Error while changing directories.");
		return -1;
	}

	// Convert key to the name of the file.
	snprintf(name, 1000, "%d.txt", key);

	// Open the file.
	if((status = open(name, O_RDONLY)) == -1){
		// Since the file doesnt exist, we proceed to create it.
		if((status = open(name, O_WRONLY | O_CREAT, 0666)) == -1){
			perror("Error while creating the tuple.\n");
			return -1;
		}
		// Format the key and values to write them into the file.
		snprintf(line, 5000, "%d, ", key);
		
		n = strlen(value1);
		strncat(line, value1, n);
		
		snprintf(temp, 1000, ", %d, ", value2);
		n = strlen(temp);
		strncat(line, temp, n);
		
		snprintf(temp, 1000, "%lf", value3);
		n = strlen(temp);
		strncat(line, temp, n);

		// Write the values into the file.
		write(status, line, strlen(line));
        
        printf("Values for key %d: value1=\"%s\", value2=%d, value3=%f\n", key, value1, value2, value3);
        printf("Successfully set values for key %d\n", key);

	} else {
		// Since file already exists, it is considered an error.
		perror("Error: key value already exists for key %d\n", key);
		return -1;
	}

	// Close the file.
	if(close(status) == -1){
		perror("Error while closing the file.\n");
		return -1;
	}

	return 0;
}


int get_value(int key, char *value1, int *value2, double *value3){
	char name[1000];
	FILE *f;
	char line[MAX_MSG_SIZE];
	char *token;
	char *ptr;
	int i = 0;

	// Change directory where we work.
    printf("Current directory: %s\n", getcwd(NULL, 0));
    printf("Changing directory to %s\n", DIR_NAME);
	if(chdir(DIR_NAME) == -1){
		perror("Error while changing directories.\n");
		return -1;
	}

	// Convert key to the name of the file.
    printf("Converting key %d to file name %s\n", key, name);
	snprintf(name, 1000, "%d.txt", key);

	// Open the file.
    printf("Opening file %s\n", name);
	if((f = fopen(name, "r")) == NULL){
		// If the file doesnt exist, return -1.
		perror("Error: element with key value does not exist.\n");
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

	printf("Successfully get values for key %d: %s, %d, %lf\n", key, value1, *value2, *value3);
	
	// Close the file.
    printf("Closing file %s\n", name);
	if (fclose(f) == EOF) {
        	perror("Error while closing the file.\n");
        	return -1;
    	}

	return 0;
}


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
        printf("Error: File can't be opened. File with key %s does not exist.\n", key_str);
		return -1;
    } else {
		printf("Modifying file with key: %s\n", key_str);
		printf("File path: %s\n", path);
		printf("New line to be saved: %s\n", new_line);
		printf("Values %s have been modified in %s%s file.\n", new_line, key_str, FILE_TYPE);
	}
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
	
    // Print the path of the deleted file
	printf("File path: %s\n", path);
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


int copy_key(int key1, int key2){

	// get keys as a string and a path to file
	const char* key1_str = get_key_str(key1);
	const char* key2_str = get_key_str(key2);

	const char* path1 = get_path(key1_str);
	const char* path2 = get_path(key2_str);

	// opening the files
    FILE* fptr1 = fopen(path1, "r");
    FILE* fptr2 = fopen(path2, "w");

    if (fptr1 == NULL){
        printf("Error: File with key %s%s doesn't exist\n", key1_str, FILE_TYPE);
        return -1;
    } else {
        printf("File with key %s%s has been successfully opened for reading\n", key1_str, FILE_TYPE);
    }

    if (fptr2 == NULL){
        printf("Error: File with key %s%s can't be created\n", key2_str, FILE_TYPE);
        return -1;
    } else {
        printf("File with key %s%s has been successfully opened for writing\n", key2_str, FILE_TYPE);
    }

    // copy the contents of the file1 to file2
    char buffer[MAX_MSG_SIZE];
    size_t bytes;

    while ((bytes = fread(buffer, 1, sizeof(buffer), fptr1)) > 0){
        fwrite(buffer, 1, bytes, fptr2);
    }

    fclose(fptr1);
    fclose(fptr2);

    printf("Key %s has been copied to %s\n", key1_str, key2_str);

    return 0;
}
