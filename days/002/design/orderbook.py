"""Day 002 — Design challenge: a passive limit order book (no matching yet).

Run: ./run.sh 002

Rules (this is the spec — read it like an interviewer handed it to you):
- Prices are integer ticks (never floats). Quantities are positive ints.
- Sides are "B" (bid/buy) and "S" (ask/sell).
- Price-time priority: better price first; at the same price, earlier order first.
- This book is *post-only*: an order that would cross the book (bid >= best ask, or
  ask <= best bid) is rejected. Matching arrives on Day 004.
- add() rejects: duplicate order id, qty <= 0, price <= 0, bad side, or would-cross.
- modify(order_id, new_qty):
    * new_qty <= 0 → rejected (use cancel)
    * new_qty < current qty → reduce in place, KEEPS queue priority
    * new_qty > current qty → LOSES priority (moves to back of its price level)
    * new_qty == current qty → no-op, returns True
- Empty price levels must disappear (depth never shows a level with 0 qty).

Today: correctness first. Don't worry about complexity yet — but write down in notes.md
what the complexity of each operation is in your version. Day 004 makes cancel O(1).
"""
from __future__ import annotations


class OrderBook:
    def __init__(self) -> None:
        # TODO: choose your data structures. (Think: how do you find the best price?
        # how do you find an order by id? how do you keep FIFO within a price?)
        pass

    def add(self, order_id: int, side: str, price: int, qty: int) -> bool:
        raise NotImplementedError

    def cancel(self, order_id: int) -> bool:
        """Remove a resting order. False if unknown."""
        raise NotImplementedError

    def modify(self, order_id: int, new_qty: int) -> bool:
        raise NotImplementedError

    def best_bid(self) -> int | None:
        raise NotImplementedError

    def best_ask(self) -> int | None:
        raise NotImplementedError

    def depth(self, side: str, levels: int) -> list[tuple[int, int]]:
        """Top `levels` price levels on `side`, best first, as (price, total_qty)."""
        raise NotImplementedError

    def queue(self, side: str, price: int) -> list[int]:
        """Order ids resting at `price` on `side`, in priority order. [] if none."""
        raise NotImplementedError
