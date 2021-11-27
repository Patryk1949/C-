#pragma once

#include "Errors.hpp"

#include <stdio.h>
#include <string>

namespace spcomp{

constexpr const char *const KeywordName[] = {
// COMPILER DIRECTIVES
	"main", "import",
	"defer", "if",
	"assert",
	"destructor",
	"implicit",
	"static", "separ",
	"mutable",

// KEYWORDS
	"fn", "class", "namespace",
	"struct", "union", "enum",

	"if", "while", "for",
	"goto", "return",
	"else", "do", "case", "break", "gotonext",
	
	"bytesize", "exists",
};

enum class NodeType : uint16_t{
// COMPILER DIRECTIVES ----------------------
	Main, Import,
	Defer, StaticIf,
	StaticAssert,
	Destructor,
	Implicit,
	Static, Separ,
	Mutable,

// KEYWORDS -------------------------------
	Fn, Class, Namespace,
	Struct, Union, Enum,

	If, While, For,
	Goto, Return,
	Else, Do, Case, Break, Gotonext,

	// OPERATORS
	Bytesize, Exists,
// END OF KEYWORDS ------------------------

	Access, Arrow, Dereference, GetAddress,

	Add, Subtract, Multiply, Divide, Modulus, Power,
	Identity, Negate,
	BitOr, BitNor, BitAnd, BitNand, BitXor, BitXnor,
	BitNot, LeftShift, RightShift,
	Equals, NotEquals, Lesser, Greater, LesserEq, GreaterEq,
	LogicOr, LogicAnd, LogicNot,

	Ternary, Elvis,

	Increment, Decrement,
	Assign, Initialize,
	AddAssign, SubtractAssign, MultiplyAssign, DivideAssign, ModulusAssign, PowerAssign,
	BitOrAssign, BitAndAssign, BitXorAssign, LeftShiftAssign, RightShiftAssign,

	
	// STATEMENTS
	OpenScope, CloseScope, Declare,

	GotoAddress,
	Switch, StaticSwitch,

	// OTHER
	Attribute, Label, Deduction,
	PredefScope,

	// LITERALS
	Number, BigNumber, Float, Letter, String,

	// EXPRESSIONS
	Name, Call, BraceInit, Subscript,
	Conversion, DirectCast, WhileOfDo,
	Literal, ArrayLiteral,
	Pointer, ConstPointer, ArgPasser,
	ArrayType, SimpleRange,
	FunctionAddress, Lambda, Tuple,


	// TOKEN ONLY
	Null, NamePart, Terminator, Comma, Placeholder, Walrus, WideWalrus,
	LeftPar, RightPar, LeftSqBr, RightSqBr, Colon,

	// SPECIFICATIONS
	OutputParameter, DereferenceOutput,
	AutoParameterPack,
};

// TOKEN CLASS
union Node{
// DATA TYPES
	union Data{
		uint64_t number;
		uint32_t numbers[4];
		double numberFloat;
		struct{
			union{
				uint16_t nameLen;
				struct{
					uint8_t shortNameLen;
					uint8_t argsCount;
				};
			};
			char name[14];
		};
	};
	struct FuncInfo{
		uint8_t argsCount;
		uint8_t returnInfo[7];
		uint8_t modInfo[8][2];
	};
	
