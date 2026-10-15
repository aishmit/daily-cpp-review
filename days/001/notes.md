1. The size of this in my guess would be 4 bytes for the int, 8 bytes for the func for Plain. Since I know very little about virtual I will assume it has no size. Hence Virt is probably 4 bytes for the int, same for Virt2. 12 bytes maybe for AB?

2. "Derived::hello\n"

3. By value and ref should both be woof

4. My assumption is it differs by the size of the lack of variable aka the int a so 4 bytes


2. days/001/notes.md: you have predictions in it. Add:
   - what surprised you
   this is hard man. it's not joke. i am so far behind and so weak in fundamentals that i have a lot of work to do
   - why noexcept matters for vector<Shape>
    we need no except because it's expected that move operations don't throw exceptions. vectors use std::mvoe to do such a thing. it's undefined behaviour if move were to throw an exception
   - the complexity of each order book operation
   skipping
   - your confidence (1–5)
   1