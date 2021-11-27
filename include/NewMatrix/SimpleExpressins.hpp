#include "Expr.hpp"
#include <algorithm>

namespace sp{ // BEGINING OF NAMESPACE //////////////////////////////////////////////////////////////////

namespace priv__{

// SIMPLE EXPRRESSIONS FOR MATRICES
template<class Arg1, auto operation>
struct ExprSimpleM{
// FLAGS
	typedef typename Arg1::type type;
	static constexpr uint32_t flags = Arg1::flags & MFlags::RowMajor;
	static constexpr uint32_t lvCount = Arg1::lvCount;

	const inline constexpr type operator ()(const uint32_t r, const uint32_t c) const noexcept{ return operation(arg(r, c)); };
	inline constexpr uint32_t rows() const noexcept{ return arg.rows(); }
	inline constexpr uint32_t cols() const noexcept{ return arg.cols(); }

	const MExpr<Arg1> &arg;
};

template<class Arg1, class ArgOp>
struct ExprSimpleMF{
// FLAGS
	typedef typename Arg1::type type;
	static constexpr uint32_t flags = Arg1::flags & MFlags::RowMajor;
	static constexpr uint32_t lvCount = Arg1::lvCount;

	const inline constexpr type operator ()(const uint32_t r, const uint32_t c) const noexcept{ return operation(arg(r, c)); };
	inline constexpr uint32_t rows() const noexcept{ return arg.rows(); }
	inline constexpr uint32_t cols() const noexcept{ return arg.cols(); }

	const MExpr<Arg1> &arg;
	ArgOp &operation;
};

template<class Arg1, class ArgOp>
struct ExprSimpleMFactive{
// FLAGS
	typedef typename Arg1::type type;
	static constexpr uint32_t flags = Arg1::flags & MFlags::RowMajor | MFlags::MixedMajor;
	static constexpr uint32_t lvCount = Arg1::lvCount;

	const inline constexpr type operator ()(const uint32_t r, const uint32_t c) const noexcept{ return operation(arg(r, c), r, c); };
	inline constexpr uint32_t rows() const noexcept{ return arg.rows(); }
	inline constexpr uint32_t cols() const noexcept{ return arg.cols(); }

	const Arg1 &arg;
	ArgOp &operation;
};

template<class Arg1>
struct ExprSimpleMTranspose{
// FLAGS
	typedef typename Arg1::type type;
	static constexpr uint32_t flags = Arg1::flags & MFlags::RowMajor;
	static constexpr uint32_t lvCount = Arg1::lvCount;

	const inline constexpr type operator ()(const uint32_t r, const uint32_t c) const noexcept{ return arg(c, r); };
	inline constexpr uint32_t rows() const noexcept{ return arg.cols(); }
	inline constexpr uint32_t cols() const noexcept{ return arg.rows(); }

	const Arg1 &arg;
};

template<class Arg1>
struct ExprSimpleMWindow{
// FLAGS
	typedef typename Arg1::type type;
	static constexpr uint32_t flags = Arg1::flags & MFlags::RowMajor;
	static constexpr uint32_t lvCount = Arg1::lvCount;

	const inline constexpr type operator ()(const uint32_t r, const uint32_t c) const noexcept{ return arg(startRow+r, startCol+c); };
	inline constexpr uint32_t rows() const noexcept{ return rws; }
	inline constexpr uint32_t cols() const noexcept{ return cls; }

	const Arg1 &arg;
	const uint32_t startRow;
	const uint32_t startCol;
	const uint32_t rws;
	const uint32_t cls;
};

template<class Arg1, class Arg2, auto operation>
struct ExprSimpleMS{
// FLAGS
	typedef typename Arg1::type type;
	static constexpr uint32_t flags = Arg1::flags & MFlags::RowMajor | (Arg1::flags^Arg2::flags) & MFlags::MixedMajor;
	static constexpr uint32_t lvCount = Arg1::lvCount + Arg2::lvCount;

	const inline constexpr type operator ()(const uint32_t r, const uint32_t c) const noexcept{ return operation(lhs(r, c), rhs); };
	inline constexpr uint32_t rows() const noexcept{ return lhs.rows(); }
	inline constexpr uint32_t cols() const noexcept{ return lhs.cols(); }

