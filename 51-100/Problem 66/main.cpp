#include <iostream>
#include <vector>

#include "sqrt.h"

using namespace std;

long long findLargest(int l) {
	int i;
	long long d, r;
	mpz_t v, t, h;
	IamLupo::Sqrt::CFraction fr;
	IamLupo::Sqrt::ExponentialE exp;
	bool f;
	
	//Init
	mpz_init(v);
	mpz_init(t);
	mpz_init(h);
	r = -1;
	
	for(d = 1; d <= l; d++) {
		fr = IamLupo::Sqrt::ContinuedFraction(d);
		if(fr.size() > 1) {
			exp = IamLupo::Sqrt::Expo_Init(fr);
			IamLupo::Sqrt::Expo_Next(exp);
			f = false;
			
			while(!f) {
				//x^2 - (d * y^2)
				mpz_mul(t, exp.x2, exp.x2);
				mpz_mul(v, exp.y2, exp.y2);
				mpz_mul_ui(v, v, d);
				mpz_sub(v, t, v);
				
				if(mpz_cmp_ui(v, 1) == 0) {
					//Found new higher x
					if(mpz_cmp(h, exp.x2) < 0) {
						//h = x
						mpz_set(h, exp.x2);
						r = d;
						
						//Debug
						//cout << mpz_get_str(nullptr, 10, exp.x2) << "^2 - ("
						//	<< d << " * "
						//	<< mpz_get_str(nullptr, 10, exp.y2) << "^2) = 1" << endl;
					}
					
					f = true;
				} else {	
					//We can skip all even generations
					IamLupo::Sqrt::Expo_Next(exp);
					IamLupo::Sqrt::Expo_Next(exp);
				}
				
			}
			IamLupo::Sqrt::clear(exp);
		}
		else if(l >= 10)
			d += 4;
	}
	
	return r;
}

int main() {
	cout << "result = " << findLargest(1000) << endl;
	
	return 0;
}