# Curriculum — Citadel Securities SWE prep · Mon–Fri · 60 min/session · paced by checkpoints

**Target:** pass Citadel Securities technical screens and superday (experienced SWE).
**Interview language: Python.** C++ is for the debugging round and systems questions.
Problems come from `research/question-bank.md` (A = runnable design + code, B = C++/systems,
C = talk-through design, D = LeetCode list). Dates live in the **Schedule** in `progress.md`.

## Principles (redesigned 2026-10-21 with him)
- **He schedules the interview when he's ready.** The plan advances by **checkpoints**, not a deadline.
  No cramming. If he asks to speed up (a real date appears), switch to *speed-up mode* below.
- **One heavy block per session**, sized to ~60 min of *his* real pace (he works full-time).
- **Retrieval practice:** every session opens with recall from memory (`qa/`), not re-reading.
- **Spacing:** topics come back after days and weeks (`qa/` spacing; Thursday interleaving; Friday mixed quizzes).
- **Interleaving:** practice days and quizzes mix in older patterns, so he learns to *recognise* the pattern,
  which is the step interviews test.
- **Worked example first, then fading help** (his C++ syntax gap): see it once, do it with scaffolding, then without.
- **Learn untimed, then practice timed.** Speed comes after understanding (Mon untimed → Thu timed → Fri quiz).

## Every session (60 min)
| Min | What |
|---|---|
| 5 | **Recall:** 3 due questions from `qa/`, answered from memory in `notes.md` |
| 45 | **One main block** (by weekday, below) |
| 10 | **Error log:** one line per mistake in `notes.md` ("swapped asks/bids", "said n² log n"). Feeds weak areas. |

## The week
| Day | Block | Shape |
|---|---|---|
| **Mon** | **DSA: learn** | New pattern. 10-min worked example (the template, when to recognise it), then 1–2 problems **untimed**. |
| **Tue** | **C++ & systems** | Concept → 5-min "C++ by hand" syntax drill → one small challenge (one TODO = one concept, tests per TODO). Debugging drills on their weeks. |
| **Wed** | **Design** | A §A runnable item (part 1 this week, part 2 next week after a 5-min recap; each part ends at a stated test count) **or** a §C talk-through (written design: diagram, data model, hot path, trade-offs). |
| **Thu** | **DSA: practice** | Monday's pattern **timed** (25 min, no hints) + 1 problem from an older pattern (interleaving). |
| **Fri** | **Quiz** (30–40 min, lighter) | Timed and graded, no hints, no new material: 1 mixed-pattern Medium (25 min) + 10 rapid-fire recall. Every 2nd quiz adds one behavioral story (2 min). **Every 4th quiz is a mock screen** (45 min CoderPad-style). |

US holidays and Fri–Sun of holiday weeks are off. The schedule is written ~8 weeks ahead; the daily run
extends it a week at a time, adjusting from quiz results and checkpoints.

## Pattern sequence (one per week; Mon learn → Thu practice → Fri quiz mixes it with older ones)
Done: arrays/hashing (121, 49), sliding window (643, 2958). Then: stacks & monotonic stack/deque → heaps
(top-K, k-way merge, running median) → intervals + binary search → BFS (grids, Word Ladder) → graphs
(topo sort, union-find) → weighted graphs (Dijkstra, Bellman-Ford, currency conversion) → DP 1-D →
DP 2-D + tries → design-style (LRU/LFU). Problems: question bank §D, Citadel-tagged first.

## C++ sequence (Tue)
Move semantics → smart-pointer internals → STL internals → **debugging drill #1** → threads + producer-consumer
→ atomics & memory ordering → lock-free SPSC ring buffer → caches / branch prediction / "make it fast" →
debugging drill #2 (data races, TSan) → virtual memory, networking basics. (Bank §B.)

## Design sequence (Wed)
Order book (A1, done in parts by Oct 22) → matching engine A2 (2 parts) → C1 market-data talk-through →
A5 conflating queue → A6 streaming stats (2 parts) → C2 order book at 1M/s → A10 reconciliation (2 parts)
→ C3/C6 risk + rate limiting → A9 k-way merge of tick files → C5 messaging/logs.

## Checkpoints (the daily run tracks these in `progress.md`)
**① Screen-ready** — tell him it's a good time to ask the recruiter for the screen (usually 2–4 weeks out; keep training).
- 2 of the last 3 graded quizzes: the Medium solved **≤ 25 min, unaided**, with restatement, input contract and
  complexity stated before coding, and edge cases traced after.
- A **mock screen passed** (score ≥ 3/4 on the rubric in `.claude/commands/mock.md`).
- Core patterns covered (learned + practiced): hashing, sliding window, stack, heap, intervals/binary search, BFS, graphs, DP 1-D.

**② Superday-ready** — tell him it's a good time to schedule the superday.
- A1 order book and A2 matching engine built; **one of them rebuilt end to end in 45 min** in a design mock.
- Three §C talk-throughs scored ≥ 3/4.
- Two C++ debugging drills scored ≥ 3/4.
- Four behavioral stories rehearsed (≤ 2 min spoken each).

Design and superday mocks are **triggered by checkpoint progress**, not fixed dates: a design mock once A1+A2
are built; a full superday mock once ① is met and ② is close.

## Speed-up mode (only when he asks, e.g. a date gets set)
Drop Wednesday talk-throughs to every other week; Mon and Thu each get 2 problems; quizzes become mock screens
every other Friday; C++ narrows to the debugging drills and "explain it" answers. Rewrite the Schedule to land a
final mock 3–4 sessions before the date, and note why in `progress.md`.

## Behavioral bank (one story every 2nd Friday quiz — STAR, ≤ 2 min spoken)
1. Most complex system you built in the past year: architecture and trade-offs
2. A production mistake you made and how you resolved it
3. Isolating the root cause of an ambiguous bug in a critical system
4. A technical compromise made to meet a deadline
5. Handling ambiguous requirements
6. Why market making / Citadel Securities rather than big tech, or staying at Bloomberg
7. Disagreeing with a senior engineer or PM
8. Your questions for them (team, on-call, bonus structure, how success is measured)