	const Arg1 &lhs;
	const Arg2 &rhs;
};

template<class Arg1, class Arg2, auto operation>
struct ExprSimpleMM{
// FLAGS
	typedef typename Arg1::type type;
	static constexpr uint32_t flags = Arg1::flags & MFlags::RowMajor | (Arg1::flags^Arg2::flags) & MFlags::MixedMajor;
	static constexpr uint32_t lvCount = Arg1::lvCount + Arg2::lvCount;

	const inline constexpr type operator ()(const uint32_t r, const uint32_t c) const noexcept{ return operation(lhs(r, c), rhs(r, c)); };
	inline constexpr uint32_t rows() const noexcept{ return lhs.rows(); }
	inline constexpr uint32_t cols() const noexcept{ return lhs.cols(); }

	const Arg1 &lhs;
	const Arg2 &rhs;

};

template<class Arg1, class Arg2, class ArgOp>
struct ExprSimpleMMF{
// FLAGS
	typedef typename Arg1::type type;
	static constexpr uint32_t flags = Arg1::flags & MFlags::RowMajor | (Arg1::flags^Arg2::flags) & MFlags::MixedMajor;
	static constexpr uint32_t lvCount = Arg1::lvCount + Arg2::lvCount;

	const inline constexpr type operator ()(const uint32_t r, const uint32_t c) const noexcept{ return operation(lhs(r, c), rhs(r, c)); };
	inline constexpr uint32_t rows() const noexcept{ return lhs.rows(); }
	inline constexpr uint32_t cols() const noexcept{ return lhs.cols(); }

	const Arg1 &lhs;
	const Arg2 &rhs;
	ArgOp &operation;
};

template<class Arg1, class Arg2, class ArgOp>
struct ExprSimpleMMFactive{
// FLAGS
	typedef typename Arg1::type type;
	static constexpr uint32_t flags = Arg1::flags & MFlags::RowMajor | (Arg1::flags^Arg2::flags) & MFlags::MixedMajor;
	static constexpr uint32_t lvCount = Arg1::lvCount + Arg2::lvCount;

	const inline constexpr type operator ()(const uint32_t r, const uint32_t c) const noexcept{ return operation(lhs(r, c), rhs(r, c), r, c); };
	inline constexpr uint32_t rows() const noexcept{ return lhs.rows(); }
	inline constexpr uint32_t cols() const noexcept{ return lhs.cols(); }

