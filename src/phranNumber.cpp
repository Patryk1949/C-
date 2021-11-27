#include "SPL/Utils.hpp"
#include <string>


int parenteshisDepth(const char *input);

int main(){

	while (true){
		constexpr int maxLineLen = 127;
		char line[maxLineLen+1];
		fgets(line, maxLineLen, stdin);
		if (*line == '\n')
			return 0;
		printf("\nparenteshis depth = %d\n\n", parenteshisDepth(line));
	}
	return 0;
}





int parenteshisDepth(const char *s){
	int m = 0;
	int c = 0;
	
	for (const char *I=s; *I!=0; ++I){
		c += (*I == '(') - (*I == ')');
		m = m<c ? c : m;
	}
	
	return m;
}



constexpr int parenteshisDepth(const std::string &input){
	int maxDepth = 0;
	int currDepth = 0;

	for (const auto &I : input){
		currDepth += (I == '(') - (I == ')');
		maxDepth = std::max(currDepth, maxDepth);
	}

	return maxDepth;
}