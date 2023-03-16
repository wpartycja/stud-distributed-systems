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
			return(-1);
		}

	} else if (ENOENT == errno){
		// If the directory doesnt exist, we create it. 
		mkdir("FilesPractice1", 0700);
	} else {
		perror("Error while opening the directory.\n");
		return(-1);
	}

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

	} else {
		// Since file already exists, it is considered an error.
		perror("Error: key value already exists.\n");
		return -1;
	}

	// Close the file.
	if(close(status) == -1){
		perror("Error while closing the file.");
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
	if(chdir("FilesPractice1") == -1){
		perror("Error while changing directories.");
		return -1;
	}

	// Convert key to the name of the file.
	snprintf(name, 1000, "%d.txt", key);

	// Open the file.
	if((f = fopen(name, "r")) == NULL){
		// If the file doesnt exist, return -1.
		perror("Error: element with key value does not exist.");
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
	
	// Close the file.
	if (fclose(f) == EOF) {
        	perror("Error while closing the file.");
        	return -1;
    	}

	return 0;
}

// int modify_value(int key, char, *value1, int value2, double value3){

// }

// int delete_key(int key){

// }

int copy_key(int key1, int key2){
    // add variable key1 and key2 in char[] type
    char key1_str[(int)((ceil(log10(key1))+1)*sizeof(char))];
    char key2_str[(int)((ceil(log10(key2))+1)*sizeof(char))]; 
    sprintf(key1_str, "%d", key1);
    sprintf(key2_str, "%d", key2);

    // creating a path to file1 (key1)
    char path1[strlen(DIR_NAME) + strlen(key1_str) + strlen(FILE_TYPE) + 2]; // 2 becuase of "/" and EOF
    snprintf(path1, sizeof(path1), "%s/%s%s", DIR_NAME, key1_str, FILE_TYPE);

    // creating a path to file2 (key2)
    char path2[strlen(DIR_NAME) + strlen(key2_str) + strlen(FILE_TYPE) + 2]; // 2 becuase of "/" and EOF
    snprintf(path2, sizeof(path2), "%s/%s%s", DIR_NAME, key2_str, FILE_TYPE);

    FILE* fptr1 = fopen(path1, "r");
    FILE* fptr2 = fopen(path2, "w");

    if (fptr1 == NULL){
        printf("Error: File with key %s%s doesn't exist\n", key1_str, FILE_TYPE);
        return -1;
    }

    if (fptr2 == NULL){
        printf("Error: File with key %s%s can't be created\n", key2_str, FILE_TYPE);
        return -1;
    }

    // copy the contents of the file1 to file2
    char buffer[1024];
    size_t bytes;

    while ((bytes = fread(buffer, 1, sizeof(buffer), fptr1)) > 0){
        fwrite(buffer, 1, bytes, fptr2);
    }

    fclose(fptr1);
    fclose(fptr2);

    printf("Key %s has been copied to %s\n", key1_str, key2_str);

    return 0;
}

