#ifndef CPP_MATH_H
#define CPP_MATH_H

#include <cmath>

namespace functional::math
{

inline constexpr double tolerance = 0.0001;

template <typename T>
T identity(T x) { return x; }

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

auto sqrt(double x)
{
	return fixedPoint(averageDamp([x](double y){ return x / y;}))(1);
}



namespace details::mapReduce
{
template <typename Combine, typename F>
auto loop(int a, int acc, int b, Combine combine, F f) {
	if (a > b)
	{
		return acc;
	}
	else
	{
		acc = combine(acc, f(a));
		return loop(a + 1, acc, b, std::move(combine), std::move(f));
	}
}
}

template <typename Combine, typename F>
auto mapReduce(Combine combine, int zero, F f) {
	using details::mapReduce::loop;
	return [combine = std::move(combine), zero, f = std::move(f)](int a, int b){
		return loop(a, zero, b, std::move(combine), std::move(f));
	};
};

template <typename F>
auto sum(F f) {
	return mapReduce([](int x, int y){ return x + y; }, 0, std::move(f));
}

template <typename F>
auto product(F f) {
	return mapReduce([](int x, int y){ return x * y; }, 1, std::move(f));
}

auto fact(int a) {
	return product(identity<int>)(1, a);
}

}

#endif