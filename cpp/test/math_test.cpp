#include "./catch.hpp"

#include "../src/math.hpp"

using namespace functional::math;

TEST_CASE("close enough is true for 1.0 +/- tolerance")
{
	REQUIRE(isCloseEnough(1.0, 1.0 + tolerance));
	REQUIRE(isCloseEnough(1.0, 1.0 - tolerance));
	REQUIRE(isCloseEnough(1.0, 1.0 + tolerance * 0.5));
	REQUIRE(isCloseEnough(1.0, 1.0 - tolerance * 0.5));
}

TEST_CASE("close enough is false for 1.0 +/- more than tolerance")
{
	REQUIRE(!isCloseEnough(1.0, 1.0 + tolerance * 1.1));
	REQUIRE(!isCloseEnough(1.0, 1.0 - tolerance * 1.1));
}

TEST_CASE("close enough for small numbers")
{
	REQUIRE(isCloseEnough(10e-3, 10e-3 + 10e-3 * tolerance));
	REQUIRE(isCloseEnough(10e-3, 10e-3 - 10e-3 * tolerance));
}

TEST_CASE("close enough for large numbers")
{
	REQUIRE(isCloseEnough(10e10, 10e10 + 10e10 * tolerance));
	REQUIRE(isCloseEnough(10e10, 10e10 - 10e10 * tolerance));
}

TEST_CASE("average damp")
{
	REQUIRE(averageDamp([](auto x) { return x / 2; })(2) == 1.5);
	REQUIRE(averageDamp([](auto x) { return x * x; })(2) == 3);
}

TEST_CASE("fixed point of x^2 - 3x + 4 is ~= 2")
{
	REQUIRE(isCloseEnough(fixedPoint([](auto x) { return x * x - 3 * x + 4; })(1), 2));
}

TEST_CASE("sqrt(4) ~= 2")
{
	REQUIRE(isCloseEnough(functional::math::sqrt(4), 2));
}

TEST_CASE("sqrt(9) ~= 3")
{
	REQUIRE(isCloseEnough(functional::math::sqrt(4), 2));
}

TEST_CASE("sqrt(2) ~= 1.41421356237")
{
	REQUIRE(isCloseEnough(functional::math::sqrt(2), 1.41421356237));
}

TEST_CASE("sum")
{
	using functional::math::identity;
	REQUIRE(sum(identity<int>)(0, 0) == 0);
	REQUIRE(sum(identity<int>)(1, 10) == 55);
	REQUIRE(sum([](int x) { return x * 2; })(1, 10) == 110);
	REQUIRE(sum([](int x) { return x * x; })(3, 5) == 50);
}

TEST_CASE("product")
{
	using functional::math::identity;
	REQUIRE(product(identity<int>)(3, 5) == 60);
	REQUIRE(product([](int x){ return x * x; })(3, 5) == 3600);
	REQUIRE(product([](int x){ return x * x * x; })(1, 4) == 13824);
}

TEST_CASE("factorial")
{
	REQUIRE(fact(0) == 1);
	REQUIRE(fact(1) == 1);
	REQUIRE(fact(5) == 120);
	REQUIRE(fact(8) == 40320);
}