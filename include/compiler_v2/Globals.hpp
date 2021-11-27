#pragma once

#include "Classes.hpp"
#include <numeric>

namespace spcomp{
namespace Global{

Namespace global{};
Namespace *currNamespace = &global;

std::vector<Class *> typeIdMap;

void loadGlobalNamespace(){
	sizeof(Statement);
// LOADING CLASSES
	global.types.emplace_back(Class::Basic{Class::Basic::Void}, "Void");
	global.types.emplace_back(Class::Basic{Class::Basic::B8}, "B8");
	global.types.emplace_back(Class::Basic{Class::Basic::B16}, "B16");
	global.types.emplace_back(Class::Basic{Class::Basic::B32}, "B32");
	global.types.emplace_back(Class::Basic{Class::Basic::B64}, "B64");
	global.types.emplace_back(Class::Basic{Class::Basic::I8}, "I8");
	global.types.emplace_back(Class::Basic{Class::Basic::I16}, "I16");
	global.types.emplace_back(Class::Basic{Class::Basic::I32}, "I32");
	global.types.emplace_back(Class::Basic{Class::Basic::I64}, "I64");
	global.types.emplace_back(Class::Basic{Class::Basic::U8}, "U8");
	global.types.emplace_back(Class::Basic{Class::Basic::U16}, "U16");
	global.types.emplace_back(Class::Basic{Class::Basic::U32}, "U32");
	global.types.emplace_back(Class::Basic{Class::Basic::U64}, "U64");
	global.types.emplace_back(Class::Basic{Class::Basic::Bool}, "Bool");
	global.types.emplace_back(Class::Basic{Class::Basic::Char}, "Char");
	global.types.emplace_back(Class::Basic{Class::Basic::F32}, "F32");
	global.types.emplace_back(Class::Basic{Class::Basic::F64}, "F64");
	
	global.types.emplace_back(Class::Alias{&global.types[(size_t)Class::Basic::I32]}, "Int");
	global.types.emplace_back(Class::Alias{&global.types[(size_t)Class::Basic::U32]}, "UInt");
	global.types.emplace_back(Class::Alias{&global.types[(size_t)Class::Basic::B8]}, "Byte");
	global.types.emplace_back(Class::Alias{&global.types[(size_t)Class::Basic::U64]}, "Size_t");
	global.types.emplace_back(Class::Alias{&global.types[(size_t)Class::Basic::F32]}, "Float");
	global.types.emplace_back(Class::Alias{&global.types[(size_t)Class::Basic::F64]}, "Double");

// LOADING FUNCTIONS

// LOADING VARIABLES
	global.variables.emplace_back("Null", nullptr, , );
}


}} // END OF NAMESPACE //////////////////////////////////