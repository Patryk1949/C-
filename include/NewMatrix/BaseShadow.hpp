#include "SPL/Utils.hpp"


namespace sp{ // BEGINING OF NAMESPACE //////////////////////////////////////////////////////////////////

namespace priv__{

template<class T, bool rowMajor>
struct MBaseDynamicShadowStateless{
// CONSTRUCTOR
	MBaseDynamicShadowStateless(T (*func)(const uint32_t, const uint32_t), const uint32_t rows, const uint32_t cols) noexcept : function{func}, rowsL{rows}, colsL{cols} {}

// FLAGS
	typedef T type;
	static constexpr bool isReal = false;
	static constexpr bool isVector = false;
	static constexpr bool isRowMajor = rowMajor;

// ACCESS
	[[nodiscard]] inline constexpr type operator ()(const uint32_t row, const uint32_t col) const noexcept{
		return function(row, col);
	}
	[[nodiscard]] inline constexpr type operator [](const uint32_t index) const noexcept{
		const uint32_t r = isRowMajor ? index / colsL : index % rowsL;
		const uint32_t c = isRowMajor ? index % colsL : index / rowsL;
		return function(r, c);
	}

// GETTERS++
	[[nodiscard]] inline constexpr uint32_t innLen() const noexcept{ return isRowMajor ? colsL : rowsL; }
	[[nodiscard]] inline constexpr uint32_t outLen() const noexcept{ return isRowMajor ? rowsL : colsL; }
	[[nodiscard]] inline constexpr uint32_t capacity() const noexcept{ return 0; }

	[[nodiscard]] inline constexpr uint32_t rows() const noexcept{ return rowsL; }
	[[nodiscard]] inline constexpr uint32_t cols() const noexcept{ return colsL; }
	[[nodiscard]] inline constexpr uint32_t size() const noexcept{ return rowsL * colsL; }

// SETTERS
	inline constexpr void resize(const uint32_t rows, const uint32_t cols){ rowsL=rows; colsL=cols; }


// DATA MEMBERS
public:
	T (*function)(const uint32_t, const uint32_t);
private:
	uint32_t rowsL;
	uint32_t colsL;
};

template<class Func, bool rowMajor>
struct MBaseDynamicShadow{
// CONSTRUCTOR
	MBaseDynamicShadow(Func &func, const uint32_t rows, const uint32_t cols) noexcept : object{&func}, rowsL{rows}, colsL{cols} {}

// FLAGS
	typedef typename std::invoke_result<Func>::type type;
	static constexpr bool isReal = false;
	static constexpr bool isVector = false;
	static constexpr bool isRowMajor = rowMajor;

// ACCESS
	[[nodiscard]] inline constexpr type operator ()(const uint32_t row, const uint32_t col) noexcept{
		return (*object)(row, col);
	}
	[[nodiscard]] inline constexpr type operator [](const uint32_t index) noexcept{
		const uint32_t r = isRowMajor ? index / colsL : index % rowsL;
		const uint32_t c = isRowMajor ? index % colsL : index / rowsL;
		return (*object)(r, c);
	}

// GETTERS++
	[[nodiscard]] inline constexpr uint32_t innLen() const noexcept{ return isRowMajor ? colsL : rowsL; }
	[[nodiscard]] inline constexpr uint32_t outLen() const noexcept{ return isRowMajor ? rowsL : colsL; }
	[[nodiscard]] inline constexpr uint32_t capacity() const noexcept{ return 0; }

	[[nodiscard]] inline constexpr uint32_t rows() const noexcept{ return rowsL; }
	[[nodiscard]] inline constexpr uint32_t cols() const noexcept{ return colsL; }
	[[nodiscard]] inline constexpr uint32_t size() const noexcept{ return rowsL * colsL; }

// SETTERS
	inline constexpr void resize(const uint32_t rows, const uint32_t cols){ rowsL=rows; colsL=cols; }


// DATA MEMBERS
public:
	Func *object;
private:
	uint32_t rowsL;
	uint32_t colsL;
};



template<class T, uint32_t rowsL, uint32_t colsL, bool rowMajor>
struct MBaseStaticShadowStateless{
// CONSTRUCTOR
	MBaseStaticShadowStateless(T (*func)(const uint32_t, const uint32_t)) noexcept : function{func} {}

// FLAGS
	typedef T type;
	static constexpr bool isReal = false;
	static constexpr bool isVector = false;
	static constexpr bool isRowMajor = rowMajor;

// ACCESS
	[[nodiscard]] inline constexpr type operator ()(const uint32_t row, const uint32_t col) const noexcept{
		return function(row, col);
	}
	[[nodiscard]] inline constexpr type operator [](const uint32_t index) const noexcept{
		const uint32_t r = isRowMajor ? index / colsL : index % rowsL;
		const uint32_t c = isRowMajor ? index % colsL : index / rowsL;
		return function(r, c);
	}

// GETTERS++
	[[nodiscard]] inline constexpr uint32_t innLen() const noexcept{ return isRowMajor ? colsL : rowsL; }
	[[nodiscard]] inline constexpr uint32_t outLen() const noexcept{ return isRowMajor ? rowsL : colsL; }
	[[nodiscard]] inline constexpr uint32_t capacity() const noexcept{ return 0; }

