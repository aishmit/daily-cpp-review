# Citadel Securities — what's been asked (research, 2026-10-15)

Public reports only. "First-hand" = a candidate's own write-up; "aggregator" = prep-site compilations.
Several sites mix **Citadel** (hedge fund) and **Citadel Securities** (market maker): treat those with care.

## Process (as reported)
1. Recruiter call (for outreach candidates, sometimes a call with the team head first). "Varies by team."
2. HackerRank OA: 2–3 problems, around LeetCode easy–medium. Sometimes skipped for outreach candidates.
3. 1–2 technical screens: CoderPad, ~45 min, resume deep-dive + live coding.
4. Superday: 3–5 × 45–60 min (coding, systems/design, behavioral).
5. Leadership / team-match call. Total ~3–8 weeks; feedback can be slow.
Language: the firm says any language is welcome; C++ is an advantage for engineering roles.

## First-hand questions
- Order book string-processing problem, described as "standard DSA" (Glassdoor, Jun 2026)
- **"Heavy C++ debugging"** round (Glassdoor, Jun 2026)
- "Reconstruct a stack processed by a worker" (options team, Glassdoor, Aug 2026)
- Open-ended systems design with trade-offs (Glassdoor, Aug 2026)
- Best exchange rate from currency A to B from a rate list. The candidate missed edge cases like self-loops (LeetCode Discuss, Citadel senior)
- Word Ladder II variant. Dinged for DFS instead of BFS for the shortest path (same post)
- K-way merge of files on disk with a min-heap (experienced hire, Apr 2026, via QuantT)
- "What is the cost of an `if` at the hardware level?", i.e. branch prediction (Taro, Citadel)

## Aggregator themes (PracHub, Dataford, QuantT)
- In-memory order book: price-time priority, level aggregation, cancel
- Simple stock exchange / matching engine with heaps → trades + remaining book
- Currency arbitrage: return a profitable cycle (Bellman-Ford on −log rates)
- Thread-safe producer-consumer queue: mutex → spinlock → lock-free
- Conflating quote queue that keeps only the latest price per symbol
- SPSC / thread-safe ring buffer
- Streaming: top-K, sliding-window max/mean, rolling median of trades
- Topological sort (parallel courses variant)
- Explain: thread vs process, cache miss vs page fault, TCP vs UDP, multicast packet loss,
  vtables, `shared_ptr`, atomics, `std::any` / `unordered_map` internals
- Design: order book at ~1M updates/s, median price across feeds, high-throughput messaging,
  log aggregation across colos
- Behavioral: complex project, production mistake, ambiguity, why low-latency trading

## Pitfalls reported
Missing edge cases (self-loops, empty input, duplicates) · DFS where BFS is needed for shortest paths ·
floats for prices · coding before pinning down the input contract · shared mutable state with no owner.

## Sources
- https://www.glassdoor.com/Interview/Citadel-Securities-Software-Engineer-Interview-Questions-EI_IE1443495.0,18_KO19,36.htm
- https://leetcode.com/discuss/interview-experience/5565531/Citadel-or-Senior-Software-Engineer-or-Reject/
- https://www.jointaro.com/interviews/companies/citadel/experiences/software-engineer-united-states-october-20-2024-declined-offer-positive-453525fb/
- https://prachub.com/interview-guide/citadel-securities-software-engineer-interview-questions-guide-2026
- https://dataford.io/interview-guides/citadel-securities/software-engineer
- https://www.quantt.co.uk/resources/citadel-interview
