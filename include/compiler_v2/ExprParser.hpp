#pragma once

#include "Tokenizer.hpp"


namespace spcomp{
// GLOBALS
	Node *iter;
	sp::DArray<Node> nodes;


size_t parseExpression() noexcept;	// TERNARY, ELVIS
size_t parse11() noexcept;		// LOGIC OR
size_t parse10() noexcept;		// LOGIC AND
size_t parse9() noexcept;		// COMPARISONS
size_t parse8() noexcept;		// ADD, SUBTRACT
size_t parse7() noexcept;		// MULTIPLY, DIVIDE
size_t parse6() noexcept;		// MODULUS
size_t parse5() noexcept;		// POWER
size_t parse4() noexcept;		// OR
size_t parse3() noexcept;		// AND
size_t parse2() noexcept;		// XOR
size_t parse1() noexcept;		// BIT SHIFTS
size_t parse0(size_t typeNodeIndex = (size_t)-1) noexcept;		// UNARY OPEARATORS AND VALUES
size_t parsePostfix(size_t lastNodeIndex, size_t typeNodeIndex) noexcept;
				// CALL, INDEX ACCESS, CLASS INITAILIZER, MEBER ACCESS, MEMBER DEREFERENCE, INCREMENT, DECREMENT

struct ArgListParseResult{ size_t exprSize, argsCount; };
ArgListParseResult parseArgList(NodeType escapeToken, ErrorType errorType) noexcept;


// DECLARATIONS OF FUNCTIONS DEFINED IN MainParser.hpp:
	void parseStatement() noexcept;
	bool parseVariable(NodeType declareType) noexcept;
	void parseFunction() noexcept;



bool isStatement(const Node *I) noexcept{
	for (size_t scopeDepth=0;; ++I){			// CHECK IF THE BRACE OPENS A SCOPE AND RETURN IF ITS TRUE
		scopeDepth += I->type == NodeType::OpenScope;
		if (I->type == NodeType::CloseScope){
			if (!scopeDepth) return false;
			--scopeDepth;
		} else if (I->type==NodeType::Terminator)
			if (!scopeDepth) return true;
		if (hasText(I->type)) I += textBlockCount(I->data.nameLen) - 1;
	}
}



size_t parseExpression(const size_t additionalOutputArgs) noexcept{
	size_t exprSize = parse11();
	const Node token = *iter;

	if (token.type == NodeType::Comma){
		size_t outputArgsCount = 0;
		do{
			++iter;
			++outputArgsCount;
			exprSize += parseExpression();
		} while (iter->type == NodeType::Comma);
	}
	
	if (token.type>=NodeType::Ternary && token.type<=NodeType::RightShiftAssign){
		++iter; ++exprSize;
		nodes.emplace_back();
		std::move_backward(std::end(nodes)-exprSize, std::end(nodes)-1, std::end(nodes));
		(nodes)[std::size(nodes)-exprSize].type = token.type;
		if (token.type > NodeType::Elvis){	// HANDLE ASSIGNMENTS
			if (token.type < NodeType::Assign) return exprSize;	// HANDLE INCREMENT AND DECREMENT
			if (iter->type>=NodeType::Increment && iter->type<=NodeType::RightShiftAssign)
				raiseError(ErrorType::ChainedAssignments, iter->row, iter->col);
		} else if (token.type == NodeType::Ternary){
			exprSize += parseExpression();
			if (iter->type != NodeType::Colon)
				raiseError(ErrorType::UnfinishedTernary, iter->row, iter->col);
			++iter;
		}
		return exprSize + parseExpression();
	}

	return exprSize;
}

size_t parse11() noexcept{
	size_t exprSize = parse10();
	
	while (iter->type==NodeType::LogicOr){
		nodes.emplace_back();
		std::move_backward(std::end(nodes)-exprSize-1, std::end(nodes)-1, std::end(nodes));
		(nodes)[std::size(nodes)-exprSize-1].type = iter->type;
		++iter;
		exprSize += 1 + parse10();
	}
	return exprSize;
}

size_t parse10() noexcept{
	size_t exprSize = parse9();
	
	while (iter->type == NodeType::LogicAnd){
		nodes.emplace_back();
		std::move_backward(std::end(nodes)-exprSize-1, std::end(nodes)-1, std::end(nodes));
		(nodes)[std::size(nodes)-exprSize-1].type = iter->type;
		++iter;
		exprSize += 1 + parse9();
	}
	return exprSize;
}

size_t parse9() noexcept{
	size_t exprSize = parse8();
	
	{ NodeType tokType = iter->type;
	while (tokType>=NodeType::Equals && tokType<=NodeType::GreaterEq){
		nodes.emplace_back();
		std::move_backward(std::end(nodes)-exprSize-1, std::end(nodes)-1, std::end(nodes));
		(nodes)[std::size(nodes)-exprSize-1].type = iter->type;
		++iter;
		exprSize += 1 + parse8();
		tokType = iter->type;
	}}
	return exprSize;
}

size_t parse8() noexcept{
	size_t exprSize = parse7();
	
	{ NodeType tokType = iter->type;
	while (tokType==NodeType::Add || tokType==NodeType::Subtract){
		nodes.emplace_back();
		std::move_backward(std::end(nodes)-exprSize-1, std::end(nodes)-1, std::end(nodes));
		(nodes)[std::size(nodes)-exprSize-1].type = iter->type;
		++iter;
		exprSize += 1 + parse7();
		tokType = iter->type;
	}}
	return exprSize;
}

size_t parse7() noexcept{
	size_t exprSize = parse6();
	
	{ NodeType tokType = iter->type;
	while (tokType==NodeType::Multiply || tokType==NodeType::Divide){
		nodes.emplace_back();
		std::move_backward(std::end(nodes)-exprSize-1, std::end(nodes)-1, std::end(nodes));
		(nodes)[std::size(nodes)-exprSize-1].type = iter->type;
		++iter;
		exprSize += 1 + parse6();
		tokType = iter->type;
	}}
	return exprSize;
}

size_t parse6() noexcept{
	size_t exprSize = parse5();
	
	while (iter->type == NodeType::Modulus){
		nodes.emplace_back();
		std::move_backward(std::end(nodes)-exprSize-1, std::end(nodes)-1, std::end(nodes));
		(nodes)[std::size(nodes)-exprSize-1].type = iter->type;
		++iter;
		exprSize += 1 + parse5();
	}
	return exprSize;
}

size_t parse5() noexcept{
	size_t exprSize = parse4();
	
	while (iter->type == NodeType::Power){
		nodes.emplace_back();
		std::move_backward(std::end(nodes)-exprSize-1, std::end(nodes)-1, std::end(nodes));
		(nodes)[std::size(nodes)-exprSize-1].type = iter->type;
		++iter;
		exprSize += 1 + parse4();
	}
	return exprSize;
}

size_t parse4() noexcept{
	size_t exprSize = parse3();
	
	while (iter->type==NodeType::BitOr || iter->type==NodeType::BitNor){
		nodes.emplace_back();
		std::move_backward(std::end(nodes)-exprSize-1, std::end(nodes)-1, std::end(nodes));
		(nodes)[std::size(nodes)-exprSize-1].type = iter->type;
		++iter;
		exprSize += 1 + parse3();
	}
	return exprSize;
}

size_t parse3() noexcept{
	size_t exprSize = parse2();
	
	while (iter->type==NodeType::BitAnd || iter->type==NodeType::BitNand){
		nodes.emplace_back();
		std::move_backward(std::end(nodes)-exprSize-1, std::end(nodes)-1, std::end(nodes));
		(nodes)[std::size(nodes)-exprSize-1].type = iter->type;
		++iter;
		exprSize += 1 + parse2();
	}
	return exprSize;
}

size_t parse2() noexcept{
	size_t exprSize = parse1();
	
	while (iter->type == NodeType::BitXor || iter->type==NodeType::BitXnor){
		nodes.emplace_back();
		std::move_backward(std::end(nodes)-exprSize-1, std::end(nodes)-1, std::end(nodes));
		(nodes)[std::size(nodes)-exprSize-1].type = iter->type;
		++iter;
		exprSize += 1 + parse1();
	}
	return exprSize;
}

size_t parse1() noexcept{
	size_t exprSize = parse0();
	
	{ NodeType tokType = iter->type;
	while (tokType==NodeType::LeftShift || tokType==NodeType::RightShift){
		nodes.emplace_back();
		std::move_backward(std::end(nodes)-exprSize-1, std::end(nodes)-1, std::end(nodes));
		(nodes)[std::size(nodes)-exprSize-1].type = iter->type;
		++iter;
		exprSize += 1 + parse0();
		tokType = iter->type;
	}}
	return exprSize;
}

size_t parse0(const size_t typeNodeIndex) noexcept{
	switch (iter->type){
	case NodeType::Add: ++iter;
		nodes.emplace_back(NodeType::Identity, iter->row, iter->col);
		return 1 + parse0();
		
	case NodeType::Subtract: ++iter;
		nodes.emplace_back(NodeType::Negate, iter->row, iter->col);
		return 1 + parse0();


	case NodeType::LogicAnd:
		nodes.emplace_back(NodeType::ArgPasser, iter->row, iter->col);
	case NodeType::BitAnd:{
		const size_t nodesCount = (iter->type == NodeType::LogicAnd) + 1;
		++iter;
		nodes.emplace_back(NodeType::ArgPasser, iter->row, iter->col);
		return nodesCount + parse0(typeNodeIndex+1 ? typeNodeIndex : std::size(nodes)-nodesCount);
	}

	case NodeType::Multiply:
	case NodeType::Power:
		nodes.emplace_back(iter->type==NodeType::Power ? NodeType::ConstPointer : NodeType::GetAddress, iter->row, iter->col);
		++iter;
		return parse0(typeNodeIndex+1 ? typeNodeIndex : std::size(nodes));


	case NodeType::Static:
	case NodeType::Separ:
		nodes.emplace_back(*iter);
		++iter;
		return 1 + parse0(typeNodeIndex+1 ? typeNodeIndex : std::size(nodes)-1);

	case NodeType::Placeholder:{
		nodes.emplace_back(*iter);
		++iter;
		if (iter->type!=NodeType::Name && iter->type!=NodeType::Multiply && iter->type!=NodeType::ConstPointer && iter->type!=NodeType::LeftSqBr){
			nodes.back().type = NodeType::AutoParameterPack;
			return 1;
		}
		return 1 + parse0();
	}

	case NodeType::LogicNot:
	case NodeType::BitNot:
		nodes.push_back(*iter);
		++iter;
		return 1 + parse0(typeNodeIndex);

	case NodeType::LeftPar: ++iter;{
		const size_t exprSize = parseExpression();
		if (iter->type != NodeType::RightPar) raiseError(ErrorType::MissingPharenthesis, iter->row, iter->col);
		++iter;
		return parsePostfix(nodes.size()-exprSize, typeNodeIndex);
	}

	case NodeType::Float:
	case NodeType::Number:
	case NodeType::BigNumber:
	case NodeType::Letter:{
		const Node token = *iter;
		const size_t nodeIndex = std::size(nodes);
		++iter;
		if (iter->type == NodeType::Literal){
			const size_t expansionSize = textBlockCount(iter->data.nameLen);
			nodes.expandBy(expansionSize);
			std::copy_n(iter, expansionSize, std::begin(nodes)+nodeIndex);
			iter += expansionSize;
		}
		nodes.push_back(token);
		return parsePostfix(nodeIndex, typeNodeIndex);
	}

	case NodeType::Deduction:
		nodes.push_back(*iter);
		++iter;
		return parsePostfix(std::size(nodes)-1, typeNodeIndex);


	case NodeType::Tuple:{
		const size_t nodeIndex = std::size(nodes);
		nodes.push_back(*iter);
		++iter;
		const ArgListParseResult argsInfo = parseArgList(NodeType::RightSqBr, ErrorType::WrongTupleSyntax);
		if (iter->type != NodeType::RightSqBr) raiseError(ErrorType::WrongTupleSyntax, iter->row, iter->col);
		nodes[nodeIndex].data.number = argsInfo.argsCount;
		return std::size(nodes) - nodeIndex;
	}
		

	case NodeType::String:{
		const size_t nodeIndex = std::size(nodes);
		const size_t strExpansionSize = textBlockCount(iter->data.nameLen);
		Node *const strToken = iter;
		iter += strExpansionSize;
		if (iter->type == NodeType::Literal){
			const size_t litExpansionSize = textBlockCount(iter->data.nameLen);
			nodes.expandBy(litExpansionSize);
			std::copy_n(iter, litExpansionSize, std::begin(nodes)+nodeIndex);
			iter += litExpansionSize;
		}
		nodes.expandBy(strExpansionSize);
		std::copy_n(strToken, strExpansionSize, std::begin(nodes)+nodeIndex);
		return parsePostfix(nodeIndex, typeNodeIndex);
	}

	case NodeType::OpenScope:{
		if (iter->type == NodeType::CloseScope)
			raiseError(ErrorType::EmptyArray, iter->row, iter->col);

		const size_t arrNodeIndex = nodes.size();
		nodes.emplace_back(NodeType::ArrayLiteral, iter->row, iter->col);
		const ArgListParseResult res = parseArgList(NodeType::CloseScope, ErrorType::WrongArraySyntax);
		(nodes)[arrNodeIndex].data.number = res.argsCount;

		if (iter->type == NodeType::Literal){
			const size_t expansionSize = textBlockCount(iter->data.nameLen);
			nodes.expandBy(expansionSize);
			std::move_backward(std::begin(nodes)+arrNodeIndex, std::end(nodes)-expansionSize, std::end(nodes));
			std::copy_n(iter, expansionSize, std::begin(nodes)+arrNodeIndex);
			iter += expansionSize;
		}
		return parsePostfix(arrNodeIndex, typeNodeIndex);
	}

	case NodeType::LeftSqBr:{ ++iter;
		const size_t arrayTypeIndex = std::size(nodes);
		nodes.emplace_back(NodeType::Lambda, iter->row, iter->col);
		nodes.back().data.number = 0;
		
		if (iter->type == NodeType::RightSqBr){
			++iter;
			if (iter->type == NodeType::LeftPar)
				if ((iter+1)->type == NodeType::Name)
					if ((iter+textBlockCount((iter+1)->data.nameLen))->type == NodeType::Colon) goto ParseLambda;
			if (iter->type==NodeType::LogicNot || iter->type==NodeType::BitNot) goto ParseLambda;
			
			nodes[arrayTypeIndex].type = NodeType::SimpleRange;
			parse0(typeNodeIndex+1 ? typeNodeIndex : arrayTypeIndex);
			return std::size(nodes) - arrayTypeIndex;
		}
		{
			bool lambdaFlag = parseVariable(NodeType::Declare);
			if (!lambdaFlag){
				const Node *const exprNodePtr = &nodes[arrayTypeIndex+1];
				parseExpression();
				lambdaFlag |= exprNodePtr->type == NodeType::Name;
				lambdaFlag |= exprNodePtr->type==NodeType::Multiply && (exprNodePtr+1)->type==NodeType::Name;
			}
			if (lambdaFlag){
				nodes[arrayTypeIndex].data.number = 1;
				while (iter->type == NodeType::Comma){
					++iter;
					++nodes[arrayTypeIndex].data.number;
					if (!parseVariable(NodeType::Declare)){
						const Node *const exprNodePtr = &nodes[arrayTypeIndex+1];
						parseExpression();
						if (exprNodePtr->type!=NodeType::Name && (exprNodePtr->type!=NodeType::Multiply || (exprNodePtr+1)->type!=NodeType::Name))
							raiseError(ErrorType::WrongCaptureSyntax, iter->row, iter->col);
					}
				}
				if (iter->type != NodeType::RightSqBr) raiseError(ErrorType::WrongCaptureSyntax, iter->row, iter->col);
				++iter;

			} else{
				nodes[arrayTypeIndex].type = NodeType::ArrayType;
				parse0(typeNodeIndex+1 ? typeNodeIndex : arrayTypeIndex);
				return std::size(nodes) - arrayTypeIndex;
			}
		}
	ParseLambda:
		parseFunction();
		return parsePostfix(arrayTypeIndex, typeNodeIndex);
	}

	case NodeType::Name:
	case NodeType::Literal:{
		const size_t expansionSize = textBlockCount(iter->data.nameLen);
		const size_t nodeIndex = std::size(nodes);

		nodes.expandBy(expansionSize);
		std::move_backward(iter, iter+expansionSize, std::end(nodes));
		iter += expansionSize;

		(nodes)[nodeIndex].type = NodeType::Name;
		return parsePostfix(nodeIndex, typeNodeIndex);
	}

	default:
		raiseError(ErrorType::WrongExprSyntax, iter->row, iter->col);
	}
	return -1;
}


size_t parsePostfix(const size_t lastNodeIndex, const size_t typeNodeIndex) noexcept{
	for (;;)
		switch (iter->type){
		case NodeType::LeftPar:{
			nodes.emplace_back();
			std::move_backward(std::begin(nodes)+lastNodeIndex, std::end(nodes)-1, std::end(nodes));
			const ArgListParseResult res = parseArgList(NodeType::RightPar, ErrorType::MissingPharenthesis);
			(nodes)[lastNodeIndex].type = NodeType::Call;
			(nodes)[lastNodeIndex].data.number = res.argsCount;
		} break;

		case NodeType::OpenScope:{
			if (isStatement(iter+1)) return std::size(nodes) - lastNodeIndex;
			if (typeNodeIndex == (size_t)-1) raiseError(ErrorType::WrongExprSyntax, iter->row, iter->col);
			nodes.emplace_back();
			std::move_backward(std::begin(nodes)+typeNodeIndex, std::end(nodes)-1, std::end(nodes));
			const ArgListParseResult res = parseArgList(NodeType::CloseScope, ErrorType::WrongMemberInitialization);
			(nodes)[typeNodeIndex].type = NodeType::BraceInit;
			(nodes)[typeNodeIndex].data.number = res.argsCount;
		} break;

		case NodeType::LeftSqBr:{
			nodes.emplace_back();
			std::move_backward(std::begin(nodes)+lastNodeIndex, std::end(nodes)-1, std::end(nodes));
			const ArgListParseResult res = parseArgList(NodeType::RightSqBr, ErrorType::WrongSubscriptOperator);
			(nodes)[lastNodeIndex].type = NodeType::Subscript;
			(nodes)[lastNodeIndex].data.number = res.argsCount;
		} break;

		case NodeType::Conversion:{
			const Node token = *iter;
			++iter;
			nodes.emplace_back();
			std::move_backward(std::begin(nodes)+lastNodeIndex, std::end(nodes)-1, std::end(nodes));
			(nodes)[lastNodeIndex] = token;
			parse0();
		} break;

		case NodeType::Dereference:{
			const Node token = *iter;
			++iter;
			nodes.emplace_back();
			std::move_backward(std::begin(nodes)+lastNodeIndex, std::end(nodes)-1, std::end(nodes));
			(nodes)[lastNodeIndex] = token;
		} break;

		case NodeType::Access: ++iter;
			if (iter->type == NodeType::Name){
				const size_t expansionSize = textBlockCount(iter->data.nameLen);
				nodes.expandBy(expansionSize);
				std::move_backward(std::begin(nodes)+lastNodeIndex, std::end(nodes)-expansionSize, std::end(nodes));
				std::copy_n(iter, expansionSize, std::begin(nodes)+lastNodeIndex);
				iter += expansionSize;

				(nodes)[lastNodeIndex].type = NodeType::Access;
			} else if (iter->type == NodeType::LeftPar){
				nodes.emplace_back();
				std::move_backward(std::begin(nodes)+lastNodeIndex, std::end(nodes)-1, std::end(nodes));
				
				(nodes)[lastNodeIndex].type = NodeType::FunctionAddress;
				const ArgListParseResult res = parseArgList(NodeType::RightPar, ErrorType::MissingPharenthesis);
				(nodes)[lastNodeIndex].data.number = res.argsCount;
			} else raiseError(ErrorType::WrongMemberAccess, iter->row, iter->col);
			break;

		default:
			return std::size(nodes) - lastNodeIndex;
		}
}



ArgListParseResult parseArgList(const NodeType escapeToken, const ErrorType errorType) noexcept{
	++iter;

	ArgListParseResult out{0, 0};
	if (iter->type == escapeToken){
		++iter;
		return out;
	}

	out.exprSize = parseExpression();
	++out.argsCount;

	for (;;){
		if (iter->type != NodeType::Comma){
			if (iter->type == escapeToken){
				++iter;
				return out;
			} else
				raiseError(errorType, iter->row, iter->col);
		} ++iter;
			out.exprSize += parseExpression();
			++out.argsCount;
	}
}


} // END OF NAMESPACE //////////////////////////////////