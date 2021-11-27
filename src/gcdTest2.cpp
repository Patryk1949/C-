#include "SPL/Utils.hpp"
#include <numeric>



int main(int argc, char **argv){
	if (argc != 3){
		puts("wrong number of arguments");
		return 1;
	}
	
	printf("gcd = %u\n", sp::gcd((uint32_t)strtol(argv[1], nullptr, 10), (uint32_t)strtol(argv[2], nullptr, 10)));

	return 0;
}