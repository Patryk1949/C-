#include <stdio.h>
#include "SPL/Utils.hpp"
#include "SPL/StateMachine.hpp"
#include <iostream>

union Un{
	uint32_t u32;
	uint16_t u16[2];
	uint8_t u8[4];
};


enum class States : uint32_t {
	DEAD, ONE, TWO, THREE, FOUR
};


struct X{
	uint32_t x;

	X(){ puts("constructor"); }
	~X(){ puts("destructor"); }
};

void farg(const int x){}

int foo(const int x){
	printf("Foooooo: %d\n", x);
	return 2137;
}


template<class T, size_t baseBits = 8> void radixLSD(T *const first, T *const last);


int main(){

	// sp::StaticStateMachine<uint32_t, 5> stM{1, {
	// 	0, 0,
	// 	2, 0,
	// 	3, 0,
	// 	4, 0,
	// 	1, 0
	// }};

	// for (;;){
	// 	printf("state = %d\n", stM.state);

	// 	const char c = getchar();
	// 	getchar();
	// 	const uint32_t inp = c=='1' || c=='t' || c=='T';

	// 	stM.update(inp);
	// }

	// Un un{12u};

	// printf("%d", un.u16[0]);

	// size_t size;
	// scanf("%lu", &size);


	// /* SCOPE */ {
	// 	X *numbers = new X[size];

	// 	for (uint32_t i=0; i<size; ++i)
	// 		numbers[i].x = i;

	// 	printf("\nSize: %lu\n\n", std::size(numbers));




	// 	delete[] numbers;
	// }

	// std::array<uint32_t, 5> vec = {1, 2, 3, 4, 5};

	// std::cout << *std::find(vec.begin(), vec.end(), 0) << '\n';

	// farg(2137);
	// goto *(void *)foo;

	std::array A = {5, 3, 7, 1, 4, 8, 144, 9, 0, 2, 1, 1, 6297, 43};
	std::array B = {1, 2 ,3};

	for (auto I : B){
		for (auto J : A){
			printf("%d ", I);
		}
	}

	const auto b = std::begin(A);
	const auto e = std::end(A);

	radixLSD(b, e);

	
	// int x;
	// scanf("%d", &x);
	// printf("%d\n\n", 100 / x);


	puts("returned 0");
	return 2;
}




template<class T, size_t baseBits>
void radixLSD(T *const first, T *const last){
	static_assert(baseBits);
	constexpr size_t base = 1 << baseBits;
	constexpr size_t bitMask = base - 1;
	
	uint32_t counts[base];
	std::vector<T> buffer(last-first);

	using IT = typename sp::UIntOfGivenSize<sp::roundUpTo2Power(sizeof(T))>::type;

	for (IT step=0; step!=sizeof(T)*8/baseBits; ++step){
		memset(counts, 0, sizeof(counts));
		if (step & 1){
			for (T *It=&*std::begin(buffer); It!=&*std::end(buffer); ++It)
				++counts[(*(IT *)It >> step*baseBits) & bitMask];

			for (IT *C=std::begin(counts)+1; C!=std::end(counts); ++C) *C += *(C-1);
			
			for (T *It=&*std::end(buffer)-1; It!=&*std::begin(buffer)-1; --It)
				first[--counts[(*(IT *)It >> step*baseBits) & bitMask]] = *It;

		} else{
			for (T *It=first; It!=last; ++It)
				++counts[(*(IT *)It >> step*baseBits) & bitMask];

			for (IT *C=std::begin(counts)+1; C!=std::end(counts); ++C) *C += *(C-1);
			
			for (T *It=last-1; It!=first-1; --It)
				buffer[--counts[(*(IT *)It >> step*baseBits) & bitMask]] = *It;
		}
	}
}