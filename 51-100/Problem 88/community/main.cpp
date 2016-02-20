#include <iostream>
#include <cstring>
#include <climits>
#include <set>

using namespace std;

static int a[12100];

void dfs(int p, int s, int n, int c) {
    int u;
	
	if(c >= 2 && p < a[p - s + c])
		a[p - s + c] = p;

    u = (12000 + s + c + 1) / (p - 1);
    for(int i = n; i <= u; i++)
        dfs(p * i, s + i, i, c + 1);
}

int main() {
	int i, sum;
    set<int> st;
	
    for(i = 2; i <= 12000; i++)
        a[i] = INT_MAX;
	
    for(i = 2; i < 120; i++)
        dfs(i, i, i, 1);

    for(i = 2; i <= 12000; i++)
        st.insert(a[i]);

    sum = 0;
    for(auto it = st.begin(); it != st.end(); it++)
        sum += *it;

    cout << sum << endl;
}