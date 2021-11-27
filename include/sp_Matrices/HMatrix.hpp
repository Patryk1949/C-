#include "BaseMatrix.hpp"


namespace sp{ // BEGINING OF NAMESPACE //////////////////////////////////////////////////////////////////

namespace priv__{



template<class T, uint32_t cap>
class ProtHMatrix{
public:
	inline constexpr ProtHMatrix() noexcept {}

// SIZE MANIPULATION AND DATA ACCESS
	inline constexpr uint32_t capacity() const;


protected:
	inline constexpr void setSize(const uint32_t outerLength, const uint32_t innerLength) noexcept;

	inline constexpr void flipStorageOrder();

// FLAGS
	static constexpr bool isView = false;

// DATA MEMBERS
public:
	T data[cap];
protected:
	uint32_t outL, innL;
};






#define TPL template<class T, uint32_t cap>
#define CLS ProtHMatrix<T, cap>



TPL inline constexpr uint32_t CLS::capacity() const{ 
	return cap;
}



TPL inline constexpr void CLS::setSize(const uint32_t outerLength, const uint32_t innerLength) noexcept{
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (innerLength*outerLength > capacity()){
			fprintf(stderr, "Linear algebra error:   Matrix has only %d capacity, and it needs at least %d.\n",
				capacity(), innerLength*outerLength
			);
			exit(2137);
		}
	}

	outL = outerLength;
	innL = innerLength;
}

TPL inline constexpr void CLS::flipStorageOrder(){
	const uint32_t temp = outL;
	outL = innL;
	innL = temp;
}


#undef TPL
#undef CLS



}	// END OF NAMESPACE PRIV

}	// END OF NAMESPACE	///////////////////////////////////////////////////////////////////