#pragma once

#include "sp_Utils.hpp"


namespace sp{ // BEGINING OF NAMESPACE //////////////////////////////////////////////////////////////////


template<class T, int cap> class SVector;


template<class T, int cap, bool rowMajor = true>
class SMatrix{
public:
	inline SMatrix() noexcept;
	inline SMatrix(const int rows, const int columns) noexcept;

	
	template<int cap1, bool rm1>
	SMatrix(const SMatrix<T, cap1, rm1> &A) noexcept;
	
	template<int cap1, bool rm1>
	SMatrix &operator =(const SMatrix<T, cap1, rm1> &A) noexcept;
	
	template<int cap1>
	SMatrix &operator =(const SVector<T, cap1> &A) noexcept;

	inline constexpr T &operator ()(const int row, const int column) noexcept;

	inline constexpr const T &operator ()(const int row, const int column) const noexcept;
	
	inline void resize(const int rows, const int columns) noexcept;

	inline constexpr int capacity() const;

	inline int rows() const;

	inline int cols() const;


	
	void init(T (*func)());
	
	void init(T (*func)(int, int));
	
	template<int maxLineLength = 512>
	bool load(FILE *const input, T (*stringToType)(const char *, char **));
	
	template<int maxLineLength = 512>
	bool load(FILE *const input, T (*stringToType)(const char *, char **), const int rowNumber, const int columnNumber);


// GENERAL MATRIX OPERATIONS
	template<int cap1, int cap2, bool rm1, bool rm2>
	SMatrix &add(const SMatrix<T, cap1, rm1> &A, const SMatrix<T, cap2, rm2> &B) noexcept;
	
	template<int cap1, int cap2, bool rm1, bool rm2>
	SMatrix &sub(const SMatrix<T, cap1, rm1> &A, const SMatrix<T, cap2, rm2> &B) noexcept;
	
	template<int cap1, int cap2, bool rm1, bool rm2>
	SMatrix &el_mul(const SMatrix<T, cap1, rm1> &A, const SMatrix<T, cap2, rm2> &B) noexcept;

	template<int cap1, int cap2, bool rm1, bool rm2>
	SMatrix &el_div(const SMatrix<T, cap1, rm1> &A, const SMatrix<T, cap2, rm2> &B) noexcept;


	template<int cap1, int cap2, bool rm1, bool rm2>
	SMatrix &mul(const SMatrix<T, cap1, rm1> &A, const SMatrix<T, cap2, rm2> &B) noexcept;

	template<int cap1, int cap2, bool rm1>
	SMatrix &mul(const SMatrix<T, cap1, rm1> &A, const SVector<T, cap2> &v) noexcept;
	
	template<int cap1, int cap2, bool rm2>
	SMatrix &mul(const SVector<T, cap1> &v, const SMatrix<T, cap2, rm2> &A) noexcept;
	

	template<int cap1, bool rm1>
	SMatrix &mul(const SMatrix<T, cap1, rm1> &A, const T &x) noexcept;
	
	template<int cap1, bool rm1>
	SMatrix &div(const SMatrix<T, cap1, rm1> &A, const T &x) noexcept;


	template<int cap1, bool rm1>
	SMatrix &transpose(const SMatrix<T, cap1, rm1> &A);
	
	template<int cap1, bool rm1>
	SMatrix &invert(const SMatrix<T, cap1, rm1> &A);


	template<int cap1, bool rm1>
	SMatrix &lu_decompose(const SMatrix<T, cap1, rm1> &A);

	template<int cap1, int cap2, bool rm2>
	SMatrix &lup_decompose(SVector<int, cap1> *P, const SMatrix<T, cap2, rm2> &A);


// MATRIX OPERATIONS ON SELF

	template<int cap1, bool rm1>
	SMatrix &post_mul(const SMatrix<T, cap1, rm1> &A);

	template<int cap1, bool rm1>
	SMatrix &pre_mul(const SMatrix<T, cap1, rm1> &A);

	SMatrix &square();

	SMatrix &psquare();	// Matrix times its transpose

	SMatrix &transpose();

	SMatrix &invert();

	SMatrix &pinvert();


