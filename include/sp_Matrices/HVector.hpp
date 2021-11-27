#include "BaseMatrix.hpp"


namespace sp{ // BEGINING OF NAMESPACE //////////////////////////////////////////////////////////////////

namespace priv__{



template<class T, uint32_t cap>
class ProtHVector{
public:
	inline constexpr ProtHVector() noexcept {}

// SIZE MANIPULATION AND DATA ACCESS
	[[nodiscard]] inline constexpr uint32_t size() const;

	[[nodiscard]] inline constexpr uint32_t capacity() const;

	inline constexpr void resize(const uint32_t size) noexcept;


protected:
// FLAGS
	static constexpr bool isView = false;

// DATA MEMBERS
public:
	T data[cap];
protected:
	uint32_t len;
};






#define TPL template<class T, uint32_t cap>
#define CLS ProtHVector<T, cap>



TPL inline constexpr uint32_t CLS::size() const{
	return len;
}

TPL inline constexpr uint32_t CLS::capacity() const{
	return cap;
}



TPL inline constexpr void CLS::resize(const uint32_t size) noexcept{
	if constexpr (SP_MATRIX_DEBUG_MODE){
		if (len > capacity()){
			fprintf(stderr, "Linear algebra error:   Vector has only %d capacity, and it needs at least %d.\n",
				capacity(), size
			);
			exit(2137);
		}
	}

	len = size;
}


#undef TPL
#undef CLS



}	// END OF NAMESPACE PRIV

}	// END OF NAMESPACE	///////////////////////////////////////////////////////////////////