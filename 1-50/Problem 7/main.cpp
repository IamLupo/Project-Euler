#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/prime.h"

using namespace std;

/*
	What is the 10 001st prime number?
*/

static IamLupo::Primes primes;

int main() {
	primes = IamLupo::Prime::generate(400);
	
	cout << "result = " << primes[10000] << endl;
	
	return 0;
}
