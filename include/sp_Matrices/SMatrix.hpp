#include "BaseMatrix.hpp"


namespace sp{ // BEGINING OF NAMESPACE //////////////////////////////////////////////////////////////////

namespace priv__{



template<class T, uint32_t outerLen, uint32_t innerLen>
class ProtSMatrix{
public:	
	inline constexpr ProtSMatrix() noexcept {}
	
// SIZE MANIPULATION AND DATA ACCESS
	inline constexpr uint32_t capacity() const;


protected:
	inline constexpr void setSize(const uint32_t outerLength, const uint32_t innerLength) noexcept;

	inline constexpr void flipStorageOrder();

// FLAGS
	static constexpr bool isView = false;

// DATA MEMBERS
public:
	T data[outerLen*innerLen];
protected:
	static constexpr uint32_t outL = outerLen;
	static constexpr uint32_t innL = innerLen;
};






#define TPL template<class T, uint32_t outerLen, uint32_t innerLen>
#define CLS ProtSMatrix<T, outerLen, innerLen>



TPL inline constexpr uint32_t CLS::capacity() const{ 
	return 0;
}



TPL inline constexpr void CLS::setSize(const uint32_t outerLength, const uint32_t innerLength) noexcept{
	
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (outL != outerLength || innL != innerLength){
			fprintf(stderr, "Linear algebra error:   Static matrix cannot be resized.\n");
			exit(2137);
		}
	}
}

TPL inline constexpr void CLS::flipStorageOrder(){
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (outL != innL){
			fprintf(stderr, "Linear algebra error:   Static matrix cannot be resized.\n");
			exit(2137);
		}
	}
}


#undef TPL
#undef CLS



}	// END OF NAMESPACE PRIV

}	// END OF NAMESPACE	///////////////////////////////////////////////////////////////////