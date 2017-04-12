#ifndef CPP_MATH_H
#define CPP_MATH_H

#include <cmath>

namespace functional::math
{

inline constexpr double tolerance = 0.0001;

constexpr bool isCloseEnough(double x, double y)
{
	return std::abs((x - y) / x) <= tolerance;
}

// Can be constexpr as soon as compiler supports constexpr lambda expressions.
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0170r1.pdf
template<typename F>
auto averageDamp(F f)
{
	return [f](double x) {
		return (x + f(x)) / 2.0;
	};
}

namespace details::fixedPoint
{
template<typename F>
double iterate(double guess, F f)
{
	auto next = f(guess);
	if (isCloseEnough(guess, next))
	{
		return next;
	}
	else
	{
		return iterate(next, std::move(f));
	}
}
}

template <typename F>
auto fixedPoint(F f)
{
	using details::fixedPoint::iterate;
	return [f = std::move(f)](double firstGuess) {
		return iterate(firstGuess, std::move(f));
	};
}

//def sqrt(x: Double): Double = {
//	fixedPoint(averageDamp(y => x / y))(1)
//}
auto sqrt(double x)
{
	return fixedPoint(averageDamp([x](double y){ return x / y;}))(1);
}


}

#endif