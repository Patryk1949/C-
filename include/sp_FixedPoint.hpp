#include "SPL/Utils.hpp"

namespace sp{


template<class IntType> struct HigherIntResolution;
template<> struct HigherIntResolution<int8_t>{ typedef int16_t type; };
template<> struct HigherIntResolution<int16_t>{ typedef int32_t type; };
template<> struct HigherIntResolution<int32_t>{ typedef int64_t type; };
template<> struct HigherIntResolution<int64_t>{ typedef int64_t type; };
template<> struct HigherIntResolution<uint8_t>{ typedef uint16_t type; };
template<> struct HigherIntResolution<uint16_t>{ typedef uint32_t type; };
template<> struct HigherIntResolution<uint32_t>{ typedef uint64_t type; };
template<> struct HigherIntResolution<uint64_t>{ typedef uint64_t type; };



template<int fracBits, class Base = int32_t>
class FixedPoint{
	static_assert(std::is_integral<Base>() && std::is_signed<Base>(), "Fixed point must be built on top of signed iteger.");
	static_assert(fracBits < std::numeric_limits<Base>::digits, "Number of fractional bits must be smaller than total number of bits.");
public:
	FixedPoint() noexcept {}
	FixedPoint(const FixedPoint &) = default;
	FixedPoint(FixedPoint &&) = default;
	FixedPoint &operator =(const FixedPoint &) = default;
	FixedPoint &operator =(FixedPoint &&) = default;


	template<int fracBits1>
	inline constexpr auto &operator +=(const FixedPoint<fracBits1, Base> rhs);
	template<int fracBits1>
	inline constexpr auto &operator -=(const FixedPoint<fracBits1, Base> rhs);
	template<int fracBits1>
	inline constexpr auto &operator *=(const FixedPoint<fracBits1, Base> rhs);
	template<int fracBits1>
	inline constexpr auto &operator /=(const FixedPoint<fracBits1, Base> rhs);
	template<int fracBits1>
	inline constexpr auto &operator %=(const FixedPoint<fracBits1, Base> rhs);

	template<int fracBits1>
	inline constexpr auto &operator |=(const FixedPoint<fracBits1, Base> rhs);
	template<int fracBits1>
	inline constexpr auto &operator &=(const FixedPoint<fracBits1, Base> rhs);
	template<int fracBits1>
	inline constexpr auto &operator ^=(const FixedPoint<fracBits1, Base> rhs);

// CONVERSIONS
	template<int fracBits1, class Base1>
	inline constexpr FixedPoint(const FixedPoint<fracBits1, Base1> x) noexcept;

	// CONVERSION FROM INTEGER TO FIXED POINT
	template<class T>
	inline constexpr FixedPoint(const T x) noexcept;

	// CONVERSION FROM FIXED POINT TO INTEGER
	template <class T, std::enable_if<std::is_integral<T>(), T>>
	inline constexpr operator T() noexcept;

	inline constexpr operator float() noexcept;
	inline constexpr operator double() noexcept;
	inline constexpr operator long double() noexcept;

	static constexpr int fractionalBits = fracBits;

