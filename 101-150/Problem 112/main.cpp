#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/vector.h"

using namespace std;

bool isBouncy(int v) {
	int i, t;
	vector<int> l;
	bool inc, dec;
	
	//Init
	l = IamLupo::Vector::to(v);
	inc = false;
	dec = false;
	t = l[0];
	
	for(i = 1; i < l.size(); i++) {
		if(t > l[i])
			dec = true;
		else if(t < l[i])
			inc = true;
		
		if(inc && dec)
			return true;
		
		t = l[i];
	}
	
	return false;
}

int f(double l) {
	int i, c, c2;
	double p;
	
	//Init
	c = 0;
	c2 = 0;
	
	for(i = 10; i < 100000000; i++) {
		if(isBouncy(i)) {
			c++;
			c2++;
			
			p = (double)c / (double)i;
			
			//Debug
			//cout << i << endl;
			
			if(p >= l)
				return i;
		}
		
		//Debug Data pattern
		/*
		if(i % 1 == 0) {
			
			cout << c2 << "	";
			
			if((i + 1) % 10 == 0)
				cout << endl;
			
			c2 = 0;
		}
		*/
	}
	
	return -1; //Unknown
}

int main() {
	cout << "Result = " << f(0.99) << endl;
	
	return 0;
}
