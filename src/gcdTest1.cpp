#include "SPL/Utils.hpp"
#include <numeric>
#include "SPL/Arrays.hpp"


int main(int argc, char **argv){
	size_t N = 1000000;
	
	sp::DArray<uint32_t> arr;
	arr.resize(N);

	sp::Rand32 rng{clock()};
	const uint32_t rngMask = 0xffff;

	const time_t timeStart1 = clock();
	/* measured computation */{
		for (auto &I : arr)
			I += sp::gcd(rng()&rngMask, rng()&rngMask);
	}
	const time_t totalTime1 = clock() - timeStart1;
	printf("time1 = %lu\n", totalTime1);
	const time_t timeStart2 = clock();
	/* measured computation */{
		for (auto &I : arr)
			I += std::gcd(rng()&rngMask, rng()&rngMask);
	}
	const time_t totalTime2 = clock() - timeStart2;
	printf("time2 = %lu\n", totalTime2);

	return 0;
}