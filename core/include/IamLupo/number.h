#include <vector>
#include <set>
#include <string>

namespace IamLupo {
	namespace Number {
		long long to(const std::vector<int> &v);
		long long to(const std::set<int> &v);
		long long to(const std::string &s);
		
		long long sum(const std::string &s);
		long long sum(const std::vector<int> &v);
		long long sum(const std::vector<long long> &v);
		long long nextBase(int b, int v);
	}
}