

namespace sp{ // BEGINING OF NAMESPACE //////////////////////////////////////////////////////////////////

namespace priv__{


template<class T, bool rowMajor, uint32_t cap>
struct MBaseHybryid{
// FLAGS
	typedef T type;
	static constexpr uint32_t flags = MFlags::Real | (rowMajor << 1);
	static constexpr uint32_t lvCount = 1;

// ACCESS
	inline constexpr type &operator ()(const uint32_t row, const uint32_t col) noexcept{
		if constexpr (rowMajor) return dat[row*innL + col]; else return dat[row + col*innL];
	}
	[[nodiscard]] inline constexpr const type &operator ()(const uint32_t row, const uint32_t col) const noexcept{
		if constexpr (rowMajor) return dat[row*innL + col]; else return dat[row + col*innL];
	}
	inline constexpr type &operator [](const uint32_t index) noexcept{ return dat[index]; }
	[[nodiscard]] inline constexpr const type &operator [](const uint32_t index) const noexcept{ return dat[index]; }

// GETTERS++
	[[nodiscard]] inline constexpr uint32_t innLen() const noexcept{ return innL; }
	[[nodiscard]] inline constexpr uint32_t outLen() const noexcept{ return outL; }
	[[nodiscard]] inline constexpr uint32_t capacity() const noexcept{ return cap; }

	[[nodiscard]] inline constexpr uint32_t rows() const noexcept{ return rowMajor ? outL : innL; }
	[[nodiscard]] inline constexpr uint32_t cols() const noexcept{ return rowMajor ? innL : outL; }
	[[nodiscard]] inline constexpr uint32_t size() const noexcept{ return innL * outL; }

	inline constexpr type *const data() noexcept{ return dat; }
	[[nodiscard]] inline constexpr const type *const data() const noexcept{ return dat; }
	inline constexpr type *const begin() noexcept{ return dat; }
	[[nodiscard]] inline constexpr const type *const begin() const noexcept{ return dat; }
	inline constexpr type *const end() noexcept{ return dat + innL*outL; }
	[[nodiscard]] inline constexpr const type *const end() const noexcept{ return dat + innL*outL; }

// SETTERS
	inline constexpr void resize(const uint32_t rows, const uint32_t cols){
		if constexpr (rowMajor){ innL = cols; outL = rows; } else{ innL = rows; outL = cols; }
	}


// DATA MEMBERS
private:
	uint32_t innL = 0;
	uint32_t outL = 0;
	T dat[cap];
};


}	// END OF NAMESPACE PRIV

}	// END OF NAMESPACE	///////////////////////////////////////////////////////////////////