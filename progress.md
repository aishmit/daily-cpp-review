# Progress — the loop's memory

Updated by the daily run (and by Claude Code sessions when you struggle). Newest first in the log.

## Status
- **Plan restarted 2026-10-15:** target is now **Citadel Securities SWE** (recruiter outreach). The
  earlier HRT/PDT C++-depth plan and the C++-only switch are superseded; see `curriculum.md`.
- Screen date: **not yet known**. When it's known, compress the plan so a mock lands 3–4 sessions before it.
- Cadence: Mon–Thu, 60 min (5 recall · 30 DSA · 25 track). No Fri–Sun. Skip US holidays (Thanksgiving Thu Nov 26).
- Interview language: **Python**. C++ for the debugging round and systems knowledge.
- Tracks alternate: even days = system design (Python), odd days = C++ & systems.
- Current session: **002** (Mon 2026-10-19), pre-written; checked by the 2026-10-19 run: stub fails 0/12,
  a private reference passes 12/12, links verified (LeetCode via search index; direct fetch is blocked
  by the routine's network policy). Nothing to review: Day 001 is done and has no pending review. The run writes 003 onward.
- Routine push check: OK (2026-10-15, new Claude Code routine with repo source).
- Day 001 (Oct 1, vtables) is done. Note from his notes: "this is hard… so far behind"; confidence 1/5.

## Schedule
| Day | Date | DSA pattern | Track |
|---|---|---|---|
| 001 | Thu Oct 1 | — | C++: virtual dispatch & vtables (done) |
| 002 | Mon Oct 19 | Arrays/hashing, "stock" pattern | Design: framework + order book |
| 003 | Tue Oct 20 | Sliding window | C++: object lifetime by hand, rule of 0/3/5 (re-test Day 001 gaps) |
| 004 | Wed Oct 21 | Sliding window (deque) | Design: matching engine |
| 005 | Thu Oct 22 | Mixed wk-1 review | C++: move semantics + behavioral #1 |
| 006–009 | Oct 26–29 | Stacks, monotonic, heaps | curriculum wk 2 |
| 010–013 | Nov 2–5 | Intervals, binary search, BFS | wk 3 |
| 014–017 | Nov 9–12 | Graphs | wk 4 · **017 mock screen (Thu Nov 12)** |
| 018–021 | Nov 16–19 | Bellman-Ford, union-find, tries | wk 5 |
| 022–024 | Nov 23–25 | DP | wk 6 (Thanksgiving week, 3 sessions) |
| 025–028 | Nov 30–Dec 3 | DP / design-style | wk 6–7 · **028 mock design (Thu Dec 3)** |
| 029–032 | Dec 7–10 | Design-style, mixed | wk 7–8 · **030 mock superday design (Tue Dec 8)** |
| 033 | Mon Dec 14 | Mixed | **Mock superday** |

## Calibration notes for the daily run (read before writing the next day)
- **2026-10-01, Day 001 live session:** level is below what Day 001 assumed. Concepts (vtable/vptr,
  ctor sets vptr, destructor chaining) needed explaining from scratch; hand-writing C++ syntax is
  the bigger gap: lambda bodies, `return` placement, casts (`static_cast<const T*>`), calling a
  function pointer through a struct (`vptr_->area(obj_)`). Part B took ~8 attempts for 3 one-liners.
- **Adjust:** smaller steps per challenge (one TODO = one concept), a tiny worked example of every
  syntax form the challenge needs (cast, function-pointer call, lambda→fn ptr), and tests that fail
  one concept at a time (don't fold leak checks into a "dispatch" test). Keep the next C++ day (now Day 003) on lifetime/
  move but add a 5-min "C++ syntax by hand" drill before the challenge until this row closes.
- **Tutor pace:** he asked to be "pushed through": escalate hints faster (pseudocode by the 2nd miss,
  the missing line by the 3rd) instead of long Socratic loops. Still no full solutions unless asked twice.

## Calibration notes added 2026-10-15
- Interview reports flag missed edge cases, BFS vs DFS for shortest paths, and input contracts:
  drill these in every DSA review.
- Prior Python interview practice: rate limiter, LRU cache, webhook delivery with retries.

## DSA log (LeetCode); the run fills this from notes.md
| Day | Problem | Pattern | Time | Solved without hints? | Notes |
|---|---|---|---|---|---|

## Weak areas (drives remediation + recall)
| Topic | Evidence | First seen | Status |
|---|---|---|---|
| Virtual functions / vtables | self-reported; Day 001 predict.cpp 0/4: thought `virtual` adds no size, missed ctor/dtor dispatch and didn't know the vptr is written by the ctor — guessed "when called" (cpp-om-003), thought an overridden virtual dtor skips ~Base (cpp-om-011), unsure how dispatch finds the derived fn — said "the vtable of the Sink" is looked up (cpp-om-001), slicing (cpp-om-004), MI pointer adjust (cpp-om-006) | 2026-10-01 | open |
| Object layout: sizeof, padding, alignment | Day 001 Q1: thought member functions occupy object storage (cpp-om-009); no padding model (cpp-om-010) | 2026-10-01 | open |
| C++ syntax fluency: casts, lambda bodies | Day 001 B1: `return Circle* c = reinterpret_cast<Circle>(s); ...` (declaration after return, cast to value not pointer, dropped const, wrong cast) (cpp-om-012) | 2026-10-01 | open |
| Type erasure: wrapper vs erased object | Day 001 B3: wrote `obj_->area()`, then `vptr_->area(this)` (passed the Shape, not the object); unsure what a deep copy needs (cpp-om-008) | 2026-10-01 | open |
| Move semantics: what a move does | Day 001 B2: proposed clone+delete as a move; didn't null the source (cpp-ml-001) | 2026-10-01 | open |
| Advanced templates | self-reported | 2026-10-01 | open |

## Day log
| Day | Date | Systems / C++ topic | Design topic | Attempted? | Score | Notes |
|---|---|---|---|---|---|---|
| 001 | 2026-10-01 | Virtual functions & vtables | Order book: requirements & core ops | systems: yes (live session) | — | Live session: wrote Part A, B1 tables, B3 dispatch, clone, copy ctor himself (many hints). Tutor wrote move ctor (asked twice), copy-and-swap operator=, destroy slots + ~Shape (asked twice). Re-test him on destroy/~Shape/operator= by hand on Day 003 (plan restarted; Day 002 is a design day). |
