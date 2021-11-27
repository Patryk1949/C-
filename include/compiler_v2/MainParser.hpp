#pragma once

#include "ExprParser.hpp"
#include "SPL/SOArrays.hpp"


namespace spcomp{



struct Scopes : sp::FiniteArray<NodeType, 64>{
	sp::DArray<size_t> labels;

	Scopes() noexcept: labels{} {}
};

// GLOBALS
	Scopes scopes;

void pushScope(const NodeType t) noexcept{
	if (scopes.isFull()) raiseError(ErrorType::TooManyScopes, iter->row, iter->col);
	scopes.push_back(t);
}
void popScope() noexcept{
	scopes.pop_back();
}



// PARSES THE SCOPE AFTER CLOSING PHARENTHESIS AFTER CONDITIONAL, HANDLES FOR LOOP ENDING OPEARATIONS AND ELSE BRANCHES
void parseConditionalScope(NodeType condType) noexcept;

// PARSES FOR LOOP STARTNG FROM THE SYMBOL THE '>>' OR '<< TILL THE CLOSING PHARENTHESIS,
//    EXPECTS CURRENT SCOPE BEING LOOP WITH DEFERED RANGE VARAIBLE DECLARATION
void parseRangedForLoopVars();


constexpr bool isDeclaration(const Node *const I) noexcept{
	if (I->type != NodeType::Name) return false;
	const NodeType t = (I + textBlockCount(I->data.shortNameLen))->type;
	return t==NodeType::Colon || t==NodeType::Walrus || t==NodeType::WideWalrus;
}



// NAMESPACES
struct Namespace{
	sp::SBArray<char, 16> name;
	sp::SOADArray<sp::SBArray<char, 16>, sp::SBArray<Node *, 2>> members;
	sp::PtrArray<Namespace> children;
	sp::PtrArray<Node> parameters;
};

Namespace globalNams;
sp::FiniteArray<size_t, 16> namsStack;
Namespace *currNamespace = &globalNams;





void parseGlobal() noexcept{
	for (;;){
		switch (iter->type){
		case NodeType::Namespace:{
			++iter;

			Namespace dasdas;
			
			// if (iter->type != NodeType::Name) raiseError(ErrorType::WrongNamespaceSyntax, iter->row, iter->col);
			// if (iter->data.nameLen > 32) raiseError(ErrorType::TooLongName, iter->row, iter->col);
			// std::copy_n((const char *)iter->data.shortNameLen, 32, nams[](nodes));
			// iter += textBlockCount(iter->data.nameLen);
			// ArgListParseResult argListInfo{0, 0};
			// if (iter->type == NodeType::LeftPar){
			// 	++iter;
			// 	argListInfo = parseArgList(NodeType::RightPar, ErrorType::WrongNamespaceSyntax);
			// }
			// nodes[namespaceNodeIndex].data.number = argListInfo.argsCount;

		} break;

		case NodeType::Fn: ++iter;
			// ADD FUNCTION TO NAMESPACE
			{
				const size_t expansionSize = textBlockCount(iter->data.nameLen);
				nodes.expandBy(expansionSize);
				std::copy_backward(iter, iter+expansionSize, std::end(nodes));
				iter += expansionSize;
			}
			parseFunction();
			break;

		case NodeType::Mutable: ++iter;
			if (iter->type == NodeType::Name)
				if (parseVariable(NodeType::Mutable)) break;
			raiseError(ErrorType::MissingVariableDeclaration, iter->row, iter->col);

		case NodeType::Name:
			if (parseVariable(NodeType::Mutable)) break;
			raiseError(ErrorType::MissingVariableDeclaration, iter->row, iter->col);


		case NodeType::Import: ++iter;
			break;

		case NodeType::Main:
			nodes.push_back(*iter);
			parseFunction();
			// MAYBE CHECK IF ARGS ARE CORRECT
			break;
		
		case NodeType::Null:
			nodes.push_back(*iter);
			return;

		default: raiseError(ErrorType::UnrecognizedGlobal, iter->row, iter->col);
		}
	}
}




void parseFunction() noexcept{
	const size_t infoNode = std::size(nodes);
	nodes.emplace_back(nullptr);

	size_t counter = 0;
	while (iter->type != NodeType::LeftPar)
		if (iter->type==NodeType::LogicNot || iter->type==NodeType::BitNot){
			nodes[infoNode].funcInfo.modInfo[counter][0] = 1 + (iter->type==NodeType::BitNot);
			++iter;
			++counter;
			if (iter->type == NodeType::OpenScope){
				const auto argListInfo = parseArgList(NodeType::CloseScope, ErrorType::MissingClosingBrace);
				if (argListInfo.argsCount < 2) raiseError(ErrorType::MissingArguments, iter->row, iter->col);
				nodes[infoNode].funcInfo.modInfo[counter][1] = argListInfo.argsCount;
			}
		} else raiseError(ErrorType::WrongFunctionSyntax, iter->row, iter->col);
	if (counter >= 8) raiseError(ErrorType::TooManyArguments, iter->row, iter->col);
	const auto argListInfo = parseArgList(NodeType::RightPar, ErrorType::WrongFunctionArgument);
	if (argListInfo.argsCount > 240) raiseError(ErrorType::TooManyArguments, iter->row, iter->col);
	nodes[infoNode].funcInfo.argsCount = argListInfo.argsCount;

	for (size_t i=0;; ++i){
		if (i == 7) raiseError(ErrorType::TooManyArguments, iter->row, iter->col);
		switch (iter->type){
		case NodeType::Colon:{ ++iter;
			nodes[infoNode].funcInfo.returnInfo[i] = 1;
			parse0();
			break;
		}
		case NodeType::Name:{
			nodes[infoNode].funcInfo.returnInfo[i] = 3;
			const size_t expansionSize = textBlockCount(iter->data.nameLen);
			nodes.expandBy(expansionSize);
			std::copy_backward(iter, iter+expansionSize, std::end(nodes));
			iter += expansionSize;
			if (iter->type == NodeType::Dereference){
				nodes[infoNode].funcInfo.returnInfo[i] = 4;
				++iter;
			} else if (iter->type == NodeType::Multiply){
				nodes[infoNode].funcInfo.returnInfo[i] = 5;
				++iter;
			}
			if (iter->type != NodeType::Colon) raiseError(ErrorType::WrongFunctionSyntax, iter->row, iter->col);
			++iter;
			parse0();
			break;
		}
		case NodeType::Dereference:{ ++iter;
			nodes[infoNode].funcInfo.returnInfo[i] = 2;
			parse0();
			break;
		}
		
		case NodeType::Comma: ++iter; break;
		case NodeType::OpenScope: ++iter;
			goto ParseBody;

		default: raiseError(ErrorType::WrongFunctionSyntax, iter->row, iter->col);
		}
	}

ParseBody:
	pushScope(NodeType::Fn);
	for (;;){
		if (iter->type == NodeType::CloseScope){ ++iter;

			if (!(scopes.size()-1)){
				nodes.emplace_back(NodeType::CloseScope, iter->row, iter->col);
				popScope();
				return;
			}

			if ((scopes.back()==NodeType::If || scopes.back()==NodeType::StaticIf) && iter->type==NodeType::Else){
				++iter;
				if (iter->type != NodeType::OpenScope) raiseError(ErrorType::MissingScope, iter->row, iter->col);
				++iter;

				nodes.emplace_back(NodeType::Else, iter->row, iter->col);
				scopes.back() = NodeType::Else;
				continue;
			} else if (scopes.back()==NodeType::Do && iter->type==NodeType::While){
				++iter;
				if (isDeclaration(iter)) raiseError(ErrorType::DoublyPredefinedVariables, iter->row, iter->col);
				
				nodes.emplace_back(NodeType::WhileOfDo, iter->row, iter->col);
				parseExpression();
				if (iter->type != NodeType::OpenScope) raiseError(ErrorType::MissingScope, iter->row, iter->col);
				scopes.back() = NodeType::WhileOfDo;
				++iter;
				continue;
			}
			nodes.emplace_back(NodeType::CloseScope, iter->row, iter->col);
			popScope();
			if (scopes.back() == NodeType::PredefScope){
				nodes.emplace_back(NodeType::CloseScope, iter->row, iter->col);
				popScope();
			}
		} else{
			parseStatement();
		}
	}
}



bool inConditional(const NodeType cond) noexcept{
	const NodeType *const sentinel = std::cbegin(scopes) - 1;
	const NodeType *I=std::cend(scopes);
	while (--I != sentinel) if (*I == cond) return true;
	return false;
}



void parseStatement() noexcept{
Repeat:
	switch (iter->type){
	case NodeType::Name:
		if (parseVariable(NodeType::Declare)) goto Terminator;
		break;

	case NodeType::Greater: ++iter;
		if (iter->type == NodeType::Name){
			if (inConditional(NodeType::StaticIf))
				raiseError(ErrorType::LabelInStaticIf, iter->row, iter->col);
			const size_t expansionSize = textBlockCount(iter->data.nameLen);
			const size_t nodeIndex = std::size(nodes);

			nodes.expandBy(expansionSize);
			std::copy_n(iter, expansionSize, std::end(nodes)-expansionSize);
			iter += expansionSize;

			(nodes)[nodeIndex].type = NodeType::Label;
			if (iter->type != NodeType::Greater) raiseError(ErrorType::WrongLabelSyntax, iter->row, iter->col);
			++iter;
			goto Repeat;
		} else raiseError(ErrorType::WrongLabelSyntax, iter->row, iter->col);

	case NodeType::Defer:{ ++iter;
		nodes.emplace_back(NodeType::Defer, iter->row, iter->col);
		pushScope(NodeType::Defer);
		
		if (iter->type != NodeType::OpenScope){
			parseStatement();
			nodes.emplace_back(NodeType::CloseScope, iter->row, iter->col);
			popScope();
		} else ++iter;
		return;
	}

	case NodeType::StaticIf: ++iter;
		if (isDeclaration(iter)){
			pushScope(NodeType::PredefScope);
			nodes.emplace_back(NodeType::OpenScope, iter->row, iter->col);
			do parseStatement(); while (isDeclaration(iter));
		}
		nodes.emplace_back(NodeType::StaticIf, iter->row, iter->col);
		parseExpression();
		if (iter->type != NodeType::OpenScope) raiseError(ErrorType::MissingScope, iter->row, iter->col);
		++iter;
		pushScope(NodeType::StaticIf);
		return;

	case NodeType::If: ++iter;
		if (isDeclaration(iter)){
			pushScope(NodeType::PredefScope);
			nodes.emplace_back(NodeType::OpenScope, iter->row, iter->col);
			do parseStatement(); while (isDeclaration(iter));
		}
		nodes.emplace_back(NodeType::If, iter->row, iter->col);
		parseExpression();
		if (iter->type != NodeType::OpenScope) raiseError(ErrorType::MissingScope, iter->row, iter->col);
		++iter;
		pushScope(NodeType::If);
		return;

	case NodeType::Do: ++iter;
		if (isDeclaration(iter)){
			pushScope(NodeType::PredefScope);
			nodes.emplace_back(NodeType::OpenScope, iter->row, iter->col);
			do parseStatement(); while (isDeclaration(iter));
		}
		nodes.emplace_back(NodeType::Do, iter->row, iter->col);
		if (iter->type != NodeType::OpenScope) raiseError(ErrorType::MissingScope, iter->row, iter->col);
		++iter;
		pushScope(NodeType::Do);
		return;

	case NodeType::While: ++iter;
		if (isDeclaration(iter)){
			pushScope(NodeType::PredefScope);
			nodes.emplace_back(NodeType::OpenScope, iter->row, iter->col);
			do parseStatement(); while (isDeclaration(iter));
		}
		nodes.emplace_back(NodeType::While, iter->row, iter->col);
		parseExpression();
		if (iter->type != NodeType::OpenScope) raiseError(ErrorType::MissingScope, iter->row, iter->col);
		++iter;
		pushScope(NodeType::While);
		return;


/*	case NodeType::For:{ ++iter;
		if (iter->type != NodeType::LeftPar)
			raiseError(ErrorType::MissingPharenthesis, iter->row, iter->col);
		++iter;
		if (iter->type != NodeType::Terminator){
			const size_t varIndex = nodes.size();

			if (scopes.isFull()) raiseError(ErrorType::TooManyScopes, iter->row, iter->col);
			pushScope(NodeType::PreConditionalScope);
			parseExpression();
			parseVariables(iterator, nodes, varIndex);

			if (iter->type==NodeType::LeftShift || iter->type==NodeType::RightShift){
				if ((nodes)[varIndex].data.varsInfo[0] != 1)
					raiseError(ErrorType::ConstructorInRangeBasedForLoop, iter->row, iter->col);
				if ((nodes)[varIndex].data.varsInfo[1])
					raiseError(ErrorType::TooManyVariablesInForLoop, iter->row, iter->col);

				if (scopes.isFull()) raiseError(ErrorType::TooManyScopes, iter->row, iter->col);
				pushScope(NodeType::Loop);
				scopes.addDefers(&*std::begin(nodes)+varIndex, &*std::end(nodes));
				nodes.resize(varIndex);
				parseRangedForLoopVars(iterator, nodes, scopes);
				return;
			}
			if (iter->type != NodeType::Terminator)
				raiseError(ErrorType::MissingTerminator, iter->row, iter->col);
		} ++iter;

		const size_t loopIndex = nodes.size();
		nodes.emplace_back(NodeType::Loop);
		if (iter->type == NodeType::Terminator){
			nodes.emplace_back(NodeType::Name);
			new (&nodes.back()) std::string("True");
		} else parseExpression();

		if (iter->type == NodeType::Name){
			parseVariables(iterator, nodes, loopIndex+1);
			if ((nodes)[loopIndex+1].data.varsInfo[0] != 1)
				raiseError(ErrorType::ConstructorInRangeBasedForLoop, iter->row, iter->col);
			if ((nodes)[loopIndex+1].data.varsInfo[1])
				raiseError(ErrorType::TooManyVariablesInForLoop, iter->row, iter->col);
			if (iter->type!=NodeType::LeftShift && iter->type!=NodeType::RightShift)
				raiseError(ErrorType::WrongLoopSyntax, iter->row, iter->col);
			++iter;

			if (scopes.isFull()) raiseError(ErrorType::TooManyScopes, iter->row, iter->col);
			pushScope(NodeType::Loop);
			scopes.addDefers(&*std::begin(nodes)+loopIndex+1, &*std::end(nodes));
			nodes.resize(loopIndex);
			parseRangedForLoopVars(iterator, nodes, scopes);
			return;
		}
		if (iter->type != NodeType::Terminator)
			raiseError(ErrorType::MissingTerminator, iter->row, iter->col);
		++iter;

		if (iter->type != NodeType::RightPar){
			parseExpression(iterator, &scopes.back().deferedOps);
			while (iter->type != NodeType::RightPar){
				if (iter->type != NodeType::Comma)
					raiseError(ErrorType::MissingComma, iter->row, iter->col);
				++iter;
				parseExpression(iterator, &scopes.back().deferedOps);
			}
			++iter;
		}

		if (scopes.isFull()) raiseError(ErrorType::TooManyScopes, iter->row, iter->col);
		pushScope(NodeType::Loop);
	} return;
*/

	case NodeType::Goto: ++iter;
		if (iter->type == NodeType::Dereference){
			++iter;
			nodes.emplace_back(NodeType::GotoAddress, iter->row, iter->col);
			parseExpression();
		} else if (iter->type == NodeType::Name){
			const size_t expansionSize = textBlockCount(iter->data.nameLen);
			const size_t nodeIndex = std::size(nodes);

			nodes.expandBy(expansionSize);
			std::copy_n(iter, expansionSize, std::end(nodes)-expansionSize);
			iter += expansionSize;

			(nodes)[nodeIndex].type = NodeType::Goto;
		} else raiseError(ErrorType::WrongGotoSyntax, iter->row, iter->col);
		goto Terminator;

	case NodeType::Break:
		nodes.emplace_back(NodeType::Break, iter->row, iter->col);
		nodes.back().data.number = 0;	// NUMBER IS THE COUNT OF ADDITIONAL BREAKS / GOTONEXTS
		while ((++iter)->type == NodeType::Break) ++nodes.back().data.number;
		if (iter->type == NodeType::Gotonext){ ++iter;
			++nodes.back().data.number;
			nodes.back().type = NodeType::Gotonext;
		}
		goto Terminator;

	case NodeType::Gotonext: ++iter;
		nodes.emplace_back(NodeType::Gotonext, iter->row, iter->col);
		nodes.back().data.number = 0;
		goto Terminator;

	case NodeType::Return: ++iter;
		nodes.emplace_back(NodeType::Return, iter->row, iter->col);
		nodes.back().data.number = 0;
		goto Terminator;

	case NodeType::StaticAssert:{ ++iter;
		if (iter->type != NodeType::LeftPar) raiseError(ErrorType::MissingPharenthesis, iter->row, iter->col);
		const size_t StassertIndex = nodes.size();
		nodes.emplace_back(NodeType::StaticAssert, iter->row, iter->col);
		const ArgListParseResult res = parseArgList(NodeType::RightPar, ErrorType::MissingPharenthesis);
		if (!res.argsCount || res.argsCount > 2) raiseError(ErrorType::WrongNumberOfArguments, iter->row, iter->col);
		(nodes)[StassertIndex].data.number = res.argsCount == 2; // NUMBER WORKS AS FLAG FOR HAVING A MESSAGE
		goto Terminator;
	}

	case NodeType::Class:
		// HANDLE TYPE ALIAS DECLARATION

	case NodeType::OpenScope: ++iter;
		pushScope(NodeType::OpenScope);
		nodes.emplace_back(NodeType::OpenScope, iter->row, iter->col);
		return;
	
	default: break;
	}
	parseExpression();
Terminator:
	if (iter->type != NodeType::Terminator) raiseError(ErrorType::MissingTerminator, iter->row, iter->col);
	++iter;
}



bool parseVariable(const NodeType declareType) noexcept{
	const size_t expansionSize = textBlockCount(iter->data.nameLen);
	if (iter[expansionSize].type==NodeType::Colon){
		if (iter->data.nameLen > 240) raiseError(ErrorType::TooLongName, iter->row, iter->col);
		const size_t nodeIndex = std::size(nodes);
		
		Node *const nameToken = iter;
		iter += 1 + expansionSize;

		size_t argsCount = 1;

		nodes.expandBy(expansionSize - 1);
		parseExpression();
		Node *const typeNode = std::begin(nodes) + nodeIndex + expansionSize - 1;
		if (typeNode->type == NodeType::Assign){
			if (typeNode[1].type == NodeType::BraceInit){
				if (typeNode[1].data.argsCount != 0) raiseError(ErrorType::BlantDefinitionWithBraceArguments, iter->row, iter->col);
				std::move(typeNode+1, std::end(nodes), typeNode);
				nodes.pop_back();
				argsCount = 4;
			} else
				argsCount = 2;
		} else if (typeNode->type == NodeType::BraceInit){
			if (typeNode->data.number > 240) raiseError(ErrorType::TooManyArguments, iter->row, iter->col);
			argsCount = 5 + typeNode->data.number;
		} else{
			nodes.emplace_back();
			std::move_backward(std::begin(nodes)+nodeIndex+expansionSize-1, std::end(nodes)-1, std::end(nodes));
		}

		std::copy_n(nameToken, expansionSize, std::begin(nodes)+nodeIndex);
		(nodes)[nodeIndex].type = declareType;
		(nodes)[nodeIndex].data.argsCount = argsCount;
	} else if (iter[expansionSize].type==NodeType::Walrus){
		if (iter->data.nameLen > 240) raiseError(ErrorType::TooLongName, iter->row, iter->col);
		const size_t nodeIndex = std::size(nodes);
		
		Node *const nameToken = iter;
		iter += 1 + expansionSize;

		nodes.expandBy(expansionSize);
		parseExpression();

		std::copy_n(nameToken, expansionSize, std::begin(nodes)+nodeIndex);
		(nodes)[nodeIndex].type = declareType;
		(nodes)[nodeIndex].data.argsCount = 0;
	} else if (iter[expansionSize].type==NodeType::WideWalrus){
		if (iter->data.nameLen > 240) raiseError(ErrorType::TooLongName, iter->row, iter->col);
		const size_t nodeIndex = std::size(nodes);
		
		Node *const nameToken = iter;
		iter += 1 + expansionSize;

		nodes.expandBy(expansionSize);
		parseExpression();

		std::copy_n(nameToken, expansionSize, std::begin(nodes)+nodeIndex);
		(nodes)[nodeIndex].type = declareType;
		(nodes)[nodeIndex].data.argsCount = 3;
	} else return false;
	return true;
}



void parseConditionalScope(const NodeType condType) noexcept{
	pushScope(condType);
	
	if (iter->type != NodeType::OpenScope){
		parseStatement();
		
		nodes.emplace_back(NodeType::CloseScope, iter->row, iter->col);
		popScope();
		
		if ((condType==NodeType::If || condType==NodeType::StaticIf) && iter->type==NodeType::Else){
			++iter;
			nodes.back().type = NodeType::Else;

			if (scopes.isFull()) raiseError(ErrorType::TooManyScopes, iter->row, iter->col);
			pushScope(NodeType::Else);
			
			if (iter->type != NodeType::OpenScope){
				parseStatement();
				nodes.emplace_back(NodeType::CloseScope, iter->row, iter->col);
				popScope();
			} else{
				++iter; return;
			}
		}
	
	} else ++iter;
}


size_t pareseStructMembers() noexcept{
	size_t argsCount = 0;
	while (iter->type != NodeType::CloseScope){
		const size_t rootIndex = std::size(nodes);
		parseExpression();
		// parseVariables(iterator, nodes, rootIndex);
		if (iter->type != NodeType::Terminator) raiseError(ErrorType::MissingTerminator, iter->row, iter->col);
		++argsCount;
		++iter;
	}
	++iter;
	return argsCount;
}



/* RETURNED PARAMETERS ENCODING :
		0 - no parameter (auto deduction)
		1 - defined type
		2 - defined type and auto dereferece is set
		3 - defined type and name
		4 - defined type and name and auto dereference is set
		5 - definde type and name and output parameter is set
*/

} // END OF NAMESPACE //////////////////////////////////