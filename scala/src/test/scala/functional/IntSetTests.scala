package functional

import org.scalatest.FunSuite

/**
  * Created by simon on 4/28/17.
  */
class IntSetTests extends FunSuite {

  test("empty int set does not contain small integer values") {
    val empty = Empty
    for (x <- -1000 to 1000) {
      assert(!empty.contains(x))
    }
  }

  test("non empty set contains value it is constructed from") {
    assert(new NonEmpty(1, Empty, Empty).contains(1))
    assert(new NonEmpty(2, Empty, Empty).contains(2))
    assert(new NonEmpty(5, Empty, Empty).contains(5))
    assert(new NonEmpty(-6, Empty, Empty).contains(-6))
  }

  test("non empty set does not contain other values") {
    assert(!new NonEmpty(1, Empty, Empty).contains(2))
    assert(!new NonEmpty(2, Empty, Empty).contains(5))
    assert(!new NonEmpty(5, Empty, Empty).contains(-5))
    assert(!new NonEmpty(-6, Empty, Empty).contains(6))
  }

  test("non empty set contains value it includes") {
    val set = new NonEmpty(1, Empty, Empty)
    assert((set incl 2) contains 1)
    assert((set incl 2) contains 2)
    assert((set incl 2 incl 3 incl 5) contains 3)
  }

  test("union") {
    val set1 = Empty incl 1 incl 2 incl 3
    val set2 = Empty incl 4 incl 5 incl 6
    val union = set1 union set2
    assert(union contains 1)
    assert(union contains 2)
    assert(union contains 3)
    assert(union contains 4)
    assert(union contains 5)
    assert(union contains 6)
  }
}
