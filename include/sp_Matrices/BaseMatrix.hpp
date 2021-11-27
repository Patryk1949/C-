#pragma once
#include "SPL/Utils.hpp"
#include "SPL/GlobalStorage.hpp"

namespace sp{ // BEGINING OF NAMESPACE //////////////////////////////////////////////////////////////////

// GLOBAL PARAMETERS
#ifndef SP_MATRIX_DEBUG_MODE
	#define SP_MATRIX_DEBUG_MODE false
#endif

sp::GeneralStorage *MatrixTempStorage = nullptr;


namespace priv__{


template<class Prot, class T>
class Vector;



template<class Prot, class T, bool rowMajor>
class Matrix : public Prot{
public:
// GENERAL DATA METHODS
	inline constexpr Matrix() noexcept;

	inline constexpr Matrix(const uint32_t rows, const uint32_t cols) noexcept;

	template<class Mat1>
	Matrix(const Mat1 &A) noexcept;
	template<class Mat1>
	Matrix(Mat1 &A) noexcept;

	template<class Mat1>
	Matrix(Mat1 &&A) noexcept;

	constexpr Matrix(const std::initializer_list<std::initializer_list<T>> &initList) noexcept;

	template<class Mat1>
	Matrix(const Mat1 &A, const uint32_t startRow, const uint32_t startCol, const uint32_t endRow, const uint32_t endCol) noexcept;
	
	
	
	// template<class Mat1>
	// Matrix &operator =(const Mat1 &A) noexcept;
	// template<class Mat1>
	// Matrix &operator =(Mat1 &A) noexcept;

	// template<class Mat1>
	// Matrix &operator =(Mat1 &&A) noexcept;

	template<class Mat1>
	Matrix &assignSubMatrix(const Mat1 &A, const uint32_t startRow, const uint32_t startCol, const uint32_t endRow, const uint32_t endCol) noexcept;


// FLAGS
	typedef T type;

	static constexpr bool isVector = false;
	static constexpr bool isRowMajor = rowMajor;


// SIZE AND DATA FUNCTIONS
	inline constexpr void resize(const uint32_t rows, const uint32_t columns) noexcept;

	inline constexpr const T &operator ()(const uint32_t row, const uint32_t column) const noexcept;

	inline constexpr T &operator ()(const uint32_t row, const uint32_t column) noexcept;


	[[nodiscard]] inline constexpr uint32_t rows() const;

	[[nodiscard]] inline constexpr uint32_t cols() const;

	[[nodiscard]] inline constexpr uint32_t size() const;

	
	[[nodiscard]] inline constexpr uint32_t innLen() const;

	[[nodiscard]] inline constexpr uint32_t outLen() const;


// INITIALIZATION
	void init(T (*func)());
	
	void init(T (*func)(uint32_t, uint32_t));

	template<class Arg>
	void init(T (*func)(const Arg &, uint32_t, uint32_t), const Arg &funcArg);
	
	template<uint32_t maxLineLength = 512>
	bool load(FILE *const input, T (*stringToType)(const char *, char **));
	
	template<uint32_t maxLineLength = 512>
	bool load(FILE *const input, T (*stringToType)(const char *, char **), const uint32_t rowNumber, const uint32_t columnNumber);


// ELEMENTARY OPERATIONS
	Matrix &mulRow(const uint32_t index, const T multiplier);

	Matrix &swapRows(const uint32_t index1, const uint32_t index2);

	Matrix &addRows(const uint32_t destIndex, const uint32_t srcIndex, const T multiplier = (T)1);

	Matrix &mulColumn(const uint32_t index, const T multiplier);

	Matrix &swapColumns(const uint32_t index1, const uint32_t index2);

	Matrix &addColumns(const uint32_t destIndex, const uint32_t srcIndex, const T multiplier = (T)1);


// GENERAL MATRIX OPERATIONS
	template<class Mat1, class Mat2>
	Matrix &add(const Mat1 &A, const Mat2 &B);
	
	template<class Mat1, class Mat2>
	Matrix &sub(const Mat1 &A, const Mat2 &B);
	
	template<class Mat1, class Mat2>
	Matrix &elwiseMul(const Mat1 &A, const Mat2 &B);

	template<class Mat1, class Mat2>
	Matrix &elwiseDiv(const Mat1 &A, const Mat2 &B);

	template<class Mat1, class Mat2>
	Matrix &elwiseApply(const Mat1 &A, const Mat2 &B, T (*func)(T, T));


	template<class Mat1, class Mat2>
	Matrix &mul(const Mat1 &A, const Mat2 &B);

	template<class Mat1, class Mat2>
	Matrix &mulDiag(const Mat1 &A, const Mat2 &B);

	template<class Mat1, class Mat2>
	Matrix &mulBlock(const Mat1 &A, const Mat2 &B);
	

	template<class Mat1>
	Matrix &mul(const Mat1 &A, const T &x);
	
	template<class Mat1>
	Matrix &div(const Mat1 &A, const T &x);
	
	template<class Mat1>
	Matrix &apply(const Mat1 &A, T (*func)(T));
	
	template<class Mat1>
	Matrix &apply(const Mat1 &A, T (*func)(T, uint32_t, uint32_t));

	template<class Mat1, class Arg>
	Matrix &apply(const Mat1 &A, T (*func)(T, uint32_t, uint32_t, const Arg &), const Arg &funcArg);

	
	template<class Mat1, class Mat2>
	Matrix &kronProd(const Mat1 &A, const Mat2 &B);

	template<class Mat1, class Mat2>
	Matrix &kronApply(const Mat1 &A, const Mat2 &B, T (*func)(T, T));


	template<class Mat1>
	Matrix &transpose(const Mat1 &A);
	
	template<class Mat1>
	Matrix &invert(const Mat1 &A);


//	template<class Mat1>
//	Matrix &lu_decompose(const Mat1 &A);

//	template<uint32_t cap1, uint32_t cap2, bool rm2>
//	Matrix &lup_decompose(SVector<uint32_t, cap1> *P, const priv__::Matrix<T, cap2, rm2> &A);


// MATRIX OPERATIONS ON SELF
	template<class Mat1>
	Matrix &add(const Mat1 &A);
	
	template<class Mat1>
	Matrix &subFromSelf(const Mat1 &A);

	template<class Mat1>
	Matrix &subSelfFrom(const Mat1 &A);
	
	template<class Mat1>
	Matrix &elwiseMul(const Mat1 &A);

	template<class Mat1>
	Matrix &elwiseDiv(const Mat1 &A);

	template<class Mat1>
	Matrix &elwiseApply(const Mat1 &A, T (*func)(T, T));
	

	template<class Mat1>
	Matrix &postMul(const Mat1 &A);

	template<class Mat1>
	Matrix &preMul(const Mat1 &A);

	Matrix &square();

	Matrix &psquare();	// Matrix times its transpose


	Matrix &mul(const T &x);
	
	Matrix &div(const T &x);
	
	Matrix &apply(T (*func)(T));
	
	Matrix &apply(T (*func)(T, uint32_t, uint32_t));

	template<class Arg>
	Matrix &apply(T (*func)(T, uint32_t, uint32_t, const Arg &), const Arg &funcArg);



	Matrix &transpose();

	Matrix &invert();

	Matrix &pinvert();

	template<class Prot1>
	Matrix &lupDecompose(priv__::Vector<Prot1, uint32_t> *const permutation);
	Matrix &lupDecompose(uint32_t *const permutation);

	template<class Mat1>
	Matrix &extractLower(Mat1 *A);

	template<class Mat1>
	Matrix &extractUpper(Mat1 *A);


// MATRIX VECTOR OPERATIONS
	template<class Mat1, class Prot2>
	Matrix &add(const Mat1 &A, const Vector<Prot2, T> &B);
	
	template<class Mat1, class Prot2>
	Matrix &sub(const Mat1 &A, const Vector<Prot2, T> &B);
	
	template<class Prot1, class Mat2>
	Matrix &sub(const Vector<Prot1, T> &A, const Mat2 &B);
	
	template<class Mat1, class Prot2>
	Matrix &elwiseMul(const Mat1 &A, const Vector<Prot2, T> &B);

	template<class Mat1, class Prot2>
	Matrix &elwiseDiv(const Mat1 &A, const Vector<Prot2, T> &B);

	template<class Mat1, class Prot2>
	Matrix &elwiseApply(const Mat1 &A, const Vector<Prot2, T> &B, T (*func)(T, T));


	template<class Mat1, class Prot2>
	Matrix &mul(const Mat1 &A, const Vector<Prot2, T> &B);

	template<class Prot1, class Mat2>
	Matrix &mul(const Vector<Prot1, T> &A, const Mat2 &B);



// MATRIX VECTOR OPERATIONS ON SELF
	template<class Prot1>
	Matrix &add(const Vector<Prot1, T> &A);
	
	template<class Prot1>
	Matrix &subFromSelf(const Vector<Prot1, T> &A);
	
	template<class Prot1>
	Matrix &subSelfFrom(const Vector<Prot1, T> &A);
	
	template<class Prot1>
	Matrix &elwiseMul(const Vector<Prot1, T> &A);

	template<class Prot1>
	Matrix &elwiseDiv(const Vector<Prot1, T> &A);

