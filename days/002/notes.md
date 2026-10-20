## Warm-up recall (from memory, Mon Oct 19)
1. When a virtual function is called, the compiler first looks up the function in the class. If a vtable
   exists at the start of the class (first 8 bytes) it then checks its entries. If an entry exists for that
   function it then points to the base reference's definition of it, then uses that version of it.
2. A virtual call inside a constructor will call the base class's function rather than the derived one's.
3. A static cast is used, as it's one the compiler can check and make sense of.

Tutor marks (live session): 1 partial (vptr in the first 8 bytes is right; but the slot points to the
*object's real class's* version, not the base reference's, and the lookup happens at runtime in generated
code, not by the compiler) · 2 right, missing the "why" · 3 right cast, missing the exact form
`static_cast<const Circle*>(s)`.

## DSA log
| Problem | Time | Solved without hints? | Brute force → optimal | Edge cases I listed | What tripped me up |
|---|---|---|---|---|---|
| 121 | | 1 hint (level 1), done Oct 15, in C++ | | | `size_t` for a value that goes negative: -6 wrapped to 18446744073709551610 |
| 49  | ~9 min | yes | pairwise O(n²·k) → sorted-word key O(n·k log k) | empty string, (after review) empty list + dupes | complexity: mixed n and k at first |

## Order book: complexity of my version
add: ... cancel: ... modify: ... best: ... depth: ...

## Confidence (1–5): DSA __ · order book __

## Questions
