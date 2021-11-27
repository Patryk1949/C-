#include "BaseMatrix.hpp"


namespace sp{ // BEGINING OF NAMESPACE //////////////////////////////////////////////////////////////////

namespace priv__{


template<class T>
class ProtDMatrix{
public:
	inline constexpr ProtDMatrix() noexcept : data{0}, cap{0} {}
	~ProtDMatrix();
// SIZE MANIPULATION AND DATA ACCESS
	inline constexpr uint32_t capacity() const;


protected:
	inline constexpr void setSize(const uint32_t outerLength, const uint32_t innerLength) noexcept;

	template<bool rm1>
	inline constexpr void swapData(Matrix<ProtDMatrix, T, rm1> &&A) noexcept;

	inline constexpr void flipStorageOrder();

// FLAGS
	static constexpr bool isView = false;

// DATA MEMBERS
public:
	T *data;
protected:
	uint32_t outL, innL, cap;
};






#define TPL template<class T>
#define CLS ProtDMatrix<T>


TPL CLS::~ProtDMatrix(){
	if (data)
		free(data);
}



TPL inline constexpr uint32_t CLS::capacity() const{
	return cap;
}



TPL inline constexpr void CLS::setSize(const uint32_t outerLength, const uint32_t innerLength) noexcept{
	outL = outerLength;
	innL = innerLength;
	const uint32_t reqSize = outL*innL;
	if (capacity() < reqSize){
		if (data)
			free(data);
		data = (T *)malloc(reqSize*sizeof(T));
		cap = reqSize;
	}
}

TPL template<bool rm1>
inline constexpr void CLS::swapData(Matrix<ProtDMatrix, T, rm1> &&A) noexcept{
	sp::swap(&data, &A.data);
	sp::swap(&outL, &A.outL);
	sp::swap(&innL, &A.innL);
	sp::swap(&cap, &A.cap);
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