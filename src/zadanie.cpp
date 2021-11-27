#define SP_MATRIX_DEBUG

#include "matrix/Initializators.hpp"
#include "SPL/Arrays.hpp"
#include <stdio.h>
#include <assert.h>
#include <complex>
#include "SPL/BigInt.hpp"


template<SP_MATRIX_T(M)>
void pirintMatrix(M &&A){
	for (size_t i=0; i!=sp::rows(A); ++i){
		for (size_t j=0; j!=sp::cols(A); ++j)
			printf("%7.2lf", (double)A(i, j));
		putchar('\n');
	}
}


int main(){
	sp::MatrixWrapper<sp::priv__::MatrixHybrid<double, false, 128>> A;
	sp::MatrixWrapper<sp::priv__::MatrixHybrid<double, true, 128>> B, C, D, E;
	sp::DArray<uint32_t> permuts;
	
	auto rng = [rng=sp::Rand32{1}](size_t i, size_t j) mutable{ return (double)(rng() % 5); };

	A = sp::generate(3, 3, rng);
	A = cp(A) * tr(cp(A));
	B = A;
//	sp::invert(B);
	sp::choleskyDecompose(B);
	D = B;
	sp::extractLower(C, D);
	sp::extractUpper(E, D);


	pirintMatrix(A);
	putchar('\n');
	pirintMatrix(B);
	putchar('\n');
	pirintMatrix(C);
	putchar('\n');
	pirintMatrix(D);
	putchar('\n');
	pirintMatrix(C * D * tr(C));
	putchar('\n');



	return 0;
}