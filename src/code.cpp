//#include "compiler_v2/ExprParser.hpp"
#include "SPL/Complex.hpp"
#include "SPL/Rational.hpp"
#include "SPL/BigInt.hpp"


	constexpr std::string adadas("dasdas");


int main(){

	constexpr sp::Rational<int8_t> x{-1, 1};
	constexpr sp::Rational<int8_t> y{1, 1};

	constexpr bool dasdas = x < y;


	// z.nom = 462394793494323111;
	// z.den = 4324321;
	// z.simplify();


	printf("x = %u / %u\ny = %u / %u\n\n\n", x.nom, x.den, y.nom, y.den);

	printf("x = %lf\ny = %lf\n", (double)x, (double)y);

	return 0;
}