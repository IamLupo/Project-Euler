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

static IamLupo::Primes primes;

void test_generate(int l) {
	unsigned int start, end;
	
	start = clock();
	primes = IamLupo::Prime::generate(l);
	end = clock();
	cout << "generate: " << end - start << " ticks" << endl;
}

void test_readFile(int l) {
	unsigned int start, end;
	
	start = clock();
	primes = IamLupo::Prime::readFile(l);
	end = clock();
	cout << "readFile: " << end - start << " ticks" << endl;
}

void test_speed() {
	cout << "primes 1000 or lower:" << endl;
	test_generate(1000);
	test_readFile(1000);
	
	cout << "primes 10000 or lower:" << endl;
	test_generate(10000);
	test_readFile(10000);
	
	cout << "primes 100000 or lower:" << endl;
	test_generate(100000);
	test_readFile(100000);
	
	cout << "primes 1000000 or lower:" << endl;
	test_generate(1000000);
	test_readFile(1000000);
	
	cout << "primes 10000000 or lower:" << endl;
	test_generate(10000000);
	test_readFile(10000000);
	
	cout << "primes 100000000 or lower:" << endl;
	test_generate(100000000);
	test_readFile(100000000);
}

void test_data() {
	int i;
	primes = IamLupo::Prime::generate(100000000);
	
	//Debug
	cout << "First 10 primes :" << endl;
	for(i = 0; i < 10; i++)
		cout << primes[i] << endl;
	
	cout << "Last 10 primes :" << endl;
	for(i = primes.size() - 10; i < primes.size(); i++)
		cout << primes[i] << endl;
	
	
	cout << "total primes for 100000000 is " << primes.size() << endl;
}

int main() {
	test_speed();
	test_data();
	
	return 0;
}
