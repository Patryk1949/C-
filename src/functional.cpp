#include <stdio.h>
#include <time.h>
#include <random>
#include <vector>
#include <string.h>
#include "SPL/Containers.hpp"

#include "sparsepp/spp.h"

using std::size, std::begin, std::end, std::cbegin, std::cend, std::rbegin, std::rend, std::crbegin, std::crend;

template<class T>
std::vector<T> subarray(std::vector<T> A, const uint32_t first, const uint32_t last){ std::rotate(begin(A),begin(A)+first, end(A)); A.resize(last-first); return A; }
template<class T>
std::vector<T> operator &(std::vector<T> A, const std::vector<T> B){ A.resize(size(A) + size(B)); std::copy_backward(rbegin(B), rend(B), rbegin(A)+size(B)); return A; }
template<class T>
std::vector<T> operator &(std::vector<T> A, const T b){ A.push_back(b); return A; }



template<class T>
std::vector<T> &insortImperative(std::vector<T> &input){
	for (auto I=begin(input)+1; I<end(input); ++I){
		const T temp = std::move(*I);
		auto J = I;
		for (; J!=begin(input) && *(J-1)>temp; --J)
			*J = std::move(*(J-1));
		*J = std::move(temp);
	}
	return input;
}

template<class T>
std::vector<T> insortFunRec(const std::vector<T> input, const T swapVal){
	if (size(input)<=1 || *(cend(input)-2)<=swapVal)
		return subarray(input, 0, size(input)-1) & swapVal;

	return insortFunRec(subarray(input, 0, size(input)-1), swapVal) & input[size(input)-2];
}

template<class T>
std::vector<T> insortFunctional(const std::vector<T> input, const size_t index = 1){

	if (index >= size(input)) return input;

	const auto result = insortFunRec(subarray(input, 0, index+1), input[index]) & subarray(input, index+1, size(input));
	return insortFunctional(result, index+1);
}

template<class ...Types>
constexpr auto sum(const Types ...x){
	return (x + ...);
}

template<class T>
T multipleApply(T (*func)(T), uint32_t N){
	T result{};
	while (--N) result = func(result);
	return result;
}


int main(const int argc, const char *const *const argv){
	// size_t size = 10;
	// if (argc == 2) size = strtol(argv[1], nullptr, 10);

	// std::vector<char> input(size);
	// {
	// 	sp::rand32 rng(clock());
	// 	for (auto &I : input) I = ' ' + rng()%('~'-' ');
	// }

	// for (auto I : input) putchar(I);
	// putchar('\n');

	// const std::vector<char> result = insortImperative(input);

	// for (auto I : result) putchar(I);
	// putchar('\n');

	// std::string s;


	// sp::PtrVector<double> vec;
	// vec.reserve(100);
	// printf("size: %lu\ncapacity: %lu\n\n", vec.size(), vec.capacity());

	// for (uint32_t i=0; i<10; ++i) vec.push_back((double)i);

	// printf("size: %lu\ncapacity: %lu\n\n", vec.size(), vec.capacity());
	// for (const auto &I : vec) printf("%lf\n", I);

	auto square = [](auto x){ return x*x; };

	printf("%d\n%lf\n\n%p\n", square(2), square(3.0), (int(*)(int))square);
	
	{ auto var = square(21.37);
	if (true){
		puts(var==3.0 ? "dasdasdas" : "dsad");
	}}

	return 0;
}