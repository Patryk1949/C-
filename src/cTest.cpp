#include "SPL/Utils.hpp"

template<class T>
auto func(T &&x) noexcept{
	x.append('a');
	return std::forward<T>(x);
}


int main(){

	const std::string s = "sdfsdfksdjfsdfsdfsd";


	const auto var = func(s);


	return 0;
}