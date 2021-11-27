#pragma once

#include <stdio.h>
#include <math.h>
#include "sp_Utils.hpp"


namespace sp{ // BEGINNINF OF NAMESPACE //////////////////////////////////////////////////////////////////


struct Token{
	enum class Type : int{
		Error=0, End, Value, Variable, ArgsRef, Comma,
		Add, Subtract, Divide , Multiply, Power, Abs, ParenL, ParenR, UPlus, UMinus, Factorial,
		Pi, Euler, Gravity,
		Sqrt, Cbrt, Exp, Exp2, Ln, Log, Log2, Log10, Gamma, Erf,
		Floor, Ceil, Round, Sign, Step,
		Sin, Cos, Tan, Sinh, Cosh, Tanh, Asin, Acos, Atan, Atan2, Asinh, Acosh, Atanh,
	};
	enum class ErrorMsg : int{
		WrongSyntax=0, MissingArgument, MissingBracket, MissingAbsSymbol
	};

	Type type;
	union{
		Token *node[2];
		double value;
		ErrorMsg errMsg;
		char name[16];
	};
};

struct Variable{
	char name[16];
	double value;
};


int makeTokens(Token *tokens, const char *input);

inline Token *parseTokens(Token *nodes, const Token *tokens, Variable *variables);

void printNodes(FILE *const dest, const Token *startingNode);

double calculateNodes(const Token *startingNode);




int makeTokens(Token *tokens, char *input){
	Token *const tokensBegin = tokens;
	while (*input){
		if (*input>='0' && *input<='9' || *input=='.'){
			tokens->type = Token::Type::Value;
			tokens->value = strtod(input, &input);
		} else{
			switch (*input){
			case '+':
				tokens->type = Token::Type::Add;
				break;
			case '-':
				tokens->type = Token::Type::Subtract;
				break;
			case '*':
				tokens->type = Token::Type::Multiply;
				break;
			case '/':
				tokens->type = Token::Type::Divide;
				break;
			case '^':
				tokens->type = Token::Type::Power;
				break;
			case '|':
				tokens->type = Token::Type::Abs;
				break;
			case '(':
				tokens->type = Token::Type::ParenL;
				break;
			case ')':
				tokens->type = Token::Type::ParenR;
				break;
			case '!':
				tokens->type = Token::Type::Factorial;
				break;
			case ',':
				tokens->type = Token::Type::Comma;
				break;
			case 'a':
				if (input[1]=='c' && input[2]=='o' && input[3]=='s'){
					if(input[4]=='h'){
						input += 4;
						tokens->type = Token::Type::Acosh;
					} else{
						input += 3;
						tokens->type = Token::Type::Acos;
					}
				} else if (input[1]=='s' && input[2]=='i' && input[3]=='n'){
					if(input[4]=='h'){
						input += 4;
						tokens->type = Token::Type::Asinh;
					} else{
						input += 3;
						tokens->type = Token::Type::Asin;
					}
				} else if (input[1]=='t' && input[2]=='a' && input[3]=='n'){
					input += 3;
					if (input[1]=='h'){
						++input;
						tokens->type = Token::Type::Atanh;
					} else if (input[1]=='2' && input[2]=='('){
						++input;
						tokens->type = Token::Type::Atan2;
					} else{
						tokens->type = Token::Type::Atan;
					}
				}
				break;
			case 'c':
				if (input[1]=='e' && input[2]=='i' && input[3]=='l'){
					input += 3;
					tokens->type = Token::Type::Ceil;
				} else if (input[1]=='b' && input[2]=='r' && input[2]=='t'){
					input += 3;
					tokens->type = Token::Type::Cbrt;
				} else if (input[1]=='o' && input[2]=='s'){
					if (input[2]=='h'){
						input += 3;
						tokens->type = Token::Type::Cosh;
					} else{
						input += 2;
						tokens->type = Token::Type::Cos;
					}
				}
				break;
			case 'e':
				if (input[1]=='x' && input[2]=='p'){
					if (input[2]=='b'){
						input += 3;
						tokens->type = Token::Type::Exp2;
					} else{	
						input += 2;
						tokens->type = Token::Type::Exp;
					}
				} else if (input[1]=='r' && input[2]=='f'){
					input += 2;
					tokens->type = Token::Type::Erf;
				} else
					tokens->type = Token::Type::Euler;
				break;
			case 'f':
				if (input[1]=='l' && input[2]=='o' && input[3]=='o' && input[4]=='r'){
					input += 4;
					tokens->type = Token::Type::Floor;
				}
				break;
			case 'g':
				if (input[1]=='a' && input[2]=='m' && input[2]=='m' && input[4]=='a'){
					input += 4;
					tokens->type = Token::Type::Gamma;
				} else
					tokens->type = Token::Type::Gravity;
				break;
			case 'l':
				if (input[1]=='n'){
					++input;
					tokens->type = Token::Type::Ln;
				} else if (input[1]=='o' && input[2]=='g'){
					input += 2;
					if(input[1]=='b'){
						++input;
						tokens->type = Token::Type::Log2;
					} else if (input[1]=='d'){
						++input;
						tokens->type = Token::Type::Log10;
					} else if (input[1]=='('){
						tokens->type = Token::Type::Log;
					}
				}
				break;
			case 'p':
				if(input[1]=='i'){
					++input;
					tokens->type = Token::Type::Pi;
				}
				break;
			case 'r':
				if (input[1]=='o' && input[2]=='u' && input[3]=='n' && input[4]=='d'){
					input += 4;
					tokens->type = Token::Type::Round;
				}
				break;
			case 's':
				if(input[1]=='q' && input[2]=='r' && input[3]=='t'){
					input += 3;
					tokens->type = Token::Type::Sqrt;
				} else if(input[1]=='t' && input[2]=='e' && input[3]=='p'){
					input += 3;
					tokens->type = Token::Type::Step;
				} else if(input[1]=='i'){
					++input;
					if (input[1]=='n'){
						++input;
						if (input[1]=='h'){
							++input;
							tokens->type = Token::Type::Sinh;
						} else
							tokens->type = Token::Type::Sin;
					} else if (input[1]=='g' && input[2]=='n'){
						input += 2;
						tokens->type = Token::Type::Sign;
					}
				}
				break;
			case 't':
				if(input[1]=='a' && input[2]=='n'){
					if (input[3]=='h'){
						input += 3;
						tokens->type = Token::Type::Tanh;
					}
					else{
						input += 2;
						tokens->type = Token::Type::Tan;
					}
				}
				break;
			default:
				if (*input>='a' && *input<='z' || *input>='A' && *input<='Z' || *input=='_'){
					tokens->type = Token::Type::Variable;
					tokens->name[0] = *input;
					++input;
					int i = 1;
					for (; i<15 && *input>='a' && *input<='z' || *input>='A' && *input<='Z' || *input=='_' ||
							*input>='0' && *input<='9'; ++i, ++input)
						tokens->name[i] = *input;
					tokens->name[i] = 0;
				} 
				--tokens;
				break;
			}
			++input;
		}
		++tokens;
	}
	tokens->type = Token::Type::End;
	return tokens - tokensBegin;
}

namespace priv__{	// PRIVATE NAMESPACE