	Node() noexcept{}
	Node(const void *) noexcept{ memset(longName, 0, 24); }
	Node(const Node &rhs) noexcept = default;
	Node(const NodeType t, const uint32_t r, const uint16_t c) noexcept : type{t}, col{c}, row{r} {}
	Node(const NodeType t, const uint32_t r, const uint16_t c, const uint64_t n) noexcept : type{t}, col{c}, row{r}, data{.number = n} {}
	Node(const NodeType t, const uint32_t r, const uint16_t c, const double n) noexcept : type{t}, col{c}, row{r}, data{.numberFloat = n} {}


// DATA MEMBERS
	struct{
		NodeType type;
		uint16_t col;
		uint32_t row;
		Data data;
	};
	char longName[24];
	FuncInfo funcInfo;
};


constexpr size_t textBlockCount(const uint16_t charCount) noexcept{
	return 1 + ((charCount - 14) + 23) / 24;
}

constexpr bool hasText(const NodeType t) noexcept{
	return t==NodeType::String || t==NodeType::Name || t==NodeType::Label || t==NodeType::Goto || t==NodeType::Declare;
}


constexpr bool isKeywordStatement(const NodeType type) noexcept{
	return (uint32_t)type >= (uint32_t)NodeType::Fn && (uint32_t)type <= (uint32_t)NodeType::Exists;
}
bool isNumberLiteral(const char *inpIter) noexcept{
	const char c = *inpIter;
	return isNumber(c) || ((c=='+'||c=='-') && isNumber(inpIter[1]));
}
void pushNamedToken(const char **const iterator, sp::DArray<Node> *const tokens, const uint32_t row, const uint16_t col, const bool isLiteral) noexcept{
	std::string_view text = getText(*iterator);
	if (std::size(text) > 65535) raiseError(ErrorType::TooLongName, row, col);
	*iterator += std::size(text);
	for (uint32_t i=(uint32_t )NodeType::Fn; i<=(uint32_t)NodeType::Exists; ++i)
		if (text == KeywordName[i]){
			tokens->emplace_back((NodeType)i, row, col);
			return;
		}
	const size_t nameTokenIndex = std::size(*tokens);
	tokens->expandBy(textBlockCount(std::size(text)));

	(*tokens)[nameTokenIndex].type = isLiteral ? NodeType::Literal : NodeType::Name;
	(*tokens)[nameTokenIndex].row = row;
	(*tokens)[nameTokenIndex].col = col;
	(*tokens)[nameTokenIndex].data.nameLen = std::size(text);

	std::copy(std::begin(text), std::end(text), (*tokens)[nameTokenIndex].data.name);
}








char getCharFromIterator(const char **const inpIter) noexcept;
Node getNumberTokenFromIterator(const char **const inpIter, const uint32_t row, const uint16_t col) noexcept;

sp::DArray<Node> makeTokens(const char *input) noexcept{
	sp::DArray<Node> tokens;
	size_t row = 0;
	size_t col = 0;
	for (;;){
		const char *prevInput = input;
		switch (*input){
		case '=': ++input;
			if (*input == '='){
				tokens.emplace_back(NodeType::Equals, row, col);
				++input;
			} else
				tokens.emplace_back(NodeType::Assign, row, col);
			break;


		case '+': ++input;
			if (*input == '='){
				tokens.emplace_back(NodeType::AddAssign, row, col);
				++input;
			} else if (*input == '+'){
				tokens.emplace_back(NodeType::Increment, row, col);
				++input;
			} else
				tokens.emplace_back(NodeType::Add, row, col);
			break;


		case '-': ++input;
			if (*input == '='){
				tokens.emplace_back(NodeType::SubtractAssign, row, col);
				++input;
			} else if (*input == '-'){
				tokens.emplace_back(NodeType::Decrement, row, col);
				++input;
			} else if (*input == '>'){
				tokens.emplace_back(NodeType::Arrow, row, col);
				++input;
			} else
				tokens.emplace_back(NodeType::Subtract, row, col);
			break;


		case '*': ++input;
			if (*input == '='){
				tokens.emplace_back(NodeType::MultiplyAssign, row, col);
				++input;
			} else
				tokens.emplace_back(NodeType::Multiply, row, col);
			break;


		case '/': ++input;
			if (*input == '='){
				tokens.emplace_back(NodeType::DivideAssign, row, col);
				++input;
			} else if (*input == '/'){
				++input;
				while (*input && *input!='\n') ++input;
			} else if (*input == '*'){
				++input;
				while (*input && !(input[0]=='*' && input[1]=='/')){
					if (*input == '\n'){
						col = 0;
						++row;
					}
					++input;
				} input += 2;
			} else
				tokens.emplace_back(NodeType::Divide, row, col);
			break;

		case '%': ++input;
			if (*input == '='){
				tokens.emplace_back(NodeType::ModulusAssign, row, col);
				++input;
			} else
				tokens.emplace_back(NodeType::Modulus, row, col);
			break;


		case '|': ++input;
			if (*input == '='){
				tokens.emplace_back(NodeType::BitOrAssign, row, col);
				++input;
			} else if (*input == '|'){
				tokens.emplace_back(NodeType::LogicOr, row, col);
				++input;
			} else
				tokens.emplace_back(NodeType::BitOr, row, col);
			break;


		case '&': ++input;
			if (*input == '='){
				tokens.emplace_back(NodeType::BitAndAssign, row, col);
				++input;
			} else if (*input == '&'){
				tokens.emplace_back(NodeType::LogicAnd, row, col);
				++input;
			} else
				tokens.emplace_back(NodeType::BitAnd, row, col);
			break;


		case '^': ++input;
			if (*input == '='){
				tokens.emplace_back(NodeType::PowerAssign, row, col);
				++input;
			} else
				tokens.emplace_back(NodeType::Power, row, col);
			break;


		case '~': ++input;
			if (*input == '|'){
				++input;
				tokens.emplace_back(NodeType::BitNor, row, col);
			} else if (*input == '&'){
				++input;
				tokens.emplace_back(NodeType::BitNand, row, col);
			} else if (*input == '^'){
				++input;
				tokens.emplace_back(NodeType::BitXnor, row, col);
			} else{
				tokens.emplace_back(NodeType::BitNot, row, col);
			}
			break;


		case '<':
			++input;
			if (*input == '='){
				tokens.emplace_back(NodeType::LesserEq, row, col);
				++input;
			} else if (*input == '<'){
				++input;
				if (input[1] == '='){
					tokens.emplace_back(NodeType::LeftShiftAssign, row, col);
					++input;
				} else
					tokens.emplace_back(NodeType::LeftShift, row, col);
			} else if(input[0]==':' && input[1]=='='){
				tokens.emplace_back(NodeType::Initialize, row, col);
				input += 2;
			} else
				tokens.emplace_back(NodeType::Lesser, row, col);
			break;


		case '>':
			++input;
			if (*input == '='){
				tokens.emplace_back(NodeType::GreaterEq, row, col);
				++input;
			} else if (*input == '>'){
				++input;
				if (input[1] == '='){
					tokens.emplace_back(NodeType::RightShiftAssign, row, col);
					++input;
				} else
					tokens.emplace_back(NodeType::RightShift, row, col);
			} else if (*input == '<'){
				++input;
				if (*input == '='){
					++input;
					tokens.emplace_back(NodeType::BitXorAssign, row, col);
				} else{
					tokens.emplace_back(NodeType::BitXor, row, col);
				}
			}	else
				tokens.emplace_back(NodeType::Greater, row, col);
			break;


		case '!':
			++input;
			if (*input == '='){
				tokens.emplace_back(NodeType::NotEquals, row, col);
				++input;
			} else
				tokens.emplace_back(NodeType::LogicNot, row, col);
			break;

		
		case '(':
			tokens.emplace_back(NodeType::LeftPar, row, col);
			++input;
			break;
		

		case ')':
			tokens.emplace_back(NodeType::RightPar, row, col);
			++input;
			break;
		
		
		case '{':
			tokens.emplace_back(NodeType::OpenScope, row, col);
			++input;
			break;
		
		
		case '}':
			tokens.emplace_back(NodeType::CloseScope, row, col);
			++input;
			if (isValidNameChar(*input))
				pushNamedToken(&input, &tokens, row, col, true);
			break;
		
		
		case '[': ++input;
			if (*input == '['){
				tokens.emplace_back(NodeType::Tuple, row, col);
				++input;
			} else{
				tokens.emplace_back(NodeType::LeftSqBr, row, col);
			}
			break;
		
		
		case ']':
			tokens.emplace_back(NodeType::RightSqBr, row, col);
			++input;
			break;

		
		case '?':
			++input;
			if (*input == '?'){
				tokens.emplace_back(NodeType::Deduction, row, col);
				++input;
			} else if (*input == ':'){
				tokens.emplace_back(NodeType::Elvis, row, col);
				++input;
			} else{
				tokens.emplace_back(NodeType::Ternary, row, col);
			} break;
		
		
		case ':':
			++input;
			if (*input == ':'){
				tokens.emplace_back(NodeType::Conversion, row, col);
				++input;
			} else if (*input == '='){
				tokens.emplace_back(NodeType::Walrus, row, col);
				++input;
			} else if (*input == '{'){
				if (input[1]=='}' && input[2]=='='){
					tokens.emplace_back(NodeType::WideWalrus, row, col);
					input += 3;
				} else
					tokens.emplace_back(NodeType::Colon, row, col);
			} else {
				tokens.emplace_back(NodeType::Colon, row, col);
			} break;
		

		case ',':
			++input;
			tokens.emplace_back(NodeType::Comma, row, col);
			break;


		case '.':
			++input;
			if (input[0]=='.' && input[1]=='.'){
				input += 2;
				tokens.emplace_back(NodeType::Placeholder, row, col);
			} else
				tokens.emplace_back(NodeType::Access, row, col);
			break;


		case ';':
			++input;
			tokens.emplace_back(NodeType::Terminator, row, col);
			break;
		
		
		case '\'':{
				++input;
				if (*input=='\\' || *(input+1)=='\''){
					const uint64_t c = getCharFromIterator(&input);
					tokens.emplace_back(NodeType::Letter, c, row, col);

					if (!c || *input!='\'') raiseError(ErrorType::WrongCharacterLiteral, row, col);

					++input;
					if (isValidNameChar(*input))
						pushNamedToken(&input, &tokens, row, col, true);
				} else
					tokens.emplace_back(NodeType::Dereference, row, col);
			}
			break;
		
		
		case '\"':{ ++input;
				const size_t stringIndex = std::size(tokens);
				tokens.emplace_back(NodeType::String, row, col);
				char *I = tokens.back().data.name;
				const char *end = (char *)std::end(tokens);

				while(*input!='\"' && *input){
					*I = getCharFromIterator(&input);
					++tokens[stringIndex].data.nameLen;

					if (*I == '\n'){
						++row;
						prevInput = input;
					}
					if (I == end){
						tokens.emplace_back();
						I = tokens.back().longName;
						end = (char *)std::end(tokens);
					}
				}

				if (!*input) raiseError(ErrorType::UnfinishedCode, row, col);

				++input;
				if (isValidNameChar(*input))
					pushNamedToken(&input, &tokens, row, col, true);
			}
			break;


		case '#': ++input;{
			std::string_view text = getText(input);
			input += std::size(text);
			for (uint32_t i=0; i<(uint32_t)NodeType::Fn; ++i)
				if (text == KeywordName[i]){
					tokens.emplace_back((NodeType)i, row, col);
					goto Break;
				}
			raiseError(ErrorType::WrongCompileDirective, row, col);
		}
		
		case '\n': ++input;
			++row;
			col = -1;
			break;

		
		case ' ':
		case '\t': ++input;
			break;


		default:
			if (isValidNameFirstChar(*input))
				pushNamedToken(&input, &tokens, row, col, false);
			else if (isNumberLiteral(input)){
				tokens.push_back(getNumberTokenFromIterator(&input, row, col));
				if (isValidNameFirstChar(*input))
					pushNamedToken(&input, &tokens, row, col, true);
			} else{
				tokens.emplace_back(NodeType::Null, row, col);
				return tokens;
			}
			break;
		} Break:

		col += input - prevInput;
	}
}



char getCharFromIterator(const char **const inpIter) noexcept{
	char c = **inpIter;
	++*inpIter;

	if (c=='\'' || c== '\"') return 0;
	
	if (c == '\\')
		switch (**inpIter){
		case '\'':
		case '\"': ++*inpIter;
			return *(*inpIter-1);
		case '0' ... '9':
			c = strtol(*inpIter, const_cast<char **>(inpIter), 10);
			if (c > 255) return 0;
			return c;
		case 'n': ++*inpIter;
			return '\n';
		case 't': ++*inpIter;
			return '\t';
		}
	return c;
}

Node getNumberTokenFromIterator(const char **const inpIter, const uint32_t row, const uint16_t col) noexcept{
	int64_t numsign;
	uint64_t intResult;
	{
		const char c = **inpIter;
		numsign = (c=='+') - (c=='-');
		*inpIter += numsign & 1;
		numsign += !numsign;
	}
	if (**inpIter == '0'){
		++*inpIter;
		switch (**inpIter){
		case 'x':
		case 'X':
			intResult = numsign * (uint64_t)numsign*strtoul(*inpIter+1, (char **)inpIter, 16);
			return Node{intResult>>32 ? NodeType::BigNumber : NodeType::Number, row, col, intResult};
		
		case 'q':
		case 'Q':
			intResult = numsign * (uint64_t)strtoul(*inpIter+1, (char **)inpIter, 8);
			return Node{intResult>>32 ? NodeType::BigNumber : NodeType::Number, row, col, intResult};

		case 'b':
		case 'B':
			intResult = numsign * (uint64_t)strtoul(*inpIter+1, (char **)inpIter, 2);
			return Node{intResult>>32 ? NodeType::BigNumber : NodeType::Number, row, col, intResult};

		default: break;
		}
	}
	{
		const char *const prevInpIter = *inpIter;
		intResult = numsign * (uint64_t)strtoul(*inpIter, (char **)inpIter, 10);
		if (**inpIter == '.'){
			return Node{NodeType::Float, row, col, numsign*strtod(prevInpIter, (char**)inpIter)};
		}
	}
	return Node{intResult>>32 ? NodeType::BigNumber : NodeType::Number, row, col, intResult};
}

} // END OF NAMESPACE /////////////////////////////////////////////////