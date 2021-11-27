#include "SPL/Utils.hpp"
#include <stdio.h>
#include <functional>
#include "SPL/FixedPoint.hpp"
#include <typeinfo>

int main(){

	sp::FixedPoint<20> fix1 = 21.52;
	sp::FixedPoint<20> fix2 = 2.53;


	printf("%lf op %lf = %lf\n", (double)fix1, (double)fix2, (double)(fix1 % fix2));

	if (fix1 != fix2)
		puts("Condition was met.");


	return 0;
}