	Token *parse0(Token **nodes, const Token **tokens, double *varValues, char *const *varNames);
	Token *parse1(Token **nodes, const Token **tokens, double *varValues, char *const *varNames);
	Token *parse2(Token **nodes, const Token **tokens, double *varValues, char *const *varNames);
	Token *parse3(Token **nodes, const Token **tokens, double *varValues, char *const *varNames);

	Token *parse0(Token **nodes, const Token **tokens, Variable *variables){
		Token *prevNode = (*nodes)++;
		prevNode->type = (*tokens)->type;
		
		switch ((*tokens)->type){
		case Token::Type::Value:
			prevNode->value = (*tokens)->value;
			++(*tokens);
			break;
		case Token::Type::ParenL:
			++(*tokens);
			prevNode = parse3(nodes, tokens, variables);
			if ((*tokens)->type != Token::Type::ParenR){
				prevNode->errMsg = prevNode->type==Token::Type::Error ?
						prevNode->errMsg : Token::ErrorMsg::MissingBracket;
				prevNode->type = Token::Type::Error;
			}
			++(*tokens);
			break;
		case Token::Type::Abs:
			++(*tokens);
			prevNode->node[0] = parse3(nodes, tokens, variables);
			if ((*tokens)->type != Token::Type::Abs){
				prevNode->errMsg = Token::ErrorMsg::MissingAbsSymbol;
				prevNode->type = Token::Type::Error;
			}
			++(*tokens);
			break;
		case Token::Type::Add:
			++(*tokens);
			prevNode->type = Token::Type::UPlus;
			prevNode->node[0] = parse0(nodes, tokens, variables);
			break;
		case Token::Type::Subtract:
			++(*tokens);
			prevNode->type = Token::Type::UMinus;
			prevNode->node[0] = parse0(nodes, tokens, variables);
			break;
		case Token::Type::Pi:
			++(*tokens);
			prevNode->type = Token::Type::Value;
			prevNode->value = M_PI;
			break;
		case Token::Type::Euler:
			prevNode->type = Token::Type::Value;
			prevNode->value = M_E;
			break;
		case Token::Type::Acos:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Acosh:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Asin:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Asinh:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Atan:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Atanh:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Atan2:
			*tokens += 2;
			prevNode->node[0] = parse3(nodes, tokens, variables);
			if ((*tokens)->type != Token::Type::Comma){
				prevNode->errMsg = Token::ErrorMsg::MissingArgument;
				prevNode->type = Token::Type::Error;
			}
			++(*tokens);
			prevNode->node[1] = parse3(nodes, tokens, variables);
			if ((*tokens)->type != Token::Type::ParenR){
				prevNode->errMsg = prevNode->type==Token::Type::Error ?
						Token::ErrorMsg::MissingArgument : Token::ErrorMsg::MissingBracket;;
				prevNode->type = Token::Type::Error;
			}
			++(*tokens);
			break;
		case Token::Type::Cbrt:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Ceil:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Cos:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Cosh:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Erf:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Exp:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Exp2:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Floor:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Gamma:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Ln:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Log10:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Log2:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Log:
			*tokens += 2;
			prevNode->node[0] = parse3(nodes, tokens, variables);
			if ((*tokens)->type != Token::Type::Comma){
				prevNode->errMsg = Token::ErrorMsg::MissingArgument;
				prevNode->type = Token::Type::Error;
			}
			++(*tokens);
			prevNode->node[1] = parse3(nodes, tokens, variables);
			if ((*tokens)->type != Token::Type::ParenR){
				prevNode->errMsg = prevNode->type==Token::Type::Error ?
						Token::ErrorMsg::MissingArgument : Token::ErrorMsg::MissingBracket;
				prevNode->type = Token::Type::Error;
			}
			++(*tokens);
			break;
		case Token::Type::Round:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Sqrt:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Step:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Sin:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Sinh:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Sign:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Tan:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		case Token::Type::Tanh:
			++(*tokens);
			prevNode->node[0] = parse2(nodes, tokens, variables);
			break;
		default:
			prevNode->type = Token::Type::Error;
			prevNode->errMsg = Token::ErrorMsg::WrongSyntax;
			break;
		}
		if ((*tokens)->type == Token::Type::Factorial){
			++(*tokens);
			(*nodes)->type = Token::Type::Factorial;
			(*nodes)->node[0] = prevNode;
			prevNode = (*nodes)++;
		}
		return prevNode;
	}