	template<class Prot1>
	Matrix &elwiseApply(const Vector<Prot1, T> &A, T (*func)(T, T));


	template<class Prot1>
	Matrix &postMul(const Vector<Prot1, T> &A);

	template<class Prot1>
	Matrix &preMul(const Vector<Prot1, T> &A);
};



}	// END OF NAMESPACE PRIV







template<class Prot, class T>
inline constexpr priv__::Matrix<Prot, T, false> &tr(priv__::Matrix<Prot, T, true> &A);

template<class Prot, class T>
inline constexpr priv__::Matrix<Prot, T, true> &tr(priv__::Matrix<Prot, T, false> &A);

template<class Prot, class T>
inline constexpr const priv__::Matrix<Prot, T, false> &tr(const priv__::Matrix<Prot, T, true> &A);

template<class Prot, class T>
inline constexpr const priv__::Matrix<Prot, T, true> &tr(const priv__::Matrix<Prot, T, false> &A);



template<class Prot, class T, bool rm1>
[[nodiscard]] T determinant(const priv__::Matrix<Prot, T, rm1> &A);

template<class Prot, class T, bool rm1>
[[nodiscard]] T minor(const priv__::Matrix<Prot, T, rm1> &A, const uint32_t row, const uint32_t column);

template<class Prot, class T, bool rm1>
[[nodiscard]] inline T cofactor(const priv__::Matrix<Prot, T, rm1> &A, const uint32_t row, const uint32_t column);

template<class Prot, class T, bool rm1>
[[nodiscard]] uint32_t rank(const priv__::Matrix<Prot, T, rm1> &A);




template<class T, class Prot1, class Prot2, bool rm1, bool rm2>
[[nodiscard]] bool operator ==(const priv__::Matrix<T, Prot1, rm1> &A, const priv__::Matrix<T, Prot2, rm2> &B);



template<class Mat1>
void printM(FILE *const output, const Mat1 &A);

template<class Mat1>
void printBM(FILE *const output, const Mat1 &A);

template<class Mat1>
void printMM(FILE *const output, const Mat1 &A);








namespace priv__{

#define TPL template<class Prot, class T, bool rowMajor>
#define CLS priv__::Matrix<Prot, T, rowMajor>


TPL inline constexpr CLS::Matrix() noexcept : Prot{} {}

TPL inline constexpr CLS::Matrix(const uint32_t rows, const uint32_t columns) noexcept : Prot{} {
	this->resize(rows, columns);
}

TPL template<class Mat1>
CLS::Matrix(const Mat1 &A) noexcept{
	this->resize(A.rows(), A.cols());
	if constexpr (this->isView){
		this->lookAt(A);	
	} else{
		if constexpr (isRowMajor == A.isRowMajor){
			memcpy(this->data, A.data, this->size()*sizeof(T));
		} else{
			for (uint32_t i=0, j; i<this->rows(); ++i)
				for (j=0; j<this->cols(); ++j)
					(*this)(i, j) = A(i, j);
		}
	}
}
TPL template<class Mat1>
CLS::Matrix(Mat1 &A) noexcept{
	this->resize(A.rows(), A.cols());
	if constexpr (this->isView){
		this->lookAt(A);
	} else{
		if constexpr (isRowMajor == A.isRowMajor){
			memcpy(this->data, A.data, this->size()*sizeof(T));
		} else{
			for (uint32_t i=0, j; i<this->rows(); ++i)
				for (j=0; j<this->cols(); ++j)
					(*this)(i, j) = A(i, j);
		}
	}
}

TPL template<class Mat1>
CLS::Matrix(Mat1 &&A) noexcept{
	static_assert(isRowMajor == A.isRowMajor, "Only matrices with the same storage order can be moved.\n");
	static_assert(!A.isView, "Matrix View can't be moved.\n");
	
	this->swapData(A);
}

TPL constexpr CLS::Matrix(const std::initializer_list<std::initializer_list<T>> &initList) noexcept : Prot{} {
	this->resize(initList.size(), initList.begin()->size());
	for (uint32_t i=0, j; i<this->rows(); ++i)
		for (j=0; j<this->cols(); ++j)
			(*this)(i, j) = initList.begin()[i].begin()[j];
}

TPL template<class Mat1>
CLS::Matrix(const Mat1 &A, const uint32_t startRow, const uint32_t startCol, const uint32_t endRow, const uint32_t endCol) noexcept{
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (endRow>=A.rows() || endCol>=A.cols()){
			fprintf(stderr, "Linear algebra error:   Submatrix exceeds dimensions of orginal matrix.\n");
			exit(2137);
		}
	}

	this->resize(endRow-startRow, endCol-startCol);
	if constexpr (this->isView){
		this->lookAt(&A(startRow, startCol));	
	} else{
		for (uint32_t i=0, j; i<this->rows(); ++i)
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) = A(i+startRow, j+startCol);
	}
}

// TPL template<class Mat1>
// CLS &CLS::operator =(const Mat1 &A) noexcept{
// 	this->resize(A.rows(), A.cols());
// 	if constexpr (this->isView){
// 		this->lookAt(A);
// 	} else{
// 		if constexpr (isRowMajor == A.isRowMajor){
// 			memcpy(this->data, A.data, this->size()*sizeof(T));
// 		} else{
// 			for (uint32_t i=0, j; i<this->rows(); ++i)
// 				for (j=0; j<this->cols(); ++j)
// 					(*this)(i, j) = A(i, j);
// 		}
// 	}
// 	return *this;
// }
// TPL template<class Mat1>
// CLS &CLS::operator =(Mat1 &A) noexcept{
// 	this->resize(A.rows(), A.cols());
// 	if constexpr (this->isView){
// 		this->lookAt(A);
// 	} else{
// 		if constexpr (isRowMajor == A.isRowMajor){
// 			memcpy(this->data, A.data, this->size()*sizeof(T));
// 		} else{
// 			for (uint32_t i=0, j; i<this->rows(); ++i)
// 				for (j=0; j<this->cols(); ++j)
// 					(*this)(i, j) = A(i, j);
// 		}
// 	}
// 	return *this;
// }

// TPL template<class Mat1>
// CLS &CLS::operator =(Mat1 &&A) noexcept{
// 	static_assert(isRowMajor == A.isRowMajor, "Only matrices with the same storage order can be moved.\n");
// 	static_assert(!A.isView(), "Matrix View can't be moved.\n");
	
// 	this->swapData(A);
// 	return *this;
// }

TPL template<class Mat1>
CLS &CLS::assignSubMatrix(const Mat1 &A, const uint32_t startRow, const uint32_t startCol, const uint32_t endRow, const uint32_t endCol) noexcept{
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (endRow>=A.rows() || endCol>=A.cols()){
			fprintf(stderr, "Linear algebra error:   Submatrix exceeds dimensions of orginal matrix.\n");
			exit(2137);
		}
	}

	this->resize(endRow-startRow, endCol-startCol);
	if constexpr (this->isView){
		this->lookAt(&A(startRow, startCol));	
	} else{
		for (uint32_t i=0, j; i<this->rows(); ++i)
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) = A(i+startRow, j+startCol);
	}
	return *this;
}



TPL inline constexpr void CLS::resize(const uint32_t rows, const uint32_t columns) noexcept{
	if constexpr (isRowMajor)
		this->setSize(rows, columns);
	else
		this->setSize(columns, rows);
}

TPL inline constexpr const T &CLS::operator ()(const uint32_t row, const uint32_t column) const noexcept{
	if constexpr (isRowMajor)
		return this->data[row*this->innLen() + column];
	else
		return this->data[column*this->innLen() + row];
}

TPL inline constexpr T &CLS::operator ()(const uint32_t row, const uint32_t column) noexcept{
	if (row >= this->rows() || column >= this->cols())
		printf("out of range access\n");
	if constexpr (isRowMajor)
		return this->data[row*this->innLen() + column];
	else
		return this->data[column*this->innLen() + row];
}




TPL inline constexpr uint32_t CLS::rows() const{
	if constexpr (isRowMajor)
		return this->outLen();
	else
		return this->innLen();
}

TPL inline constexpr uint32_t CLS::cols() const{
	if constexpr (isRowMajor)
		return this->innLen();
	else
		return this->outLen();
}

TPL inline constexpr uint32_t CLS::size() const{
	return this->outLen() * this->innLen();
}


TPL inline constexpr uint32_t CLS::innLen() const{
	return this->innL;
}

TPL inline constexpr uint32_t CLS::outLen() const{
	return this->outL;
}



TPL void CLS::init(T (*func)()){
	const T *const end = this->data + this->size();
	for (T *I=this->data; I!=end; ++I)
		*I = func();
}

TPL void CLS::init(T (*func)(uint32_t, uint32_t)){
	for (uint32_t i=0, j; i<this->rows(); ++i)
		for (j=0; j<this->cols(); ++j)
				(*this)(i, j) = func(i, j);
}

TPL template<class Arg>
void CLS::init(T (*func)(const Arg &, uint32_t, uint32_t), const Arg &funcArg){
	for (uint32_t i=0, j; i<this->rows(); ++i)
		for (j=0; j<this->cols(); ++j)
				(*this)(i, j) = func(funcArg, i, j);
}

