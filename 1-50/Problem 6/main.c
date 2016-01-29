#include <stdio.h>
#include <math.h>

int sumSquares(int min, int max) {
	int i, sum;
	
	sum = 0;
	
	for(i = min; i <= max; i++) {
		sum += pow(i, 2);
	}
	
	return sum;
}

int squaresSum(int min, int max) {
	int total_values;
	
	//Init
	total_values = max - min + 1;

	if(total_values % 2 == 0)
		return pow(((max + min) * (total_values / 2)), 2);
	else
		return pow(((max + min) * (total_values / 2)) + min + ((total_values - 1) / 2), 2);
}

int main() {
	int x, y;
	
	x = squaresSum(1, 10);
	y = sumSquares(1, 10);
	printf("%d - %d = %d\n", x, y, x - y);
	
	x = squaresSum(1, 100);
	y = sumSquares(1, 100);
	printf("%d - %d = %d\n", x, y, x - y);
	
	return 0;
}