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
	For 1 ≤ k ≤ 200, find ∑ m(k).
*/

int f(int l) {
	int i, j, k, v, r;
	vector<int> t;
	vector<vector<vector<int>>> m(l * 3);
	
	//Init
	r = 0;
	m[1] = {{1}};
	
	for(i = 1; i <= l; i++) { 
		for(j = 0; j < m[i].size(); j++) { // Loop options
			for(k = 0; k < m[i][j].size(); k++) { // Loop value
				//Generate value
				v = i + m[i][j][k];
				
				// if no results exist or a lower varient exist
				if(m[v].size() == 0 || m[v][0].size() > m[i][j].size() + 1) {
					t = m[i][j];
					t.push_back(v);
					
					//Create new option list
					m[v] = {t};
				} // A new option with same size exist
				else if(m[v][0].size() == m[i][j].size() + 1) {
					t = m[i][j];
					t.push_back(v);
					
					//Add to option list
					m[v].push_back(t);
				}
			}
		}
		
		r += m[i][0].size();
	}
	
	return r - l;
}

int main() {
	cout << "Result = " << f(200) << endl;
	
	return 0;
}
