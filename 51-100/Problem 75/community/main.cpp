#include<iostream>

/*
	https://en.wikipedia.org/wiki/Tree_of_primitive_Pythagorean_triples
*/

using namespace std;

#define MAX_NUM 1500000

int array_L[MAX_NUM] = {0};

void generate_triplets(int m, int n) {
	int i, v;
	
	//calc L
	v = 2 * m * (m + n);
	
	//End of level
	if(v > MAX_NUM)
		return;

	//Save results
	for(i = v; i <= MAX_NUM; i += v)
		array_L[i]++;

	//Generate next level
	generate_triplets(2 * m - n, m);
	generate_triplets(2 * m + n, m);
	generate_triplets(m + 2 * n, n);
}

int main() {
	int c = 0;
	
	//Generate
	generate_triplets(2, 1);
	
	//Find result
	for(int i = 0; i < MAX_NUM; ++i)
		if(array_L[i] == 1)
			c++;
	
	//Draw
	cout << c << endl;
	
	return 0;
}