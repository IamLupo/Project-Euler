#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

/*
	Statistically it can be shown that the three most popular squares, in order,
	are JAIL (6.24%) = Square 10, E3 (3.18%) = Square 24, and GO (3.09%) = Square 00.
	So these three most popular squares can be listed with the six-digit modal string: 102400.
	
	If, instead of using two 6-sided dice,
	two 4-sided dice are used, find the six-digit modal string.
*/

/*
	two 6-sided dice:
		2:	{1, 1},					= 1 / 21 = 4.76%
		3:	{2, 1},					= 1 / 21 = 4.76%
		4:	{3, 1}, {2, 2}			= 2 / 21 = 9.52%
		5:	{4, 1}, {3, 2}			= 2 / 21 = 9.52%
		6:	{5, 1}, {4, 2}, {3, 3}	= 3 / 21 = 14.29%
		7:	{6, 1}, {5, 2}, {4, 3}	= 3 / 21 = 14.29%
		8:	{6, 2}, {5, 3}, {4, 4}	= 3 / 21 = 14.29%
		9:	{6, 3}, {5, 4}			= 2 / 21 = 9.52%
		10:	{6, 4}, {5, 5}			= 2 / 21 = 9.52%
		11:	{6, 5}					= 1 / 21 = 4.76%
		12:	{6, 6}					= 1 / 21 = 4.76%
	
	two 4-sided dice:
		2:	{1, 1},					= 1 / 10 = 10%
		3:	{2, 1},					= 1 / 10 = 10%
		4:	{3, 1}, {2, 2}			= 2 / 10 = 20%
		5:	{4, 1}, {3, 2}			= 2 / 10 = 20%
		6:	{4, 2}, {3, 3}			= 2 / 10 = 20%
		7:	{4, 3},					= 1 / 10 = 10%
		8:	{4, 4},					= 1 / 10 = 10%
	
	Community Chest (CC):
		1: Advance to GO			= 1 / 16 = 6.25%
		2: Go to JAIL				= 1 / 16 = 6.25%
		
		extra:
			On first time card pick there is a 12.5% chance we have to move
		
	Chance (CH):
		Advance to GO					= 1 / 16 = 6.25%
		Go to JAIL						= 1 / 16 = 6.25%
		Go to C1						= 1 / 16 = 6.25%
		Go to E3						= 1 / 16 = 6.25%
		Go to H2						= 1 / 16 = 6.25%
		Go to R1						= 1 / 16 = 6.25%
		Go to next R (railway company)	= 1 / 16 = 6.25%
		Go to next R					= 1 / 16 = 6.25%
		Go to next U (utility company)	= 1 / 16 = 6.25%
		Go back 3 squares.				= 1 / 16 = 6.25%

		extra:
			On first time card pick there is a 62.5% chance we have to move
		
	Jail:
		G2J								= ???%
		Community Chest					= 6.25%
		Chance							= 6.25%
		
		three consecutive doubles:
			two 6-sided dice			= 6 / 9261 = 0.06%
			two 4-sided dice			= 4 / 1000 = 0.4%
*/

vector<string> board = {
	"GO", "A1", "CC1", "A2", "T1", "R1", "B1", "CH1", "B2", "B3",
	"JAIL", "C1", "U1", "C2", "C3", "R2", "D1", "CC2", "D2", "D3",
	"FP", "E1", "CH2", "E2", "E3", "R3", "F1", "F2", "U2", "F3",
	"G2J", "G1", "G2", "CC3", "G3", "R4", "CH3", "H1", "T2", "H2"
};

static vector<int> community_chest = {
	0, 10, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1
};

static vector<int> chance = {
	0, 10, 11, 24, 39, 5, -3, -2,
	-4, -5, -1, -1, -1, -1, -1, -1
};

int getCard(vector<int> &c) {
	int r;
	
	r = c[0];
	c.erase(c.begin());
	c.push_back(r);
	
	return r;
}

int getHighestStatics(int d) {
	int i, j, p, d1, d2, db, dbn, c, v;
	vector<int> r(40, 0), h;
	vector<int>::iterator it;
	
	srand(time(NULL));
	
	for(i = 0; i < 1000; i++) {
		//Shuffle the cards
		random_shuffle(chance.begin(), chance.end());
		random_shuffle(community_chest.begin(), community_chest.end());
		
		//Init 
		p = 0; // position
		db = 0; // rolled doubles
		
		for(j = 0; j < 1000; j++) {
			//Roll dices
			d1 = rand() % d + 1;
			d2 = rand() % d + 1;
		
			//Check if double dices
			db = (d1 == d2) ? db + 1 : 0;
			
			//Go to jail when 3x double dices
			if(db == 3) {
				db = 0;
				p = 10;
			} else {
				p = (p + d1 + d2) % 40;
			}
			
			//Save result where we have been
			r[p]++;
			
			if(p == 30) { // Go 2 Jail
				p = 10;
				
				//Save result where we have been
				r[p]++;
			}
			//Community Chest (CC)
			else if(p == 2 || p == 17 || p == 33) {
				c = getCard(community_chest);
				
				if(c >= 0) {
					p = c;
					
					//Save result where we have been
					r[p]++;
				}
			}
			//Chance (CH)
			else if(p == 7 || p == 22 || p == 36) {
				c = getCard(chance);
				
				if(c >= 0) { 
					p = c;
					
					//Save result where we have been
					r[p]++;
				} else if(c == -2) { // Go to next R (railway company)
					if(p == 7) // CH1 -> R1
						p = 5;
					else if(p == 22) // CH2 -> R2
						p = 15;
					else if(p == 36) // CH3 -> R3
						p = 25;
					
					//Save result where we have been
					r[p]++;
				} else if(c == -3) { // Go to next R
					if(p == 7) // CH1 -> R2
						p = 15;
					else if(p == 22) // CH2 -> R3
						p = 25;
					else if(p == 36) // CH3 -> R1
						p = 5;
					
					//Save result where we have been
					r[p]++;
				} else if(c == -4) { // Go to next U (utility company)
					if(p == 7 || p == 36) // CH1 -> U1 or CH3 -> U1
						p = 12;
					else if(p == 22) // CH2 -> U2
						p = 28;
					
					//Save result where we have been
					r[p]++;
				} else if(c == -5) {// Go back 3 squares.
					p -= 3;
					
					//Save result where we have been
					r[p]++;
				}
			}
		}
	}
	
	//Generate answer
	v = 0;
	h = r;
	sort(h.begin(), h.end());
	reverse(h.begin(), h.end());
	
	for(i = 0; i < 3; i++) {
		v *= 100;
		it = find(r.begin(), r.end(), h[i]);
		v += (it - r.begin());
	}
	
	/*
	//Debug
	for(i = 0; i < r.size(); i++)
		if(r[i] > 3000000)
			cout << board[i] << "(" << i << ") = " << ((r[i] / 10000) / 100.0) << "%" << endl;
	*/
	
	return v;
}

int main() {
	cout << "result = " << getHighestStatics(4) << endl;
	
	return 0;
}
