#include <iostream>
#include <cstring>
#include <climits>
#include <set>
#include <vector>

using namespace std;

static vector<int> a(12100, INT_MAX);

/*
	Depth First Search
*/
void dfs(int p, int s, int n, int c) {
    int i, u;

	if(c >= 2 && p < a[p - s + c])
		a[p - s + c] = p;

    u = (12000 + s + c + 1) / (p - 1);
	
    for(i = n; i <= u; i++)
        dfs(p * i, s + i, i, c + 1);
}

int main() {
	int i, sum;
	set<int> st;

	//Generate
	for(i = 2; i < 120; i++)
		dfs(i, i, i, 1);

	//Filter uniek values
	for(i = 2; i <= 12000; i++)
		st.insert(a[i]);

	//Calculate the anwer
	sum = 0;
	for(auto it = st.begin(); it != st.end(); it++)
		sum += *it;

	//Draw
	cout << "result = " << sum << endl;
}