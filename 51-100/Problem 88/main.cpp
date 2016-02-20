#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/number.h"

using namespace std;

/*
	What is the sum of all the minimal product-sum numbers for 2≤k≤12000?
*/

/*
	f(1) = 1								= 1								= 1
	f(2) = 2 × 2 							= 2 + 2							= 4
	f(3) = 1 × 2 × 3 						= 1 + 2 + 3						= 6
	f(4) = 1 × 1 × 2 × 4 					= 1 + 1 + 2 + 4					= 8
	f(5) = 1 × 1 × 2 × 2 × 2 				= 1 + 1 + 2 + 2 + 2				= 8
	f(6) = 1 × 1 × 1 × 1 × 2 × 6 			= 1 + 1 + 1 + 1 + 2 + 6			= 12
	f(7) = 1 × 1 × 1 × 1 × 1 × 4 × 3 		= 1 + 1 + 1 + 1 + 1 + 4 + 3		= 12
	f(8) = 1 × 1 × 1 × 1 × 1 × 2 × 2 x 3	= 1 + 1 + 1 + 1 + 1 + 2 + 2 + 3	= 12
	
	f(n) results:
		1, 4, 6, 8, 8, 12, 12, 12, 15, 16, 16, 16, 18, 20, 24, 24, 24, 24, 24, 28, 27, 32,
		30, 48, 32, 32, 32, 36, 36, 36, 42, 40, 40, 48, 48, 48, 45, 48, 48, 48, 48, 48, 54,
		60, 54, 56, 54, 60, 63, 60, 60, 60, 63, 64, 64, 64, 64, 64, 70, 72, 72, 72, 72, 72,
		72, 84, 80, 80, 81, 80, 80
	
	n < f(n) <= n * 2
*/

static int lowest;
static int loop;
static int found_at;
static int loop_max;

void bruteforce(int target, int x, int sum_p, int sum_m, int l) {
	int i, m, p;
	
	if(target == l) {
		if(sum_p == sum_m && lowest > sum_p) {
			lowest = sum_p;
			found_at = loop;
		}
	}
	else {
		for(i = x; i <= target; i++) {
			p = sum_p + i;
			m = sum_m * i;
			loop++;
			
			if(lowest > p && p >= m) {
				bruteforce(target, i, p, m, l + 1);
				
				if(loop > loop_max)
					return;
			}
			else
				i = target;
		}
	}
}

int sumProduct(int l) {
	int i;
	vector<int> r;
	vector<int>::iterator it;
	
	loop_max = 25;
	
	for(i = 2; i <= l; i++) {
		//Calc f(i)
		loop = 0;
		lowest = i * 2;
		if(found_at != 0 && loop_max < found_at * 1.5)
			loop_max = found_at * 1.5;
		found_at = 0;
		
		bruteforce(i, 1, 0, 1, 0);
		
		//only add the result once to the list
		it = find(r.begin(), r.end(), lowest);
		if(it == r.end())
			r.push_back(lowest);
		
		//Debug
		system("clear");
		cout << "Progress: " << i << "/" << l << endl;
		cout << found_at << "/" << loop << endl;
		
	}
	
	//system("clear");
	return IamLupo::Number::sum(r);
}

int main() {
	cout << "result = " << sumProduct(12000) << endl;
	
	return 0;
}
