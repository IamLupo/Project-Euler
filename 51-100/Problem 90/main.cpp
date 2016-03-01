#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;

/*
	How many distinct arrangements of the two cubes allow for all
	of the square numbers to be displayed?
*/

static vector<vector<int>> combi = {
	{0, 1}, {0, 4}, {0, 9}, {1, 6}, {2, 5}, {3, 6}, {4, 9}, {6, 4}, {8, 1}
};

bool valid(const vector<int> &d1, const vector<int> &d2) {
	int i, v;
	vector<int>::const_iterator d1_1, d1_2, d2_1, d2_2;
	
	for(i = 0; i < combi.size(); i++) {
		d1_1 = find(d1.begin(), d1.end(), combi[i][0]);
		d1_2 = find(d1.begin(), d1.end(), combi[i][1]);
		d2_1 = find(d2.begin(), d2.end(), combi[i][0]);
		d2_2 = find(d2.begin(), d2.end(), combi[i][1]);
		
		/*
			6 and 9 can make each other
		*/
		v = combi[i][0];
		if(v == 6 || v == 9) {
			if(d1_1 == d1.end())
				d1_1 = find(d1.begin(), d1.end(), (v == 6) ? 9 : 6);
			
			if(d2_1 == d2.end())
				d2_1 = find(d2.begin(), d2.end(), (v == 6) ? 9 : 6);
		}
		
		v = combi[i][1];
		if(v == 6 || v == 9) {
			if(d1_2 == d1.end())
				d1_2 = find(d1.begin(), d1.end(), (v == 6) ? 9 : 6);
			
			if(d2_2 == d2.end())
				d2_2 = find(d2.begin(), d2.end(), (v == 6) ? 9 : 6);
		}
		
		//Check result
		if(d1_1 == d1.end() || d2_2 == d2.end())
			if(d1_2 == d1.end() || d2_1 == d2.end())
				return false;
	}
	
	return true;
}

//Generate possible dices
vector<vector<int>> generate() {
	int i, j, k, l, m, n;
	vector<vector<int>> r;
	
	for(i = 0; i < 10; i++) {
		for(j = i + 1; j < 10; j++) {
			for(k = j + 1; k < 10; k++) {
				for(l = k + 1; l < 10; l++) {
					for(m = l + 1; m < 10; m++) {
						for(n = m + 1; n < 10; n++) {
							r.push_back({i, j, k, l, m, n});
						}
					}
				}
			}
		}
	}
	
	return r;
}

int countDistinctCombinations() {
	int i, j, r;
	vector<vector<int>> d;

	r = 0;
	d = generate();
	
	for(i = 0; i < d.size(); i++) {
		for(j = i + 1; j < d.size(); j++) {
			if(valid(d[i], d[j])) {
				r++;
			}
		}
	}
	
	return r;
}

int main() {
	cout << "result = " << countDistinctCombinations() << endl;
	
	return 0;
}
