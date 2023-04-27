#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DIR_NAME "FilesPractice3"
#define FILE_TYPE ".txt"
#define MAX_SIZE 256

const char* get_key_str(int key){
	int key_mem;
	if (key < 0){
		key_mem = -key;
	} else if (key == 0){
		key_mem = 1;
	} else {
		key_mem = key;
	}
	char key_str[(int)((ceil(log10(key_mem))+1)*sizeof(char))]; // inside fancy way to calculate dynamically size of key_str
	sprintf(key_str, "%d", key);

	char* key_ptr = (char*)malloc((int)((ceil(log10(key_mem))+1)*sizeof(char)));
	strcpy(key_ptr, key_str);
	return key_ptr;
}


const char* get_path(const char* key_str){
	// creating a path to file
	char path[strlen(DIR_NAME) + strlen(key_str) + strlen(FILE_TYPE) + 2]; // 2 becuase of "/" and EOF
	snprintf(path, sizeof(path), "%s/%s%s", DIR_NAME, key_str, FILE_TYPE);

	char* path_ptr = (char*)malloc(strlen(DIR_NAME) + strlen(key_str) + strlen(FILE_TYPE) + 2);
	strcpy(path_ptr, path);

	return path_ptr;
}

int check_size_v1(char *value1){
	int n = strlen(value1)+1;

	if(n > MAX_SIZE){
		return -1; // If size if bigger.
	}

	return 0;
}
