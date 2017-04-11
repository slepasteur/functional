package functional

import org.scalatest.FunSuite
import org.junit.runner.RunWith
import org.scalatest.junit.JUnitRunner

/**
  * Created by simon on 4/11/17.
  */
@RunWith(classOf[JUnitRunner])
class MathTests extends FunSuite {
  import Math._

  test("close enough is true for 1.0 +/- tolerance") {
    assert(isCloseEnough(1.0, 1.0 + tolerance))
    assert(isCloseEnough(1.0, 1.0 - tolerance))
    assert(isCloseEnough(1.0, 1.0 + tolerance * 0.5))
    assert(isCloseEnough(1.0, 1.0 - tolerance * 0.5))
  }

  test("close enough is false for 1.0 +/- more than tolerance") {
    assert(!isCloseEnough(1.0, 1.0 + tolerance * 1.1))
    assert(!isCloseEnough(1.0, 1.0 - tolerance * 1.1))
  }

  test("close enough for small numbers") {
    assert(isCloseEnough(10e-3, 10e-3 + 10e-3 * tolerance))
    assert(isCloseEnough(10e-3, 10e-3 - 10e-3 * tolerance))
  }

  test("close enough for large numbers") {
    assert(isCloseEnough(10e10, 10e10 + 10e10 * tolerance))
    assert(isCloseEnough(10e10, 10e10 - 10e10 * tolerance))
  }

  test("average damp") {
    assert(averageDamp(x => x / 2)(2) === 1.5)
    assert(averageDamp(x => x * x)(2) === 3)
  }

  test("fixed point of x^2 - 3x + 4 is ~= 2") {
    assert(isCloseEnough(fixedPoint(x => x * x - 3 * x + 4)(1), 2))
  }

  test("sqrt(4) ~= 2") {
    assert(isCloseEnough(sqrt(4), 2))
  }

  test("sqrt(9) ~= 3") {
    assert(isCloseEnough(sqrt(4), 2))
  }

  test("sqrt(2) ~= 1.41421356237") {
    assert(isCloseEnough(sqrt(2), 1.41421356237))
  }
}
