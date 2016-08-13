#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "gmp.h"
#include "IamLupo/prime.h"
#include "IamLupo/number.h"

using namespace std;

/*
	Find the sum of all S(10, d).
*/

static IamLupo::Primes primes;

struct Data {
	int n; // Max length value
	int d; // Repeatable value
	
	vector<int> l; // List values
	
	bool f; // Found valid result
	
	mpz_t r; // Result
};

/*
	Check all permutations with generated list numbers
	Updates the data when he founds a valid prime
*/
void update(Data &da) {
	long long v;
	
	//Sort the list to let the next permutation loop all possebilities
	sort(da.l.begin(), da.l.end());
	
	do {
		//Convert list of numbers to integer
		v = IamLupo::Number::to(da.l);
		
		if(v >= pow(10, da.n - 1) && IamLupo::Prime::is(primes, v)) {
			// Result += v
			mpz_add_ui(da.r, da.r, v);
			
			//We found results
			da.f = true;
			
			//Debug
			//cout << v << endl;
		}
	} while(next_permutation(da.l.begin(), da.l.end()));
}

/*
	Generate the empty space in data->l vector
*/
void gen(Data &da, int p, int l, int m) {
	int i;
	vector<int> t;
	
	//When all emptry space is filled
	if(l == m) {
		update(da);
		
		return;
	}
	
	//Fill up all possible values in the data->l empty space
	for(i = p; i < 10; i++) {
		//Backup list
		t = da.l;
		
		//Generate second generation list
		da.l.push_back(i);
		
		//Generate next level
		gen(da, i, l + 1, m);
		
		//Restore old list
		da.l = t;
	}
}

void algo(Data &da, int l) {
	int i;
	
	//Init
	da.l.clear();
	da.f = false;
	
	//Generate the data->l with the repeatable number
	for(i = 0; i < da.n - l; i++)
		da.l.push_back(da.d);
	
	//Fill up the emptry space in data->l
	gen(da, 0, 0, l);
	
	//Check if valid result is found
	if(!da.f)
		algo(da, l + 1);
}

string f(int n) {
	Data da;
	string s;
	
	//Init
	da.n = n;
	mpz_init_set_ui(da.r, 0);
	
	//Loop all repeatable values
	for(da.d = 0; da.d < 10; da.d++)
		algo(da, 1);
	
	//Convert result to string
	s = mpz_get_str(nullptr, 10, da.r);
	
	//Clean
	mpz_clear(da.r);
	
	return s;
}

int main() {
	primes = IamLupo::Prime::generate(81000);
	
	//cout << "Result = " << f(4) << endl;
	cout << "Result = " << f(10) << endl;
	
	return 0;
}