TPL template<uint32_t maxLineLength>
bool CLS::load(FILE *const input, T (*stringToType)(const char *, char **)){
	char line[maxLineLength];
	char *linePointer = line;
	std::vector<T> buffer;

	fgets(line, maxLineLength, input);
	if(*line=='\n' || feof(input))
		return false;
	
	uint32_t tempCols = 1;
	for (;; ++tempCols){
		buffer.push_back(stringToType(linePointer, &linePointer));
		if(*linePointer=='\n')
			break;
	}

	uint32_t tempRows = 1;
	for (;; ++tempRows){
		fgets(line, maxLineLength, input);
		linePointer = line;
		if(*linePointer=='\n' || feof(input))
			break;

		buffer.push_back(stringToType(linePointer, &linePointer));
		
		for(uint32_t j=1; j<tempCols; j++){
			if(*linePointer=='\n' || feof(input)){
				this->setSize(0, 0);
				return false;
			}
			buffer.push_back(stringToType(linePointer, &linePointer));
		}
	}
	
	this->resize(tempRows, tempCols);

	if constexpr (isRowMajor){
		memcpy(this->data, buffer.data(), tempRows*tempCols);
	} else{
		for (uint32_t i=0; i<tempRows; ++i)
			for (uint32_t j=0; j<tempCols; ++j)
				(*this)(i, j) = buffer[i*tempCols+j];
	}

	return true;
}

TPL template<uint32_t maxLineLength>
bool CLS::load(FILE *const input, T (*stringToType)(const char *, char **), const uint32_t rows, const uint32_t columns){
	char line[maxLineLength];
	char *linePointer = line;
	this->resize(rows, columns);
	for (uint32_t i=0, j; i<this->rows(); ++i){
		fgets(line, maxLineLength, input);
		for (j=0; j<this->cols(); ++j){
			if(*linePointer=='\n' || feof(input))
				return false;
			(*this)(i, j) = stringToType(linePointer, &linePointer);
		}
	}
	return true;
}


// ELEMENTARY OPERATIONS
TPL CLS &CLS::mulRow(const uint32_t index, const T multiplier){
	if constexpr (rowMajor){
		T *I = this->data + index*this->innLen();
		const T *end = I + this->innLen();
		for (; I!=end; ++I)
			*I *= multiplier;
	} else{
		T *I = this->data + index;
		const T *end = I + this->size();
		for (; I!=end; I+=innLen())
			*I *= multiplier;
	}
	return *this;
}

TPL CLS &CLS::swapRows(const uint32_t index1, const uint32_t index2){
	if constexpr (rowMajor){
		T *I = this->data + index1*this->innLen();
		T *J = this->data + index2*this->innLen();
		const T *end = I + this->innLen();
		for (; I!=end; ++I, ++J)
			sp::swap(I, J);
	} else{
		T *I = this->data + index1;
		T *J = this->data + index2;
		const T *end = I + this->size();
		for (; I!=end; I+=innLen(), J+=innLen())
			sp::swap(I, J);
	}
	return *this;
}

TPL CLS &CLS::addRows(const uint32_t destIndex, const uint32_t srcIndex, const T multiplier){
	if constexpr (rowMajor){
		T *I = this->data + destIndex*this->innLen();
		T *J = this->data + srcIndex*this->innLen();
		const T *end = I + this->innLen();
		for (; I!=end; ++I, ++J)
			*I = *J * multiplier;
	} else{
		T *I = this->data + destIndex;
		T *J = this->data + srcIndex;
		const T *end = I + this->size();
		for (; I!=end; I+=innLen(), J+=innLen())
			*I = *J * multiplier;
	}
	return *this;
}

TPL CLS &CLS::mulColumn(const uint32_t index, const T multiplier){
	if constexpr (rowMajor){
		T *I = this->data + index;
		const T *end = I + this->size();
		for (; I!=end; I+=innLen())
			*I *= multiplier;
	} else{
		T *I = this->data + index*this->innLen();
		const T *end = I + this->innLen();
		for (; I!=end; ++I)
			*I *= multiplier;
	}
	return *this;
}

TPL CLS &CLS::swapColumns(const uint32_t index1, const uint32_t index2){
	if constexpr (rowMajor){
		T *I = this->data + index1;
		T *J = this->data + index2;
		const T *end = I + this->size();
		for (; I!=end; I+=innLen(), J+=innLen())
			sp::swap(I, J);
	} else{
		T *I = this->data + index1*this->innLen();
		T *J = this->data + index2*this->innLen();
		const T *end = I + this->innLen();
		for (; I!=end; ++I, ++J)
			sp::swap(I, J);
	}
	return *this;
}

TPL CLS &CLS::addColumns(const uint32_t destIndex, const uint32_t srcIndex, const T multiplier){
	if constexpr (rowMajor){
		T *I = this->data + destIndex;
		T *J = this->data + srcIndex;
		const T *end = I + this->size();
		for (; I!=end; I+=innLen(), J+=innLen())
			*I = *J * multiplier;
	} else{
		T *I = this->data + destIndex*this->innLen();
		T *J = this->data + srcIndex*this->innLen();
		const T *end = I + this->innLen();
		for (; I!=end; ++I, ++J)
			*I = *J * multiplier;
	}
	return *this;
}
	

// STANDARD MATRIX OPERATIONS
TPL template<class Mat1, class Mat2>
CLS &CLS::add(const Mat1 &A, const Mat2 &B){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (A.rows()!=B.rows() || A.cols()!=B.cols()){
			fprintf(stderr, "Linear algebra error:   Added matrices must have the same dimensions.\n");
			exit(2137);
		}

		if ((this->data==A.data && isRowMajor!=A.isRowMajor) || (this->data==B.data && isRowMajor!=B.isRowMajor)){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for the result of addition at the same time.\n");
			exit(2137);
		}
	}

	this->resize(A.rows(), A.cols());
/*	if constexpr (isRowMajor == A.isRowMajor && isRowMajor == B.isRowMajor){
		const T *const end = this->data + this->size();
		const T *J=A.data, *K=B.data;
		for (T *I=this->data; I!=end; ++I, ++J, ++K)
			*I = *J + *K;

	} else*/{
		for (uint32_t i=0, j; i<this->rows(); ++i)
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) = A(i, j) + B(i, j);
	}
	return *this;
}

TPL template<class Mat1, class Mat2>
CLS &CLS::sub(const Mat1 &A, const Mat2 &B){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (A.rows()!=B.rows() || A.cols()!=B.cols()){
			fprintf(stderr, "Linear algebra error:   Subtracted matrices must have the same dimensions.\n");
			exit(2137);
		}

		if ((this->data==A.data && isRowMajor!=A.isRowMajor) || (this->data==B.data && isRowMajor!=B.isRowMajor)){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for the result of subtraction at the same time.\n");
			exit(2137);
		}
	}

	this->resize(A.rows(), A.cols());
	if constexpr (isRowMajor == A.isRowMajor && isRowMajor == B.isRowMajor){
		const T *const end = this->data + this->size();
		const T *J=A.data, *K=B.data;
		for (T *I=this->data; I!=end; ++I, ++J, ++K)
			*I = *J - *K;

	} else{
		for (uint32_t i=0, j; i<this->rows(); ++i)
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) = A(i, j) - B(i, j);
	}
	return *this;
}

TPL template<class Mat1, class Mat2>
CLS &CLS::elwiseMul(const Mat1 &A, const Mat2 &B){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (A.rows()!=B.rows() || A.cols()!=B.cols()){
			fprintf(stderr, "Linear algebra error:   Elementwise multiplied matrices must have the same dimensions.\n");
			exit(2137);
		}

		if ((this->data==A.data && isRowMajor!=A.isRowMajor) || (this->data==B.data && isRowMajor!=B.isRowMajor)){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for the result of elementwise multiplication at the same time.\n");
			exit(2137);
		}
	}

	this->resize(A.rows(), A.cols());
	if constexpr (isRowMajor == A.isRowMajor && isRowMajor == B.isRowMajor){
		const T *const end = this->data + this->size();
		const T *J=A.data, *K=B.data;
		for (T *I=this->data; I!=end; ++I, ++J, ++K)
			*I = *J * *K;

	} else{
		for (uint32_t i=0, j; i<this->rows(); ++i)
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) = A(i, j) * B(i, j);
	}
	return *this;
}

TPL template<class Mat1, class Mat2>
CLS &CLS::elwiseDiv(const Mat1 &A, const Mat2 &B){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (A.rows()!=B.rows() || A.cols()!=B.cols()){
			fprintf(stderr, "Linear algebra error:   Elementwise divided matrices must have the same dimensions.\n");
			exit(2137);
		}

		if ((this->data==A.data && isRowMajor!=A.isRowMajor) || (this->data==B.data && isRowMajor!=B.isRowMajor)){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for the result of elementwise division at the same time.\n");
			exit(2137);
		}
	}

	this->resize(A.rows(), A.cols());
	if constexpr (isRowMajor == A.isRowMajor && isRowMajor == B.isRowMajor){
		const T *const end = this->data + this->size();
		const T *J=A.data, *K=B.data;
		for (T *I=this->data; I!=end; ++I, ++J, ++K)
			*I = *J / *K;

	} else{
		for (uint32_t i=0, j; i<this->rows(); ++i)
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) = A(i, j) / B(i, j);
	}
	return *this;
}

