#include "SPL/Utils.hpp"
#include <string>


std::string binaryForm(uint32_t n, std::string napis = ""){
	if (n == 0) return napis;
	return binaryForm(n >> 1, (char)('0'+(n&1)) + napis);
}


int main(){
	puts(binaryForm(64).c_str());


	return 0;
}