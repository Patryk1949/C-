#include "sp_Calculator_v2.hpp"

int main(const int argc, char **argv){
	sp::Calc calculator;


	if (!strncmp(argv[1], "-f", 2)){

		const bool printFile = argv[1][2]=='p' ? true :
			[x=argv[1][2]](){ if (x){ puts("ERROR: wrong fomat argument"); exit(1); } else return false; }();


		FILE *const inputFile = fopen(argv[2], "r");
		if (!inputFile){
			puts("ERROR: this file does not exist");
			return 1;
		}
		fseek(inputFile, 0, SEEK_END);
   	const size_t fileSize = ftell(inputFile);

   	char *const str = (char *)malloc(fileSize*sizeof(char));

   	rewind(inputFile);
   	fread(str, sizeof(char), fileSize, inputFile);
		
		calculator.parseString(str);
		if (printFile) printf("%s ", str);

		fclose(inputFile);
	} else{
		calculator.parseString(argv[1]);
	}

	const auto[result, error] = calculator.calculate();
	if ((uint32_t)error){
		printf("ERROR: ");
		switch (error){
		case sp::Calc::Token::ErrorMsg::LexingError:
			puts("lexical error");
			break;
		case sp::Calc::Token::ErrorMsg::WrongSyntax:
			puts("wrong syntax");
			break;
		case sp::Calc::Token::ErrorMsg::MissingArgument:
			puts("missing argument");
			break;
		case sp::Calc::Token::ErrorMsg::MissingParenthesis:
			puts("missing parenthsis");
			break;
		case sp::Calc::Token::ErrorMsg::MissingBracket:
			puts("missing bracket");
			break;
		case sp::Calc::Token::ErrorMsg::MissingAbsSymbol:
			puts("missing '|' symbol");
			break;
		case sp::Calc::Token::ErrorMsg::MissingVariable:
			puts("missing variable");
			break;
		case sp::Calc::Token::ErrorMsg::DivisionByZero:
			puts("division by zero");
			break;
		case sp::Calc::Token::ErrorMsg::NegativeBase:
			puts("negative base raised to non integral exponent");
			break;
		case sp::Calc::Token::ErrorMsg::ArgIsNonInDomain:
			puts("argument is outside function's domain");
			break;
		case sp::Calc::Token::ErrorMsg::NonIntegralIndex:
			puts("index variable is not an integer");
			break;
		case sp::Calc::Token::ErrorMsg::NonExistingVariable:
			puts("variable was not declared");
			break;
		case sp::Calc::Token::ErrorMsg::VariableRedefinition:
			puts("varaible redefinition");
			break;
		default:
			puts("unknown error");
			break;
		}
		return 1;
	} else
		printf("= %lf\n", result);

	return 0;
}