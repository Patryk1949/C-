#include "BaseMatrix.hpp"



namespace sp{ // BEGINING OF NAMESPACE //////////////////////////////////////////////////////////////////

namespace priv__{


template<class Prot, class T>
class Vector : public Prot {
public:
// GENERAL DATA METHODS
	inline constexpr Vector() noexcept;

	inline constexpr Vector(const uint32_t size) noexcept;

	template<class Vec1>
	Vector(const Vec1 &A) noexcept;
	template<class Vec1>
	Vector(Vec1 &A) noexcept;

	template<class Vec1>
	Vector(Vec1 &&A) noexcept;
	
	
	
	template<class Vec1>
	Vector &operator =(const Vec1 &A) noexcept;
	template<class Vec1>
	Vector &operator =(Vec1 &A) noexcept;

	template<class Vec1>
	Vector &operator =(Vec1 &&A) noexcept;


// SIZE AND DATA FUNCTIONS
	inline constexpr const T &operator ()(const uint32_t index) const noexcept;

	inline constexpr T &operator ()(const uint32_t index) noexcept;

	inline constexpr const T &operator [](const uint32_t index) const noexcept;

	inline constexpr T &operator [](const uint32_t index) noexcept;





// INITIALIZATION
	void init(T (*func)());
	
	void init(T (*func)(uint32_t));

	template<class Arg>
	void init(T (*func)(const Arg &, uint32_t), const Arg &funcArg);
	
	template<uint32_t maxLineLength = 512>
	bool load(FILE *const input, T (*stringToType)(const char *, char **));
	
	template<uint32_t maxLineLength = 512>
	bool load(FILE *const input, T (*stringToType)(const char *, char **), const uint32_t indexNumber);


// GENERAL VECTOR OPERATIONS
	template<class Vec1, class Vec2>
	Vector &add(const Vec1 &A, const Vec2 &B) noexcept;
	
	template<class Vec1, class Vec2>
	Vector &sub(const Vec1 &A, const Vec2 &B) noexcept;
	
	template<class Vec1, class Vec2>
	Vector &elMul(const Vec1 &A, const Vec2 &B) noexcept;

	template<class Vec1, class Vec2>
	Vector &elDiv(const Vec1 &A, const Vec2 &B) noexcept;


	template<class Vec1>
	Vector &mul(const Vec1 &A, const T &x) noexcept;
	
