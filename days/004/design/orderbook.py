"""Day 004 — Design, part 2: finish the passive limit order book (no matching yet).
Run: ./run.sh 004

Below the spec is YOUR Day 002 code, copied verbatim. Part 2 = make all 16 tests green
(the 12 from Day 002 + 4 new ones). Order of work: lesson.md §2.

Rules (this is the spec — read it like an interviewer handed it to you):
- Prices are integer ticks (never floats). Quantities are positive ints.
- Sides are "B" (bid/buy) and "S" (ask/sell).
- Price-time priority: better price first; at the same price, earlier order first.
- This book is *post-only*: an order that would cross the book (bid >= best ask, or
  ask <= best bid) is rejected. Matching arrives with the matching engine (A2, Wed Oct 28).
- add() rejects: duplicate order id, qty <= 0, price <= 0, bad side, or would-cross.
  A rejected add() changes NOTHING (the id stays free).
- modify(order_id, new_qty):
    * new_qty <= 0 → rejected (use cancel)
    * new_qty < current qty → reduce in place, KEEPS queue priority
    * new_qty > current qty → LOSES priority (moves to back of its price level)
    * new_qty == current qty → no-op, returns True
- Empty price levels must disappear (depth never shows a level with 0 qty).
- depth(side, levels): levels <= 0 → []; fewer levels than asked → all of them.

When it's green, write the complexity of each operation in notes.md (L = number of levels
on a side, k = orders at one level).
"""
from __future__ import annotations

import heapq

class Order:
    def __init__(self, idd, side, price, qty):
        self.idd = idd
        self.side = side
        self.price = price
        self.qty = qty

class OrderBook:
    def __init__(self) -> None:
        self.asks = []
        self.bids = []
        self.asks_by_price = dict()
        self.bids_by_price = dict()
        self.orders = dict()

        pass

    def add(self, order_id: int, side: str, price: int, qty: int) -> bool:

        if price <= 0 or qty <= 0:
            return False
        
        if self.orders.get(order_id):
            return False

        order = Order(order_id, side, price, qty)
        self.orders[order_id] = order

        if side == 'S':
            if (self.best_bid() and self.best_bid() >= price):
                return False
            
            if not self.asks_by_price.get(price):
                self.asks_by_price[price] = dict()
                heapq.heappush(self.asks, price)

        
            self.asks_by_price[price][order_id] = qty

        elif side == 'B':
            if (self.best_ask() and self.best_ask() <= price):
                return False

            if not self.bids_by_price.get(price):
                self.bids_by_price[price] = dict()
                heapq.heappush(self.bids, -price)
        
            self.bids_by_price[price][order_id] = qty

        else:
            return False
        
        return True

    def cancel(self, order_id: int) -> bool:
        """Remove a resting order. False if unknown."""
        raise NotImplementedError


    """
    - modify(order_id, new_qty):
    * new_qty <= 0 → rejected (use cancel)
    * new_qty < current qty → reduce in place, KEEPS queue priority
    * new_qty > current qty → LOSES priority (moves to back of its price level)
    * new_qty == current qty → no-op, returns True
    """
    def modify(self, order_id: int, new_qty: int) -> bool:
        raise NotImplementedError

    def best_bid(self) -> int | None:
        if not self.bids:
            return None
        price = -1*self.bids[0]
        return price
            

    def best_ask(self) -> int | None:
        if not self.asks:
            return None
        price = self.asks[0]
        return price

    def depth(self, side: str, levels: int) -> list[tuple[int, int]]:
        """Top `levels` price levels on `side`, best first, as (price, total_qty)."""
        raise NotImplementedError

    def queue(self, side: str, price: int) -> list[int]:
        """Order ids resting at `price` on `side`, in priority order. [] if none."""
        raise NotImplementedError
