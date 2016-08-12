#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

/*
	How many distinct ways can a player checkout with a score less than 100?
*/

static vector<int> score_all = {
	1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, // Singles
	2,  4,  6,  8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, // Doubles
	3,  6,  9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48, 51, 54, 57, 60, // Triples
	25, 50, // Middles
};

static vector<int> score_double = {
	2,  4,  6,  8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, // Doubles
	50, // Middles
};

int f(int l) {
	int i, j, k, r;
	
	//Init
	r = 0;
	
	for(i = 0; i < score_double.size(); i++) {
		for(j = 0; j < score_all.size(); j++) {
			for(k = j; k < score_all.size(); k++) {
				//count all hit, hit, double
				if(score_double[i] + score_all[j] + score_all[k] < l)
					r++;
			}
			//count all miss, hit, double
			if(score_double[i] + score_all[j] < l)
				r++;
		}
		//count all miss, miss, double
		if(score_double[i] < l)
			r++;
	}
	
	return r;
}

int main() {
	cout << "result = " << f(100) << endl;

	return 0;
}