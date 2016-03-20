#include <string>
#include <vector>
#include <sstream>
#include <utility>

namespace IamLupo {
	namespace String {
		bool isPalindrome(long long n);
		bool isPalindrome(const std::string &s);
		bool common(const std::string &a, const std::string &b);
		
		std::vector<std::string> explode(const std::string &s, char delim);
		
		std::string binairy(int v);
	}
}