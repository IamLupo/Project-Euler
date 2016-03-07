#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/fibonacci.h"

using namespace std;

/*
	By considering the terms in the Fibonacci sequence whose values do not exceed four million,
	find the sum of the even-valued terms.
*/

int sumEvenFibonacci(int m) {
	int r;
	IamLupo::Fibonacci::Number n;
	
	//Init
	r = 0;
	n = {0, 1};
	
	while(n.y < m) {
		if(n.y % 2 == 0)
			r += n.y;
		
		IamLupo::Fibonacci::next(n);
	}
	
	return r;
}

int main() {
	cout << "result = " << sumEvenFibonacci(4000000) << endl;
	
	return 0;
}
