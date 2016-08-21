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
	double i, c;
	
	//Init
	i = 10;
	c = 0;
	
	while(true) {
		if(isBouncy(i)) {
			c++;
			
			if(c / i >= l)
				return i;
		}
		i++;
	}
	
	return -1; //Unknown
}

int main() {
	cout << "Result = " << f(0.99) << endl;
	
	return 0;
}
