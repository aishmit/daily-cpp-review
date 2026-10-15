# Q&A bank

One file per topic. Every lesson adds questions; every miss in review/mock adds or re-flags one.
The daily run picks 3 warm-up questions per day: overdue `low` first, then `med`, then random `high`.

Files: `dsa-patterns.md`, `system-design.md`, `cpp-object-model.md`, `cpp-memory-and-lifetime.md`,
`cpp-templates.md`, `concurrency.md`, `os-memory.md`, `networking.md`, `behavioral.md`
(created on first use).

## Entry format

```markdown
### Q: <question, phrased like an interviewer would>
`id: cpp-om-001` · `from: day 001` · `confidence: low|med|high` · `last: 2026-10-01` · `next: 2026-10-05`

<details><summary>Answer</summary>

<crisp answer an interviewer would accept — then one line of "why it matters" / follow-up>

</details>
```

**Spacing rule:** after a recall, `low` → next session, `med` → +3 sessions, `high` → +8 sessions.
Answering wrong drops confidence to `low`. Confidence is set from *your* answers in `notes.md`.
