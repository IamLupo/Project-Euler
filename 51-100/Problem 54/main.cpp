#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>

#include "gmp.h"

using namespace std;

/*
	How many hands does Player 1 win?
*/

#define CARD_VALUE					0x0
#define CARD_TYPE					0x1

#define CARD_VALUE_UNKNOWN			0x0
#define CARD_VALUE_JACK				0xB
#define CARD_VALUE_QUEEN			0xC
#define CARD_VALUE_KING				0xD
#define CARD_VALUE_ACE				0xE

#define CARD_TYPE_UNKNOWN			0x0
#define CARD_TYPE_SPADES			0x1
#define CARD_TYPE_HEATS				0x2
#define CARD_TYPE_DIAMONDS			0x3
#define CARD_TYPE_CLUBS				0x4

#define CARDS_STATE_HIGH_CARD		0x0
#define CARDS_STATE_ONE_PAIR		0x1
#define CARDS_STATE_TWO_PAIR		0x2
#define CARDS_STATE_THREE_OF_A_KIND	0x3
#define CARDS_STATE_STRAIGHT		0x4
#define CARDS_STATE_FLUSH			0x5
#define CARDS_STATE_FULL_HOUSE		0x6
#define CARDS_STATE_FOUR_OF_A_KIND	0x7
#define CARDS_STATE_STRAIGHT_FLUSH	0x8
#define CARDS_STATE_ROYAL_FLUSH		0x9

const vector<string> explode(const string &s, const char &c) {
	string buff{""};
	vector<string> v;
	
	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
}

void readFile(vector<vector<string>> &l, string &f) {
	string v;
	vector<string> g;
	
	ifstream file(f);
	
	if(file.is_open()) {
		while(file.good()) {
			getline(file, v);
			
			if(v.size() > 1) {
				g = explode(v, ' ');
				l.push_back(g);
			}
		}
	}
	
	file.close();
}

void getValueAndType(const string& s, vector<int> &v, vector<int> &t) {
	switch(s[0]) {
		case 'T':	v.push_back(10);				break;
		case 'J':	v.push_back(CARD_VALUE_JACK);	break;
		case 'Q':	v.push_back(CARD_VALUE_QUEEN);	break;
		case 'K':	v.push_back(CARD_VALUE_KING);	break;
		case 'A':	v.push_back(CARD_VALUE_ACE);	break;
		default: 	v.push_back(s[0] - 0x30);		break;
	}
	
	switch(s[1]) {
		case 'S':	t.push_back(CARD_TYPE_SPADES);		break;
		case 'H':	t.push_back(CARD_TYPE_HEATS);		break;
		case 'D':	t.push_back(CARD_TYPE_DIAMONDS);	break;
		case 'C':	t.push_back(CARD_TYPE_CLUBS);		break;
	}
}

vector<int> countMostCard(vector<int> v) {
	int i, c, t;
	vector<int> r;
	
	c = 1;
	t = v[0];
	
	r.push_back(c);
	r.push_back(t);
	
	for(i = 1; i < v.size(); i++) {
		if(t == v[i]) {
			c++;
		} else {
			c = 1;
			t = v[i];
		}
		
		if(c > r[0]) {
			r[0] = c;
			r[1] = t;
		}	
	}
	
	return r;
}