	Base data;
};

template<int fracBits1, int fracBits2, class Base>
inline constexpr auto operator +(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs);
template<int fracBits1, int fracBits2, class Base>
inline constexpr auto operator -(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs);
template<int fracBits1, int fracBits2, class Base>
inline constexpr auto operator *(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs);
template<int fracBits1, int fracBits2, class Base>
inline constexpr auto operator /(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs);
template<int fracBits1, int fracBits2, class Base>
inline constexpr auto operator %(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs);

template<int fracBits1, int fracBits2, class Base>
inline constexpr auto operator |(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs);
template<int fracBits1, int fracBits2, class Base>
inline constexpr auto operator &(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs);
template<int fracBits1, int fracBits2, class Base>
inline constexpr auto operator ^(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs);
template<int fracBits, class Base>
inline constexpr auto operator ~(const FixedPoint<fracBits, Base> lhs);

template<int fracBits1, int fracBits2, class Base>
inline constexpr bool operator ==(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs){
	typedef FixedPoint<std::max(fracBits1, fracBits2), Base> ResultType;
	return ((ResultType)lhs).data == ((ResultType)rhs).data;
}
template<int fracBits1, int fracBits2, class Base>
inline constexpr bool operator !=(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs){
	typedef FixedPoint<std::max(fracBits1, fracBits2), Base> ResultType;
	return ((ResultType)lhs).data != ((ResultType)rhs).data;
}
template<int fracBits1, int fracBits2, class Base>
inline constexpr bool operator >(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs){
	typedef FixedPoint<std::max(fracBits1, fracBits2), Base> ResultType;
	return ((ResultType)lhs).data >= ((ResultType)rhs).data;
}
template<int fracBits1, int fracBits2, class Base>
inline constexpr bool operator <(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs){
	typedef FixedPoint<std::max(fracBits1, fracBits2), Base> ResultType;
	return ((ResultType)lhs).data <= ((ResultType)rhs).data;
}
template<int fracBits1, int fracBits2, class Base>
inline constexpr bool operator >=(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs){
	typedef FixedPoint<std::max(fracBits1, fracBits2), Base> ResultType;
	return ((ResultType)lhs).data >= ((ResultType)rhs).data;
}
template<int fracBits1, int fracBits2, class Base>
inline constexpr bool operator <=(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs){
	typedef FixedPoint<std::max(fracBits1, fracBits2), Base> ResultType;
	return ((ResultType)lhs).data <= ((ResultType)rhs).data;
}
template<int fracBits, class Base>
inline constexpr bool operator !(const FixedPoint<fracBits, Base> lhs){ return !x.data; }






#define TPL template<int fracBits, class Base>
#define CLS FixedPoint<fracBits, Base>

TPL template<int fracBits1, class Base1>
inline constexpr CLS::FixedPoint(const FixedPoint<fracBits1, Base1> x) noexcept{
	constexpr int pointsDistance = fracBits1 - fracBits;
	if constexpr (pointsDistance >= 0)
		data = (Base)x.data >> pointsDistance;
	else
		data = (Base)x.data << -pointsDistance;
}

TPL template<class T>
inline constexpr CLS::FixedPoint(const T x) noexcept{
	static_assert(std::is_arithmetic<T>(), "Only a number can be converted to fixed point.");
	if constexpr (std::is_integral<T>())
		data = (Base)x << fracBits;
	else
		data =  (Base)(x * (1 << fracBits));
}

TPL template <class T>
inline constexpr CLS::operator T() noexcept{
	static_assert(std::is_integral<T>(), "Fixed point can only be converted to a number.");
	return (T)(data >> fracBits);
}

TPL inline constexpr CLS::operator float() noexcept{
	return (float)data / (float)(1 << fracBits);
}
TPL inline constexpr CLS::operator double() noexcept{
	return (double)data / (double)(1 << fracBits);
}
TPL inline constexpr CLS::operator long double() noexcept{
	return (long double)data / (long double)(1 << fracBits);
}


TPL template<int fracBits1>
inline constexpr auto &CLS::operator +=(const FixedPoint<fracBits1, Base> rhs){
	data += ((FixedPoint<fracBits, Base>)rhs).data;
	return *this;
}
TPL template<int fracBits1>
inline constexpr auto &CLS::operator -=(const FixedPoint<fracBits1, Base> rhs){
	data -= ((FixedPoint<fracBits, Base>)rhs).data;
	return *this;
}
TPL template<int fracBits1>
inline constexpr auto &CLS::operator *=(const FixedPoint<fracBits1, Base> rhs){
	data = ((typename HigherIntResolution<Base>::type)data *
		(typename HigherIntResolution<Base>::type)((FixedPoint<fracBits, Base>)rhs).data) >> fracBits;
	return *this;
}
TPL template<int fracBits1>
inline constexpr auto &CLS::operator /=(const FixedPoint<fracBits1, Base> rhs){
	data = (((typename HigherIntResolution<Base>::type)data << fracBits) /
		(typename HigherIntResolution<Base>::type)((FixedPoint<fracBits, Base>)rhs).data);
	return *this;
}
TPL template<int fracBits1>
inline constexpr auto &CLS::operator %=(const FixedPoint<fracBits1, Base> rhs){
	data %= ((FixedPoint<fracBits, Base>)rhs).data;
	return *this;
}

TPL template<int fracBits1>
inline constexpr auto &CLS::operator |=(const FixedPoint<fracBits1, Base> rhs){
	data |= ((FixedPoint<fracBits, Base>)rhs).data;
	return *this;
}
TPL template<int fracBits1>
inline constexpr auto &CLS::operator &=(const FixedPoint<fracBits1, Base> rhs){
	data &= ((FixedPoint<fracBits, Base>)rhs).data;
	return *this;
}
TPL template<int fracBits1>
inline constexpr auto &CLS::operator ^=(const FixedPoint<fracBits1, Base> rhs){
	data ^= ((FixedPoint<fracBits, Base>)rhs).data;
	return *this;
}


#undef CLS
#undef TPL



template<int fracBits1, int fracBits2, class Base>
inline constexpr auto operator +(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs){
	typedef FixedPoint<std::max(fracBits1, fracBits2), Base> ResultType;
	ResultType result;
	result.data = ((ResultType)lhs).data + ((ResultType)rhs).data;
	return result;
}
template<int fracBits1, int fracBits2, class Base>
inline constexpr auto operator -(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs){
	typedef FixedPoint<std::max(fracBits1, fracBits2), Base> ResultType;
	ResultType result;
	result.data = ((ResultType)lhs).data - ((ResultType)rhs).data;
	return result;
}
template<int fracBits1, int fracBits2, class Base>
inline constexpr auto operator *(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs){
	typedef FixedPoint<std::max(fracBits1, fracBits2), Base> ResultType;
	ResultType result;
	result.data = ((typename HigherIntResolution<Base>::type)((ResultType)lhs).data *
		(typename HigherIntResolution<Base>::type)((ResultType)rhs).data) >> ResultType::fractionalBits;
	return result;
}
template<int fracBits1, int fracBits2, class Base>
inline constexpr auto operator /(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs){
	typedef FixedPoint<std::max(fracBits1, fracBits2), Base> ResultType;
	ResultType result;
	result.data = (((typename HigherIntResolution<Base>::type)((ResultType)lhs).data << ResultType::fractionalBits) /
		(typename HigherIntResolution<Base>::type)((ResultType)rhs).data);
	return result;
}
template<int fracBits1, int fracBits2, class Base>
inline constexpr auto operator %(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs){
	typedef FixedPoint<std::max(fracBits1, fracBits2), Base> ResultType;
	ResultType result;
	result.data = ((ResultType)lhs).data % ((ResultType)rhs).data;
	return result;
}

template<int fracBits1, int fracBits2, class Base>
inline constexpr auto operator |(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs){
	typedef FixedPoint<std::max(fracBits1, fracBits2), Base> ResultType;
	ResultType result;
	result.data = ((ResultType)lhs).data | ((ResultType)rhs).data;
	return result;
}
template<int fracBits1, int fracBits2, class Base>
inline constexpr auto operator &(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs){
	typedef FixedPoint<std::max(fracBits1, fracBits2), Base> ResultType;
	ResultType result;
	result.data = ((ResultType)lhs).data & ((ResultType)rhs).data;
	return result;
}
template<int fracBits1, int fracBits2, class Base>
inline constexpr auto operator ^(const FixedPoint<fracBits1, Base> lhs, const FixedPoint<fracBits2, Base> rhs){
	typedef FixedPoint<std::max(fracBits1, fracBits2), Base> ResultType;
	ResultType result;
	result.data = ((ResultType)lhs).data ^ ((ResultType)rhs).data;
	return result;
}
template<int fracBits, class Base>
inline constexpr auto operator ~(const FixedPoint<fracBits, Base> x){
	typedef FixedPoint<fracBits, Base> ResultType;
	ResultType result;
	result.data = ~x.data;
	return result;
}



/*
template<int fracBits, class Base>
char *fixedToString(char *const output, FixedPoint<fracBits, Base> x, const int length){
	char *charPtr = output+length-1;
	const bool isNegative = signbit(x.data);
	if (isNegative)
		x.data = -x.data;

	const char *const pointPlace = output - fracBits;
	while (x.data && charPtr >= pointPlace){
		const Base prev = x.data;
		x.data /= 10;
		*charPtr-- = '0' + prev - x.data*10;
	}
	*charPtr-- = '.';
	while (x.data && charPtr >= output){
		const Base prev = x.data;
		x.data /= 10;
		*charPtr-- = '0' + prev - x.data*10;
	}
	if (isNegative && charPtr >= output)
		*charPtr-- = '-';
	while (charPtr >= output)
		*charPtr-- = ' ';

	return output + length;
}*/

} // END OF NAMESPACE //////////////////////////////////////////////////////////////////////////////////////////