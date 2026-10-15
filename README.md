# daily-cpp-review

A weekday learning loop to get interview-ready for SWE roles at top hedge funds / prop shops
(north star: **HRT, PDT**; also Citadel / Citadel Securities, Jane Street, Two Sigma, Jump, Millennium).

Every **Mon–Thu at ~6 PM ET** a scheduled Claude run (Opus) reviews whatever you pushed since the
last run, then writes that evening's material into this repo. Fri–Sun are off.

## A day = ~30 min core (+ optional deep dive)

> **C++ only for now (2026-10-01):** the design rows below are paused and replaced by a ~10 min
> "C++ by hand" syntax drill. They come back when you ask for them.

| Block | Time | Language | What |
|---|---|---|---|
| Warm-up recall | 3 min | — | 3 questions pulled from `qa/` (spaced repetition) |
| Systems lesson | 7 min | C++ | C++ / memory / OS / concurrency / low-latency concept |
| Systems challenge | 8 min | C++ | compiled, tested under ASan + UBSan (TSan on concurrency days) |
| Design lesson | 5 min | — | architecture for trading/finance systems |
| Design challenge | 7 min | Python | build the core component of the design, with tests |
| Deep dive (optional) | 15–45 min | either | stretch problem + reading list |

The Thursday closing every second week is a **mock interview day** (Days 008, 016, 024, 032, then
every other day in weeks 9–10). You can also run `/mock` in Claude Code any time.

## Your loop

```bash
git pull
cat days/NNN/lesson.md           # read it (or open in your editor)
./run.sh NNN                     # build + test systems (C++) and design (Python)
# ... solve the TODOs, write days/NNN/notes.md (answers to the recall + reflection) ...
git add -A && git commit -m "day NNN" && git push
```

The next evening's run reads your code + `notes.md`, writes `days/NNN/review.md`,
updates `progress.md` (weak areas), and files new questions in `qa/`.

## Layout

```
CLAUDE.md            rules for Claude Code in this repo (tutor mode — it won't just write your code)
curriculum.md        10-week, two-track syllabus (adapts based on progress)
progress.md          day log, weak areas, recall schedule — the loop's memory
qa/                  question & answer bank by topic (answers collapsed)
days/NNN/            lesson.md, systems/ (C++), design/ (Python), notes.md (you), review.md (Claude)
common/              tiny header-only test harness + python test runner
prompts/daily-run.md the full instructions the scheduled run follows
run.sh               build/test a day
.claude/commands/    /hint, /review, /mock, /explain slash commands for Claude Code
```

## Working with Claude Code here

- `/hint` — escalating hints (concept → approach → pseudocode). Never full code.
- `/review` — review your current solution like a strict interviewer would.
- `/explain <topic>` — deep explanation with a compiled demo you can poke at.
- `/mock` — timed mock interview (systems, design, or mixed).
- Ask for a solution explicitly ("show me the solution") and it will — after one more nudge.
