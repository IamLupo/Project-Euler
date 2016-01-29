#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


bool isPalindromicNumber(int number, int digit) {
	int i, max_digit;
	char* c_number;

	max_digit = digit * 2;
	c_number = (char*)malloc((max_digit + 1) * sizeof(char));

	sprintf(c_number, "%d", number);
	
	if(strlen(c_number) != max_digit)
		return false;
	
	for(i = 0; i < digit; i++)
		if(c_number[i] != c_number[max_digit - 1 - i])
			return false;
	
	return true;
}

int findHighestPalindromicNumber(int digit) {
	int i, j, sum, highest, max_number;
	
	highest = 0;
	max_number = pow(10, digit) - 1;
	
	for(i = max_number; i > 0; i--) {
		for(j = max_number; j > i; j--) {
			sum = i * j;
			if(isPalindromicNumber(sum, digit) && highest < sum) {
				highest = sum;
			}
		}
	}
	
	return highest;
}

int main() {
	printf("largest palindrome for 2 digit = %d\n", findHighestPalindromicNumber(2));
	printf("largest palindrome for 3 digit = %d\n", findHighestPalindromicNumber(3));
	
	return 0;
}