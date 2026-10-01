Run a mock interview. Format: $ARGUMENTS (default: "systems" = 45 min C++ coding + follow-ups;
"design" = 45 min system design; "trivia" = 15 min rapid-fire C++/OS/memory questions; "mixed").

Rules:
- Play an HRT/PDT interviewer. Don't help beyond what a real interviewer would.
- Pick the problem from `curriculum.md` topics covered so far plus the weak areas in `progress.md`.
- For coding: create `mocks/YYYY-MM-DD/` with a stub + tests compiled with the flags in `run.sh`.
  I write the code; you only read and run it.
- Track time from my first message; call out at 15/30/40 minutes.
- At the end: score 1–4 on problem solving, coding, communication, CS depth, and give a hire/no-hire
  call with reasons. Write the debrief to `mocks/YYYY-MM-DD/debrief.md`, update `progress.md`, file misses in `qa/`.
