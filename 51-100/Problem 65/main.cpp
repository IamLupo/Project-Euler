#include <iostream>
#include <vector>

#include "IamLupo/sqrt.h"
#include "IamLupo/number.h"

using namespace std;

/*
	Find the sum of digits in the numerator of the
	100th convergent of the continued fraction for e.
*/

//e = [2; 1,2,1, 1,4,1, 1,6,1 , ... , 1,2k,1, ...].
IamLupo::Sqrt::CFraction generateE(int l) {
	int n;
	IamLupo::Sqrt::CFraction r;
	
	n = 2;
	r.push_back(2);
	
	while(r.size() < l) {
		r.push_back(1);
		r.push_back(n);
		r.push_back(1);
		
		n += 2;
	}
	
	return r;
}

int sumDigitsNumerator(int l) {
	int i;
	IamLupo::Sqrt::CFraction fr;
	IamLupo::Sqrt::ExponentialE exp;
	
	fr = generateE(l);
	exp = IamLupo::Sqrt::Expo_Init(fr);
	
	for(i = 1; i < l; i++)
		IamLupo::Sqrt::Expo_Next(exp);
	
	return IamLupo::Number::sum(mpz_get_str(nullptr, 10, exp.x2));
}

int main() {
	cout << "result = " << sumDigitsNumerator(100) << endl;
	
	return 0;
}