	Token *parse1(Token **nodes, const Token **tokens, Variable *variables){
		Token *prevNode = parse0(nodes, tokens, variables);
		while ((*tokens)->type==Token::Type::Power){
			(*nodes)->type = (*tokens)->type;
			++(*tokens);
			(*nodes)->node[0] = prevNode;
			prevNode = (*nodes)++;
			prevNode->node[1] = parse0(nodes, tokens, variables);
		}
		return prevNode;
	}

	Token *parse2(Token **nodes, const Token **tokens, Variable *variables){
		Token *prevNode = parse1(nodes, tokens, variables);
		while ((*tokens)->type==Token::Type::Multiply || (*tokens)->type==Token::Type::Divide){
			(*nodes)->type = (*tokens)->type;
			++(*tokens);
			(*nodes)->node[0] = prevNode;
			prevNode = (*nodes)++;
			prevNode->node[1] = parse1(nodes, tokens, variables);
		}
		return prevNode;
	}

	Token *parse3(Token **nodes, const Token **tokens, Variable *variables){
		Token *prevNode = parse2(nodes, tokens, variables);
		while ((*tokens)->type==Token::Type::Add || (*tokens)->type==Token::Type::Subtract){
			(*nodes)->type = (*tokens)->type;
			++(*tokens);
			(*nodes)->node[0] = prevNode;
			prevNode = (*nodes)++;
			prevNode->node[1] = parse2(nodes, tokens, variables);
		}
		return prevNode;
	}

} // END OF PRIVATE NAMESPACE

inline Token *parseTokens(Token *nodes, const Token *tokens, Variable *variables){	// VarValues should be array of pointers to variable values stored in nodes
	return priv__::parse3(&nodes, &tokens, variables);
}

void printNodes(FILE *const dest, const Token *startingNode){
	switch (startingNode->type){
	case Token::Type::Value:
		fprintf(dest, "%lf", startingNode->value);
		break;
	case Token::Type::Add:
		fprintf(dest, "( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " + ");
		printNodes(dest, startingNode->node[1]);
		fprintf(dest, " )");
		break;
	case Token::Type::Subtract:
		fprintf(dest, "( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " - ");
		printNodes(dest, startingNode->node[1]);
		fprintf(dest, " )");
		break;
	case Token::Type::Multiply:
		fprintf(dest, "( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " * ");
		printNodes(dest, startingNode->node[1]);
		fprintf(dest, " )");
		break;
	case Token::Type::Divide:
		fprintf(dest, "( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " / ");
		printNodes(dest, startingNode->node[1]);
		fprintf(dest, " )");
		break;
	case Token::Type::Power:
		fprintf(dest, "( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " ^ ");
		printNodes(dest, startingNode->node[1]);
		fprintf(dest, " )");
		break;
	case Token::Type::Abs:
		fprintf(dest, "( | ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " | )");
		break;
	case Token::Type::UPlus:
		fprintf(dest, "( +");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::UMinus:
		fprintf(dest, "( -");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Factorial:
		fprintf(dest, "( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, "! )");
		break;
	case Token::Type::Acos:
		fprintf(dest, "acos( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Acosh:
		fprintf(dest, "acosh( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Asin:
		fprintf(dest, "asin( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Asinh:
		fprintf(dest, "asinh( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Atan:
		fprintf(dest, "atan( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Atanh:
		fprintf(dest, "atanh( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Atan2:
		fprintf(dest, "atan2( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " , ");
		printNodes(dest, startingNode->node[1]);
		fprintf(dest, " )");
		break;
	case Token::Type::Cbrt:
		fprintf(dest, "cbrt( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Ceil:
		fprintf(dest, "ceil( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Cos:
		fprintf(dest, "cos( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Cosh:
		fprintf(dest, "cosh( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Erf:
		fprintf(dest, "erf( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Exp:
		fprintf(dest, "exp( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Exp2:
		fprintf(dest, "exp2( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Floor:
		fprintf(dest, "floor( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Gamma:
		fprintf(dest, "gamma( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Ln:
		fprintf(dest, "ln(");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Log2:
		fprintf(dest, "log2( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Log10:
		fprintf(dest, "log10( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Log:
		fprintf(dest, "( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " , ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Round:
		fprintf(dest, "round( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Sqrt:
		fprintf(dest, "sqrt( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Step:
		fprintf(dest, "heviside( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Sin:
		fprintf(dest, "sin( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Sinh:
		fprintf(dest, "sinh( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Sign:
		fprintf(dest, "sign( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Tan:
		fprintf(dest, "tan( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Tanh:
		fprintf(dest, "tanh( ");
		printNodes(dest, startingNode->node[0]);
		fprintf(dest, " )");
		break;
	case Token::Type::Error:
		fprintf(dest, "\" ERROR: ");
		switch (startingNode->errMsg){
		case Token::ErrorMsg::WrongSyntax:
			fprintf(dest, "wrong syntax \"");
			break;
		case Token::ErrorMsg::MissingArgument:
			fprintf(dest, "missing argument \"");
			break;
		case Token::ErrorMsg::MissingBracket:
			fprintf(dest, "missing bracket \"");
			break;
		case Token::ErrorMsg::MissingAbsSymbol:
			fprintf(dest, "missing '|' symbol \"");
			break;
		default:
			fprintf(dest, "unknown error \"");
			break;
		}
	default:
		break;
	}
}

double calculateNodes(const Token *startingNode){
	switch (startingNode->type){
	case Token::Type::Error:
		return NAN;
		break;
	case Token::Type::Value:
		return startingNode->value;
		break;
	case Token::Type::Add:
		return calculateNodes(startingNode->node[0]) + calculateNodes(startingNode->node[1]);
		break;
	case Token::Type::Subtract:
		return calculateNodes(startingNode->node[0])-calculateNodes(startingNode->node[1]);
		break;
	case Token::Type::Multiply:
		return calculateNodes(startingNode->node[0])*calculateNodes(startingNode->node[1]);
		break;
	case Token::Type::Divide:
		return calculateNodes(startingNode->node[0])/calculateNodes(startingNode->node[1]);
		break;
	case Token::Type::Power:
		return pow(calculateNodes(startingNode->node[0]), calculateNodes(startingNode->node[1]));
		break;
	case Token::Type::Abs:
		return abs(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::UPlus:
		return calculateNodes(startingNode->node[0]);
		break;
	case Token::Type::UMinus:
		return -calculateNodes(startingNode->node[0]);
		break;
	case Token::Type::Factorial:
		return tgamma(calculateNodes(startingNode->node[0]) + 1.);
		break;
	case Token::Type::Acos:
		return acos(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Acosh:
		return acosh(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Asin:
		return asin(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Asinh:
		return asinh(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Atan:
		return atan(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Atanh:
		return atanh(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Atan2:
		return atan2(calculateNodes(startingNode->node[0]), calculateNodes(startingNode->node[1]));
		break;
	case Token::Type::Cbrt:
		return cbrt(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Ceil:
		return ceil(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Cos:
		return cos(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Cosh:
		return cosh(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Erf:
		return erf(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Exp:
		return exp(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Exp2:
		return exp2(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Floor:
		return floor(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Gamma:
		return tgamma(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Ln:
		return log(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Log2:
		return log2(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Log10:
		return log10(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Log:
		return log(calculateNodes(startingNode->node[0]))/log(calculateNodes(startingNode->node[1]));
		break;
	case Token::Type::Round:
		return round(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Sqrt:
		return sqrt(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Step:
		return (double)!signbit(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Sin:
		return sin(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Sinh:
		return sinh(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Sign:
		return sp::sign(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Tan:
		return tan(calculateNodes(startingNode->node[0]));
		break;
	case Token::Type::Tanh:
		return tanh(calculateNodes(startingNode->node[0]));
		break;
	default:
		break;
	}
	return M_PI;
}

} // END OF NAMESPACE ////////////////////////////////////////////////////////////////////////////