TPL template<class Mat1, class Mat2>
CLS &CLS::elwiseApply(const Mat1 &A, const Mat2 &B, T (*func)(T, T)){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (A.rows()!=B.rows() || A.cols()!=B.cols()){
			fprintf(stderr, "Linear algebra error:   Matrices which are arguments for elementwise applied function must have the same dimensions.\n");
			exit(2137);
		}

		if ((this->data==A.data && isRowMajor!=A.isRowMajor) || (this->data==B.data && isRowMajor!=B.isRowMajor)){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for the result of"
				"appying the function elementwise at the same time.\n"
			);
			exit(2137);
		}
	}

	this->resize(A.rows(), A.cols());
	if constexpr (isRowMajor == A.isRowMajor && isRowMajor == B.isRowMajor){
		const T *const end = this->data + this->size();
		const T *J=A.data, *K=B.data;
		for (T *I=this->data; I!=end; ++I, ++J, ++K)
			*I = func(*J, *K);

	} else{
		for (uint32_t i=0, j; i<this->rows(); ++i)
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) = func(A(i, j), B(i, j));
	}
	return *this;
}


TPL template<class Mat1, class Mat2>
CLS &CLS::mul(const Mat1 &A, const Mat2 &B){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (A.cols() != B.rows()){
			fprintf(stderr, "Linear algebra error:   Multiplied matrices have wrong dimensions.\n");
			exit(2137);
		}

		if (this->data==A.data || this->data==B.data){
			fprintf(stderr, "Linear algebra error:   Matrix can't be multiplied with itself this way.\nTry preMul, postMul or square.\n");
			exit(2137);
		}
	}

	this->resize(A.rows(), B.cols());
	const uint32_t imL = A.cols();

	T sum;
	for(uint32_t i=0, j, k; i<this->outLen(); ++i)
		for(j=0; j<this->innLen(); ++j){
			sum = (T)0;
			for(k=0; k<imL; k += 4){
				if constexpr(isRowMajor){
					sum += A(i, k) * B(k, j);
					sum += A(i, k+1) * B(k+1, j);
					sum += A(i, k+2) * B(k+2, j);
					sum += A(i, k+3) * B(k+3, j);
					sum += A(i, k+4) * B(k+4, j);
					sum += A(i, k+5) * B(k+5, j);
					sum += A(i, k+6) * B(k+6, j);
					sum += A(i, k+7) * B(k+7, j);
				} else
					sum += A(j, k) * B(k, i);
			}
			this->data[i*this->innLen()+j] = sum;
		}
	return *this;
}

TPL template<class Mat1, class Mat2>
CLS &CLS::mulDiag(const Mat1 &A, const Mat2 &B){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (A.cols() != B.rows()){
			fprintf(stderr, "Linear algebra error:   Multiplied matrices have wrong dimensions.\n");
			exit(2137);
		}

		if (this->data==A.data || this->data==B.data){
			fprintf(stderr, "Linear algebra error:   Matrix can't be multiplied with itself this way.\nTry preMul, postMul or square.\n");
			exit(2137);
		}
	}

	this->resize(A.rows(), B.cols());
	const uint32_t imL = A.cols() >> 2;

	const uint32_t totalSize = this->size();
	const T *const end = this->data + this->size();
	const T *const endA = A.data + A.size();
	const T *const endB = B.data + B.size();

	T sum;
	T *I = this->data;
	const uint32_t step = this->cols() + 1;
	const T *itA = A.data, *itB = B.data;
	uint32_t rctr = 0;
	for(T *I=this->data; I!=end; I+=step){
		I -= totalSize * (I>=end);

		sum = (T)0;
		for (uint32_t j=0; j<imL; ++j){
			sum += itA[0] * itB[0];
			sum += itA[1] * itB[1];
			sum += itA[2] * itB[2];
			sum += itA[3] * itB[3];
			itA += 4;
			itB += 4;
		}
		itA = itA==endA ? A.data : itA;
		itB = itB==endB ? B.data : itB;

		*I = sum;
		if (++rctr == A.rows()){
			itA += A.cols();
			rctr = 0;
		}
	}

	return *this;
}

TPL template<class Mat1, class Mat2>
CLS &CLS::mulBlock(const Mat1 &A, const Mat2 &B){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (A.cols() != B.rows()){
			fprintf(stderr, "Linear algebra error:   Multiplied matrices have wrong dimensions.\n");
			exit(2137);
		}

		if (this->data==A.data || this->data==B.data){
			fprintf(stderr, "Linear algebra error:   Matrix can't be multiplied with itself this way.\nTry preMul, postMul or square.\n");
			exit(2137);
		}
	}

	this->resize(A.rows(), B.cols());
	const uint32_t imL = A.cols();
	
	return *this;
}

TPL template<class Mat1>
CLS &CLS::mul(const Mat1 &A, const T &x){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->data==A.data && isRowMajor!=A.isRowMajor){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for the result of scalar multiplication at the same time.\n");
			exit(2137);
		}
	}

	this->resize(A.rows(), A.cols());
	const T *const end = this->data + this->size();
	for (T *I=this->data, *J=A.data; I!=end; ++I, ++J)
		*I =  *J * x;
	return *this;
}

TPL template<class Mat1>
CLS &CLS::div(const Mat1 &A, const T &x){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->data==A.data && isRowMajor!=A.isRowMajor){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for the result of scalar division at the same time.\n");
			exit(2137);
		}
	}
	
	this->resize(A.rows(), A.cols());
	const T *const end = this->data + this->size();
	for (T *I=this->data, *J=A.data; I!=end; ++I, ++J)
		*I =  *J / x;
	return *this;
}

TPL template<class Mat1>
CLS &CLS::apply(const Mat1 &A, T (*func)(T)){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->data==A.data && isRowMajor!=A.isRowMajor){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for the result of applying a function at the same time.\n");
			exit(2137);
		}
	}
	
	this->resize(A.rows(), A.cols());
	for (uint32_t i=0, j; i<this->rows(); ++i)
		for (j=0; j<this->cols(); ++j)
			(*this)(i, j) = func(A(i, j));
	return *this;
}

TPL template<class Mat1>
CLS &CLS::apply(const Mat1 &A, T (*func)(T, uint32_t, uint32_t)){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->data==A.data && isRowMajor!=A.isRowMajor){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for the result of applying a function at the same time.\n");
			exit(2137);
		}
	}
	
	this->resize(A.rows(), A.cols());
	for (uint32_t i=0, j; i<this->rows(); ++i)
		for (j=0; j<this->cols(); ++j)
			(*this)(i, j) = func(A(i, j), i, j);
	return *this;
}

TPL template<class Mat1, class Arg>
CLS &CLS::apply(const Mat1 &A, T (*func)(T, uint32_t, uint32_t, const Arg &), const Arg &funcArg){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->data==A.data && isRowMajor!=A.isRowMajor){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for the result of applying a function at the same time.\n");
			exit(2137);
		}
	}
	
	this->resize(A.rows(), A.cols());
	for (uint32_t i=0, j; i<this->rows(); ++i)
		for (j=0; j<this->cols(); ++j)
			(*this)(i, j) = func(A(i, j), i, j, funcArg);
	return *this;
}

TPL template<class Mat1, class Mat2>
CLS &CLS::kronProd(const Mat1 &A, const Mat2 &B){
	this->resize(A.rows()*B.rows(), A.cols()*B.cols());
	for (uint32_t i=0; i<A.rows(); ++i)
		for (uint32_t j=0; j<A.cols(); ++j){
			const T componentA = A(i, j);
			for (uint32_t k=0; k<B.rows(); ++k)
				for (uint32_t l=0; l<B.cols(); ++l)
					(*this)(i*B.rows()+k, j*B.cols()+l) = componentA * B(k, l);
		}
	return *this;
}

TPL template<class Mat1, class Mat2>
CLS &CLS::kronApply(const Mat1 &A, const Mat2 &B, T (*func)(T, T)){
	this->resize(A.rows()*B.rows(), A.cols()*B.cols());
	for (uint32_t i=0; i<A.rows(); ++i)
		for (uint32_t j=0; j<A.cols(); ++j){
			const T componentA = A(i, j);
			for (uint32_t k=0; k<B.rows(); ++k)
				for (uint32_t l=0; l<B.cols(); ++l)
					(*this)(i*B.rows()+k, j*B.cols()+l) = func(componentA, B(k, l));
		}
	return *this;
}


TPL template<class Mat1>
CLS &CLS::transpose(const Mat1 &A){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->data==A.data){
			fprintf(stderr, "Linear algebra error:   Matrix can't be argument and container for the result of"
				" transposition at the same time.\nUse transpose() instead."
			);
			exit(2137);
		}
	}
	
	this->resize(A.cols(), A.rows());
	if constexpr (isRowMajor == A.isRowMajor){
		for (uint32_t i=0, j; i<this->rows(); ++i)
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) = A(j, i);
	} else{
		const T *const end = this->data + this->size();
		for (T *I=this->data, J=A.data; I!=end; ++I, ++J)
			*I = *J;
	}
	return *this;
}


