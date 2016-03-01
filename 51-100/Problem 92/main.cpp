#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/vector.h"
#include "IamLupo/number.h"

using namespace std;

/*
	How many starting numbers below ten million will arrive at 89?
*/

int sumSquareRoot(int v) {
	int i;
	vector<int> r;
	
	r = IamLupo::Vector::to(v);
	
	for(i = 0; i < r.size(); i++)
		r[i] *= r[i];
	
	return IamLupo::Number::sum(r);
}

int countSequence(int l) {
	int i, j, v, r;
	static vector<int> f, t;
	
	//Init
	r = 1; // we already have 89
	
	/*
		generate found table
		
		-1 = will not reach to 89
		0 = unknown link
		1 = will reach to 89
	*/
	for(i = 0; i < 10000000; i++)
		f.push_back(0);
	
	//We know that 89 is a valid answer
	f[89] = 1;
	
	//Make all chance
	for(i = 1; i <= l; i++) {
		v = i;
		
		//Initialize temp list
		t.clear();
		t.push_back(v);
		
		//Keep looking for new values till we reach a link
		while(f[v] == 0) {
			//Default say it will not reach 89
			f[v] = -1;
			
			//Calculate next level
			v = sumSquareRoot(v);
			
			//Store in our temp list
			t.push_back(v);
		}
		
		//We found a link to 89
		if(f[v] == 1) {
			//Make all values in temp list that it has a link to 89
			for(j = 0; j < t.size(); j++)
				f[t[j]] = 1;
			
			//add new numbers to total size
			r += t.size() - 1;
		}
	}
	
	//Fix: buffer overflow after multiple calls to "countSequence" function
	f.clear();
	
	return r;
}

int main() {
	cout << "result = " << countSequence(10000000) << endl;
	
	return 0;
}
