#pragma once

#include "SimpleExpressins.hpp"

#include "BaseStatic.hpp"
#include "BaseHybryid.hpp"
#include "BaseDynamic.hpp"
//#include "BaseShadow.hpp"

namespace sp{ // BEGINING OF NAMESPACE //////////////////////////////////////////////////////////////////


template<class Type, uint32_t rows, uint32_t columns, bool isRowMajor = true>
using SMatrix = priv__::MExpr<priv__::MBaseStatic<Type, isRowMajor, columns&-isRowMajor|rows&-!isRowMajor, rows&-isRowMajor|columns&-!isRowMajor>>;

template<class Type, uint32_t capacity, bool isRowMajor = true>
using HMatrix = priv__::MExpr<priv__::MBaseHybryid<Type, isRowMajor, capacity>>;

template<class Type, bool isRowMajor = true>
using DMatrix = priv__::MExpr<priv__::MBaseDynamic<Type, isRowMajor>>;

// template<class Function, uint32_t rows, uint32_t cols, bool isRowMajor = true>
// using ShMatrix = priv__::MExpr<priv__::MBaseConstShadow<Function, rows, cols, isRowMajor>>;


}	// END OF NAMESPACE	///////////////////////////////////////////////////////////////////