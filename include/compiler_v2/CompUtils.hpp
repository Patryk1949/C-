#pragma once

#include "SPL/Arrays.hpp"


namespace spcomp{

constexpr bool isValidNameChar(const char c){
	return (c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9') || c=='_';
}

constexpr bool isValidNameFirstChar(const char c){
	return (c>='a' && c<='z') || (c>='A' && c<='Z') || c=='_';
}

constexpr bool isNumber(const char c){
	return c>='0' && c<='9';
}

std::string_view getText(const char *const input){
	const char *it = input + 1;
	for (;isValidNameChar(*it); ++it);

	return std::string_view(input, it-input);
}


} // END OF NAMESPACE /////////////////////////