TPL template<class Mat1>
CLS &CLS::invert(const Mat1 &A){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (A.rows() != A.cols()){
			fprintf(stderr, "Linear algebra error:   Only square matrix can be inverted.\nMaybe try pInvert.\n");
			exit(2137);
		}
	}

	this->resize(A.rows(), A.rows());
	const T det = determinant(A);
	for (uint32_t i=0, j; i<this->rows(); ++i)
		for (j=0; j<this->rows(); ++j)
			(*this)(j, i) = cofactor(A, i, j)/det;
	return *this;
}
/*
TPL template<class Mat1>
CLS &CLS::invert(const Mat1 &A){
	const uint32_t len = A.rows();
	this->resize(len, len);
	
	int32_t sign = 1;
	T factor1, factor2;
	for (uint32_t i=0, j, k; i<len-1; ++i){
		k = i;
		for (j=i+1; j<len; ++j)	// find row with max value
			k = abs(MatrixTempStorage->at<T>(j*len+i))>abs(MatrixTempStorage->[k*len+i]) ? j : k;
		if (k != i){
			for (j=i; j<len; ++j)	// exchange top row with row with max value
				sp::swap(&MatrixTempStorage->at<T>(i*len+j), &MatrixTempStorage->at<T>(k*len+j));
			sign ^= 0xfffffffe;
		}
		factor1 = MatrixTempStorage->at<T>(i*(len+1));
		for (j=i+1; j<len; ++j){
			factor2 = MatrixTempStorage->at<T>(j*len+i) / factor1;
			for (k=i+1; k<len; ++k)
				MatrixTempStorage->at<T>(j*len+k) -= MatrixTempStorage->at<T>(i*len+k)*factor2;
		}
	}
	factor1 = *MatrixTempStorage-> * (T)sign;
	for (uint32_t i=1; i<len; ++i)
		factor1 *= MatrixTempStorage->at<T>(i*(len+1));
	
	free(MatrixTempStorage->);
	return *this;
}*/

/*
TPL template<uint32_t cap1, bool rm1>
CLS &CLS::lu_decompose(const ProtHMatrix<T, cap1, rm1> &A){
	if constexpr (tr){

	} else{
		rows = cols = A.rows;
		memcpy(data, A.data, rows*rows);

		T factor1, factor2;
		for (uint32_t i=0, j, k; i<rows; ++i){
			factor1 = A.data[i*(rows+1)];
			for (j=i+1; j<rows; ++j){
				factor2 = A.data[j*rows+i] / factor1;
				data[j*rows+i] = factor2;
				for (k=i+1; k<rows; ++k)
					data[j*rows+k] -= data[i*rows+k]*factor2;
			}
		}
	return *this;
}

TPL template<uint32_t cap1, uint32_t cap2, bool rm2>
CLS &CLS::lup_decompose(SVector<uint32_t, cap1> *P, const ProtHMatrix<T, cap2, rm2> &A){
	return *this;
}*/


// MATRIX OPERATIONS ON SELF

TPL template<class Mat1>
CLS &CLS::add(const Mat1 &A){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->rows()!=A.rows() || this->cols()!=A.cols()){
			fprintf(stderr, "Linear algebra error:   Added matrices must have the same dimensions.\n");
			exit(2137);
		}

		if (this->data==A.data && isRowMajor!=A.isRowMajor){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for the result of addition at the same time.\n");
			exit(2137);
		}
	}

	if constexpr (isRowMajor == A.isRowMajor){
		const T *const end = this->data + this->size();
		const T *J=A.data;
		for (T *I=this->data; I!=end; ++I, ++J)
			*I += *J;

	} else{
		for (uint32_t i=0, j; i<this->rows(); ++i)
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) += A(i, j);
	}
	return *this;
}

TPL template<class Mat1>
CLS &CLS::subFromSelf(const Mat1 &A){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->rows()!=A.rows() || this->cols()!=A.cols()){
			fprintf(stderr, "Linear algebra error:   Subtracted matrices must have the same dimensions.\n");
			exit(2137);
		}

		if (this->data==A.data && isRowMajor!=A.isRowMajor){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for the result of subtraction at the same time.\n");
			exit(2137);
		}
	}

	if constexpr (isRowMajor == A.isRowMajor){
		const T *const end = this->data + this->size();
		const T *J=A.data;
		for (T *I=this->data; I!=end; ++I, ++J)
			*I -= *J;

	} else{
		for (uint32_t i=0, j; i<this->rows(); ++i)
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) -= A(i, j);
	}
	return *this;
}

TPL template<class Mat1>
CLS &CLS::subSelfFrom(const Mat1 &A){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->rows()!=A.rows() || this->cols()!=A.cols()){
			fprintf(stderr, "Linear algebra error:   Subtracted matrices must have the same dimensions.\n");
			exit(2137);
		}

		if (this->data==A.data && isRowMajor!=A.isRowMajor){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for the result of subtraction at the same time.\n");
			exit(2137);
		}
	}

	if constexpr (isRowMajor == A.isRowMajor){
		const T *const end = this->data + this->size();
		const T *J=A.data;
		for (T *I=this->data; I!=end; ++I, ++J)
			*I = *J - *I;

	} else{
		for (uint32_t i=0, j; i<this->rows(); ++i)
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) = A(i, j) - (*this)(i, j);
	}
	return *this;
}

TPL template<class Mat1>
CLS &CLS::elwiseMul(const Mat1 &A){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->rows()!=A.rows() || this->cols()!=A.cols()){
			fprintf(stderr, "Linear algebra error:   Elementwise multiplied matrices must have the same dimensions.\n");
			exit(2137);
		}

		if (this->data==A.data && isRowMajor!=A.isRowMajor){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for"
				" the result of elementwise multiplication at the same time.\n"
			);
			exit(2137);
		}
	}

	if constexpr (isRowMajor == A.isRowMajor){
		const T *const end = this->data + this->size();
		const T *J=A.data;
		for (T *I=this->data; I!=end; ++I, ++J)
			*I *= *J;

	} else{
		for (uint32_t i=0, j; i<this->rows(); ++i)
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) *= A(i, j);
	}
	return *this;
}

TPL template<class Mat1>
CLS &CLS::elwiseDiv(const Mat1 &A){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->rows()!=A.rows() || this->cols()!=A.cols()){
			fprintf(stderr, "Linear algebra error:   Elementwise divided matrices must have the same dimensions.\n");
			exit(2137);
		}

		if (this->data==A.data && isRowMajor!=A.isRowMajor){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for"
				" the result of elementwise division at the same time.\n"
			);
			exit(2137);
		}
	}

	if constexpr (isRowMajor == A.isRowMajor){
		const T *const end = this->data + this->size();
		const T *J=A.data;
		for (T *I=this->data; I!=end; ++I, ++J)
			*I /= *J;

	} else{
		for (uint32_t i=0, j; i<this->rows(); ++i)
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) /= A(i, j);
	}
	return *this;
}

TPL template<class Mat1>
CLS &CLS::elwiseApply(const Mat1 &A, T (*func)(T, T)){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->rows()!=A.rows() || this->cols()!=A.cols()){
			fprintf(stderr, "Linear algebra error:   Matrices which are arguments for elementwise applied function must have the same dimensions.\n");
			exit(2137);
		}

		if (this->data==A.data && isRowMajor!=A.isRowMajor){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for"
				" the result of applying the function elementwise at the same time.\n"
			);
			exit(2137);
		}
	}

	if constexpr (isRowMajor == A.isRowMajor){
		const T *const end = this->data + this->size();
		const T *J=A.data;
		for (T *I=this->data; I!=end; ++I, ++J)
			*I = func(*I, *J);

	} else{
		for (uint32_t i=0, j; i<this->rows(); ++i)
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) = func((*this)(i, j), A(i, j));
	}
	return *this;
}


TPL template<class Mat1>
CLS &CLS::postMul(const Mat1 &A){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->cols()!=A.rows()){
			fprintf(stderr, "Linear algebra error:   Multiplied matrices have wrong dimensions.\n");
			exit(2137);
		}

		if (this->data == A.data){
			fprintf(stderr, "Linear algebra error:   Matrix can't be argument and container for the result of"
				" post multiplication at the same time.\nUse square() instead."
			);
			exit(2137);
		}
	}

	MatrixTempStorage->resize(this->size()*sizeof(T));
	memcpy(MatrixTempStorage->data(), this->data, this->size()*sizeof(T));

	const uint32_t imL = this->cols();
	resize(this->rows(), A.cols());

	T sum;
	for(uint32_t i=0, j, k; i<this->outLen(); ++i)
		for(j=0; j<this->innLen(); ++j){
			sum = (T)0;
			for(k=0; k<imL; ++k){
				if constexpr (isRowMajor)
					sum += MatrixTempStorage->at<T>(i*imL+k) * A(k, j);
				else
					sum += MatrixTempStorage->at<T>(k*imL+j) * A(k, i);
			}
			this->data[i*this->innLen()+j] = sum;
		}

	return *this;
}

