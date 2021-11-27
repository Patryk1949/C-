#include "BaseVector.hpp"
#include "Miscellenious.hpp"

#include "HVector.hpp"
#include "DVector.hpp"

#include "SMatrix.hpp"
#include "HMatrix.hpp"
#include "DMatrix.hpp"
#include "MatrixView.hpp"

namespace sp{ // BEGINING OF NAMESPACE //////////////////////////////////////////////////////////////////



// STATIC MATRIX
template<class T, uint32_t rows, uint32_t columns, bool rowMajor = true>
using SMatrix = priv__::Matrix<priv__::ProtSMatrix<T, rows*rowMajor + columns*!rowMajor, rows*!rowMajor + columns*rowMajor>, T, rowMajor>;

// HYBRYID MATRIX
template<class T, uint32_t capacity, bool rowMajor = true>
using HMatrix = priv__::Matrix<priv__::ProtHMatrix<T, capacity>, T, rowMajor>;

// DYNAMIC MATRIX
template<class T, bool rowMajor = true>
using DMatrix = priv__::Matrix<priv__::ProtDMatrix<T>, T, rowMajor>;

// MATRIX VIEW
template<class T, bool rowMajor = true>
using MatrixView = priv__::Matrix<priv__::ProtMatrixView<T>, T, rowMajor>;


// HYBRYID VECTOR
template<class T, uint32_t capacity>
using HVector = priv__::Vector<priv__::ProtHVector<T, capacity>, T>;

// HYBRYID VECTOR
template<class T>
using DVector = priv__::Vector<priv__::ProtDVector<T>, T>;




}	// END OF NAMESPACE	//////////////////////////////////////////////////////////////////////////////////