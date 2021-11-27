#include <stdio.h>
#include <stdint.h>
#include "SPL/Containers.hpp"
#include <string>

int main(){
	sp::SBArray<double, 10> arr = {1.0, 2.0};

	sp::SBArray<double, 8> arr1;

	for (size_t i=0; i!=10000000; ++i)
		arr1.emplace_back((double)i);
	auto ddd = arr.size();
	auto ccc = arr.capacity();

	return 0;
}