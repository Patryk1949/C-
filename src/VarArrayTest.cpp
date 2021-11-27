#include "SPL/Complex.hpp"
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <memory>
#include <deque>
#include "SPL/Polynomial.hpp"
#include <array>


template<class T>
void printPolynomial(const T &P){
	typedef typename T::value_type valType;
	if constexpr (std::is_integral_v<valType>){
		for (uint32_t i=0; i<std::size(P); ++i)
			printf("%6.d", (int)P[i]);
	} else if constexpr (std::is_floating_point_v<valType>){
		for (uint32_t i=0; i<std::size(P); ++i)
			printf("%8.2f", (float)P[i]);
	} else{
		constexpr bool b = true;
		static_assert(b, "Canot print polynomial of this type.");
	}

	putchar('\n');
}

template<class T>
void printCPolynomial(const T &P){
	for (uint32_t i=0; i<std::size(P); ++i)
		printf("(%8.2f,%8.2f)  ", (float)P[i].real, (float)P[i].imag);

	putchar('\n');
}

int main(){
	{	
		sp::Polynomial<sp::DArray<sp::Complex<double>>> P1{{{33.0}, {1.0}, {-11.0}, {2.0}, {-7.0}}};
		sp::Polynomial<sp::DArray<sp::Complex<double>>> P2{{{-32.0}, {-3.0}}};

		sp::Polynomial<sp::DArray<sp::Complex<double>>> P3{{{1.0}, {2.0}}};
		sp::Polynomial<sp::DArray<double>> P4;


	typedef sp::Polynomial<sp::DArray<double>> Pol;

	P4 = Pol{{1.0, 1.0/1.0}} * Pol{{1.0, 1.0/2.0}} * Pol{{1.0, 1.0/3.0}} * Pol{{1.0, 1.0/4.0}} * Pol{{1.0, 1.0/5.0}} * Pol{{1.0, 1.0/6.0}} * Pol{{1.0, 1.0/7.0}} * Pol{{1.0, 1.0/8.0}} * Pol{{1.0, 1.0/9.0}} * Pol{{1.0, 1.0/10.0}}
		* Pol{{1.0, 1.0/11.0}} * Pol{{1.0, 1.0/12.0}} * Pol{{1.0, 1.0/13.0}} * Pol{{1.0, 1.0/14.0}} * Pol{{1.0, 1.0/15.0}} * Pol{{1.0, 1.0/16.0}} * Pol{{1.0, 1.0/17.0}} * Pol{{1.0, 1.0/18.0}} * Pol{{1.0, 1.0/19.0}} * Pol{{1.0, 1.0/20.0}};
		
	//	auto x = (P1 * P2)({2.0, 0});


		// printPolynomial(P1);
		// printPolynomial(P2);
		// putchar('\n');

		// sp::divideInplace(P3, P1, P2);

		// printPolynomial(P3);
		// printPolynomial(P1);

		printPolynomial(P4);
		sp::DArray<double> roots;

		const bool noRootsFlag = sp::findRoots(roots, P4, 0.001);
		std::sort(std::begin(roots), std::end(roots));

		putchar('\n');
		// for (auto I : roots) printf("(%8.2f,%8.2f)  ", (float)I.real, (float)I.imag);
		for (auto I : roots) printf("%8.2f  ", (float)I);
		putchar('\n');

		if (noRootsFlag){
			puts("cannot find the root");
			return 1;
		}

		sizeof(FILE);


		// P2 += P1 * P1;

		// printPolynomial(P2);


		// sp::Ratiomial<sp::Polynomial<sp::DArray<float>>> R1{P1, P2};
		// printPolynomial(R1.nom);
		// printPolynomial(R1.den);
		// putchar('\n');
		// sp::Ratiomial<> R2{P3, P4};
		// printPolynomial(R2.nom);
		// printPolynomial(R2.den);
		// putchar('\n');
		// putchar('\n');

		// R2 *= sp::diff(R1);

		// printPolynomial(R2.nom);
		// printPolynomial(R2.den);

//		printf("\n\n%lf\n", (R1 + R1 * R2)(2));
	}

	return 0;
}