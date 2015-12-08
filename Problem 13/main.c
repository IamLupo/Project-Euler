#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "gmp.h"

/*
	Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
*/
uint64_t getSumOfFile(char* output_answer, char* input_file, int colums) {
	FILE* pFile;
	char data[colums + 1];
	mpz_t answer, value;
	
	mpz_init(value);
	mpz_init_set_ui(answer, 0);
	
	pFile = fopen(input_file , "r");
	
	while(!feof(pFile)) {
		//Read the numbers
		if(fread(data, colums, 1, pFile) == 0)
			break;
		data[colums] = 0;
		
		// Get value and add it to the answer
		mpz_set_str(value, data, 10);
		mpz_add(answer, answer, value);
		
		//pass the end of line
		fseek(pFile, 1, SEEK_CUR);
	}
	
	//Put the answer to the
	mpz_get_str(output_answer, 10, answer);
	output_answer[10] = 0;
	
	fclose(pFile);
	
	return 0;
}

int main() {
	char answer[60];
	getSumOfFile(answer, "input.txt", 50);
	
	printf("sum = %s\n", answer);
	
	return 0;
}