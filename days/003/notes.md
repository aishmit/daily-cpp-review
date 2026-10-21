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
