#include <vector>
#include "gmp.h"

namespace IamLupo {
	namespace Sqrt {
		typedef std::vector<long long> CFraction;
		
		struct ExponentialE {
			int level;
			CFraction fr;
			mpz_t x1;
			mpz_t x2;
			mpz_t y1;
			mpz_t y2;
		};
		
		CFraction ContinuedFraction(long long s);
		
		ExponentialE Expo_Init(const CFraction &fr);
		void Expo_Next(ExponentialE &fr);
	}
}