	template<class Vec1>
	Vector &div(const Vec1 &A, const T &x) noexcept;

// VECTOR OPERATIONS WITH MATRICES
/*	template<class Mat1, class Vec2>
	Vector &add(const Mat1 &A, const Vec2 &B) noexcept;
	
	template<class Mat1, class Vec2>
	Vector &sub(const Vec1 &A, const Vec2 &B) noexcept;
	
	template<class Mat1, class Vec2>
	Vector &elMul(const Vec1 &A, const Vec2 &B) noexcept;

	template<class Mat1, class Vec2>
	Vector &elDiv(const Vec1 &A, const Vec2 &B) noexcept;


	template<class Vec1>
	Vector &mul(const Vec1 &A, const T &x) noexcept;
	
	template<class Vec1>
	Vector &div(const Vec1 &A, const T &x) noexcept;*/
	
	


//	template<class Vec1>
//	Vector &lu_decompose(const Vec1 &A);

//	template<uint32_t cap1, uint32_t cap2, bool rm2>
//	Vector &lup_decompose(SVector<uint32_t, cap1> *P, const Vector<T, cap2, rm2> &A);


// VECTOR OPERATIONS ON SELF
};



}	// END OF NAMESPACE PRIV






using namespace priv__;

template<class Prot, class T>
uint32_t rank(const Vector<Prot, T> &A);


template<class T, class Prot1, class Prot2>
[[nodiscard]] T innerProd(const Vector<T, Prot1> &A, const Vector<T, Prot2> &B) noexcept;


//template<class T, class Prot1, class Prot2>
//[[no_discard]] T crossProd(const Vector<T, Prot1> &A, const Vector<T, Prot2> &B) noexcept;



template<class T, class Prot1, class Prot2>
[[nodiscard]] bool operator ==(const Vector<T, Prot1> &A, const Vector<T, Prot2> &B);



template<class Vec1>
void printHorV(FILE *const output, const Vec1 &A);

template<class Vec1>
void printVerV(FILE *const output, const Vec1 &A);

template<class Vec1>
void printBV(FILE *const output, const Vec1 &A);

template<class Vec1>
void printMV(FILE *const output, const Vec1 &A);








namespace priv__{

#define TPL template<class Prot, class T>
#define CLS Vector<Prot, T>


TPL inline constexpr CLS::Vector() noexcept : Prot(){
	this->resize(0);
}

TPL inline constexpr CLS::Vector(const uint32_t size) noexcept{
	this->resize(size);
}

TPL template<class Vec1>
CLS::Vector(const Vec1 &A) noexcept{
//	if constexpr (this->isView()){
//		this->lookAt(A);	
//	} else{
		this->resize(A.size());
		memcpy(this->data, A.data, this->size()*sizeof(T));
//	}
}
TPL template<class Vec1>
CLS::Vector(Vec1 &A) noexcept{
//	if constexpr (this->isView()){
//		this->lookAt(A);	
//	} else{
		this->resize(A.size());
		memcpy(this->data, A.data, this->size()*sizeof(T));
//	}
}

TPL template<class Vec1>
CLS::Vector(Vec1 &&A) noexcept{
	static_assert(!A.isView(), "Vector View can't be moved.");
	
	this->moveDataToThis(A.moveDataFromThis());
	this->resize(A.size());
}

TPL template<class Vec1>
CLS &CLS::operator =(const Vec1 &A) noexcept{
//	if constexpr (this->isView()){
//		this->lookAt(A);	
//	} else{
		this->resize(A.size());
		memcpy(this->data, A.data, this->size()*sizeof(T));
//	}
	return *this;
}
TPL template<class Vec1>
CLS &CLS::operator =(Vec1 &A) noexcept{
//	if constexpr (this->isView()){
//		this->lookAt(A);	
//	} else{
		this->resize(A.size());
		memcpy(this->data, A.data, this->size()*sizeof(T));
//	}
	return *this;
}

TPL template<class Vec1>
CLS &CLS::operator =(Vec1 &&A) noexcept{
	static_assert(!A.isView(), "Vector View can't be moved.");
	
	this->moveDataToThis(A.moveDataFromThis());
	this->resize(A.size());
	return *this;
}




TPL inline constexpr const T &CLS::operator ()(const uint32_t index) const noexcept{
	return this->data[index];
}

TPL inline constexpr T &CLS::operator ()(const uint32_t index) noexcept{
	return this->data[index];
}

TPL inline constexpr const T &CLS::operator [](const uint32_t index) const noexcept{
	return this->data[index];
}

TPL inline constexpr T &CLS::operator [](const uint32_t index) noexcept{
	return this->data[index];
}






TPL void CLS::init(T (*func)()){
	const T *const end = this->data + this->size();
	for (T *I=this->data; I!=end; ++I)
		*I = func();
}

TPL void CLS::init(T (*func)(uint32_t)){
	for (uint32_t i=0; i<this->size(); ++i)
		this->data[i] = func(i);
}

TPL template<class Arg>
void CLS::init(T (*func)(const Arg &, uint32_t), const Arg &funcArg){
	for (uint32_t i=0; i<this->size(); ++i)
		this->data[i] = func(funcArg, i);
}

TPL template<uint32_t maxLineLength>
bool CLS::load(FILE *const input, T (*stringToType)(const char *, char **)){
	char line[maxLineLength];
	char *linePointer = line;

	fgets(line, maxLineLength, input);
	if(*line=='\n' || feof(input))
		return false;
	
	uint32_t i;
	for (i=0; true; ++i){
		if(*linePointer=='\n')
			break;
		this->data[i] = stringToType(linePointer, &linePointer);
	}
	this->resize(i+1);
	return true;
}

TPL template<uint32_t maxLineLength>
bool CLS::load(FILE *const input, T (*stringToType)(const char *, char **), const uint32_t size){
	char line[maxLineLength];
	char *linePointer = line;
	this->resize(size);
	fgets(line, maxLineLength, input);

	const T*const end = this->data + this->size();
	for (T *I=this->data; I!=end; ++I){
		*I = stringToType(linePointer, &linePointer);
		if(*line=='\n' || feof(input))
			return false;
	}
	return true;
}


// STANDARD MATRIX OPERATIONS
TPL template<class Vec1, class Vec2>
CLS &CLS::add(const Vec1 &A, const Vec2 &B) noexcept{
	this->resize(A.size());
	const T *const end = this->data + this->size();
	const T *J=A.data, *K=B.data;
	for (T *I=this->data; I!=end; ++I, ++J, ++K)
		*I = *J + *K;

	return *this;
}

TPL template<class Vec1, class Vec2>
CLS &CLS::sub(const Vec1 &A, const Vec2 &B) noexcept{
	this->resize(A.size());
	const T *const end = this->data + this->size();
	const T *J=A.data, *K=B.data;
	for (T *I=this->data; I!=end; ++I, ++J, ++K)
		*I = *J - *K;
		
	return *this;
}

TPL template<class Vec1, class Vec2>
CLS &CLS::elMul(const Vec1 &A, const Vec2 &B) noexcept{
	this->resize(A.size());
	const T *const end = this->data + this->size();
	const T *J=A.data, *K=B.data;
	for (T *I=this->data; I!=end; ++I, ++J, ++K)
		*I = *J * *K;
		
	return *this;
}

TPL template<class Vec1, class Vec2>
CLS &CLS::elDiv(const Vec1 &A, const Vec2 &B) noexcept{
	this->resize(A.size());
	const T *const end = this->data + this->size();
	const T *J=A.data, *K=B.data;
	for (T *I=this->data; I!=end; ++I, ++J, ++K)
		*I = *J / *K;
		
	return *this;
}


TPL template<class Vec1>
CLS &CLS::mul(const Vec1 &A, const T &x) noexcept{
	this->resize(A.size());
	const T *const end = this->data + this->size();
	const T *J = A.data;
	for (T *I=this->data; I!=end; ++I, ++J)
		*I = *J * x;
		
	return *this;
}

TPL template<class Vec1>
CLS &CLS::div(const Vec1 &A, const T &x) noexcept{
	this->resize(A.size());
	const T *const end = this->data + this->size();
	const T *J = A.data;
	for (T *I=this->data; I!=end; ++I, ++J)
		*I = *J / x;
		
	return *this;
}




// VECTOR OPERATIONS ON SELF



#undef CLS
#undef TPL

}	// END OF NAMESPACE PRIV











template<class T, class Prot1, class Prot2>
T innerProd(const Vector<T, Prot1> &A, const Vector<T, Prot2> &B) noexcept{
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (A.length() != B.length())
			throw std::domain_error("Only square matrix can be squared.\nMaybe try pSuqare.");
	}

	T resoult = (T)0;
	const T *const end = A.data + A.size();
	for (T *I=A.data, *J=B.data; I!=end; ++I, ++J)
		resoult += *I * *J;
	return resoult; 
}


template<class T, class Prot1, class Prot2>
bool operator ==(const Vector<T, Prot1> &A, const Vector<T, Prot2> &B){
	if (A.size()!=B.size())
		return false;
	const T *const end = A.data + A.size();
	for (T *I=A.data, *J=B.data; I!=end; ++I, ++J)
		if (*I != *J)
			return false;
	return true;
}

/*
template<class T, uint32_t cap1, bool rm1>
void printM(FILE *const output, const ProtHVector<T, cap1, rm1> &A){
	for (uint32_t i=0, j; i<A.cols(); ++i){
		for (j=0; j<A.rows(); ++j){
			
				printf("%8.2lf", A(j, i));
		}
		putchar('\n');
	}
}

template<class T, uint32_t cap1, bool rm1>
void printBM(FILE *const output, const ProtHVector<T, cap1, rm1> &A);

template<class T, uint32_t cap1, bool rm1>
void printMM(FILE *const output, const ProtHVector<T, cap1, rm1> &A);*/




}	// END OF NAMESPACE	///////////////////////////////////////////////////////////////////