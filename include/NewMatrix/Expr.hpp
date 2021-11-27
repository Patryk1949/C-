#include <type_traits>
#include <functional>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "SPL/Utils.hpp"

namespace sp{ // BEGINING OF NAMESPACE //////////////////////////////////////////////////////////////////

constexpr uint32_t CacheSize = 32768;
constexpr uint32_t CachePage = 64;
constexpr uint32_t CacheAvalible = 4*CacheSize / 2;

namespace priv__{

struct MFlags{
	enum : uint32_t{
		Real=1, RowMajor=2, MixedMajor=4
	};
};

template<class Base>
struct MExpr : Base{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnarrowing"
	template<class... Args>
	MExpr(Args&&... args) noexcept : Base{std::forward<Args>(args)...} {}
#pragma GCC diagnostic pop
	
// FLAGS
/*	typedef typename type;
	static constexpr bool isReal;
	static constexpr bool isVector;
	static constexpr bool isRowMajor;
*/

// type operator ()(uint32_t row, uint32_t col);	<- can be const or can return by reference

	template<class Mat1>
	constexpr Base &operator =(const MExpr<Mat1> &rhs){	// SOMETIMES USE BLOCKING
		this->resize(rhs.rows(), rhs.cols());
		for (uint32_t i=0; i<rhs.rows(); ++i)
			for (uint32_t j=0; j<rhs.cols(); ++j)
				(*this)(i, j) = rhs(i, j);
		return *this;
	}

	template<class Mat1>
	constexpr Base &operator =(MExpr<Mat1> &&rhs){
		if constexpr (Mat1::flags & MFlags::Real){
			// MOVE
		} else{		// DO THIS, BUT ALSO USE BLOCKING AND HANDLE OPERATIONS THAT NEED AXULARY STORAGE
			this->resize(rhs.rows(), rhs.cols());
			constexpr uint32_t StorageAvalible = CacheAvalible / sizeof(typename Base::type);
			constexpr uint32_t StoragePage = CachePage / sizeof(typename Base::type);
			constexpr uint32_t blockSize = sp::intSqrt(StorageAvalible / (Mat1::lvCount + 1)) / StoragePage * StoragePage;
			uint32_t ii, jj;
			for (ii=blockSize; ii<this->rows(); ii+=blockSize){
				for (jj=blockSize; jj<this->cols(); jj+=blockSize)
					for(uint32_t i=ii-blockSize; i<ii; ++i)
						for(uint32_t j=jj-blockSize; j<jj; ++j)
							(*this)(i, j) = rhs(i, j);
				for(uint32_t i=ii-blockSize; i<ii; ++i)
					for(uint32_t j=jj-blockSize; j<this->cols(); ++j)
						(*this)(i, j) = rhs(i, j);
			}
			for (jj=blockSize; jj<this->cols(); jj+=blockSize)
				for(uint32_t i=ii-blockSize; i<this->rows(); ++i)
					for(uint32_t j=jj-blockSize; j<jj; ++j)
						(*this)(i, j) = rhs(i, j);
			for(uint32_t i=ii-blockSize; i<this->rows(); ++i)
				for(uint32_t j=jj-blockSize; j<this->cols(); ++j)
					(*this)(i, j) = rhs(i, j);
		}
		return *this;
	}

};


}	// END OF NAMESPACE PRIV

}	// END OF NAMESPACE	///////////////////////////////////////////////////////////////////