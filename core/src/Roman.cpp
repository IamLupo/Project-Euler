#include "IamLupo/roman.h"

/*
	https://en.wikipedia.org/wiki/Roman_numerals
*/

std::string IamLupo::Roman::to(int n) {
	int i, v;
	std::string r;
	
	v = n;
	
	for(i = IamLupo::Roman::value.size() - 1; i >= 0; i--) {
		if(v >= IamLupo::Roman::value[i]) {
			v -= IamLupo::Roman::value[i];
			r.append(IamLupo::Roman::symbols[i]);
			i++;
		}
	}
	
	return r;
}

int IamLupo::Roman::to(const std::string &s) {
	int i, v;
	
	v = 0;
			
	for(i = 0; i < s.size(); i++) {
		switch(s[i]) {
			case 'I':
				if(s[i + 1] == 'X') {
					v += 9;
					i++;
				}
				else if(s[i + 1] == 'V') {
					v += 4;
					i++;
				}
				else
					v += 1;
			break;
			case 'V':	v += 5;		break;
			case 'X':
				if(s[i + 1] == 'L') {
					v += 40;
					i++;
				}
				else if(s[i + 1] == 'C') {
					v += 90;
					i++;
				}
				else
					v += 10;
			break;
			case 'L':
					v += 50;
			break;
			case 'C':
				if(s[i + 1] == 'D') {
					v += 400;
					i++;
				}
				else if(s[i + 1] == 'M') {
					v += 900;
					i++;
				}
				else
					v += 100;
			break;
			case 'D':	v += 500;	break;
			case 'M':	v += 1000;	break;
		}
	}
	
	return v;
}