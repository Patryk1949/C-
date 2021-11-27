#include "compiler_v2/MainParser.hpp"
#include "compiler_v2/Printer.hpp"




int main(int argc, char **argv){
	if (argc != 2){
		puts("wrong number of arguments");
		return 1;
	}

	FILE *const file = fopen(argv[1], "r");
	if (!file){
		puts("cannot open this file");
		return 1;
	}

	fseek(file, 0, SEEK_END);
	const size_t fileSize = ftell(file);
	rewind(file);

	char *const input = (char *)aligned_alloc(alignof(char), (fileSize + 1)*sizeof(char));
	fread(input, sizeof(char), fileSize, file);
	fclose(file);
	input[fileSize] = '\0';

	puts(input);
	
	sp::DArray<spcomp::Node> tokens = spcomp::makeTokens(input);
	spcomp::iter = std::begin(tokens);
	spcomp::parseGlobal();

	// FILE *out = fopen("/home/basher/Programming/SoyDev/output.dat", "w");
	// if (!out){
	// 	puts("\n\n\n\ncannot write to this file");
	// 	return 1;
	// }
	// fwrite(std::begin(spcomp::nodes), sizeof(spcomp::Node), std::size(spcomp::nodes), out);

	puts("PROGRAM:");
	spcomp::printFunctionNodes(spcomp::nodes);


	return 0;
}
