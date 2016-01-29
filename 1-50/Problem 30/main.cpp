#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

/*
	Find the sum of all the numbers that can be written as the sum
	of fifth powers of their digits.
*/

static vector<int> options;
static int result;

void bruteforce(int v, int r, int level, int max) {
	int i;
	
	if(level == max) {
		if(v == r && v != 1)
			result += v;
		
		return;
	}
	
	for(i = 0; i < options.size(); i++)
		bruteforce(
			v + options[i],
			r + (i * pow(10, level)),
			level + 1,
			max
		);
}

int sumNumbersOfPowers(int d) {
	int i;
	
	//Init
	result = 0;
	options.clear();
	
	//Calculate powers
	for(i = 0; i < 10; i++)
		options.push_back(pow(i, d));
	
	//Find numbers
	bruteforce(0, 0, 0, d + 1);
}

int main() {
	sumNumbersOfPowers(5);
	cout << "result = " << result << endl;
	
	return 0;
}