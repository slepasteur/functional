package functional

import scala.math.abs

/**
  * Created by simon on 4/11/17.
  */
object Math {

  val tolerance = 0.0001

  def isCloseEnough(x: Double, y: Double): Boolean =
    abs((x - y) / x) <= tolerance

  def averageDamp(f: Double => Double)(x: Double): Double = (x + f(x)) / 2

  def fixedPoint(f: Double => Double)(firstGuess: Double): Double = {
    def iterate(guess: Double): Double = {
      val next = f(guess)
      if (isCloseEnough(guess, next)) next
      else iterate(next)
    }

    iterate(firstGuess)
  }

  def sqrt(x: Double): Double = {
    fixedPoint(averageDamp(y => x / y))(1)
  }

  /**
    * Map the values of the range [a, b] through f and reduce them through combine.
    * @param combine The reduce function (fold).
    * @param zero The zero value of the combine function.
    * @param f The mapping function.
    * @param a The beginning of the range.
    * @param b The end of the range.
    * @return The reduce value of range [f(a), f(b)]
    */
  def mapReduce(combine: (Int, Int) => Int, zero: Int, f: Int => Int)(a: Int, b: Int): Int = {
    def loop(a: Int, acc: Int): Int = {
      if (a > b) acc
      else loop(a + 1, combine(acc, f(a)))
    }

    loop(a, zero)
  }

  def sum(f: Int => Int)(a: Int, b: Int): Int = mapReduce((x, y) => x + y, 0, f)(a, b)
  def product(f: Int => Int)(a: Int, b: Int): Int = mapReduce((x, y) => x * y, 1, f)(a, b)
  def fact(a: Int) = product(x => x)(1, a)
}
