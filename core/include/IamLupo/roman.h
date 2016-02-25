#include <vector>
#include <string>

namespace IamLupo {
	namespace Roman {
		static std::vector<std::string> symbols = {
			"I",   "II",  "III",  "IV",  "V",   "VI",   "VII",  "VIII",  "IX",  "X",
			"XI",  "XII", "XIII", "XIV", "XV",  "XVI",  "XVII", "XVIII", "XIX", "XX", 
			"XXX", "XL",  "L",    "LX",  "LXX", "LXXX", "XC",   "C",
			"CC",  "CCC", "CD",   "D",   "DC",  "DCC",  "DCCC", "CM",    "M"
		};

		static std::vector<int> value = {
			1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
			11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
			30, 40, 50, 60, 70, 80, 90, 100,
			200, 300, 400, 500, 600, 700, 800, 900, 1000
		};
		
		std::string to(int n);
		int to(const std::string &s);
	}
}