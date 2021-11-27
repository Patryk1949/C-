#pragma once

#include "MainParser.hpp"


namespace spcomp{
	void printDecodedChar(const char c){
		switch (c){
		case '\n': printf("\\n"); break;
		case '\t': printf("\\t"); break;
		default:
			if (c < 32) printf("\\%u", (uint32_t)c);
			else putchar(c);
		}
	}


	void printFunctionNodes(sp::DArray<Node> &nodes){
		struct{
			sp::DArray<uint16_t> indents;
			size_t scopeCounter = 0;
			
			void operator ()(const char *text){
				for (size_t i=0; i!=std::size(indents)+scopeCounter; ++i) printf("   ");
				puts(text);
				if (std::size(indents)) --indents.back();
			}
			size_t operator ()(const char *text, const char *const name, const uint16_t nameLen){
				for (size_t i=0; i!=std::size(indents)+scopeCounter; ++i) printf("   ");
				printf("%s :  ", text);
				for (size_t i=0; i!=nameLen; ++i) printDecodedChar(name[i]);
				putchar('\n');
				if (std::size(indents)) --indents.back();
				return textBlockCount(nameLen) - 1;
			}
			void operator ()(const char *text, const ssize_t arg){
				for (size_t i=0; i!=std::size(indents)+scopeCounter; ++i) printf("   ");
				printf("%s :  %ld\n", text, arg);
				if (std::size(indents)) --indents.back();
			}
			void operator ()(const char *text, const size_t arg){
				for (size_t i=0; i!=std::size(indents)+scopeCounter; ++i) printf("   ");
				printf("%s :  %lu\n", text, arg);
				if (std::size(indents)) --indents.back();
			}
			void operator ()(const char *text, const double arg){
				for (size_t i=0; i!=std::size(indents)+scopeCounter; ++i) printf("   ");
				printf("%s :  %lf\n", text, arg);
				if (std::size(indents)) --indents.back();
			}
			void operator ()(const char *text, const char arg){
				for (size_t i=0; i!=std::size(indents)+scopeCounter; ++i) printf("   ");
				printf("%s :  ", text);
				printDecodedChar(arg);
				putchar('\n');
				if (std::size(indents)) --indents.back();
			}
		} printIndented;

		auto reduceIndents = [&printIndented]() mutable{
			while (std::size(printIndented.indents)){
				if (!printIndented.indents.back()) printIndented.indents.pop_back();
				else break;
			}
		};

		for (const Node *I=std::begin(nodes);; ++I){
			switch (I->type){
			case NodeType::Assign:
				printIndented("assign");
				printIndented.indents.push_back(2);
				break;
			case NodeType::AddAssign:
				printIndented("add assign");
				printIndented.indents.push_back(2);
				break;
			case NodeType::SubtractAssign:
				printIndented("subtract assign");
				printIndented.indents.push_back(2);
				break;
			case NodeType::MultiplyAssign:
				printIndented("multiply assign");
				printIndented.indents.push_back(2);
				break;
			case NodeType::DivideAssign:
				printIndented("divide assign");
				printIndented.indents.push_back(2);
				break;
			case NodeType::ModulusAssign:
				printIndented("modulus assign");
				printIndented.indents.push_back(2);
				break;
			case NodeType::PowerAssign:
				printIndented("power assign");
				printIndented.indents.push_back(2);
				break;
			case NodeType::BitOrAssign:
				printIndented("bitwise or assign");
				printIndented.indents.push_back(2);
				break;
			case NodeType::BitAndAssign:
				printIndented("bitwise and assign");
				printIndented.indents.push_back(2);
				break;
			case NodeType::BitXorAssign:
				printIndented("bitwise xor assign");
				printIndented.indents.push_back(2);
				break;
			case NodeType::LeftShiftAssign:
				printIndented("left shift assign");
				printIndented.indents.push_back(2);
				break;
			case NodeType::RightShiftAssign:
				printIndented("right shift assign");
				printIndented.indents.push_back(2);
				break;
			case NodeType::Initialize:
				printIndented("initialize");
				printIndented.indents.push_back(2);
				break;
			case NodeType::Increment:
				printIndented("increment");
				printIndented.indents.push_back(1);
				break;
			case NodeType::Decrement:
				printIndented("decrement");
				printIndented.indents.push_back(1);
				break;
			case NodeType::LogicOr:
				printIndented("logic or");
				printIndented.indents.push_back(2);
				break;
			case NodeType::LogicAnd:
				printIndented("logic and");
				printIndented.indents.push_back(2);
				break;
			case NodeType::Lesser:
				printIndented("lesser comparison");
				printIndented.indents.push_back(2);
				break;
			case NodeType::Greater:
				printIndented("greater comparison");
				printIndented.indents.push_back(2);
				break;
			case NodeType::LesserEq:
				printIndented("lesser or equal comparison");
				printIndented.indents.push_back(2);
				break;
			case NodeType::GreaterEq:
				printIndented("greater or equal comparison");
				printIndented.indents.push_back(2);
				break;
			case NodeType::Equals:
				printIndented("equals");
				printIndented.indents.push_back(2);
				break;
			case NodeType::NotEquals:
				printIndented("not equals");
				printIndented.indents.push_back(2);
				break;
			case NodeType::Add:
				printIndented("add");
				printIndented.indents.push_back(2);
				break;
			case NodeType::Subtract:
				printIndented("subtract");
				printIndented.indents.push_back(2);
				break;
			case NodeType::Multiply:
				printIndented("multiply");
				printIndented.indents.push_back(2);
				break;
			case NodeType::Divide:
				printIndented("divide");
				printIndented.indents.push_back(2);
				break;
			case NodeType::Modulus:
				printIndented("modulus");
				printIndented.indents.push_back(2);
				break;
			case NodeType::Power:
				printIndented("power");
				printIndented.indents.push_back(2);
				break;
			case NodeType::BitOr:
				printIndented("bitwise or");
				printIndented.indents.push_back(2);
				break;
			case NodeType::BitAnd:
				printIndented("bitwise and");
				printIndented.indents.push_back(2);
				break;
			case NodeType::BitXor:
				printIndented("bitwise xor");
				printIndented.indents.push_back(2);
				break;
			case NodeType::BitNor:
				printIndented("bitwise nor");
				printIndented.indents.push_back(2);
				break;
			case NodeType::BitNand:
				printIndented("bitwise nand");
				printIndented.indents.push_back(2);
				break;
			case NodeType::BitXnor:
				printIndented("bitwise xnor");
				printIndented.indents.push_back(2);
				break;
			case NodeType::LeftShift:
				printIndented("left shift");
				printIndented.indents.push_back(2);
				break;
			case NodeType::RightShift:
				printIndented("right shift");
				printIndented.indents.push_back(2);
				break;
			case NodeType::Negate:
				printIndented("negate");
				printIndented.indents.push_back(1);
				break;
			case NodeType::Identity:
				printIndented("get identity");
				printIndented.indents.push_back(1);
				break;
			case NodeType::LogicNot:
				printIndented("logic not");
				printIndented.indents.push_back(1);
				break;
			case NodeType::BitNot:
				printIndented("bitwise not");
				printIndented.indents.push_back(1);
				break;
			case NodeType::Dereference:
				printIndented("dereference");
				printIndented.indents.push_back(1);
				break;
			case NodeType::GetAddress:
				printIndented("get address");
				printIndented.indents.push_back(1);
				break;

			case NodeType::Elvis:
				printIndented("elvis operator");
				printIndented.indents.push_back(2);
				break;
			case NodeType::Ternary:
				printIndented("ternary operator");
				printIndented.indents.push_back(1);
				break;
			case NodeType::Bytesize:
				printIndented("get byte size");
				printIndented.indents.push_back(1);
				break;
			case NodeType::Exists:
				printIndented("check is exists");
				printIndented.indents.push_back(2);
				break;
			case NodeType::StaticAssert:
				printIndented("static assert");
				printIndented.indents.push_back(2);
				break;

			case NodeType::Call:
				printIndented("function call", I->data.number);
				printIndented.indents.push_back(1 + I->data.number);
				break;
			case NodeType::FunctionAddress:
				printIndented("adress of function", I->data.number);
				printIndented.indents.push_back(1 + I->data.number);
				break;
			case NodeType::Subscript:
				printIndented("subscript", I->data.number);
				printIndented.indents.push_back(1 + I->data.number);
				break;
			case NodeType::Access:
				I += printIndented("member access", I->data.name, I->data.nameLen);
				printIndented.indents.push_back(1);
				break;
			case NodeType::Conversion:
				printIndented("conversion");
				printIndented.indents.push_back(2);
				break;
			case NodeType::Literal:
				I += printIndented("literal", I->data.name, I->data.nameLen);
				printIndented.indents.push_back(1);
				break;
			case NodeType::ArrayLiteral:
				printIndented("array literal", I->data.number);
				printIndented.indents.push_back(I->data.number);
				break;
			case NodeType::BraceInit:
				printIndented("member access", I->data.number);
				printIndented.indents.push_back(1 + I->data.number);
				break;

			case NodeType::Declare:
				switch (I->data.argsCount){
				case 0:
					I += printIndented("variable declaration : auto", I->data.name, I->data.shortNameLen); break;
				case 1:
					I += printIndented("variable declaration : default", I->data.name, I->data.shortNameLen); break;
				case 2:
					I += printIndented("variable declaration : assign", I->data.name, I->data.shortNameLen); break;
				case 3:
					I += printIndented("variable declaration : auto, no destructor", I->data.name, I->data.shortNameLen); break;
				case 4:
					I += printIndented("variable declaration : assign, no destructor", I->data.name, I->data.shortNameLen); break;
				default:
					I += printIndented("variable declaration : brace init, no destructor", I->data.name, I->data.shortNameLen); break;
				}
				printIndented.indents.push_back(!I->data.argsCount + I->data.argsCount - (I->data.argsCount>2)*2);
				break;
			case NodeType::Label:
				I += printIndented("label", I->data.name, I->data.nameLen);
				break;
			case NodeType::Goto:
				I += printIndented("goto label", I->data.name, I->data.nameLen);
				break;
			case NodeType::GotoAddress:
				printIndented("goto address");
				printIndented.indents.push_back(1);
				break;
			case NodeType::Break:
				printIndented("break", I->data.number);
				break;
			case NodeType::Gotonext:
				printIndented("goto next iteration", I->data.number);
				break;

			


			case NodeType::Fn:
				printIndented("function");
				++printIndented.scopeCounter;
				break;
			case NodeType::Comut:
				printIndented("commutative specifier", I->data.number);
				printIndented.indents.push_back(I->data.number);
				break;
			case NodeType::Restr:
				printIndented("restrict pointers specifier", I->data.number);
				printIndented.indents.push_back(I->data.number);
				break;
			case NodeType::OpenScope:
				printIndented("open scope");
				++printIndented.scopeCounter;
				break;
			case NodeType::CloseScope:
				printIndented("close scope");
				if (!printIndented.scopeCounter) return;
				--printIndented.scopeCounter;
				break;
			case NodeType::If:
				printIndented("if");
				printIndented.indents.push_back(1);
				++printIndented.scopeCounter;
				break;
			case NodeType::StaticIf:
				printIndented("static if");
				printIndented.indents.push_back(1);
				++printIndented.scopeCounter;
				break;
			case NodeType::Else:
				printIndented("else");
				break;
			case NodeType::Do:
				printIndented("do");
				++printIndented.scopeCounter;
				break;
			case NodeType::WhileOfDo:
				printIndented("while loop");
				printIndented.indents.push_back(1);
				break;
			case NodeType::While:
				printIndented("while loop");
				printIndented.indents.push_back(1);
				++printIndented.scopeCounter;
				break;
			case NodeType::Defer:
				printIndented("defer");
				++printIndented.scopeCounter;
				break;
				

			case NodeType::ArrayType:
				printIndented("array declaration");
				printIndented.indents.push_back(2);
				break;
			case NodeType::ConstPointer:
				printIndented("pointer to constant");
				printIndented.indents.push_back(1);
				break;
			case NodeType::Static:
				printIndented("static");
				printIndented.indents.push_back(1);
				break;

			case NodeType::Name:
				I += printIndented("identifier", I->data.name, I->data.nameLen);
				reduceIndents();
				break;
			case NodeType::Deduction:
				printIndented("deduced type or value");
				reduceIndents();
				break;
			case NodeType::Class:
				printIndented("class");
				reduceIndents();
				break;
			case NodeType::Float:
				printIndented("floating point number", (double)I->data.numberFloat);
				reduceIndents();
				break;
			case NodeType::Number:
				printIndented("32 bit number", (int64_t)I->data.number);
				reduceIndents();
				break;
			case NodeType::BigNumber:
				printIndented("64 bit number", (int64_t)I->data.number);
				reduceIndents();
				break;
			case NodeType::Letter:
				printIndented("letter", (char)I->data.number);
				reduceIndents();
				break;
			case NodeType::String:
				I += printIndented("string", I->data.name, I->data.nameLen);
				reduceIndents();
				break;
			case NodeType::Null: return;
			default: raiseError(ErrorType::WrongGotoSyntax, I->row, I->col);
			}
		}
	}



} // END OF NAMESPACE //////////////////////////////////