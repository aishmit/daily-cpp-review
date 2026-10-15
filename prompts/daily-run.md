# Daily run — instructions for the scheduled Claude session

You are running unattended at ~6 PM ET, Mon–Thu, for Aishmit's hedge-fund SWE interview prep.
Use maximum care: this is high priority and he wants to genuinely learn. Read `CLAUDE.md` first.

> **C++ only for now (decided 2026-10-01).** The design (Python) track is **paused**: write no
> `design/` folder, no design lesson, no design scores. The freed time goes to a short "C++ by hand"
> drill (see §3). Resume design only when he asks; the design column in `curriculum.md` is kept for then.
> Also read the "Calibration notes" in `progress.md` before writing; they set the difficulty.

## 0. Setup
- Ensure `aishmit/daily-cpp-review` is cloned (attach it with push access if it isn't), `git pull`.
- Read: `CLAUDE.md`, `curriculum.md`, `progress.md`, `qa/README.md`, and every file in the
  most recent two `days/NNN/` folders (including his `notes.md` and code).
- Determine the next day number N = last published day + 1.

## 1. Review (always do this before writing new material)
For each published day without a `review.md` where he committed work since publication
(`git log -- days/NNN/`):
- Run `./run.sh NNN` (and `SAN=thread` on concurrency days). Record results.
- Read his code and `notes.md` carefully. Write `days/NNN/review.md`:
  - **Verdict** (one line) and score 1–4 for systems.
  - What's correct; what's wrong (cite lines); edge cases missed; C++ idiom/safety/perf issues.
  - His recall answers: right/wrong, with the correct answer for anything wrong.
  - 2 interviewer follow-up questions he should be able to answer next (answers collapsed).
  - Do NOT paste a full rewritten solution; show only the minimal diff/idea per issue.
- Update `qa/`: set confidence from his answers; add a `low` entry for every miss.
- Update `progress.md`: day log row (attempted, scores, notes), weak-areas table (add/close).
If a day was never attempted, note it in the log; don't review.

## 2. Decide today's material
- Default: day N from `curriculum.md`.
- If 2+ published days are unattempted → today is a **catch-up day**: no new topic; a short recap of
  the backlog + 3 recall questions, and say so in the notification.
- If a weak area has failed twice → insert a remediation day on it before continuing; shift the
  curriculum (edit `curriculum.md`, note why in `progress.md`).
- Mock days: create `days/NNN/mock.md` with one timed systems problem (stub + tests) plus a short
  C++ trivia round, and the scoring rubric from `.claude/commands/mock.md`. He runs it with `/mock` in Claude Code.

## 3. Write `days/NNN/`
Budget: ~30 min core + optional deep dive. Quality over breadth. Every concept must be correct —
compile and run every snippet you include.

`lesson.md`:
1. **Warm-up recall** — 3 questions from `qa/` (due ones first). Questions only; answers are in `qa/`.
2. **Systems** (~7 min read): the mental model, what the compiler/CPU/OS actually does, a compiled
   snippet with real output, the 3 things interviewers probe, common traps. Build on prior days
   explicitly ("Day 001's vptr is why…").
3. **Systems challenge** brief: what to implement in `systems/`, how to run it, what "done" means.
4. **C++ by hand** (~10 min): 4–6 tiny write-it-yourself snippets drilling the exact syntax today's
   challenge needs (casts, lambdas → function pointers, calling through a function pointer, ctor
   init lists, `std::swap`, …), plus any syntax row still open in the weak-areas table. Each with the
   expected output; put them in `systems/drill.cpp` with TODOs and checks.
5. **Deep dive (optional)**: one stretch problem + 2–4 resources. Verify every link resolves
   (WebFetch) before including it; prefer cppreference, the Itanium ABI, LWN, kernel docs,
   Agner Fog, Drepper's "What Every Programmer Should Know About Memory", CppCon talks (verified URLs).
6. **Notes prompt** — what to write in `notes.md` (recall answers + 2-line reflection + confidence 1–5).

`systems/`: `challenge.hpp` (stubs with TODOs, compiles), `test_challenge.cpp` (uses
`common/check.hpp`; tests fail on stubs, pass on a correct solution). Optional `predict.cpp`
("predict the output" exercise). Verify: stub compiles and fails; a private reference solution
(NOT committed) passes under ASan+UBSan with both g++ and clang++.

Add the day's new questions (5–8) to the right `qa/*.md` file, `confidence: low`, `next` = next session.

## 4. Commit, push, notify
- Update `progress.md` status (current day, next mock).
- Commit: `day NNN: <systems topic>` (+ `review NNN-1` if reviewed). Push to main.
- Send him a message (this is the "post"): 
  - Gist in 2 lines (today's topic + why it matters for HF interviews)
  - Review headline of the previous day (score + biggest fix) if any
  - The 3 warm-up questions
  - "`git pull && ./run.sh NNN`"
- If push fails, still send the message with the lesson content inline and say the push failed.