TPL template<class Mat1>
CLS &CLS::preMul(const Mat1 &A){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (A.cols() != this->rows()){
			fprintf(stderr, "Linear algebra error:   Multiplied matrices have wrong dimensions.\n");
			exit(2137);
		}

		if (this->data == A.data){
			fprintf(stderr, "Linear algebra error:   Matrix can't be argument and container for the result of"
				" pre multiplication at the same time.\nUse square() instead."
			);
			exit(2137);
		}
	}

	MatrixTempStorage->resize(this->size()*sizeof(T));
	memcpy(MatrixTempStorage->data(), this->data, this->size()*sizeof(T));

	resize(A.rows(), this->cols());
	const uint32_t imL = this->rows();

	T sum;
	for(uint32_t i=0, j, k; i<this->outLen(); ++i)
		for(j=0; j<this->innLen(); ++j){
			sum = (T)0;
			for(k=0; k<imL; ++k){
				if constexpr (isRowMajor)
					sum += A(i, k) * MatrixTempStorage->at<T>(k*this->innLen()+j);
				else
					sum += A(i, k) * MatrixTempStorage->at<T>(k+j*this->innLen());
			}
			this->data[i*this->innLen()+j] = sum;
		}

	return *this;
}

TPL CLS &CLS::square(){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->rows() != this->cols()){
			fprintf(stderr, "Linear algebra error:   Only square matrix can be squared.\nMaybe try pSuqare.\n");
			exit(2137);
		}
	}

	const uint32_t len = this->rows();

	MatrixTempStorage->resize(len*len*sizeof(T));
	memcpy(MatrixTempStorage->data(), this->data, len*len*sizeof(T));

	T sum;
	for(uint32_t i=0, j, k; i<len; ++i)
		for(j=0; j<len; ++j){
			sum = (T)0;
			for(k=0; k<len; ++k){
				if constexpr (isRowMajor)
					sum += MatrixTempStorage->at<T>(i*len+k) * MatrixTempStorage->at<T>(k*len+j);
				else
					sum += MatrixTempStorage->at<T>(i+k*len) * MatrixTempStorage->at<T>(k+j*len);
			}
			this->data[i*len+j] = sum;
		}

	return *this;
}

TPL CLS &CLS::psquare(){
	MatrixTempStorage->resize(this->size()*sizeof(T));
	memcpy(MatrixTempStorage->data(), this->data, this->size()*sizeof(T));

	T sum;
	for(uint32_t i=0, j, k; i<this->rows(); ++i)
		for(j=0; j<this->rows(); ++j){
			sum = (T)0;
			for(k=0; k<this->cols(); ++k){
				if constexpr (isRowMajor)
					sum += MatrixTempStorage->at<T>(i*this->cols()+k) * MatrixTempStorage->at<T>(k*this->rows()+j);
				else
					sum += MatrixTempStorage->at<T>(i+k*this->rows()) * MatrixTempStorage->at<T>(k+j*this->cols());
			}
			this->data[i*this->rows()+j] = sum;
		}

	this->resize(this->rows(), this->rows());
	return *this;
}

TPL CLS &CLS::transpose(){
	MatrixTempStorage->resize(this->size()*sizeof(T));
	memcpy(MatrixTempStorage->data(), this->data, this->size()*sizeof(T));

	for (uint32_t i=0, j; i<this->outLen(); ++i)
		for (j=0; j<this->innLen(); ++j)
			this->data[j*this->outLen()+i] = MatrixTempStorage->at<T>(i*this->innLen()+j);

	this->flipStorageOrder();

	return *this;
}


TPL CLS &CLS::mul(const T &x){
	const T *const end = this->data + this->size();
	for (T *I=this->data; I!=end; ++I)
		*I *= x;
	return *this;
}

TPL CLS &CLS::div(const T &x){
	const T *const end = this->data + this->size();
	for (T *I=this->data; I!=end; ++I)
		*I /=  x;
	return *this;
}

TPL CLS &CLS::apply(T (*func)(T)){
	const T *const end = this->data + this->size();
	for (T *I=this->data; I!=end; ++I)
		*I =  func(*I);
	return *this;
}

TPL CLS &CLS::apply(T (*func)(T, uint32_t, uint32_t)){
	for (uint32_t i=0, j; i<this->rows(); ++i)
		for (j=0; j<this->cols(); ++j)
			(*this)(i, j) = func((*this)(i, j), i, j);
	return *this;
}

TPL template<class Arg>
CLS &CLS::apply(T (*func)(T, uint32_t, uint32_t, const Arg &), const Arg &funcArg){
	for (uint32_t i=0, j; i<this->rows(); ++i)
		for (j=0; j<this->cols(); ++j)
			(*this)(i, j) = func((*this)(i, j), i, j, funcArg);
	return *this;
}




TPL template<class Prot1>
CLS &CLS::lupDecompose(priv__::Vector<Prot1, uint32_t> *const permutation){
	permutation->resize(this->rows());
	for (uint32_t i=0; i<this->rows(); ++i)
		permutation->data[i] = i;

	const uint32_t length = std::min(this->rows(), this->cols());
	T factor1, factor2;
	for (uint32_t i=0, j, k; i<length; ++i){
		k = i;
		for (j=i+1; j<this->rows(); ++j)	// find row with max value
			k = abs((*this)(j, i))>abs((*this)(k, i)) ? j : k;
		if (k != i){
			for (j=0; j<this->cols(); ++j)	// exchange top row with row with max value
				sp::swap(&(*this)(i, j), &(*this)(k, j));
			sp::swap(permutation->data+i, permutation->data+k);
		}
		factor1 = this->data[i*(this->innLen()+1)];
		for (j=i+1; j<this->rows(); ++j){
			factor2 = (*this)(j, i) / factor1;
			(*this)(j, i) = factor2;
			for (k=i+1; k<this->cols(); ++k)
				(*this)(j, k) -= (*this)(i, k)*factor2;
		}
	}
	return *this;
}
TPL CLS &CLS::lupDecompose(uint32_t *const permutation){
	for (uint32_t i=0; i<this->rows(); ++i)
		permutation[i] = i;

	const uint32_t length = std::min(this->rows(), this->cols());
	T factor1, factor2;
	for (uint32_t i=0, j, k; i<length; ++i){
		k = i;
		for (j=i+1; j<this->rows(); ++j)	// find row with max value
			k = abs((*this)(j, i))>abs((*this)(k, i)) ? j : k;
		if (k != i){
			for (j=0; j<this->cols(); ++j)	// exchange top row with row with max value
				sp::swap(&(*this)(i, j), &(*this)(k, j));
			sp::swap(permutation+i, permutation+k);
		}
		factor1 = this->data[i*(this->innLen()+1)];
		for (j=i+1; j<this->rows(); ++j){
			factor2 = (*this)(j, i) / factor1;
			(*this)(j, i) = factor2;
			for (k=i+1; k<this->cols(); ++k)
				(*this)(j, k) -= (*this)(i, k)*factor2;
		}
	}
	return *this;
}

TPL template<class Mat1>
CLS &CLS::extractLower(Mat1 *const A){
	const uint32_t length = std::min(this->rows(), this->cols());
	A->resize(this->rows(), length);
	this->resize(length, this->cols());
	for (uint32_t i=0, j; i<length; ++i){
		for (j=i+1; j<A->rows(); ++j){
			(*A)(j, i) = (*this)(j, i);
			(*this)(j, i) = (T)0;
		}
		(*A)(i, i) = (T)1;
		for (j=i+1; j<this->cols(); ++j)
			(*A)(i, j) = (T)0;
	}
	return *this;
}

TPL template<class Mat1>
CLS &CLS::extractUpper(Mat1 *const A){
	const uint32_t length = std::min(this->rows(), this->cols());
	A->resize(length, this->cols());
	this->resize(this->rows(), length);
	for (uint32_t i=0, j; i<length; ++i){
		for (j=i+1; j<A->cols(); ++j){
			(*A)(i, j) = (*this)(i, j);
			(*this)(i, j) = (T)0;
		}
		(*A)(i, i) = (*this)(i, i); 
		(*this)(i, i) = (T)1;
		for (j=i+1; j<this->rows(); ++j)
			(*A)(j, i) = (T)0;
	}
	return *this;
}

TPL CLS &CLS::invert(){
	MatrixTempStorage->resize(this->rows()*this->rows()*sizeof(uint32_t));
	this->lupDecompose(MatrixTempStorage->data<uint32_t>());
	return *this;
}
/*
TPL CLS &CLS::pinvert(){
	return *this;
}*/



TPL template<class Mat1, class Prot2>
CLS &CLS::add(const Mat1 &A, const Vector<Prot2, T> &B){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (A.rows()!=B.size()){
			fprintf(stderr, "Linear algebra error:   Added vector must have the same number of rows as matrix.\n");
			exit(2137);
		}

		if (this->data==A.data && isRowMajor!=A.isRowMajor){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for the result of addition at the same time.\n");
			exit(2137);
		}
	}

	this->resize(A.rows(), A.cols());
	if constexpr (isRowMajor){
		T valueHolder;
		for (uint32_t i=0, j; i<this->rows(); ++i){
			valueHolder = B[i];
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) = A(i, j) + valueHolder;
		}
	} else{
		for (uint32_t i=0, j; i<this->cols(); ++i)
			for (j=0; j<this->rows(); ++j)
				(*this)(i, j) = A(i, j) + B[j];
	}
	return *this;
}