	T data[cap];
	int vL, hL;
};



template<class T, int cap1>
inline constexpr SMatrix<T, cap1, false> &tr(SMatrix<T, cap1, true> &A);

template<class T, int cap1>
inline constexpr SMatrix<T, cap1, true> &tr(SMatrix<T, cap1, false> &A);


template<class T, int cap1, bool rm1>
T determinant(const SMatrix<T, cap1, rm1> &A);

template<class T, int cap1, bool rm1>
T minor(const SMatrix<T, cap1, rm1> &A, const int row, const int column);

template<class T, int cap1, bool rm1>
inline T cofactor(const SMatrix<T, cap1, rm1> &A, const int row, const int column);

template<class T, int cap1, bool rm1>
int rank(const SMatrix<T, cap1, rm1> &A);



template<class T, int cap1, int cap2, bool rm1>
bool operator ==(const SVector<T, cap1> &A, const SVector<T, cap2> &B);

template<class T, int cap1, int cap2, bool rm1, bool rm2>
bool operator ==(const SMatrix<T, cap1, rm1> &A, const SMatrix<T, cap2, rm2> &B);


template<class T, int cap1, bool rm1>
void printM(FILE *const output, const SMatrix<T, cap1, rm1> &A);

template<class T, int cap1, bool rm1>
void printBM(FILE *const output, const SMatrix<T, cap1, rm1> &A);

template<class T, int cap1, bool rm1>
void printMM(FILE *const output, const SMatrix<T, cap1, rm1> &A);





template<class T, int cap>
class SVector{
public:
	inline SVector() noexcept;

	inline SVector(const int lenNumber) noexcept;

	template<int cap1>
	inline SVector(const SVector<T, cap1> &v) noexcept;
	
	template<int cap1>
	inline SVector &operator =(const SVector<T, cap1> &v) noexcept;


	inline constexpr T &operator [](const int index) noexcept;

	inline void resize(const int lenNumber) noexcept;


	void init(T (*func)());

	void init(T (*func)(int));

	bool load(FILE *const input, T (*stringToType)(const char *, char **));

	bool load(FILE *const input, T (*stringToType)(const char *, char **), const int lenghtNumber);

