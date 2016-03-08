#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;

/*
	If all the numbers from 1 to 1000 (one thousand) inclusive were written
	out in words, how many letters would be used? 
*/

int getLength(int value) {
	int l, x[4];
	
	l = 0;
	
	//first decimal number
	x[0] = value % 10;
	switch(x[0]) {
		case 0: l += 0; break;
		case 1: l += 3; break; // one
		case 2: l += 3; break; // two
		case 3: l += 5; break; // three
		case 6: l += 3; break; // six
		case 7: l += 5; break; // seven
		case 8: l += 5; break; // eight
		default: l += 4; break; // 0, 4, 5, 9
	}
	
	if(value < 10)
		return l;
	
	value /= 10;
	
	//Second decimal number
	x[1] = value % 10;
	switch(x[1]) {
		case 0: l += 0; break;
		case 1:
			switch(x[0]) {
				case 0: l += 3; break;	// 10: ten
				case 1: l += 3; break;	// 11: eleven
				case 2: l += 3; break; // 12: twelve
				case 3: l += 3; break; // 13: thirteen
				case 5: l += 3; break; // 15: fifteen
				case 8: l += 3; break; // 18: eighteen
				default: l += 4; break; // 14, 16, 17, 19
			}
		break;
		case 4: l += 5; break; // 40: forty
		case 5: l += 5; break; // 50: fifty
		case 6: l += 5; break; // 60: sixty
		case 7: l += 7; break; // 70: seventy
		default: l += 6; break; // 20, 30, 80, 90
	}
	
	if(value < 10)
		return l;
	
	value /= 10;
	
	//third decimal number
	x[2] = value % 10;
	switch(x[2]) { // + hundred
		case 1: l += 10; break; // one
		case 2: l += 10; break; // two
		case 3: l += 12; break; // three
		case 6: l += 10; break; // six
		case 7: l += 12; break; // seven
		case 8: l += 12; break; // eight
		default: l += 11; break; // 0, 4, 5, 9
	}
	
	if(x[0] != 0 || x[1] != 0) // One hundred --> AND <-- Twenty
		l += 3;
	
	if(value < 10)
		return l;
	
	return 11;
}

long long sumLength(int m) {
	int i;
	long long r;
	
	r = 0;
	
	for(i = 1; i <= m; i++)
		r += getLength(i);
	
	return r;
}

int main() {
	cout << "result = " << sumLength(1000) << endl;
	
	return 0;
}