TPL template<class Mat1, class Prot2>
CLS &CLS::sub(const Mat1 &A, const Vector<Prot2, T> &B){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (A.rows()!=B.size()){
			fprintf(stderr, "Linear algebra error:   Subtracted vector must have the same number of rows as matrix.\n");
			exit(2137);
		}

		if (this->data==A.data && isRowMajor!=A.isRowMajor){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for the result of subtraction at the same time.\n");
			exit(2137);
		}
	}

	this->resize(A.rows(), A.cols());
	if constexpr (isRowMajor){
		T valueHolder;
		for (uint32_t i=0, j; i<this->rows(); ++i){
			valueHolder = B[i];
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) = A(i, j) - valueHolder;
		}
	} else{
		for (uint32_t i=0, j; i<this->cols(); ++i)
			for (j=0; j<this->rows(); ++j)
				(*this)(i, j) = A(i, j) - B[j];
	}
	return *this;
}

TPL template<class Prot1, class Mat2>
CLS &CLS::sub(const Vector<Prot1, T> &A, const Mat2 &B){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (A.size()!=B.rows()){
			fprintf(stderr, "Linear algebra error:   Subtracted vector must have the same number of rows as matrix.\n");
			exit(2137);
		}

		if (this->data==B.data && isRowMajor!=B.isRowMajor){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for the result of subtraction at the same time.\n");
			exit(2137);
		}
	}

	this->resize(A.rows(), A.cols());
	if constexpr (isRowMajor){
		T valueHolder;
		for (uint32_t i=0, j; i<this->rows(); ++i){
			valueHolder = B[i];
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) = valueHolder - A(i, j);
		}
	} else{
		for (uint32_t i=0, j; i<this->cols(); ++i)
			for (j=0; j<this->rows(); ++j)
				(*this)(i, j) = B[j] - A(i, j);
	}
	return *this;
}


TPL template<class Mat1, class Prot2>
CLS &CLS::elwiseMul(const Mat1 &A, const Vector<Prot2, T> &B){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (A.rows()!=B.size()){
			fprintf(stderr, "Linear algebra error:   Elementwise multiplied vector must have the same number of rows as matrix.\n");
			exit(2137);
		}

		if (this->data==A.data && isRowMajor!=A.isRowMajor){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for the result of elementwse multiplication at the same time.\n");
			exit(2137);
		}
	}

	this->resize(A.rows(), A.cols());
	if constexpr (isRowMajor){
		T valueHolder;
		for (uint32_t i=0, j; i<this->rows(); ++i){
			valueHolder = B[i];
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) = A(i, j) * valueHolder;
		}
	} else{
		for (uint32_t i=0, j; i<this->cols(); ++i)
			for (j=0; j<this->rows(); ++j)
				(*this)(i, j) = A(i, j) * B[j];
	}
	return *this;
}

TPL template<class Mat1, class Prot2>
CLS &CLS::elwiseDiv(const Mat1 &A, const Vector<Prot2, T> &B){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (A.rows()!=B.size()){
			fprintf(stderr, "Linear algebra error:   Elementwise divided vector must have the same number of rows as matrix.\n");
			exit(2137);
		}

		if (this->data==A.data && isRowMajor!=A.isRowMajor){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for the result of elementwse division at the same time.\n");
			exit(2137);
		}
	}

	this->resize(A.rows(), A.cols());
	if constexpr (isRowMajor){
		T valueHolder;
		for (uint32_t i=0, j; i<this->rows(); ++i){
			valueHolder = B[i];
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) = A(i, j) / valueHolder;
		}
	} else{
		for (uint32_t i=0, j; i<this->cols(); ++i)
			for (j=0; j<this->rows(); ++j)
				(*this)(i, j) = A(i, j) / B[j];
	}
	return *this;
}

TPL template<class Mat1, class Prot2>
CLS &CLS::elwiseApply(const Mat1 &A, const Vector<Prot2, T> &B, T (*func)(T, T)){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (A.rows()!=B.size()){
			fprintf(stderr, "Linear algebra error:   Matrix and vector which are arguments for elementwise applied function must have the same dimensions.\n");
			exit(2137);
		}

		if (this->data==A.data && isRowMajor!=A.isRowMajor){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for the result of"
				"appying the function elementwise at the same time.\n"
			);
			exit(2137);
		}
	}

	this->resize(A.rows(), A.cols());
	if constexpr (isRowMajor){
		T valueHolder;
		for (uint32_t i=0, j; i<this->rows(); ++i){
			valueHolder = B[i];
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) = func(A(i, j), valueHolder);
		}
	} else{
		for (uint32_t i=0, j; i<this->cols(); ++i)
			for (j=0; j<this->rows(); ++j)
				(*this)(i, j) = func(A(i, j), B[j]);
	}
	return *this;
}

TPL template<class Mat1, class Prot2>
CLS &CLS::mul(const Mat1 &A, const Vector<Prot2, T> &B){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (A.cols() != B.size()){
			fprintf(stderr, "Linear algebra error:   Multiplied matrix and vector have wrong dimensions.\n");
			exit(2137);
		}

		if (this->data==A.data && isRowMajor!=A.isRowMajor){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for the result of multiplication at the same time.\n");
			exit(2137);
		}
	}

	T sum;
	for(uint32_t i=0, j; i<this->rows(); ++i){
		sum = (T)0;
		for(j=0; j<this->cols(); ++j)
			sum += A(i, j) * B[j];
		this->data[i] = sum;
	}

	this->resize(A.rows(), 1);
	return *this;
}

TPL template<class Prot1, class Mat2>
CLS &CLS::mul(const Vector<Prot1, T> &A, const Mat2 &B){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (A.size() != B.rows()){
			fprintf(stderr, "Linear algebra error:   Multiplied matrix and vector have wrong dimensions.\n");
			exit(2137);
		}

		if (this->data==B.data && isRowMajor!=B.isRowMajor){
			fprintf(stderr, "Linear algebra error:   Matrix can't be transposed argument and container for the result of multiplication at the same time.\n");
			exit(2137);
		}
	}

	T sum;
	for(uint32_t i=0, j; i<A.cols(); ++i){
		sum = (T)0;
		for(j=0; j<A.rows(); ++j)
			sum += A[j] * B(j, i);
		this->data[i] = sum;
	}

	this->resize(1, A.cols());
	return *this;
}

TPL template<class Prot1>
CLS &CLS::add(const Vector<Prot1, T> &A){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->rows()!=A.size()){
			fprintf(stderr, "Linear algebra error:   Added vector must have the same number of rows as matrix.\n");
			exit(2137);
		}
	}

	if constexpr (isRowMajor){
		T valueHolder;
		for (uint32_t i=0, j; i<this->rows(); ++i){
			valueHolder = A[i];
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) += valueHolder;
		}
	} else{
		for (uint32_t i=0, j; i<this->cols(); ++i)
			for (j=0; j<this->rows(); ++j)
				(*this)(i, j) += A[j];
	}
	return *this;
}

TPL template<class Prot1>
CLS &CLS::subFromSelf(const Vector<Prot1, T> &A){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->rows()!=A.size()){
			fprintf(stderr, "Linear algebra error:   Subtracted vector must have the same number of rows as matrix.\n");
			exit(2137);
		}
	}

	if constexpr (isRowMajor){
		T valueHolder;
		for (uint32_t i=0, j; i<this->rows(); ++i){
			valueHolder = A[i];
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) -= valueHolder;
		}
	} else{
		for (uint32_t i=0, j; i<this->cols(); ++i)
			for (j=0; j<this->rows(); ++j)
				(*this)(i, j) -= A[j];
	}
	return *this;
}

TPL template<class Prot1>
CLS &CLS::subSelfFrom(const Vector<Prot1, T> &A){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->rows()!=A.size()){
			fprintf(stderr, "Linear algebra error:   Subtracted vector must have the same number of rows as matrix.\n");
			exit(2137);
		}
	}

	if constexpr (isRowMajor){
		T valueHolder;
		for (uint32_t i=0, j; i<this->rows(); ++i){
			valueHolder = A[i];
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) = valueHolder - (*this)(i, j);
		}
	} else{
		for (uint32_t i=0, j; i<this->cols(); ++i)
			for (j=0; j<this->rows(); ++j)
				(*this)(i, j) = A[j] - (*this)(i, j);
	}
	return *this;
}

TPL template<class Prot1>
CLS &CLS::elwiseMul(const Vector<Prot1, T> &A){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->rows()!=A.size()){
			fprintf(stderr, "Linear algebra error:   Elementwise multiplied vector must have the same number of rows as matrix.\n");
			exit(2137);
		}
	}

	if constexpr (isRowMajor){
		T valueHolder;
		for (uint32_t i=0, j; i<this->rows(); ++i){
			valueHolder = A[i];
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) *= valueHolder;
		}
	} else{
		for (uint32_t i=0, j; i<this->cols(); ++i)
			for (j=0; j<this->rows(); ++j)
				(*this)(i, j) *= A[j];
	}
	return *this;
}

