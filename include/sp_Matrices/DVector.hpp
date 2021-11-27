#include "BaseMatrix.hpp"


namespace sp{ // BEGINING OF NAMESPACE //////////////////////////////////////////////////////////////////

namespace priv__{



template<class T>
class ProtDVector{
public:
	inline constexpr ProtDVector() noexcept : data{0}, cap{0} {}
	~ProtDVector();

// SIZE MANIPULATION AND DATA ACCESS
	[[nodiscard]] inline constexpr uint32_t size() const;

	[[nodiscard]] inline constexpr uint32_t capacity() const;

	inline constexpr void resize(const uint32_t size) noexcept;


protected:
// FLAGS
	static constexpr bool isView = false;

// DATA MEMBERS
public:
	T *data;
protected:
	uint32_t len, cap;
};






#define TPL template<class T>
#define CLS ProtDVector<T>



TPL CLS::~ProtDVector(){
	if (data)
		free(data);
}

TPL inline constexpr uint32_t CLS::size() const{
	return len;
}

TPL inline constexpr uint32_t CLS::capacity() const{
	return cap;
}



TPL inline constexpr void CLS::resize(const uint32_t size) noexcept{
	len = size;
	if (cap < len){
		if (data)
			free(data);
		data = (T *)malloc(len*sizeof(T));
		cap = len;
	}
}


#undef TPL
#undef CLS



}	// END OF NAMESPACE PRIV

}	// END OF NAMESPACE	///////////////////////////////////////////////////////////////////