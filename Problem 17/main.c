#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "gmp.h"

/*
	If all the numbers from 1 to 1000 (one thousand) inclusive were written
	out in words, how many letters would be used? 
*/
int getTextLength(int value) {
	int length, x[4];
	
	length = 0;
	
	//first decimal number
	x[0] = value % 10;
	switch(x[0]) {
		case 0: length += 0; break;
		case 1: length += 3; break; // one
		case 2: length += 3; break; // two
		case 3: length += 5; break; // three
		case 6: length += 3; break; // six
		case 7: length += 5; break; // seven
		case 8: length += 5; break; // eight
		default: length += 4; break; // 0, 4, 5, 9
	}
	
	if(value < 10)
		return length;
	
	value /= 10;
	
	//Second decimal number
	x[1] = value % 10;
	switch(x[1]) {
		case 0: length += 0; break;
		case 1:
			switch(x[0]) {
				case 0: length += 3; break;	// 10: ten
				case 1: length += 3; break;	// 11: eleven
				case 2: length += 3; break; // 12: twelve
				case 3: length += 3; break; // 13: thirteen
				case 5: length += 3; break; // 15: fifteen
				case 8: length += 3; break; // 18: eighteen
				default: length += 4; break; // 14, 16, 17, 19
			}
		break;
		case 4: length += 5; break; // 40: forty
		case 5: length += 5; break; // 50: fifty
		case 6: length += 5; break; // 60: sixty
		case 7: length += 7; break; // 70: seventy
		default: length += 6; break; // 20, 30, 80, 90
	}
	
	if(value < 10)
		return length;
	
	value /= 10;
	
	//third decimal number
	x[2] = value % 10;
	switch(x[2]) { // + hundred
		case 1: length += 10; break; // one
		case 2: length += 10; break; // two
		case 3: length += 12; break; // three
		case 6: length += 10; break; // six
		case 7: length += 12; break; // seven
		case 8: length += 12; break; // eight
		default: length += 11; break; // 0, 4, 5, 9
	}
	
	if(x[0] != 0 || x[1] != 0) // One hundred --> AND <-- Twenty
		length += 3;
	
	if(value < 10)
		return length;
	
	return 11;
}

uint64_t getSumTextLength(int max) {
	int i;
	uint64_t sum;
	
	sum = 0;
	
	for(i = 1; i <= max; i++)
		sum += getTextLength(i);
	
	return sum;
}

int main() {
	printf("sum = %lld\n", getSumTextLength(5));
	printf("sum = %lld\n", getSumTextLength(1000));
	
	return 0;
}