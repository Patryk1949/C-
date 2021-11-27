namespace sp{ // BEGINING OF NAMESPACE //////////////////////////////////////////////////////////////////

namespace priv__{



template<class T>
class ProtVectorView{
public:
	inline constexpr ProtVectorView() noexcept : data{nullptr} {}

// SIZE MANIPULATION AND DATA ACCESS
	[[nodiscard]] inline constexpr uint32_t size() const;

	inline constexpr void resize(const uint32_t size) noexcept;

// VIEW
	inline constexpr void lookAt(T *const dataPtr) noexcept;

// FLAGS
protected:
	static constexpr bool isView = true;

// DATA MEMBERS
public:
	T *data;
protected:
	uint32_t len;
};






#define TPL template<class T>
#define CLS ProtVectorView<T>



TPL inline constexpr uint32_t CLS::size() const{
	return len;
}

TPL inline constexpr void CLS::resize(const uint32_t size) noexcept{
	len = size;
}


TPL inline constexpr void CLS::lookAt(T *const dataPtr) noexcept{
	data = dataPtr;
}


#undef TPL
#undef CLS



}	// END OF NAMESPACE PRIV

}	// END OF NAMESPACE	///////////////////////////////////////////////////////////////////