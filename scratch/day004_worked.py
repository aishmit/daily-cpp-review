"""Day 004 worked Python idioms, on a different problem: a restaurant waitlist.
The lesson quotes this file. Run: python3 scratch/day004_worked.py
"""
import heapq

# 1. A dict keeps insertion order, so it is a FIFO you can delete from in O(1).
waitlist = {}                      # name -> party size, in arrival order
waitlist["ana"] = 2
waitlist["bo"] = 4
waitlist["cy"] = 3
print(list(waitlist))              # ['ana', 'bo', 'cy']   keys, in arrival order

# 2. Remove from the middle: O(1) on average. Check membership with `in`, not .get().
if "bo" in waitlist:
    del waitlist["bo"]
print(list(waitlist))              # ['ana', 'cy']

# 3. Move a key to the back: pop it, insert it again.
size = waitlist.pop("ana")
waitlist["ana"] = size + 1
print(list(waitlist), waitlist["ana"])   # ['cy', 'ana'] 3

# 4. A nested container that empties gets deleted, so nobody sees an empty one.
sections = {"patio": {"dee": 2}, "bar": {"eli": 1}}
del sections["patio"]["dee"]
if not sections["patio"]:          # empty dict is falsy
    del sections["patio"]
print(sections)                    # {'bar': {'eli': 1}}
print(sections.get("patio", {}))   # {}   default when the key is missing

# 5. Lazy deletion: a heap can't delete from the middle, so leave stale entries in it
#    and throw them away only when they reach the top. Max-heap = push the negative.
latest = []                        # max-heap of reservation hours (negated)
booked = {18, 19, 20}
for h in booked:
    heapq.heappush(latest, -h)
booked.discard(20)                 # cancel 20:00; the heap still holds -20
while latest and -latest[0] not in booked:
    heapq.heappop(latest)          # each stale entry is popped once, ever
print(-latest[0] if latest else None)    # 19

# 6. Top n keys, largest first, with a total per key.
tables = {4: {"t1": 4, "t7": 4}, 2: {"t3": 2}, 6: {"t9": 6}}
top = sorted(tables, reverse=True)[:2]
print([(seats, sum(tables[seats].values())) for seats in top])   # [(6, 6), (4, 8)]
print(sorted(tables, reverse=True)[:0])  # []   slicing past either end never raises
