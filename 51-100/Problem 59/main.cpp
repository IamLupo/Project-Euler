#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>

#include "gmp.h"
#include "string.h"

using namespace std;

/*
	What is the message in "cipher.txt" ?
*/

vector<int> readFile(string &f) {
	int i;
	string v;
	vector<string> t;
	vector<int> r;
	string::size_type sz;
	
	ifstream file(f);
	
	if(file.is_open()) {
		while(file.good()) {
			getline(file, v);
			
			if(v.size() > 1) {
				t = IamLupo::String::explode(v, ',');
			}
		}
	}
	
	// Convert string number to integer
	for(i = 0; i < t.size(); i++)
		r.push_back(stoi(t[i], &sz));
	
	file.close();
	
	return r;
}

vector<int> findOptions(const vector<int> &v, int p, int l) {
	int i, j, t;
	bool f;
	vector<int> r;
	
	for(i = 0; i <= 0xFF; i++) {
		f = true;
		
		for(j = p; j < v.size() && f; j += l) {
			t = v[j] ^ i;
			if(t < 0x20 || t > 0x7A)
				f = false;
		}
		
		if(f)
			r.push_back(i);
	}
	
	return r;
}

string decrypt(const string &v, const vector<int> &k) {
	int i, j;
	string r;
	
	//Initialise string
	for(i = 0; i < v.size(); i++)
		r.push_back(0x3F);
		
	//Decrypt text
	for(i = 0; i < k.size(); i++)
		for(j = i; j < v.size(); j += k.size())
			r[j] = v[j] ^ k[i];
	
	return r;
}

vector<string> decrypt(vector<int> v, vector<vector<int>> k) {
	int x, y, z;
	string s, t;
	vector<int> key;
	vector<string> r;
	
	//Convert Integer to Char
	for(x = 0; x < v.size(); x++)
		s.push_back(v[x]);
	
	for(x = 0; x < k[0].size(); x++) {
		for(y = 0; y < k[1].size(); y++) {
			for(z = 0; z < k[2].size(); z++) {
				r.push_back(decrypt(s, {k[0][x], k[1][y], k[2][z]}));
			}
		}
	}
	
	return r;
}

int isEnglish(string s) {
	int c;
	string d;
	string::size_type f;
	
	c = 0;
	
	d.resize(s.size());
	transform(s.begin(), s.end(), d.begin(), ::tolower);
	
	f = 0;
	while((f = d.find("the", f)) != string::npos) {
		c++;
		f += 3;
	}
	
	f = 0;
	while((f = d.find("and", f)) != string::npos) {
		c++;
		f += 3;
	}
	
	f = 0;
	while((f = d.find("is", f)) != string::npos) {
		c++;
		f += 2;
	}
	
	f = 0;
	while((f = d.find("are", f)) != string::npos) {
		c++;
		f += 3;
	}
	
	return c;
}

int sumDecryptedText(string f, int l) {
	int i, t, h, c;
	string r;
	vector<int> v;
	vector<vector<int>> k;
	vector<string> o;
	
	//Read File
	v = readFile(f);
	
	//Look for possible keys
	for(i = 0; i < l; i++)
		k.push_back(findOptions(v, i, l));

	//Store all possible decrypted text
	o = decrypt(v, k);
		
	//Find the text that looks the most english
	h = -1;
	for(i = 0; i < o.size(); i++) {
		t = isEnglish(o[i]);
		if(h < t) {
			h = t;
			r = o[i];
		}
	}
	
	//Sum all charters
	c = 0;
	for(i = 0; i < r.size(); i++)
		c += r[i];

	return c;
}

int main() {
	cout << "result = " << sumDecryptedText("cipher.txt", 3) << endl;
	
	return 0;
}