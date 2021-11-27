#pragma once

#include "CompUtils.hpp"


namespace spcomp{


enum class ErrorType : uint32_t{
	Tokenizer = 0, MissingPharenthesis, UnfinishedTernary, WrongFunctionArgument, MissingFunctionName, UndefinedReturnType, MissingFunctionBody,
	WrongExprSyntax, TooManyConditionals, Unexcepted, WrongIfElseSyntax, TooManyArguments, MissingComma, TooManyOperations,
	WrongVariableSyntax, WrongLoopSyntax, WrongGotoSyntax, WrongLabelSyntax, MissingClassName, RepeatingLabel, MissingTerminator,
	WrongCharacterLiteral, WrongStringLiteral, EmptyArray, WrongArraySyntax, WrongMemberAccess, NotAvalible, MissingVariableDeclaration,
	TooManyVariables, WrongDestructorSpecification, TooManyScopes, WrongNumberOfArguments, LabelInStaticIf, LabelNotDefined,
	TooManyVariablesInForLoop, ConstructorInRangeBasedForLoop, DestructorInRangeBasedForLoop, MissingArrow, NestedDefers,
	MissingCondExpression, MissingScope, WrongCompileDirective, ChainedAssignments, WrongCaptureSyntax, WrongMemberInitialization, WrongSubscriptOperator,
	TooLongName, UnfinishedCode, BlantDefinitionWithBraceArguments, DoublyPredefinedVariables, MissingClosingBrace, MissingArguments, WrongFunctionSyntax,
	UnrecognizedGlobal, WrongNamespaceSyntax, WrongTupleSyntax,
};

constexpr const char *const ErrorMsg[] = {
	"wrong token",									// 0
	"missing pharenthesis",
	"unfinished ternary operator",
	"wrong function argument",
	"mising function name",
	"undefined return type in function forward declaration",
	"function definition misses it\'s body",
	"wrong expression syntax",
	"too many nested conditionals (16 is maximum possible number)",
	"this error should be impossible to raise",
	"wrong if/else syntax",									// 10
	"too many function arguments (8 is maximum possible number)",
	"comma \',\' is missing",
	"too many operations inside 'for' operator (8 is maximum possible number)",
	"wrong variable declaration syntax",
	"wrong loop syntax",
	"wrong goto syntax",
	"wrong label syntax",
	"missing name in class definition",
	"label with this name was already defined in this function",
	"terminator symbol \';\' is missing",			// 20
	"wrong character literal grammar",
	"wrong string literal grammar",
	"empty array definition, cannot deduce type",
	"wrong array definition syntax",
	"wrong argument for member access operator",
	"this feature is not avalible yet",
	"missing varaible declaration",
	"too many variables in one declaration, 12 is maximul number",
	"wrong destructor specification in variable declaration",
	"too many nested scopes",				// 30
	"wrong number of arguments",
	"label cannot be define inside static if, use static if on goto instead",
	"this label was not defined in this function",
	"range based for loop can iterate only through one variable",
	"iterating variable in range based cannot have a contructor",
	"iterating variable in range based must have default destructor",
	"missing arrow symbol after specyfiation of function's return type",
	"defered scopes cannot be nested, there's no use for them",
	"missing condition expression in loop definition",
	"switch statement is required to have a scope",	// 40
	"this compile time directive does not exist or is not supported",
	"this is not C you can't have chained assignemts",
	"wrong capture syntax in lambda definition",
	"misiing closing brace in member wise initialization",
	"missing closing square bracket in subscript operator",
	"name is too longer than 38 characters",
	"unfinished code",
	"blant variable declaration cannot have an argument inside curly braces",
	"variables in the do while loop can be predeclared after the \'do\' keyword",
	"missing closing brace",
	"missing arguments for metadata specification",
	"wrong function definition syntax",
	"unrecognized global identifier",
	"wrong namespace syntax",
	"wrong tuple syntax",
};


void raiseError(const ErrorType errType, const uint32_t row, uint16_t col) noexcept{
	printf("parsing error: %s\nat line: %d, column: %d\n",
		ErrorMsg[(uint32_t)errType], row, col
	);
	exit(1488);
};




} // END OF NAMESPACE //////////////////////////////////