#include <algorithm>
#include <string>
#include <iostream>

/*
	What is the millionth lexicographic permutation of the digits?
*/

using namespace std;

int main() {
	int i = 0;
	string s = "0123456789";

	do {
		i++;
		if(i == 1000000)
			break;
	} while(next_permutation(s.begin(), s.end()));

	cout << s << '\n';
}
