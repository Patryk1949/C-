#pragma once

#include "Nodes.hpp"
#include <deque>
#include "sparsepp/spp.h"

namespace SPComp{

struct Namespace;
struct Function;




struct TypeInfo{
	std::vector<Function *> impConversions;
	const Function *implConstructor;
	const Function *implDestructor;
	size_t size;
};



struct Class{
	struct Struct{
		std::vector<const Class *> types;
	};
	struct Union{
		std::vector<const Class *> types;
	};
	struct Enum{
		std::vector<std::string> names;
		uint64_t countStart = 0;
	};
	struct Alias{
		const Class *type;
	};
	struct Basic{
		enum : uint32_t{
			Void,
			B8, B16, B32, B64,
			I8, I16, I32, I64, U8, U16, U32, U64,
			Bool, Char,
			F32, F64,
		} type;
	};
	struct Array{
		const Class *type;
		size_t size;
		bool isConst;
	};
	struct Pointer{
		const Class *type;
		bool isConst;
	};
	struct LValRef{
		const Class *type;
		bool isConst;
	};
	struct RValRef{
		const Class *type;
	};
	struct FuncPointer{
		std::vector<const Class *> argsTypes;
		const Class *returnType;
	};

	std::deque<Class> specs;
	std::variant<Struct, Union, Enum, Alias, Basic, Array, Pointer, LValRef, RValRef, FuncPointer> data;
	std::vector<VarInfo> args;
};






struct Function{
	sp::SmallVector<const Class *, 8> args;
	std::vector<Node> code;
	std::vector<uint32_t> labels;
	std::string name;

	const Class *retvalType;
	bool canBeStatic;
};



struct Namespace{
	spp::sparse_hash_map<std::string,
		std::variant<Class, Function, Namespace>
	> elems;

	std::string name;
	Namespace *parent;
};


} // END OF NAMESPACE //////////////////////////////////