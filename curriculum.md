# Curriculum — 10 weeks, Mon–Thu (40 days)

> **Design track paused (2026-10-01):** C++ only for now; the Design column below is kept for when
> he resumes it. Its time slot is a "C++ by hand" syntax drill instead (see `prompts/daily-run.md`).

Two tracks run in parallel every day. No sessions Fri–Sun. This is a plan, not a contract: the daily
run reorders, repeats, or splits days based on `progress.md` (weak areas get remediation days; strong
areas compress). If the plan slips, the run extends it rather than cramming.

Legend: **M** = mock interview day (no new material; timed problem + debrief). Mocks land on the
Thursday that closes every second week.

## Phase 1 — Rebuild the C++ core (Weeks 1–2)

| Day | Systems (C++) | Design (Python) |
|---|---|---|
| 001 | Virtual functions, vtables/vptr, virtual dtors, slicing, override/final | Interview framework + limit order book: requirements & core ops |
| 002 | Object lifetime, rule of 0/3/5, copy elision, value categories & move semantics | Order book internals: price levels, FIFO queues, O(1) cancel |
| 003 | RAII + smart pointers: implement `unique_ptr`; `shared_ptr` control block | Matching engine: price-time priority, partial fills, event output |
| 004 | Templates I: deduction, class templates, full/partial specialization | Order gateway + pre-trade risk checks (limits, fat-finger, throttles) |
| 005 | Templates II: SFINAE → `enable_if` → concepts; type traits | Sequencer & deterministic replay (event sourcing) |
| 006 | Variadic templates, fold expressions, perfect forwarding | Market data feed handler: seq numbers, gaps, snapshot+incremental recovery |
| 007 | CRTP & static polymorphism vs virtual (measure it); `constexpr` | Pub/sub fan-out + tick store for market data |
| 008 | **M** — Mock #1 (systems) | **M** — Mock #1 (design: order book end-to-end) |

## Phase 2 — Memory & OS (Weeks 3–4)

| Day | Systems (C++) | Design (Python) |
|---|---|---|
| 009 | Memory hierarchy, cache lines, locality (benchmark it) | Back-pressure, flow control, idempotency |
| 010 | Alignment, padding, struct layout, AoS vs SoA, false sharing | Real-time position, PnL & risk aggregation |
| 011 | Custom allocators: arena + pool; placement new | Replicated state & consensus basics (Raft at interview depth) |
| 012 | Processes vs threads, context switches, syscall cost | Reference/security master + caching & invalidation |
| 013 | Virtual memory, page tables, TLB, huge pages, page faults | Backtesting platform |
| 014 | `mmap`, shared-memory IPC; scheduling, CPU pinning, NUMA | EOD batch pipeline & job scheduling |
| 015 | Remediation day (weak areas from weeks 1–4) | Remediation day |
| 016 | **M** — Mock #2 | **M** — Mock #2 |

## Phase 3 — Concurrency & low latency (Weeks 5–6)

| Day | Systems (C++) | Design (Python) |
|---|---|---|
| 017 | Mutex, condvar, deadlock, lock ordering | Low-latency async binary logging |
| 018 | Atomics & memory ordering (acquire/release/seq_cst) | Monitoring, alerting, kill switches |
| 019 | SPSC lock-free ring buffer (TSan) | Exchange throttles & rate limiting |
| 020 | MPMC, ABA; seqlock & read-mostly patterns | Failover, hot standby, split brain |
| 021 | I/O models: blocking, `epoll`, `io_uring`; non-blocking sockets, UDP multicast | Smart order router; colocation & multi-venue |
| 022 | Kernel bypass concepts (DPDK, Onload/ef_vi), HW timestamping | Market-making system (quote engine + hedger) |
| 023 | Measuring latency: `rdtsc`, histograms, tail latency, coordinated omission | Historical data lake + research compute grid |
| 024 | **M** — Mock #3 | **M** — Mock #3 |

## Phase 4 — Internals & performance (Weeks 7–8)

| Day | Systems (C++) | Design (Python) |
|---|---|---|
| 025 | `vector` growth, iterator invalidation, exception guarantees | Distributed cache |
| 026 | `unordered_map` internals → write an open-addressing flat map | Kafka-like log / message queue |
| 027 | SSO/small-buffer optimization, `string_view`, `span`, intrusive containers | Clock sync (NTP vs PTP), event ordering |
| 028 | Cache-friendly order book in flat arrays (benchmark vs `std::map`) | Safe config & deploys in trading; drop copy & reconciliation |
| 029 | Branch prediction, inlining, `[[likely]]`, reading assembly; SIMD basics | Options pricing service at scale |
| 030 | Exceptions cost, `noexcept`; UB catalogue; linking, ODR, static init order | Alt-data ingestion pipeline |
| 031 | Remediation day | Remediation day |
| 032 | **M** — Mock #4 | **M** — Mock #4 |

## Phase 5 — Interview mode (Weeks 9–10)

Days 033–040: alternate **remediation** (from weak areas in `progress.md`, plus HRT/PDT-style
problems: cache/latency/concurrency depth, rapid C++ trivia) and **mocks** (034, 036, 038, 040).
