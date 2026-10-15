# Progress — the loop's memory

Updated by the daily run (and by Claude Code sessions when you struggle). Newest first in the log.

## Status
- Current day: **001** (published 2026-10-01)
- Next mock: Day 008 (systems + C++ trivia only)
- Tracks: **C++ only** (design paused 2026-10-01 at his request; Day 001 `design/` is optional)
- Schedule: Mon–Thu, ~6 PM ET (no Fri–Sun)
- Start date: 2026-10-01 (Thu) — Day 001 published at kickoff; next scheduled run Mon 2026-10-05

## Self-assessment baseline (from kickoff, 2026-10-01)
- C++: comfortable with application-level syntax; rusty on virtual dispatch internals, templates
  beyond basics, move semantics details. Not writing much code by hand lately.
- Interviews previously practiced in Python (rate limiter, LRU cache, webhook delivery).
- Goal: confident at HRT / PDT; strong fundamentals for Citadel/Jane Street/etc.

## Calibration notes for the daily run (read before writing the next day)
- **2026-10-01, Day 001 live session:** level is below what Day 001 assumed. Concepts (vtable/vptr,
  ctor sets vptr, destructor chaining) needed explaining from scratch; hand-writing C++ syntax is
  the bigger gap: lambda bodies, `return` placement, casts (`static_cast<const T*>`), calling a
  function pointer through a struct (`vptr_->area(obj_)`). Part B took ~8 attempts for 3 one-liners.
- **Adjust:** smaller steps per challenge (one TODO = one concept), a tiny worked example of every
  syntax form the challenge needs (cast, function-pointer call, lambda→fn ptr), and tests that fail
  one concept at a time (don't fold leak checks into a "dispatch" test). Keep Day 002 on lifetime/
  move but add a 5-min "C++ syntax by hand" drill before the challenge until this row closes.
- **Tutor pace:** he asked to be "pushed through": escalate hints faster (pseudocode by the 2nd miss,
  the missing line by the 3rd) instead of long Socratic loops. Still no full solutions unless asked twice.

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
| Day | Date | Systems topic | Design topic | Attempted? | Score (sys/design) | Notes |
|---|---|---|---|---|---|---|
| 001 | 2026-10-01 | Virtual functions & vtables | Order book: requirements & core ops | systems: yes (live session) | — | Live session: wrote Part A, B1 tables, B3 dispatch, clone, copy ctor himself (many hints). Tutor wrote move ctor (asked twice), copy-and-swap operator=, destroy slots + ~Shape (asked twice). Re-test him on destroy/~Shape/operator= by hand on Day 002. |
