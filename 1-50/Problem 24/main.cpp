#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

/*
	What is the millionth lexicographic permutation of the digits?
*/

using namespace std;

string permutation(const string &s, int n) {
	int i;
	string r;
	
	//Init
	i = 0;
	r = s;
	
	do {
		i++;
		if(i == n)
			break;
	} while(next_permutation(r.begin(), r.end()));
	
	return r;
}

int main() {
	cout << "result = " << permutation("0123456789", 1000000) << '\n';
	
	return 0;
}