	const Arg1 &lhs;
	const Arg2 &rhs;
	ArgOp &operation;
};


// FUNCTION WRAPPERS

template<class T> inline constexpr T MExprFuncAdd(const T &lhs, const T &rhs){ return lhs + rhs; }
template<class T> inline constexpr T MExprFuncSub(const T &lhs, const T &rhs){ return lhs - rhs; } 
template<class T> inline constexpr T MExprFuncMul(const T &lhs, const T &rhs){ return lhs * rhs; } 
template<class T> inline constexpr T MExprFuncDiv(const T &lhs, const T &rhs){ return lhs / rhs; } 
template<class T> inline constexpr T MExprFuncNegate(const T &arg){ return -arg; }

}	// END OF NAMESPACE PRIV



// BINARY OPEARATIONS RETURNING SIMPLE EXPRESSION
template<class Arg1, class Arg2>
auto elMul(const priv__::MExpr<Arg1> &lhs, const priv__::MExpr<Arg2> &rhs){
	return priv__::MExpr<priv__::ExprSimpleMM<Arg1, Arg2, priv__::MExprFuncMul<typename Arg1::type>>>{lhs, rhs};
}

template<class Arg1, class Arg2>
auto elDiv(const priv__::MExpr<Arg1> &lhs, const priv__::MExpr<Arg2> &rhs){
	return priv__::MExpr<priv__::ExprSimpleMM<Arg1, Arg2, priv__::MExprFuncDiv<typename Arg1::type>>>{lhs, rhs};
}

template<auto operation, class Arg1, class Arg2>
auto apply(const priv__::MExpr<Arg1> &lhs, const priv__::MExpr<Arg2> &rhs){
	return priv__::MExpr<priv__::ExprSimpleMM<Arg1, Arg2, operation>>{lhs, rhs};
}

template<class Arg1, class Arg2, class ArgOp>
auto apply(const priv__::MExpr<Arg1> &lhs, const priv__::MExpr<Arg2> &rhs, ArgOp &&operation){
	return priv__::MExpr<priv__::ExprSimpleMMF<Arg1, Arg2, ArgOp>>{lhs, rhs, operation};
}

template<class Arg1, class Arg2, class ArgOp>
auto applyNU(const priv__::MExpr<Arg1> &lhs, const priv__::MExpr<Arg2> &rhs, ArgOp &&operation){
	return priv__::MExpr<priv__::ExprSimpleMMFactive<Arg1, Arg2, ArgOp>>{lhs, rhs, operation};
}


// UNARY OPEARATIONS RETURNING SIMPLE EXPRESSION
template<class Arg1>
auto trs(const priv__::MExpr<Arg1> &arg){
	return priv__::MExpr<priv__::ExprSimpleMTranspose<Arg1>>{arg};
}

template<class Arg1>
auto subMatrix(const priv__::MExpr<Arg1> &arg, const uint32_t rows, const uint32_t columns){
	return priv__::MExpr<priv__::ExprSimpleMWindow<Arg1>>{arg, 0, 0, rows, columns};
}

template<class Arg1>
auto subMatrix(const priv__::MExpr<Arg1> &arg, const uint32_t startRow, const uint32_t startColumn, const uint32_t rows, const uint32_t columns){
	return priv__::MExpr<priv__::ExprSimpleMWindow<Arg1>>{arg, startRow, startColumn, rows, columns};
}

template<auto operation, class Arg1>
auto apply(const priv__::MExpr<Arg1> &arg){
	return priv__::MExpr<priv__::ExprSimpleM<Arg1, operation>>{arg};
}

template<class Arg1, class ArgOp>
auto apply(const priv__::MExpr<Arg1> &arg, ArgOp &&operation){
	return priv__::MExpr<priv__::ExprSimpleMF<Arg1, ArgOp>>{arg, operation};
}

template<class Arg1, class ArgOp>
auto applyNU(const priv__::MExpr<Arg1> &arg, ArgOp &&operation){
	return priv__::MExpr<priv__::ExprSimpleMFactive<Arg1, ArgOp>>{arg, operation};
}


}	// END OF NAMESPACE	///////////////////////////////////////////////////////////////////

// BINARY OPEARATORS RETURNING SIMPLE EXPRESSION
template<class Arg1, class Arg2>
auto operator +(const sp::priv__::MExpr<Arg1> &lhs, const sp::priv__::MExpr<Arg2> &rhs){
	return sp::priv__::MExpr<sp::priv__::ExprSimpleMM<Arg1, Arg2, sp::priv__::MExprFuncAdd<typename Arg1::type>>>{lhs, rhs};
}

template<class Arg1, class Arg2>
auto operator -(const sp::priv__::MExpr<Arg1> &lhs, const sp::priv__::MExpr<Arg2> &rhs){
	return sp::priv__::MExpr<sp::priv__::ExprSimpleMM<Arg1, Arg2, sp::priv__::MExprFuncSub<typename Arg1::type>>>{lhs, rhs};
}

template<class Arg1>
auto operator *(const sp::priv__::MExpr<Arg1> &lhs, const typename Arg1::type &rhs){
	return sp::priv__::MExpr<sp::priv__::ExprSimpleMS<Arg1, typename Arg1::type, sp::priv__::MExprFuncMul<typename Arg1::type>>>{lhs, rhs};
}

template<class Arg1>
auto operator /(const sp::priv__::MExpr<Arg1> &lhs, const typename Arg1::type &rhs){
	return sp::priv__::MExpr<sp::priv__::ExprSimpleMS<Arg1, typename Arg1::type, sp::priv__::MExprFuncDiv<typename Arg1::type>>>{lhs, rhs};
}


// UNARY OPEARATORS RETURNING SIMPLE EXPRESSION
template<class Arg1, class Arg2>
auto operator -(const sp::priv__::MExpr<Arg1> arg){
	return sp::priv__::MExpr<sp::priv__::ExprSimpleM<Arg1, sp::priv__::MExprFuncNegate<typename Arg1::type>>>{arg};
}