vector<int> getState(vector<int> cv, vector<int> ct) {
	int i, t, hc;
	vector<int> chv, cht, r;
	bool f;
	
	//Count most
	chv = countMostCard(cv);
	cht = countMostCard(ct);
	
	//Get highest Card
	hc = 0;
	for(i = 0; i < cv.size(); i++)
		if(hc < cv[i])
			hc = cv[i];
	
	//Royal Flush or Straight Flush
	if(chv[0] == 1 && cht[0] == 5) { // 5 uniqe values and 5 the same suit
		//Royal Flush
		f = true;
		
		for(i = 0; i < cv.size() && f; i++)
			if(cv[i] != 0xA + i)
				f = false;
		
		if(f) {
			r.push_back(CARDS_STATE_ROYAL_FLUSH);
			return r;
		}
		
		//Straight Flush
		f = true;
		t = cv[0];
		
		for(i = 1; i < cv.size() && f; i++)
			if(cv[i] != t + i && cv[i] - 9 != t + i)
				f = false;
		
		if(f) {
			r.push_back(CARDS_STATE_STRAIGHT_FLUSH);
			r.push_back(cv[4]); //Highest Card
			return r;
		}
	}
	
	//Four of a Kind
	if(chv[0] == 4) { // 4 same values
		r.push_back(CARDS_STATE_FOUR_OF_A_KIND);
		r.push_back(chv[1]); //Highest Card
		return r;
	}
	
	//Full House
	if(chv[0] == 3) { // 3 same values
		vector<int> v;
		
		//Get the values thats not the most common
		for(i = 0; i < cv.size(); i++)
			if(chv[1] != cv[i])
				v.push_back(cv[i]);
		
		//Check he has a extra double pare
		if(v.size() == 2 && v[0] == v[1]) {
			r.push_back(CARDS_STATE_FULL_HOUSE);
			r.push_back(chv[1]); //Highest Card
			return r;
		}
	}
	
	//Flush
	if(chv[0] == 1 && cht[0] == 5) { // 5 uniqe values and 5 the same suit
		r.push_back(CARDS_STATE_FLUSH);
		r.push_back(hc); //Highest Card
		return r;
	}
	
	//Straight
	if(chv[0] == 1) { // 1 same values
		f = true;
		t = cv[0];
		
		for(i = 1; i < cv.size() && f; i++)
			if(cv[i] != t + i && cv[i] - 9 != t + i)
				f = false;
		
		if(f) {
			r.push_back(CARDS_STATE_STRAIGHT);
			r.push_back(hc); //Highest Card
			return r;
		}
	}
	
	//Three of a Kind
	if(chv[0] == 3) { // 3 same values
		r.push_back(CARDS_STATE_THREE_OF_A_KIND);
		r.push_back(chv[1]); //Highest Card
		return r;
	}
	
	//Two Pairs or One Pair
	if(chv[0] == 2) {
		//Two Pairs
		vector<int> v;
		
		//Get the values thats not the most common
		for(i = 0; i < cv.size(); i++)
			if(chv[1] != cv[i])
				v.push_back(cv[i]);
		
		sort(v.begin(), v.end());
		
		//Check he has a extra double pare
		if(v.size() == 3 && (v[0] == v[1] || v[1] == v[2])) {
			r.push_back(CARDS_STATE_TWO_PAIR);
			r.push_back((v[1] > chv[1]) ? v[1] : chv[0]); //Highest pare
			r.push_back((v[1] < chv[1]) ? v[1] : chv[0]); //Second pare
			return r;
		}
		
		//One Pair
		r.push_back(CARDS_STATE_ONE_PAIR);
		r.push_back(chv[1]); //Highest pare
		return r;
	}
	
	//High Card
	r.push_back(CARDS_STATE_HIGH_CARD);
	r.push_back(hc); //Highest card
	return r;
}

int playGame(const vector<string> &a, const vector<string> &b) {
	int i;
	vector<int> av, at, bv, bt, as, bs;

	//Get Values and Types of cards
	for(i = 0; i < a.size(); i++) {
		getValueAndType(a[i], av, at);
		getValueAndType(b[i], bv, bt);
	}
	
	// Sort all Values and Types
	sort(av.begin(), av.end());
	sort(at.begin(), at.end());
	sort(bv.begin(), bv.end());
	sort(bt.begin(), bt.end());
	
	// Result of the cards
	as = getState(av, at);
	bs = getState(bv, bt);
	
	for(i = 0; i < as.size() && i < bs.size(); i++) {
		if(as[i] > bs[i])
			return 1;
		else if(as[i] < bs[i])
			return -1;
	}
	
	return 0;
}

int findWinsPlayer1(string f) {
	int i, j, c;
	vector<vector<string>> g;
	
	//Init
	c = 0;
	
	//Read File
	readFile(g, f);
	
	//Play games
	for(i = 0; i < g.size(); i++) {
		// Grab player 1 cards
		vector<string> a(g[i].begin(), g[i].begin()+5);
		
		// Grab player 2 cards
		vector<string> b(g[i].begin()+5, g[i].end());
		
		//Play till dead!!! :D
		if(playGame(a, b) > 0)
			c++;
	}
	
	return c;
}

int main() {
	cout << "result = " << findWinsPlayer1("poker.txt") << endl;
	
	return 0;
}