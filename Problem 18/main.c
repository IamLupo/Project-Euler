#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/*
	Find the maximum total from top to bottom of the triangle 
*/

struct Triangle {
	int length;
	int** data;
};

struct Level {
	int level;
	int* data;
};

void drawTriangle(struct Triangle* tri) {
	int i, j;
	
	for(i = 0; i < tri->length; i++) {
		for(j = 0; j <= i; j++) {
			printf("%d ", tri->data[i][j]);
		}
		printf("\n");
	}
}

void drawLevel(struct Level* lvl) {
	int i;
	
	printf("Data: [");
	for(i = 0; i < lvl->level; i++) {
		printf("%d, ", lvl->data[i]);
	}
	printf("]\n");
}

void initLevel(struct Level* lvl) {
	lvl->level = 0;
	lvl->data = malloc(0);
}

void copyLevel(struct Level* destination, struct Level* input) {
	// Remove level data
	free(destination->data);
	
	// Copy pointer to destination
	*destination = *input;
}

void initTriangleLevel(struct Triangle* tri, struct Level* lvl) {
	int i;
	
	lvl->level = tri->length;
	lvl->data = realloc(lvl->data, lvl->level * sizeof(int));
	
	for(i = 0; i < lvl->level; i++) {
		lvl->data[i] = tri->data[lvl->level - 1][i];
	}
}

void nextTriangleLevel(struct Triangle* tri, struct Level* lvl, struct Level* next_lvl) {
	int i, a, b;
	
	next_lvl->level = lvl->level - 1;
	next_lvl->data = realloc(next_lvl->data, next_lvl->level * sizeof(int));
	
	for(i = 0; i < next_lvl->level; i++) {
		a = tri->data[next_lvl->level - 1][i] + lvl->data[i];
		b = tri->data[next_lvl->level - 1][i] + lvl->data[i + 1];
		
		if(a > b)
			next_lvl->data[i] = a;
		else
			next_lvl->data[i] = b;
	}
}

void readTriangleFile(struct Triangle* tri, char* input_file) {
	int i, id;
	char data[2 + 1];
	bool finished = false;
	FILE* pFile;
	
	pFile = fopen(input_file , "r");
	tri->length = 1;
	tri->data = malloc(1 * sizeof(int*));
	tri->data[0] = malloc(1 * sizeof(int));
	
	while(!feof(pFile)) {
		for(i = 0; i < tri->length; i++) {
			if(fread(data, 1, 2, pFile) == 0) {
				finished = true;
				break;
			}
			
			tri->data[tri->length - 1][i] = atoi(data);
			
			fseek(pFile, 1, SEEK_CUR);
		}
		if(finished) {
			tri->length--;
			break;
		}
		
		fseek(pFile, 1, SEEK_CUR);
		
		tri->length++;
		tri->data = realloc(tri->data, tri->length * sizeof(int*));
		tri->data[tri->length - 1] = malloc(tri->length * sizeof(int));
	}
	
	fclose(pFile);
}

int getHighestSum(char* input_file) {
	int i;
	struct Triangle tri;
	struct Level lvl, next_lvl;
	
	initLevel(&lvl);
	initLevel(&next_lvl);
	
	readTriangleFile(&tri, input_file);
	initTriangleLevel(&tri, &lvl);
	
	for(i = 0; i < tri.length - 1; i++) {
		nextTriangleLevel(&tri, &lvl, &next_lvl);
		copyLevel(&lvl, &next_lvl);
		initLevel(&next_lvl);
	}
	
	return lvl.data[0];
}

int main() {
	printf("highest sum = %d\n", getHighestSum("triangle.txt"));
	
	return 0;
}