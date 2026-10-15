# Daily run — instructions for the scheduled Claude session

You run unattended at ~6 PM ET, Mon–Thu, for Aishmit's **Citadel Securities** SWE interview prep.
Read `CLAUDE.md`, then the Status, Calibration notes and Schedule in `progress.md`, then
`curriculum.md` and `research/citadel-securities.md`. Use maximum care: he wants to actually pass.

## 0. Setup
- Ensure `aishmit/daily-cpp-review` is cloned with push access; `git pull`.
- Today's day number N = the Schedule row for today's date in `progress.md`. No row for today
  (holiday, Fri–Sun) → send nothing and stop.
- Read every file in the two most recent `days/NNN/` folders (lesson, his code, `notes.md`, `dsa/`).
- Day 001 (vtables, Oct 1) is done and needs no review; its outcome is in the day log.

## 1. Review (always first)
For each day before N without a `review.md` where he committed work (`git log -- days/NNN/`):
- Track block: `./run.sh NNN` (`SAN=thread` on concurrency days). Read his code.
- DSA: read his LeetCode log in `notes.md` and any solutions in `days/NNN/dsa/`. For each, check
  correctness, complexity, the edge cases Citadel reports flag, and code clarity. Under 25 min and no
  hints = interview-ready for that pattern.
- Write `days/NNN/review.md`: one-line verdict; score 1–4 for DSA and for the track; what's right;
  what's wrong (cite lines); missed edge cases; his recall answers right/wrong with corrections;
  2 interviewer follow-ups (answers collapsed). No full rewritten solutions, only the minimal fix per issue.
- Update `qa/` (confidence from his answers; a `low` entry per miss) and `progress.md`
  (DSA log rows, day log, weak areas).
Not attempted → note it in the day log; don't review.

## 2. Decide today
- If `days/N/` already exists (pre-written) → don't rewrite it; only check it's coherent with
  the latest review (add a "Before you start" note at the top of its lesson if a fix is needed).
- Otherwise use the curriculum row for N, adjusted:
  - 2+ unattempted days → **catch-up day**: no new track topic; 1 DSA problem + finish the oldest backlog item.
  - A DSA pattern failed twice (over 30 min or needed a hint step 3+) → repeat that pattern today
    with a different problem.
  - A track topic scored ≤ 2 → put a 10-min remediation section at the top of today's lesson.
  - Screen date known (in Status) → compress the plan so a mock lands 3–4 sessions before it;
    edit `curriculum.md` and the Schedule, and note why.

## 3. Write `days/N/`
Budget: 60 min total. Quality over breadth. Compile or run every snippet. Verify every link
(WebFetch) before including it.

`lesson.md` sections, in order:
1. **Warm-up (5 min):** 3 due questions from `qa/` (questions only).
2. **DSA (30 min):** 1 medium (2 problems on easy-pattern days) from this week's pattern on
   LeetCode, chosen to match the reported Citadel style. Give the number, title and URL
   (verify it resolves), the pattern name, and a 3-line "how to practice it": timer at 25 min;
   say the brute force first; list edge cases before coding. **No hints in the lesson.**
   Add a stretch problem.
3. **Track (25 min), even N = design:** requirements → API → data model → hot path → scale/failure
   → trade-offs, for a trading system; ASCII diagram; what Citadel interviewers push on. Then a
   Python challenge in `design/` (`<component>.py` stub + `test_<component>.py`).
   **Odd N = C++ & systems:** the concept (what the compiler/CPU/OS actually does), then a
   **5-min "C++ by hand" drill** (`systems/drill.cpp`: 4–6 tiny TODOs with checks, drilling the exact
   syntax today's challenge needs plus any syntax row still open in the weak areas), a **worked
   syntax example** before each exercise, then small steps in `systems/` (`challenge.hpp` stubs +
   `test_*.cpp`, one TODO = one concept, tests that fail one concept at a time) or a "find the bug"
   drill on debugging days. Keep the concept part short: the debugging round and "explain how X works"
   questions are the targets, not language-lawyer depth.
   Verify: the stub compiles and fails; a private reference solution (**not committed**) passes
   (ASan+UBSan, g++ and clang++).
4. **Behavioral (every 4th session):** the next story from the bank in `curriculum.md`.
5. **Optional deep dive:** 1 stretch item + 2–3 verified resources.
6. **Notes template** for `notes.md`: recall answers; the DSA log (problem, time, solved
   without hints?, what tripped him up); track reflection; confidence 1–5; questions.

Add 4–6 new `qa/` entries (`confidence: low`, `next` = next session).

## 4. Commit, push, notify
- Update `progress.md` Status (current day).
- Commit `day NNN: <DSA pattern> / <track topic>` (+ `review NNN-1`). Push to main.
- Send him the post with SendUserMessage:
  - 2-line gist: today's DSA pattern and track topic, and why each shows up at Citadel Securities
  - the previous day's review headline (scores + the single biggest fix), if any
  - the LeetCode link(s) and the 3 warm-up questions
  - `git pull && ./run.sh NNN`
- If the push fails: say so in the first line, explain that the Claude GitHub App needs access to the
  repo (https://github.com/apps/claude/installations/select_target), and include the full lesson
  inline so nothing is lost.
