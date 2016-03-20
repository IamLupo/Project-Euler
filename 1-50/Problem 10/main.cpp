#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/prime.h"
#include "IamLupo/number.h"

using namespace std;

/*
	Find the sum of all the primes below two million.
*/

static IamLupo::Primes primes;

int main() {
	primes = IamLupo::Prime::generate(2000000);
	
	cout << "result = " << IamLupo::Number::sum(primes) << endl;
	
	return 0;
}
