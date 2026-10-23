## Warm-up recall (from memory)
1.A price level is any number of orders that were placed at a given price. Moving it to the back means it is the last item in queue to be consumed for traded on when trying to fill an opposite order. e.g. 90 shares at 20 bucks then 100 shares that 90 bucks in order. qty changes of order 1 to be 80, so gets pushed back of queue aking it 20: [100, 90]
2. Two prices mean that the heap doesn't know how to distinguish between the two prices and will state that this key has already been used. Not entirely sure if that's correct. Fixing it means to not use orders as part of the heap and maintian that storage elsewhere, where heap is rather only maintaining priority of the prices.
3. Rule of 3 is an older rule before move semantics stating that if a class/struct needs to customly make either teh delete, copy ctor or copy assignment it will need to custom make all of them as the compiler may not properly clean up the data members, double free or other behaviour. Rule of 5 includes move ctor and move assignment override(overload?) . Rule of 0 means to use features such as unique pointers locak guards etc. which will handle heap clean up for us, requiring no manual deletion
Tutor marks (warm-up):
1. Partial. Definition right. Example wrong twice: $20 and $90 are **different** levels (a level = one price), and
   reducing 90 → 80 **keeps** priority; only an *increase* moves an order to the back.
   Correct: bids at 99 = [#1 qty 90, #2 qty 100]; #1 increases to 120 → [#2 qty 100, #1 qty 120].
2. Partial. Fix right (keep orders out of the heap; push the price only, or `(price, seq, order)`). Cause wrong: not
   "key already used". Tuples compare item by item; equal prices → Python compares the two `Order` objects →
   `TypeError: '<' not supported between instances of 'Order' and 'Order'`.
3. Partial. 3/5/0 right. Missing the second question: declaring **any** of the copy ctor, copy assignment or destructor
   stops the compiler from generating the moves, so `std::move` silently copies (yesterday's TODO 5).

## Recap (before changing code)
1. Line that keeps a rejected id: the `self.orders[order_id] = order` line (was line 56) ran **before** the cross check (line 70), so a refused order (#20, buy at $101) stayed in `self.orders`. The retry (#20, buy at $100) then hit the duplicate check (line 52) and returned **False**; it should return **True** ($100 doesn't cross the $101 ask). Fixed: moved the save to after every check, just before `return True`.
2. Places qty is stored: two: the level dict (`asks_by_price[price][id] = qty` / `bids_by_price`) and the `Order` object's `qty`. `modify` has to update both (on an increase, also move the order to the back of its level). Fix: store the `Order` in the level, so the quantity lives in one place.
3. Predict best_ask() after cancel(3): it *should* return the next best ask ($102). Fix: lazy removal (skip heap prices whose level no longer exists). [Tutor: with the current code it returns **101**, a price nobody is selling at, because the heap still holds 101 and `best_ask()` just reads `self.asks[0]`.]
## Build
- Predict (before step B): copies of the price in the heap: ... · depth-from-heap would show: ...
- Step A: what each method does to heap / levels / id map: ...
- Step B: ...
- Step C: ...
- Tests: A _/16 at __ min · B _/16 at __ min · C _/16 at __ min
## Complexity of my version
add: ... cancel: ... modify down/up: ... best_bid: ... depth(m): ... queue: ...
Dominant op on a real feed, and its cost here: ...
## Error log (one line per mistake)
-
## Confidence (1–5): order book __
## Questions