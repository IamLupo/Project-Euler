#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdint.h>

/*
	What is the total of all the name scores in the file?
*/

using namespace std;

void readFile(vector<string>& list, const char* filename) {
	string temp;
	
	ifstream file(filename);
	
	if(file.is_open()) {
		while(file.good()) {
			getline(file, temp, '"');
			
			if(temp.size() > 1) {
				list.push_back(temp);
			}
		}
	}
	
	file.close();
}

uint64_t calcTotalNameScore(vector<string>& list) {
	uint64_t score = 0;
	
	for(int i = 0; i < list.size(); i++)
		for(std::string::iterator it = list[i].begin(); it != list[i].end(); ++it)
			score += ((int)*it -  64) * (i + 1);
	
	return score;
}

int main() {
	int i;
	vector<string> list;
	
	readFile(list, "names.txt");
	sort(list.begin(), list.end());
	
	cout << calcTotalNameScore(list) << endl;

	return 0;
}