	[[nodiscard]] inline constexpr uint32_t rows() const noexcept{ return rowsL; }
	[[nodiscard]] inline constexpr uint32_t cols() const noexcept{ return colsL; }
	[[nodiscard]] inline constexpr uint32_t size() const noexcept{ return rowsL * colsL; }

// SETTERS
	inline constexpr void resize(const uint32_t rows, const uint32_t cols){}


// DATA MEMBERS
public:
	T (*function)(const uint32_t, const uint32_t);
};


template<class Func, uint32_t rowsL, uint32_t colsL, bool rowMajor>
struct MBaseStaticShadow{
// CONSTRUCTOR
	MBaseStaticShadow(Func &func) noexcept : object{&func} {}

// FLAGS
	typedef typename std::invoke_result<Func>::type type;
	static constexpr bool isReal = false;
	static constexpr bool isVector = false;
	static constexpr bool isRowMajor = rowMajor;

// ACCESS
	[[nodiscard]] inline constexpr type operator ()(const uint32_t row, const uint32_t col) noexcept{
		return (*object)(row, col);
	}
	[[nodiscard]] inline constexpr type operator [](const uint32_t index) noexcept{
		const uint32_t r = isRowMajor ? index / colsL : index % rowsL;
		const uint32_t c = isRowMajor ? index % colsL : index / rowsL;
		return (*object)(r, c);
	}

// GETTERS++
	[[nodiscard]] inline constexpr uint32_t innLen() const noexcept{ return isRowMajor ? colsL : rowsL; }
	[[nodiscard]] inline constexpr uint32_t outLen() const noexcept{ return isRowMajor ? rowsL : colsL; }
	[[nodiscard]] inline constexpr uint32_t capacity() const noexcept{ return 0; }

	[[nodiscard]] inline constexpr uint32_t rows() const noexcept{ return rowsL; }
	[[nodiscard]] inline constexpr uint32_t cols() const noexcept{ return colsL; }
	[[nodiscard]] inline constexpr uint32_t size() const noexcept{ return rowsL * colsL; }

// SETTERS
	inline constexpr void resize(const uint32_t rows, const uint32_t cols){}


// DATA MEMBERS
public:
	Func *object;
};



template<class T, uint32_t rowsL, uint32_t colsL, bool rowMajor>
struct MBaseConstShadowStateless{
// CONSTRUCTOR
	MBaseConstShadow(T func(uint32_t, uint32_t)) noexcept : object{func} {}

// FLAGS
	typedef typename TypeTernary<std::is_invocable<T>::value, decltype(T{}(0u, 0u)), T>::type type;
	static constexpr bool isReal = false;
	static constexpr bool isVector = false;
	static constexpr bool isRowMajor = rowMajor;

// ACCESS
	[[nodiscard]] inline constexpr type operator ()(const uint32_t row, const uint32_t col) noexcept{
		return object(row, col);
	}
	[[nodiscard]] inline constexpr type operator [](const uint32_t index) noexcept{
		const uint32_t r = isRowMajor ? index / colsL : index % rowsL;
		const uint32_t c = isRowMajor ? index % colsL : index / rowsL;
		return object(r, c);
	}

// GETTERS++
	[[nodiscard]] inline constexpr uint32_t rows() const noexcept{ return rowsL; }
	[[nodiscard]] inline constexpr uint32_t cols() const noexcept{ return colsL; }
	[[nodiscard]] inline constexpr uint32_t size() const noexcept{ return rowsL * colsL; }


// DATA MEMBERS
public:
	const T (&func)(uint32_t, uint32_t);
};

template<class T, uint32_t rowsL, uint32_t colsL, bool rowMajor>
struct MBaseConstShadow{
// CONSTRUCTOR
	MBaseConstShadow(T func(uint32_t, uint32_t)) noexcept : object{func} {}
	MBaseConstShadow(T &func) noexcept : object{func} {}

// FLAGS
	typedef typename TypeTernary<std::is_invocable<T>::value, decltype(T{}(0u, 0u)), T>::type type;
	static constexpr bool isReal = false;
	static constexpr bool isVector = false;
	static constexpr bool isRowMajor = rowMajor;

// ACCESS
	[[nodiscard]] inline constexpr type operator ()(const uint32_t row, const uint32_t col) noexcept{
		return object(row, col);
	}
	[[nodiscard]] inline constexpr type operator [](const uint32_t index) noexcept{
		const uint32_t r = isRowMajor ? index / colsL : index % rowsL;
		const uint32_t c = isRowMajor ? index % colsL : index / rowsL;
		return object(r, c);
	}

// GETTERS++
	[[nodiscard]] inline constexpr uint32_t rows() const noexcept{ return rowsL; }
	[[nodiscard]] inline constexpr uint32_t cols() const noexcept{ return colsL; }
	[[nodiscard]] inline constexpr uint32_t size() const noexcept{ return rowsL * colsL; }


// DATA MEMBERS
public:
	const T &object;
};


}	// END OF NAMESPACE PRIV


}	// END OF NAMESPACE	///////////////////////////////////////////////////////////////////