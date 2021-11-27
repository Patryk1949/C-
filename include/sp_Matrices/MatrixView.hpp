#include "BaseMatrix.hpp"


namespace sp{ // BEGINING OF NAMESPACE //////////////////////////////////////////////////////////////////

namespace priv__{



template<class T>	
class ProtMatrixView{
public:
	inline constexpr ProtMatrixView() noexcept : data{nullptr} {}

// SIZE MANIPULATION AND DATA ACCESS
	inline constexpr void setSize(const uint32_t outerLength, const uint32_t innerLength) noexcept;

	inline constexpr void flipStorageOrder();


// VIEW
	inline constexpr void lookAt(T *const dataPtr) noexcept;

// FLAGS
protected:
	static constexpr bool isView = true;

// DATA MEMBERS
public:
	T *data;
protected:
	uint32_t outL, innL;
};






#define TPL template<class T>
#define CLS ProtMatrixView<T>



TPL inline constexpr void CLS::setSize(const uint32_t outerLength, const uint32_t innerLength) noexcept{
	outL = outerLength;
	innL = innerLength;
}

TPL inline constexpr void CLS::flipStorageOrder(){
	const uint32_t temp = outL;
	outL = innL;
	innL = temp;
}

TPL inline constexpr void CLS::lookAt(T *const dataPtr) noexcept{
	data = dataPtr;
}


#undef TPL
#undef CLS



}	// END OF NAMESPACE PRIV

}	// END OF NAMESPACE	///////////////////////////////////////////////////////////////////