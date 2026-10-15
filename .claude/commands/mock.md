Run a Citadel Securities–style mock interview. Format: $ARGUMENTS
- `screen` (default): 45 min CoderPad-style. 5 min resume deep-dive, then 1 medium–hard DSA problem in Python with a follow-up.
- `design`: 45 min trading-system design (e.g. order book service at ~1M updates/s, market-data feed handler, median across feeds).
- `systems`: 30 min. C++ "find the bug" on a ~60-line snippet, then systems questions (threads/processes, cache, page faults, TCP/UDP, atomics).
- `trivia`: 15 min rapid-fire C++/OS/networking.
- `superday`: screen → systems → design → 10 min behavioral, back to back.

Rules:
- Play the interviewer. Help only as much as a real one would. Pick problems from `research/citadel-securities.md`,
  topics covered so far in `curriculum.md`, and weak areas in `progress.md`.
- Coding: create `mocks/YYYY-MM-DD/` with a stub and hidden tests (Python, or C++ for `systems`). He writes the code; you read and run it.
- Call time at 15/30/40 min. Note whether he pinned down the input contract, stated a brute force, and tested edge cases.
- End: score 1–4 on problem solving, coding, communication and CS depth, plus a hire/no-hire call with reasons.
  Write `mocks/YYYY-MM-DD/debrief.md`, update `progress.md`, and file misses in `qa/`.
