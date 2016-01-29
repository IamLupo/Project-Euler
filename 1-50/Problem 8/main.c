#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

char numbers[] = 
	"73167176531330624919225119674426574742355349194934"
	"96983520312774506326239578318016984801869478851843"
	"85861560789112949495459501737958331952853208805511"
	"12540698747158523863050715693290963295227443043557"
	"66896648950445244523161731856403098711121722383113"
	"62229893423380308135336276614282806444486645238749"
	"30358907296290491560440772390713810515859307960866"
	"70172427121883998797908792274921901699720888093776"
	"65727333001053367881220235421809751254540594752243"
	"52584907711670556013604839586446706324415722155397"
	"53697817977846174064955149290862569321978468622482"
	"83972241375657056057490261407972968652414535100474"
	"82166370484403199890008895243450658541227588666881"
	"16427171479924442928230863465674813919123162824586"
	"17866458359124566529476545682848912883142607690042"
	"24219022671055626321111109370544217506941658960408"
	"07198403850962455444362981230987879927244284909188"
	"84580156166097919133875499200524063689912560717606"
	"05886116467109405077541002256983155200055935729725"
	"71636269561882670428252483600823257530420752963450";

uint64_t greatestProductPart(int digit, char* numbers) {
	int i, number, position;
	uint64_t sum, highest;
	
	//Init
	position = 0;
	sum = 1;
	highest = 0;

	while(position + digit <= strlen(numbers)) {
		if(sum == 1) {
			for(i = 0; i < digit; i++) {
				sum *= (int)numbers[position + i] - 0x30;
			}
		}
		else
		{
			sum *= (int)numbers[position + digit - 1] - 0x30;
			sum /= (int)numbers[position - 1] - 0x30;
		}
		
		if(sum > highest)
			highest = sum;
		
		position++;
	}
	
	return highest;
}

uint64_t greatestProduct(int digit, char* numbers) {
	uint64_t sum, highest;
	char* temp_numbers;
	char* part;
	
	//Init
	sum = 0;
	highest = 0;
	
	temp_numbers = (char*)malloc(strlen(numbers) + 1 * sizeof(char));
	strcpy(temp_numbers, numbers);
	
	part = strtok(temp_numbers, "0");
	while(part != NULL) {
		
		if(strlen(part) >= digit) {
			sum = greatestProductPart(digit, part);
			
			//printf("Result: %lld - %s\n", (long long)sum, part);
		}
		
		if(sum > highest)
			highest = sum;
		
		part = strtok(NULL, "0");
	}
	
	return highest;
}

int main() {
	/*
		Result:
			9 × 9 × 8 × 9 = 5832
	*/
	printf("4 digits greatest product is %lld\n", (long long)greatestProduct(4, numbers));
	
	/*
		Challange result:
			5 * 5 * 7 * 6 * 6 * 8 * 9 * 6 * 6 * 4 * 8 * 9 * 5 = 23514624000
	*/
	printf("13 digits greatest product is %lld\n", (long long)greatestProduct(13, numbers));
	
	return 0;
}