	T data[cap];
	int len;
};







#ifndef SP_MATRIX_RUNTIME_ERRORS
	#define RTERROR(cond, text, ret) ;
#else
	#define RTERROR(cond, text, ret) if (cond){ std::runtime_error(text); return ret; }
#endif



#define TPL template<class T, int cap>
#define CLS SVector<T, cap>

TPL inline CLS::SVector() noexcept : len{0} {}

TPL inline CLS::SVector(const int lenNumber) noexcept :len{lenNumber} {}

TPL template<int cap1>
inline CLS::SVector(const SVector<T, cap1> &v) noexcept : len{v.len}{
	memcpy(data, v.data, len);
}

TPL template<int cap1>
inline CLS &CLS::operator =(const SVector<T, cap1> &v) noexcept{
	len = v.len;
	memcpy(data, v.data, len);
	return *this;
}

TPL inline constexpr T &CLS::operator [](const int index) noexcept{
	return data[index];
}

TPL inline void CLS::resize(const int lenNumber) noexcept{
	len = lenNumber;
}



TPL void CLS::init(T (*func)()){
	const T *end = data + len;
	for (T *I=data; I!=end; ++I)
		*I = func();
}

TPL void CLS::init(T (*func)(int)){
	for (int i=0; i<len; ++i)
		data[i] *= func(i);
}

TPL bool CLS::load(FILE *const input, T (*stringToType)(const char *, char **)){
	return true;
}

//TPL bool CLS::load(FILE *const input, const int lenghtNumber);

//TPL void CLS::print(FILE *const output);

#undef TPL
#undef CLS


#define TPL template<class T, int cap, bool rowMajor>
#define CLS SMatrix<T, cap, rowMajor>

TPL inline CLS::SMatrix() noexcept : hL{0}, vL{0} {}

TPL inline CLS::SMatrix(const int rows, const int columns) noexcept {
	if constexpr (rowMajor){
		vL = rows;
		hL = columns;
	} else{
		vL = columns;
		hL = rows;
	}
}

TPL template<int cap1, bool rm1>
CLS::SMatrix(const SMatrix<T, cap1, rm1> &A) noexcept {
	if constexpr (rowMajor == rm1){
		vL = A.vL;
		hL = A.hL;
		memcpy(data, A.data, vL*hL*sizeof(T));
	} else{
		vL = A.hL;
		hL = A.vL;
		for (int i=0, j; i<vL; ++i)
			for (j=0; j<hL; ++j)
				data[i*hL+j] = A.data[j*vL+i];
	}
}

TPL template<int cap1, bool rm1>
CLS &CLS::operator =(const SMatrix<T, cap1, rm1> &A) noexcept{
	if constexpr (rowMajor == rm1){
		vL = A.vL;
		hL = A.hL;
		memcpy(data, A.data, vL*hL*sizeof(T));
	} else{
		vL = A.hL;
		hL = A.vL;
		for (int i=0, j; i<vL; ++i)
			for (j=0; j<hL; ++j)
				data[i*hL+j] = A.data[j*vL+i];
	}
	return *this;
}

TPL template<int cap1>
CLS &CLS::operator =(const SVector<T, cap1> &A) noexcept{
	vL = 1;
	hL = A.len;
	memcpy(data, A.data, A.len*sizeof(T));
}

TPL inline constexpr T &CLS::operator ()(const int row, const int column) noexcept{
	if constexpr (rowMajor)
		return data[row*hL + column];
	else
		return data[column*hL + row];
}

TPL inline constexpr const T &CLS::operator ()(const int row, const int column) const noexcept{
	if constexpr (rowMajor)
		return data[row*hL + column];
	else
		return data[column*hL + row];
}

TPL inline void CLS::resize(const int rows, const int columns) noexcept{
	if constexpr (rowMajor){
		vL = rows;
		hL = columns;
	} else{
		vL = columns;
		hL = rows;
	}
}

TPL inline constexpr int CLS::capacity() const{
	return cap;
}

TPL inline int CLS::rows() const{
	if constexpr (rowMajor)
		return vL;
	else
		return hL;
}

TPL inline int CLS::cols() const{
	if constexpr (rowMajor)
		return hL;
	else
		return vL;
}


TPL void CLS::init(T (*func)()){
	const T *end = data + vL*hL;
	for (T *I=data; I!=end; ++I)
		*I = func();
}

TPL void CLS::init(T (*func)(int, int)){
	for (int i=0, j; i<vL; ++i)
		for (j=0; j<hL; ++j){
			if constexpr (rowMajor)
				data[i*hL+j] = func(i, j);
			else
				data[i*hL+j] = func(j, i);
		}
}

TPL template<int maxLineLength> bool CLS::load(FILE *const input, T (*stringToType)(const char *, char **)){
	char line[maxLineLength];
	char *linePointer = line;

	fgets(line, maxLineLength, input);
	if(*line=='\n' || feof(input))
		return false;
	
	int i, j;
	for (j=0; true; ++j){
		data[j] = stringToType(linePointer, &linePointer);
		if(*linePointer=='\n')
			break;
	}
	hL = j+1;

	for (i=1; true; ++i){
		fgets(line, maxLineLength, input);
		linePointer = line;
		if(*linePointer=='\n' || feof(input))
			break;
		
		data[i*hL] = stringToType(linePointer, &linePointer);
		for(j=1; j<hL; j++){
			if(*linePointer=='\n' || feof(input)){
				vL = 0;
				hL = 0;
				return false;
			}
			data[i*hL+j] = stringToType(linePointer, &linePointer);
		}
	}
	vL = i;
		
	if constexpr (!rowMajor){
		transpose();
	}

	return true;
}

TPL template<int maxLineLength> bool CLS::load(FILE *const input, T (*stringToType)(const char *, char **), const int rows, const int columns){
	char line[maxLineLength];
	char *linePointer = line;
	resize(rows, columns);
	for (int i=0, j; i<vL; ++i){
		fgets(line, maxLineLength, input);
		for (j=0; j<hL; ++j)
			(*this) = stringToType(linePointer, &linePointer);
	}
	return true;
}


// STANDARD MATRIX OPERATIONS
TPL template<int cap1, int cap2, bool rm1, bool rm2>
CLS &CLS::add(const SMatrix<T, cap1, rm1> &A, const SMatrix<T, cap2, rm2> &B) noexcept{
	resize(A.rows(), A.cols());
	if constexpr (rowMajor == rm1 && rowMajor == rm2){
		const T *end = data + vL*hL;
		const T *J=A.data, *K=B.data;
		for (T *I=data; I!=end; ++I, ++J, ++K)
			*I = *J + *K;

	} else{
		for (int i=0, j; i<vL; ++i)
			for (j=0; j<hL; ++j)
				(*this)(i, j) = A(i, j) + B(i, j);
	}
	return *this;
}

TPL template<int cap1, int cap2, bool rm1, bool rm2>
CLS &CLS::sub(const SMatrix<T, cap1, rm1> &A, const SMatrix<T, cap2, rm2> &B) noexcept{
	if constexpr (rowMajor == rm1){
		vL = A.vL;
		hL = A.hL;
		if constexpr (rowMajor == rm2){
			const T *end = data + vL*hL;
			const T *J=A.data, *K=B.data;
			for (T *I=data; I!=end; ++I, ++J, ++K)
				*I = *J - *K;
		} else{
			for (int i=0, j; i<vL; ++i)
				for (j=0; j<hL; ++j)
					data[i*hL+j] = A.data[i*hL+j] - B.data[i*vL+j];
		}
	} else{
		vL = A.hL;
		hL = A.vL;
		for (int i=0, j; i<vL; ++i)
			for (j=0; j<hL; ++j){
				if constexpr (rowMajor == rm2)
					data[i*hL+j] = A.data[j*vL+i] - B.data[i*hL+j];
				else
					data[i*hL+j] = A.data[j*vL+i] - B.data[j*vL+i];
			}
	}
	return *this;
}

TPL template<int cap1, int cap2, bool rm1, bool rm2>
CLS &CLS::el_mul(const SMatrix<T, cap1, rm1> &A, const SMatrix<T, cap2, rm2> &B) noexcept{
	if constexpr (rowMajor == rm1){
		vL = A.vL;
		hL = A.hL;
		if constexpr (rowMajor == rm2){
			const T *end = data + vL*hL;
			const T *J=A.data, *K=B.data;
			for (T *I=data; I!=end; ++I, ++J, ++K)
				*I = *J * *K;
		} else{
			for (int i=0, j; i<vL; ++i)
				for (j=0; j<hL; ++j)
					data[i*hL+j] = A.data[i*hL+j] * B.data[i*vL+j];
		}
	} else{
		vL = A.hL;
		hL = A.vL;
		for (int i=0, j; i<vL; ++i)
			for (j=0; j<hL; ++j){
				if constexpr (rowMajor == rm2)
					data[i*hL+j] = A.data[j*vL+i] * B.data[i*hL+j];
				else
					data[i*hL+j] = A.data[j*vL+i] * B.data[j*vL+i];
			}
	}
	return *this;
}

TPL template<int cap1, int cap2, bool rm1, bool rm2>
CLS &CLS::el_div(const SMatrix<T, cap1, rm1> &A, const SMatrix<T, cap2, rm2> &B) noexcept{
	if constexpr (rowMajor == rm1){
		vL = A.vL;
		hL = A.hL;
		if constexpr (rowMajor == rm2){
			const T *end = data + vL*hL;
			const T *J=A.data, *K=B.data;
			for (T *I=data; I!=end; ++I, ++J, ++K)
				*I = *J / *K;
		} else{
			for (int i=0, j; i<vL; ++i)
				for (j=0; j<hL; ++j)
					data[i*hL+j] = A.data[i*hL+j] / B.data[i*vL+j];
		}
	} else{
		vL = A.hL;
		hL = A.vL;
		for (int i=0, j; i<vL; ++i)
			for (j=0; j<hL; ++j){
				if constexpr (rowMajor == rm2)
					data[i*hL+j] = A.data[j*vL+i] / B.data[i*hL+j];
				else
					data[i*hL+j] = A.data[j*vL+i] / B.data[j*vL+i];
			}
	}
	return *this;
}


TPL template<int cap1, int cap2, bool rm1, bool rm2>
CLS &CLS::mul(const SMatrix<T, cap1, rm1> &A, const SMatrix<T, cap2, rm2> &B) noexcept{
	resize(A.rows(), B.cols());
	const int imL = A.cols();

	T sum;
	for(int i=0, j, k; i<hL; ++i)
		for(j=0; j<vL; ++j){
			sum = (T)0;
			for(k=0; k<imL; ++k)
				sum += A(j, k) * B(k, i);
			(*this)(j, i) = sum;
		}
	return *this;
}

TPL template<int cap1, int cap2, bool rm1>
CLS &CLS::mul(const SMatrix<T, cap1, rm1> &A, const SVector<T, cap2> &v) noexcept{
	if constexpr (rowMajor == rm1){
		vL = A.vL;
		hL = 1;
		const int imL = A.hL;
		T sum;
		for(int i=0, j; i<vL; ++i){
			sum = (T)0;
			for(j=0; j<imL; ++j)
				sum += A.data[i*imL+j] * v.data[j];
			data[i] = sum;
		}
	} else{
		vL = 1;
		hL = A.hL;
		const int imL = A.vL;
		T sum;
		for(int i=0, j; i<vL; ++i){
			sum = (T)0;
			for(j=0; j<imL; ++j)
				sum += A.data[j*hL+i] * v.data[j];
			data[i] = sum;
		}
	}
	return *this;
}

TPL template<int cap1, int cap2, bool rm2>
CLS &CLS::mul(const SVector<T, cap1> &v, const SMatrix<T, cap2, rm2> &A) noexcept{
	if constexpr (rowMajor == rm2){
		vL = 1;
		hL = A.hL;
		const int imL = v.len;
		T sum;
		for(int i=0, j; i<hL; ++i){
			sum = (T)0;
			for(j=0; j<imL; ++j)
				sum += v.data[j] * A.data[j*hL+i];
			data[i] = sum;
		}
	} else{
		vL = A.vL;
		hL = 1;
		const int imL = v.len;
		T sum;
		for(int i=0, j; i<hL; ++i){
			sum = (T)0;
			for(j=0; j<imL; ++j)
				sum += v.data[j] * A.data[i*imL+j];
			data[i] = sum;
		}
	}
	return *this;
}

TPL template<int cap1, bool rm1>
CLS &CLS::mul(const SMatrix<T, cap1, rm1> &A, const T &x) noexcept{
	if constexpr (rowMajor == rm1){
		vL = A.vL;
		hL = A.hL;
		const T *end = data + vL*hL;
		for (T *I=data, J=A.data; I!=end; ++I, ++J)
			*I = *J * x;
	} else{
		vL = A.hL;
		hL = A.vL;
		for (int i=0, j; i<vL; ++i)
			for (j=0; j<hL; ++j)
				data[i*hL+j] = A.data[j*vL+i] * x;
	}
	return *this;
}

TPL template<int cap1, bool rm1>
CLS &CLS::div(const SMatrix<T, cap1, rm1> &A, const T &x) noexcept{
	if constexpr (rowMajor == rm1){
		vL = A.vL;
		hL = A.hL;
		const T *end = data + vL*hL;
		for (T *I=data, J=A.data; I!=end; ++I, ++J)
			*I = *J / x;
	} else{
		vL = A.hL;
		hL = A.vL;
		for (int i=0, j; i<vL; ++i)
			for (j=0; j<hL; ++j)
				data[i*hL+j] = A.data[j*vL+i] / x;
	}
	return *this;
}


TPL template<int cap1, bool rm1>
CLS &CLS::transpose(const SMatrix<T, cap1, rm1> &A){
	if constexpr (rowMajor == rm1){
		vL = A.hL;
		hL = A.vL;
		for (int i=0, j; i<vL; ++i)
			for (j=0; j<hL; ++j)
				data[i*hL+j] = A.data[j*vL+i];
	} else{
		vL = A.vL;
		hL = A.hL;
		const T *end = data + vL*hL;
		for (T *I=data, J=A.data; I!=end; ++I, ++J)
			*I = *J;
	}
	return *this;
}

TPL template<int cap1, bool rm1>
CLS &CLS::invert(const SMatrix<T, cap1, rm1> &A){
	vL = A.hL;
	hL = A.vL;
	const T det = determinant(A);
	for (int i=0, j; i<vL; ++i)
		for (j=0; j<vL; ++j)
			data[i*vL+j] = cofactor(A, j, i)/det;
	return *this;
}

TPL template<int cap1, bool rm1>
CLS &CLS::lu_decompose(const SMatrix<T, cap1, rm1> &A){
/*	if constexpr (tr){

	} else{
		rows = cols = A.rows;
		memcpy(data, A.data, rows*rows);

		T factor1, factor2;
		for (int i=0, j, k; i<rows; ++i){
			factor1 = A.data[i*(rows+1)];
			for (j=i+1; j<rows; ++j){
				factor2 = A.data[j*rows+i] / factor1;
				data[j*rows+i] = factor2;
				for (k=i+1; k<rows; ++k)
					data[j*rows+k] -= data[i*rows+k]*factor2;
			}
		}
	}*/
	return *this;
}

TPL template<int cap1, int cap2, bool rm2>
CLS &CLS::lup_decompose(SVector<int, cap1> *P, const SMatrix<T, cap2, rm2> &A){
	return *this;
}


// MATRIX OPERATIONS ON SELF

TPL template<int cap1, bool rm1>
CLS &CLS::post_mul(const SMatrix<T, cap1, rm1> &A){
	return *this;
}

TPL template<int cap1, bool rm1>
CLS &CLS::pre_mul(const SMatrix<T, cap1, rm1> &A){
	return *this;
}

TPL CLS &CLS::square(){
	return *this;
}

TPL CLS &CLS::psquare(){
	return *this;
}

TPL CLS &CLS::transpose(){
	T *tempData = (T *)malloc(vL*hL*sizeof(T));
	memcpy(tempData, data, vL*hL*sizeof(T));

	for (int i=0, j; i<vL; ++i)
		for (j=0; j<hL; ++j)
			data[j*vL+i] = tempData[i*hL+j];

	sp::swap(&vL, &hL);

	free(tempData);
	return *this;
}

TPL CLS &CLS::invert(){
	return *this;
}

TPL CLS &CLS::pinvert(){
	return *this;
}



#undef CLS
#undef TPL


// FREE FUNCTIONS FOR MATRICES

template<class T, int cap1>
inline constexpr SMatrix<T, cap1, false> &tr(SMatrix<T, cap1, true> &A){
	return *(SMatrix<T, cap1, false> *)&A;
}

template<class T, int cap1>
inline constexpr SMatrix<T, cap1, true> &tr(SMatrix<T, cap1, false> &A){
	return *(SMatrix<T, cap1, true> *)&A;
}

template<class T, int cap1, bool rm1>
T determinant(const SMatrix<T, cap1, rm1> &A){
	const int len = A.vL;
	T *tempData = (T *)malloc(len*len*sizeof(T));
	memcpy(tempData, A.data, len*len*sizeof(T));
	
	int32_t sign = 1;
	T factor1, factor2;
	for (int i=0, j, k; i<len-1; ++i){
		k = i;
		for (j=i+1; j<len; ++j)	// find row with max value
			k = abs(tempData[j*len+i])>abs(tempData[k*len+i]) ? j : k;
		if (k != i){
			for (j=i; j<len; ++j)	// exchange top row with row with max value
				sp::swap(&tempData[i*len+j], &tempData[k*len+j]);
			sign ^= 0xfffffffe;
		}
		factor1 = tempData[i*(len+1)];
		for (j=i+1; j<len; ++j){
			factor2 = tempData[j*len+i] / factor1;
			for (k=i+1; k<len; ++k)
				tempData[j*len+k] -= tempData[i*len+k]*factor2;
		}
	}
	factor1 = *tempData * (T)sign;
	for (int i=1; i<len; ++i)
		factor1 *= tempData[i*(len+1)];
	
	free(tempData);
	return factor1;
}

template<class T, int cap1, bool rm1>
T minor(const SMatrix<T, cap1, rm1> &A, const int row, const int column){
	const int len = A.len-1;
	T *tempData = (T *)malloc(len*len*sizeof(T));
	int i, j, k;
	if constexpr (!rm1)
		sp::swap(&row, &column);

	for (i=0; i<row; ++i){	// Make submatrix
		for (j=0; j<column; ++j)
			tempData[i*len+j] = A.data[i*A.len+j];
		for (j=column+1; j<A.len; ++j)
			tempData[i+len+j-1] = A.data[i*A.len+j];
	}
	for (i=row+1; i<A.len; ++i){
		for (j=0; j<column; ++j)
			tempData[i*(len-1)+j] = A.data[i*A.len+j];
		for (j=column+1; j<A.len; ++j)
			tempData[i+(len-1)+j-1] = A.data[i*A.len+j];
	}

	int32_t sign = 1;
	T factor1, factor2;
	for (i=0; i<len-1; ++i){
		k = i;
		for (j=i+1; j<len; ++j)	// find row with max value
			k = abs(tempData[j*len+i])>abs(tempData[k*len+i]) ? j : k;
		if (k != i){
			for (j=i; j<len; ++j)	// exchange top row with row with max value
				sp::swap(&tempData[i*len+j], &tempData[k*len+j]);
			sign ^= 0xfffffffe;
		}

		factor1 = tempData[i*(len+1)];
		for (j=i+1; j<len; ++j){
			factor2 = tempData[j*len+i] / factor1;
			for (k=i+1; k<len; ++k)
				tempData[j*len+k] -= tempData[i*len+k]*factor2;
		}
	}
	factor1 = *tempData * (T)sign;
	for (i=1; i<len; ++i)
		factor1 *= tempData[i*(len+1)];
	
	free(tempData);
	return factor1;
}

template<class T, int cap1, bool rm1>
inline T cofactor(const SMatrix<T, cap1, rm1> &A, const int row, const int column){
	return minor(A, row, column) * (1-(((row+column)&1)>>1));
}

template<class T, int cap1, bool rm1>
int rank(const SMatrix<T, cap1, rm1> &A){
	return 0;
}



template<class T, int cap1, int cap2>
bool operator ==(const SVector<T, cap1> &v, const SVector<T, cap2> &w){
	if (v.len!=w.len)
		return false;
	const T *end = v.data + v.len;
	for (T *I=v.data, *J=w.data; I!=end; ++I){
		if (*I != *J)
			return false;
	}
	return true;
}

template<class T, int cap1, int cap2, bool rm1, bool rm2>
bool operator ==(const SMatrix<T, cap1, rm1> &A, const SMatrix<T, cap2, rm2> &B){
	if (A.rows()!=B.rows() || A.cols()!=B.cols())
		return false;
	if constexpr (rm1 == rm2){
		const T *end = A.data + A.hL*A.vL;
		for (T *I=A.data, *J=B.data; I!=end; ++I)
			if (*I != *J)
				return false;
	} else{
		for (int i=0, j; i<A.vL; ++i)
			for (j=0; j<A.hL; ++j)
				if (A(i, j) != B(i, j))
					return false;
	}
	return true;
}

template<class T, int cap1, bool rm1>
void printM(FILE *const output, const SMatrix<T, cap1, rm1> &A){
	for (int i=0, j; i<A.cols(); ++i){
		for (j=0; j<A.rows(); ++j){
			printf("%8.2lf", A(j, i));
		}
		putchar('\n');
	}
}

template<class T, int cap1, bool rm1>
void printBM(FILE *const output, const SMatrix<T, cap1, rm1> &A);

template<class T, int cap1, bool rm1>
void printMM(FILE *const output, const SMatrix<T, cap1, rm1> &A);


/*void print(FILE *const output, void (*printType)(FILE *, const T &)){
	for(int i=0, j; i<rows; ++i){
		for(j=0; j<cols; ++j)
			printType(output, data[i*cols+j]);
		putc('\n', output);
	}
}*/


}	// END OF NAMESPACE	///////////////////////////////////////////////////////////////////