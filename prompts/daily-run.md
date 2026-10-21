# Daily run — instructions for the scheduled Claude session

You run unattended at ~6 PM ET, **Mon–Fri**, for Aishmit's **Citadel Securities** SWE interview prep.
Read `CLAUDE.md`, then in `progress.md` the Status, Checkpoints, Schedule and Calibration notes, then
`curriculum.md`, `research/question-bank.md` and `research/citadel-securities.md`.
He works full-time: **one heavy block per session, ~60 min at his real pace.** He schedules the interview when
ready; the plan is paced by checkpoints. Never cram. Use maximum care: he wants to actually pass.

## 0. Setup
- The repo is attached as this session's source; `cd` into it and `git pull`.
- Today's day number N and session **type** = the Schedule row for today's date in `progress.md`.
  No row (weekend, holiday) → send nothing and stop.
- A row that says "already written / don't write a new day" → skip §3; still do §1 and send a short reminder post.
- Read every file in the two most recent `days/NNN/` folders (lesson, his code, `notes.md`, `dsa/`).

## 1. Review (always first)
For each earlier day without a `review.md` where he committed work (`git log -- days/NNN/`):
- Run his code: `./run.sh NNN` for `systems/` and `design/` (`SAN=thread` on concurrency days); run each
  `dsa/*.py` against the LeetCode examples plus edge cases (empty, n=1, duplicates, all-equal) and, where cheap,
  against a brute force on random inputs.
- Write `days/NNN/review.md`: one-line verdict; a score 1–4 per block done; what's right; what's wrong (cite
  lines); missed edge cases; his recall answers right/wrong with corrections; his **error log**, and whether a
  mistake repeats an open weak area; 2 interviewer follow-ups (answers collapsed). Only the minimal fix per issue.
- **Quiz / mock days:** grade strictly by the rubric in §3e. Add a row to the **Quiz & mock log**. Update
  **Checkpoints**. If a checkpoint is newly met, say so first in today's post (① → "good time to ask the
  recruiter for the screen"; ② → "good time to schedule the superday").
- Update `qa/` (confidence from his answers; a `low` entry per miss) and `progress.md` (DSA log rows, day log,
  weak areas, error-log repeats).
Not attempted → note it in the day log; don't review.

## 2. Decide today
- Default: the Schedule row's type and topic. Adjust:
  - **2+ unattempted sessions** → catch-up: today becomes the oldest unfinished block (don't pile on new material).
    Shift the Schedule back by the number of sessions caught up, and say so in the post.
  - A pattern **missed twice** (over 30 min, or hint level 3+) → Thursday or Friday repeats it with a new problem.
  - A block **scored ≤ 2** → a 10-min remediation section at the top of the next session of that type.
  - A **quiz below the bar** → the next quiz retests the same weak pattern.
- **Every Friday:** extend the Schedule by one week (keep ~6 weeks ahead) following `curriculum.md`.
- **Mocks beyond the fixed "every 4th quiz"** are checkpoint-triggered (see `curriculum.md`): a design mock once A1
  and A2 are built; a full superday mock once ① is met and ② is close. Put them on a Friday.
- **Speed-up mode** only if `progress.md` Status says he asked for it (see `curriculum.md`).

## 3. Write `days/N/` by session type
Compile or run every snippet. Verify every link (WebFetch, or the search index if blocked). Each lesson starts with:
**Warm-up (5 min):** 3 due questions from `qa/`, questions only, worded so they stand alone (no "remember Day X's
code" context needed). It ends with a **notes template** for `notes.md`: recall answers; the block's log;
the **error log** (one line per mistake); confidence 1–5; questions.

**a) DSA learn (Mon), 45 min.** The pattern's template in 10 min: when to recognise it, the loop shape, the
invariant, one fully worked example (a different problem from today's), common bugs. Then 1–2 problems from bank §D,
**untimed**, easiest first. Before coding he writes restatement, input contract, brute force + complexity.
No hints in the lesson. Save path: `days/N/dsa/pNNN.py`.

**b) C++ & systems (Tue), 45 min.** Concept (what the compiler/CPU/OS does) in ≤ 10 min → **5-min syntax drill**
(`systems/drill.cpp`, 4–6 tiny TODOs, the exact syntax today needs plus open syntax weak areas) → a **worked
example before each exercise** → one small challenge (`challenge.hpp` + `test_*.cpp` per TODO, one TODO = one concept,
tests fail one concept at a time). Debugging weeks: a "find the bugs" file instead. Verify: stubs compile and fail;
a private reference (**not committed**) passes under ASan+UBSan with g++ and clang++.

**c) Design (Wed), 45 min.** The curriculum's bank item.
- **§A runnable, part 1:** requirements → API → data model → hot path (≤ 10 min), then a Python stub + tests in
  `design/`. Say exactly **which tests part 1 should turn green**. **Part 2** (next week): a 5-min recap of his part-1
  code first, then finish to all green. Same verification as above (private reference, not committed).
- **§C talk-through:** no code. He writes the design in `notes.md`: requirements, ASCII diagram, data model, hot
  path, scale & failure, trade-offs. Give the prompt, the follow-ups an interviewer would push, and the rubric.

**d) DSA practice (Thu), 45 min.** One Medium from Monday's pattern, **timed 25 min, no hints**, then one problem
from an older pattern (interleaving), 15 min. He records times. Same before-coding steps.

**e) Quiz (Fri), 30–40 min.** Lighter, no new material. `quiz.md`: one Medium from a **mixed** older pattern
(don't name the pattern), 25-min timer, no hints; then 10 rapid recall questions (one line each, answers in `qa/`).
Every 2nd quiz: one behavioral story from the bank (≤ 2 min, he writes bullet points). He writes his start and end
time. **Mock screen** (every 4th quiz, and checkpoint-triggered mocks): a 45-min CoderPad-style session with a
recruiter-style intro, one problem plus follow-ups; he runs it with `/mock`.
**Rubric (1–4), used in §1:** 4 = correct, ≤ 25 min, unaided, contract + complexity stated before coding, edge cases
traced; 3 = correct and unaided but slow (≤ 35 min) or one step skipped; 2 = needed a hint or a bug left; 1 = not solved.

**Behavioral** happens only on Fridays (above). Add 3–5 new `qa/` entries per session (`confidence: low`).

## 4. Commit, push, notify
- Update `progress.md` Status (current session, next session's type).
- Commit `day NNN: <type>: <topic>` (+ `review NNN-1`). Push to main.
- Send him the post with SendUserMessage, short:
  - a checkpoint line first if one was newly met
  - 2 lines: today's block and why it shows up at Citadel Securities
  - the previous session's review headline (score + the single biggest fix), if any
  - today's links and the 3 warm-up questions
  - `git pull && ./run.sh NNN` (or "open `days/NNN/quiz.md`" on Fridays)
- If the push fails: say so in the first line and include the full lesson inline.
