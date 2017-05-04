package functional

import org.scalatest.FunSuite

/**
  * Created by simon on 5/4/17.
  */
class ListTests extends FunSuite {

  test("singleton list contains 1 value") {
    val s = Utils.singleton(1)
    assert(s.head === 1)
    assert(s.tail.isEmpty)
  }

  test("list of multiple level can be created") {
    val list = new Cons[Int](1, Utils.singleton(2))
    assert(list.head === 1)
    assert(list.tail.head === 2)
    assert(list.tail.tail.isEmpty)
  }

  test("nth element") {
    val list = new Cons[Int](1, new Cons[Int](2, Utils.singleton(3)))
    assert(Utils.nth(0, list) === 1)
    assert(Utils.nth(1, list) === 2)
    assert(Utils.nth(2, list) === 3)
    assertThrows[IndexOutOfBoundsException](Utils.nth(3, list))
    assertThrows[IndexOutOfBoundsException](Utils.nth(-1, list))
  }
}
