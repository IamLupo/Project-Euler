#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <set>
#include <climits>

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

static vector<int> list(12100, INT_MAX);

/*
	Depth First Search
*/
void dfs(int product, int sum, int m, int depth, int max) {
    int i, u, pos;

	//Init
	pos = product - sum + depth;
    u = (max + sum + depth + 1) / (product - 1);
	
	//Update value
	if(depth >= 2 && product < list[pos])
		list[pos] = product;
	
	//Next depth
    for(i = m; i <= u; i++)
        dfs(product * i, sum + i, i, depth + 1, max);
}

int sumProduct(int l) {
	int i;
	set<int> st;
	
	//Generate
	for(i = 2; i < 120; i++)
		dfs(i, i, i, 1, l);

	//Filter uniek values
	for(i = 2; i <= l; i++)
		st.insert(list[i]);
	
	return accumulate(st.begin(), st.end(), 0);
}

int main() {
	cout << "result = " << sumProduct(12000) << endl;
	
	return 0;
}
