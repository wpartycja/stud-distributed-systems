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
	char line[MAX_LEN];
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
	fgets(line, MAX_LEN, f);	

	// Extract the first token
	token = strtok(line, ", ");

	// Loop through the string to extract all other tokens.
	while((token != NULL) && i < 3){
		token = strtok(NULL, ", ");
		switch(i){
			case 0:
				value1 = token;
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
        	return = -1;
    	}

	return 0;
}

// int modify_value(int key, char, *value1, int value2, double value3){

// }

// int delete_key(int key){

// }

// int copy_key(int key1, int key2){

// }

