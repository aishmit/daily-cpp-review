# daily-cpp-review → Citadel Securities prep

A Mon–Fri, 60-minute loop (Mon DSA learn · Tue C++ · Wed design · Thu DSA timed · Fri quiz) to pass the **Citadel Securities** SWE screens and superday.
Coding rounds in **Python**; C++ studied for the debugging round and systems questions.
Plan: `curriculum.md` · What's been asked: `research/citadel-securities.md`.

Every **Mon–Fri at ~6 PM ET** a scheduled Claude run reviews what you pushed, then publishes
(or assigns) that evening's session. Fri–Sun are off.

## A session = 60 min
| Block | Min | What |
|---|---|---|
| Warm-up | 5 | 3 recall questions from `qa/` |
| DSA | 30 | 1–2 LeetCode problems in Python, timed. Log each one in `notes.md` |
| Track | 25 | Even days: system design (`design/`, Python) · Odd days: C++ & systems (`systems/`, C++) |

Every 4th session: one behavioral story too. Mocks: Day 017 (screen), 028 (design), 030/033 (superday).

## Your loop
```bash
git pull
open days/NNN/lesson.md          # or your editor
# DSA: solve the LeetCode problems listed in the lesson; optional: save solutions in days/NNN/dsa/
./run.sh NNN                     # tests for the track block
# write days/NNN/notes.md (template at the bottom of each lesson)
git add -A && git commit -m "day NNN" && git push
```
The next evening's run reads your code, LeetCode log and notes, writes `days/NNN/review.md`,
updates `progress.md` (weak patterns and topics), and files misses in `qa/`.

## Claude Code in this repo
`/hint` escalating hints (works for LeetCode too: paste the problem) · `/review` strict interviewer review ·
`/explain <topic>` deep dive with a runnable demo · `/mock screen|design|superday|trivia`.
Claude won't write your solutions unless you ask twice.

## Layout
```
curriculum.md          8-week plan (adapts to your screen date and weak areas)
progress.md            status, schedule, DSA log, weak areas, calibration notes
research/              what Citadel Securities has asked (sources inside)
qa/                    question & answer bank by topic, spaced recall
days/NNN/              lesson.md, design/ or systems/, dsa/ (optional), notes.md (you), review.md (Claude)
common/                tiny C++ test harness + Python test runner
prompts/daily-run.md   what the scheduled run does
run.sh                 build + test a day
```