TPL template<class Prot1>
CLS &CLS::elwiseDiv(const Vector<Prot1, T> &A){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->rows()!=A.size()){
			fprintf(stderr, "Linear algebra error:   Elementwise divided vector must have the same number of rows as matrix.\n");
			exit(2137);
		}
	}

	if constexpr (isRowMajor){
		T valueHolder;
		for (uint32_t i=0, j; i<this->rows(); ++i){
			valueHolder = A[i];
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) /= valueHolder;
		}
	} else{
		for (uint32_t i=0, j; i<this->cols(); ++i)
			for (j=0; j<this->rows(); ++j)
				(*this)(i, j) /= A[j];
	}
	return *this;
}

TPL template<class Prot1>
CLS &CLS::elwiseApply(const Vector<Prot1, T> &A, T (*func)(T, T)){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->rows()!=A.size()){
			fprintf(stderr, "Linear algebra error:   Matrix and vector which are arguments for elementwise applied function must have the same dimensions.\n");
			exit(2137);
		}
	}

	if constexpr (isRowMajor){
		T valueHolder;
		for (uint32_t i=0, j; i<this->rows(); ++i){
			valueHolder = A[i];
			for (j=0; j<this->cols(); ++j)
				(*this)(i, j) = func((*this)(i, j), valueHolder);
		}
	} else{
		for (uint32_t i=0, j; i<this->cols(); ++i)
			for (j=0; j<this->rows(); ++j)
				(*this)(i, j) = func((*this)(i, j), A[j]);
	}
	return *this;
}


TPL template<class Prot1>
CLS &CLS::postMul(const Vector<Prot1, T> &A){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->cols() != A.size()){
			fprintf(stderr, "Linear algebra error:   Multiplied matrix and vector have wrong dimensions.\n");
			exit(2137);
		}
	}

	T sum;
	for(uint32_t i=0, j; i<this->rows(); ++i){
		sum = (T)0;
		for(j=0; j<this->cols(); ++j)
			sum += (*this)(i, j) * A[j];
		this->data[i] = sum;
	}

	this->resize(this->rows(), 1);
	return *this;
}

TPL template<class Prot1>
CLS &CLS::preMul(const Vector<Prot1, T> &A){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (this->rows() != A.size()){
			fprintf(stderr, "Linear algebra error:   Multiplied matrix and vector have wrong dimensions.\n");
			exit(2137);
		}
	}

	T sum;
	for(uint32_t i=0, j; i<this->cols(); ++i){
		sum = (T)0;
		for(j=0; j<this->rows(); ++j)
			sum += A[j] * (*this)(j, i);
		this->data[i] = sum;
	}

	this->resize(1, this->cols());
	return *this;
}



#undef CLS
#undef TPL

}	// END OF NAMESPACE PRIV







template<class Prot, class T>
inline constexpr priv__::Matrix<Prot, T, false> &tr(priv__::Matrix<Prot, T, true> &A){
	return *(priv__::Matrix<Prot, T, false> *)&A;
}

template<class Prot, class T>
inline constexpr priv__::Matrix<Prot, T, true> &tr(priv__::Matrix<Prot, T, false> &A){
	return *(priv__::Matrix<Prot, T, true> *)&A;
}

template<class Prot, class T>
inline constexpr const priv__::Matrix<Prot, T, false> &tr(const priv__::Matrix<Prot, T, true> &A){
	return *(const priv__::Matrix<Prot, T, false> *)&A;
}

template<class Prot, class T>
inline constexpr const priv__::Matrix<Prot, T, true> &tr(const priv__::Matrix<Prot, T, false> &A){
	return *(const priv__::Matrix<Prot, T, true> *)&A;
}



template<class Prot, class T, bool rm1>
T determinant(const priv__::Matrix<Prot, T, rm1> &A){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (A.rows() != A.cols()){
			fprintf(stderr, "Linear algebra error:   Only determinant of square matrix can be calculated.\n");
			exit(2137);
		}
	}

	const uint32_t len = A.rows();
	MatrixTempStorage->resize(len*len*sizeof(T));
	memcpy(MatrixTempStorage->data(), A.data, len*len*sizeof(T));
	
	T result = (T)1;
	T factor1, factor2;
	for (uint32_t i=0, j, k; i<len-1; ++i){
		k = i;
		for (j=i+1; j<len; ++j)	// find row with max value
			k = abs(MatrixTempStorage->at<T>(j*len+i))>abs(MatrixTempStorage->at<T>(k*len+i)) ? j : k;
		if (k != i){
			for (j=i; j<len; ++j)	// exchange top row with row with max value
				sp::swap(&MatrixTempStorage->at<T>(i*len+j), &MatrixTempStorage->at<T>(k*len+j));
			result *= (T)-1;
		}
		factor1 = MatrixTempStorage->at<T>(i*(len+1));
		result *= factor1;
		for (j=i+1; j<len; ++j){
			factor2 = MatrixTempStorage->at<T>(j*len+i) / factor1;
			for (k=i+1; k<len; ++k)
				MatrixTempStorage->at<T>(j*len+k) -= MatrixTempStorage->at<T>(i*len+k) * factor2;
		}
	}
	
	return result * MatrixTempStorage->at<T>(len*len-1);
}

template<class Prot, class T, bool rm1>
T minor(const priv__::Matrix<Prot, T, rm1> &A, const uint32_t row, const uint32_t column){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (A.rows() != A.cols()){
			fprintf(stderr, "Linear algebra error:   Only minor of square matrix can be calculated.\n");
			exit(2137);
		}
	}

	const uint32_t len = A.rows()-1;

	MatrixTempStorage->resize(len*len*sizeof(T));
	memcpy(MatrixTempStorage->data(), A.data, len*len*sizeof(T));

	uint32_t i, j, k;
	for (i=0; i<row; ++i){	// Make submatrix
		for (j=0; j<column; ++j)
			MatrixTempStorage->at<T>(i*len+j) = A(i, j);
		for (j=column+1; j!=len+1; ++j)
			MatrixTempStorage->at<T>(i*len+j-1) = A(i, j);
	}
	for (i=row+1; i<A.rows(); ++i){
		for (j=0; j<column; ++j)
			MatrixTempStorage->at<T>(i*len+j-len) = A(i, j);
		for (j=column+1; j<A.rows(); ++j)
			MatrixTempStorage->at<T>(i*len+j-len-1) = A(i, j);
	}

	T result = (T)1;
	T factor1, factor2;
	for (i=0; i<len-1; ++i){
		k = i;
		for (j=i+1; j<len; ++j)	// find row with max value
			k = abs(MatrixTempStorage->at<T>(j*len+i))>abs(MatrixTempStorage->at<T>(k*len+i)) ? j : k;
		if (k != i){
			for (j=i; j<len; ++j)	// exchange top row with row with max value
				sp::swap(&MatrixTempStorage->at<T>(i*len+j), &MatrixTempStorage->at<T>(k*len+j));
			result *= (T)-1;
		}

		factor1 = MatrixTempStorage->at<T>(i*(len+1));
		result *= factor1;
		for (j=i+1; j<len; ++j){
			factor2 = MatrixTempStorage->at<T>(j*len+i) / factor1;
			for (k=i+1; k<len; ++k)
				MatrixTempStorage->at<T>(j*len+k) -= MatrixTempStorage->at<T>(i*len+k) * factor2;
		}
	}
	
	return result * MatrixTempStorage->at<T>(len*len-1);
}

template<class Prot, class T, bool rm1>
inline T cofactor(const priv__::Matrix<Prot, T, rm1> &A, const uint32_t row, const uint32_t column){
	return minor(A, row, column) * ((row+column)&1 ? -(T)1 : (T)1);
}

template<class Prot, class T, bool rm1>
uint32_t rank(const priv__::Matrix<Prot, T, rm1> &A){
	return 0;
}



template<class T, class Prot1, class Prot2, bool rm1, bool rm2>
bool operator ==(const priv__::Matrix<T, Prot1, rm1> &A, const priv__::Matrix<T, Prot2, rm2> &B){
	if (A.rows()!=B.rows() || A.cols()!=B.cols())
		return false;
	if constexpr (rm1 == rm2){
		const T *const end = A.data + A.size();
		for (T *I=A.data, *J=B.data; I!=end; ++I, ++J)
			if (*I != *J)
				return false;
	} else{
		for (uint32_t i=0, j; i<A.rows(); ++i)
			for (j=0; j<A.cols(); ++j)
				if (A(i, j) != B(i, j))
					return false;
	}
	return true;
}
/*
template<class T, uint32_t cap1, bool rm1>
void printM(FILE *const output, const ProtHMatrix<T, cap1, rm1> &A){
	for (uint32_t i=0, j; i<A.cols(); ++i){
		for (j=0; j<A.rows(); ++j){
			
				printf("%8.2lf", A(j, i));
		}
		putchar('\n');
	}
}

template<class T, uint32_t cap1, bool rm1>
void printBM(FILE *const output, const ProtHMatrix<T, cap1, rm1> &A);

template<class T, uint32_t cap1, bool rm1>
void printMM(FILE *const output, const ProtHMatrix<T, cap1, rm1> &A);*/


/*void print(FILE *const output, void (*printType)(FILE *, T)){
	for(uint32_t i=0, j; i<rows; ++i){
		for(j=0; j<cols; ++j)
			printType(output, data[i*cols+j]);
		putc('\n', output);
	}
}*/


}	// END OF NAMESPACE	///////////////////////////////////////////////////////////////////