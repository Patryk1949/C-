#include "sp_Utils.hpp"
#include "sp_Sorting.hpp"
#include "sp_Containers.hpp"
#include <unistd.h>
#include <stdio.h>
#include <numeric>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <map>
#include <unordered_map>


struct Adder{
	inline int operator()(const int x1, const int x2) noexcept{
		return value - x1 * x2;
	}
	int value;
};


int main(){

	sizeof(std::deque<int>);
	sizeof(std::deque<int>::iterator);
	sizeof(std::vector<int>::iterator);
	sizeof(std::list<int>::iterator);
	sizeof(std::map<int, int>::iterator);
	sizeof(std::unordered_map<int, int>::iterator);

	sizeof(std::forward_list<int>);

	std::forward_list<int>::_Node;

	constexpr int N = 10000;
	const int trials = 10000;

	struct Pair{
		int sort;
		int check;
	};

	sp::SmallVector<Pair> vec;
	vec.resize(20);

	constexpr double secondsPerClock = 1.0/(double)CLOCKS_PER_SEC;

	double totalTime = 0.0;
	long timeBegin;

	Adder addFunctor{2137};
	sp::FunctionRef<int(int, int)> func(&addFunctor);
//	std::function<int(int, int)> func(addFunctor);

	sp::rand32 rnd(clock());
	for (int i=0; i<trials; ++i){
		for (auto &I : vec){
			I.sort = rnd() % 10;
			I.check = rnd() % 10;
		}

	/*	for (auto &I : vec)
			printf("%d ", I.sort);
		putchar('\n');
		for (auto &I : vec)
			printf("%d ", I.check);
		putchar('\n');
		putchar('\n');
	*/
		int prod = 0;
		timeBegin = clock();
	//	sp::heapSort(vec.begin(), vec.end(), [](auto x1, auto x2){ return x1.sort < x2.sort; });
		for (auto &I : vec){
			prod +=
			func(I.check, I.sort) * 
			func(I.check, I.sort+1) *
			func(I.check, I.sort+2) *
			func(I.check, I.sort+3) *
			func(I.check, I.sort+4) *
			func(I.check, I.sort+5) *
			func(I.check, I.sort+6) *
			func(I.check, I.sort+7) *
			func(I.check, I.sort+8) *
			func(I.check, I.sort+9);
		}
		totalTime += (double)(clock()-timeBegin)*secondsPerClock;

	/*	for (auto &I : vec)
			printf("%d ", I.sort);
		putchar('\n');
		for (auto &I : vec)
			printf("%d ", I.check);
		putchar('\n');
		putchar('\n');
	*/
		system("clear");
		printf("Completed:%10.d trials   product = %d\n", i, prod);
	}

	printf("Average time: %.10lf\n\n", totalTime/(double)trials);

	return 0;
}