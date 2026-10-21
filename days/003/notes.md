1.

virtual destructor chaining.. when you delete a derived and it's been
  overridden, it actually still runs the ~Base. virtual will create a vtable still
  but the destructors will chain where derived is called first, then Base is

2.
```cpp
class Shape {
    void* obj_;   // points at a Circle that Shape created with new, and must delete itself

    Shape(Shape&& s)
    {
        this.obj_ = s.obj_;
        s.obj_ = nullptr;

    }
};
    // or simply: Shape s = std::move(old_s)

```

cloning means we are to go and copy the whole object versus just moving its reference from one class to another. deleting then is another operation where unnecessary post cpp 11. if prior to cpp11 we could swap

3.
vague question. what does this mean. if two orders share a price then we should be pushing the prices by value rather than by reference. price is probably an int or float so this shoulnd't be. aprovlem?


int x = -6; size_t y = 0; What does x > y evaluate to, and why? How do you avoid it? (cpp-om-014)
x will be the wrap around of max_int - 6. 
What's the difference between struct and class in C++? What breaks if you change struct Animal { virtual ~Animal() = default; }; to class? (cpp-om-013)
difference is that all memebrs are public by default. if class from struct then we will not be able to access the destructor when doing a derived class
Group Anagrams with the sorted-word key: what's the complexity? Name your variables. (dsa-004)
O(nlogk) where n is number of strings, and k is length of key

if your copy ctor were Buffer(const Buffer& o) : data_(o.data_), size_(o.size_) {}, which tests in test_2_copy.cpp fail, and what does ASan print when the test ends?
test 2 in test 2 would fail because shallow copy would effectively be what's happening. my assumption is that o.data_ is likely a pointer array. if we're doing a shallow copy like implied above, then they point to the same addresses and hence line 26 CHECK(b.data() != a.data());   fails

test 5:
doing a std::move on venue means doing a move on the rvalue of it? it seems like it's a temp value from being copied. both tests are failing in that section. not sure if std::move() would do anything to properly move the venue

---
Tutor marks (live session, Tue Oct 20):
1. Partial. Chaining right (~Derived, then ~Base). Missing what `virtual` buys: `delete base_ptr` starts at
   ~Derived; without it only ~Base runs (UB, Derived's resources leak).
2. Partial. Steal + null the source is right. `this.obj_` doesn't compile (`this` is a pointer → `this->obj_`
   or just `obj_`); missing `noexcept`. Why not clone+delete: clone allocates (slow) and `new` can throw,
   which breaks `noexcept`, so `std::vector` would copy instead of move on growth.
3. Wrong. Not value vs reference: tuples compare element by element, a tie on price compares the Order
   objects → TypeError (the exact error from the Day 002 order book). Fix: push the price only, or
   (price, seq, order).

Tutor marks (Wed warm-up):
1. Partial. -6 converts to size_t: 2^64 − 6 = 18446744073709551610 (not "max_int − 6"), so `x > y` is **true**.
   Missing the fix: keep values that can go negative signed; `-Wsign-compare` (in -Wall/-Wextra) flags it.
2. Mostly right. struct = public members **and public inheritance** by default; class = private for both. With class,
   ~Animal is private, so Dog's destructor is deleted (compile errors), and `Animal* a = &dog` fails (private base).
3. Wrong. O(n · k log k): sorting one word is k log k, done n times. (Said correctly on Monday; slipped back.)
