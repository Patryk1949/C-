#include "sp_Matrices/Matrix.hpp"
#include "SPL/Print.hpp"
#include <unistd.h>



template<uint32_t... args>
inline constexpr void printArgs(){
	uint32_t i = std::numeric_limits<uint32_t>::max();
	(printf("%u %6.u\n", ++i, args), ...);
} 

template<uint32_t... args>
inline constexpr void sumArgs(){
	printf("%u\n", (args - ...));
}

float func(float x){ return 2*x; }
double func(double x){ return 2*x; }


template<class Mat1>
void pirintMatrixD(const Mat1 &A){
	for (uint32_t i=0; i<A.rows(); ++i){
		for (uint32_t j=0; j<A.cols(); ++j)
			printf("%6.2lf", A(i, j));
		putchar('\n');
	}
}

template<class Mat1>
void pirintMatrixI(const Mat1 &A){
	for (uint32_t i=0; i<A.rows(); ++i){
		for (uint32_t j=0; j<A.cols(); ++j)
			printf("%4d", (int32_t)A(i, j));
		putchar('\n');
	}
}

template<class Mat1>
void pirintMatrixB(const Mat1 &A){
	for (uint32_t i=0; i<A.rows(); ++i){
		for (uint32_t j=0; j<A.cols(); ++j){
			putchar(' ' + A(i, j)*('['-' '));
			putchar(' ' + A(i, j)*(']'-' '));
		}
		putchar('\n');
	}
}

[[nodiscard]] sp::DMatrix<uint8_t> removeIslands(const sp::DMatrix<uint8_t> &A);


int main(){

	sp::DMatrix<uint8_t> A(30, 30);

	// A.load(stdin, [](const char *ptr, char **ptrPtr){
	// 	return (uint8_t)strtol(ptr, ptrPtr, 10);
	// });

	sp::rand32 rd(clock());
	for (auto I=A.data; I!=A.data+A.size(); ++I)
		*I = rd()&1;
	

	pirintMatrixB(A);
	putchar('\n');

	auto B = removeIslands(A);

	pirintMatrixB(B);


	






	return 0;
}


bool validateCell(sp::DMatrix<uint8_t> *const res, const sp::DMatrix<uint8_t> &A, const uint32_t r, const uint32_t c){
	if ((*res)(r, c) || !A(r, c))
		return A(r, c) && (*res)(r, c)!=2;

	(*res)(r, c) = 2;

	return (*res)(r, c) = validateCell(res, A, r, c+1) || validateCell(res, A, r, c-1) ||
		validateCell(res, A, r+1, c) || validateCell(res, A, r-1, c);
}


sp::DMatrix<uint8_t> removeIslands(const sp::DMatrix<uint8_t> &A){
	sp::DMatrix<uint8_t> res(A.rows(), A.cols());
	
	std::fill(res.data+res.cols(), res.data+res.size()-res.cols(), 0);
	for (uint32_t i=0; i<res.cols(); ++i){
		res(0, i) = A(0, i);
		res(res.rows()-1, i) = A(A.rows()-1, i);
	}
	for (uint32_t i=1; i<res.rows()-1; ++i){
		res(i, 0) = A(i, 0);
		res(i, res.cols()-1) = A(i, A.cols()-1);
	}

	for (uint32_t i=1; i<A.rows()-1; ++i){
		for (uint32_t j=1; j<A.cols()-1; ++j)
			validateCell(&res, A, i, j);
		pirintMatrixB(res);
		putchar('\n');
		usleep(500000);
	}
	
	return res;
}