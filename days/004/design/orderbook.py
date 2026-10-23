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
from functools import reduce

import heapq

class Order:
    def __init__(self, idd, side, price, qty):
        self.idd = idd
        self.side = side
        self.price = price
        self.qty = qty
    
    def __str__(self):
        return f"Order(id={self.idd}, side={self.side}, price={self.price}, qty={self.qty})"
    

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
        
        if order_id in self.orders:
            return False

        if side == 'S':
            best_bid = self.best_bid()
            if (best_bid is not None and best_bid >= price):
                return False
    
        elif side == 'B':
            best_ask = self.best_ask()
            if (best_ask is not None and best_ask <= price):
                return False

        else:
            return False

        order = Order(order_id, side, price, qty)
        self.orders[order_id] = order

        if side == 'S':
            if not self.asks_by_price.get(price):
                self.asks_by_price[price] = dict()
                heapq.heappush(self.asks, price)
        
            self.asks_by_price[price][order_id] = order
        elif side == 'B':
            if not self.bids_by_price.get(price):
                self.bids_by_price[price] = dict()
                heapq.heappush(self.bids, -price)
        
            self.bids_by_price[price][order_id] = order
        else:
            return False
        
        return True

    def cancel(self, order_id: int) -> bool:
        """Remove a resting order. False if unknown."""
        if order_id not in self.orders:
            return False

        order = self.orders[order_id]
        
        book = self.bids_by_price if order.side == 'B' else self.asks_by_price

        del book[order.price][order_id]
        del self.orders[order_id]


        if len(book[order.price]) == 0:
            del book[order.price]
        
        return True

    """
    - modify(order_id, new_qty):
    * new_qty <= 0 → rejected (use cancel)
    * new_qty < current qty → reduce in place, KEEPS queue priority
    * new_qty > current qty → LOSES priority (moves to back of its price level)
    * new_qty == current qty → no-op, returns True
    """
    def modify(self, order_id: int, new_qty: int) -> bool:
        if new_qty <= 0:
            return False

        if order_id not in self.orders:
            return False

        order = self.orders[order_id]
        
        if order.qty == new_qty:
            return True
        elif order.qty < new_qty:
            side = order.side
            price = order.price

            self.cancel(order_id)
            self.add(order_id, side, price, new_qty)
        elif order.qty > new_qty:
            book = self.bids_by_price if order.side == 'B' else self.asks_by_price
            book[order.price][order_id].qty = new_qty
        
        return True
        
    def best_bid(self) -> int | None:
        if not self.bids:
            return None
        price = -1*self.bids[0]

        if price not in self.bids_by_price:
            heapq.heappop(self.bids)
            return self.best_bid()

        return price
            

    def best_ask(self) -> int | None:
        if not self.asks:
            return None
        price = self.asks[0]

        if price not in self.asks_by_price:
            heapq.heappop(self.asks)
            return self.best_ask()

        return price

    def depth(self, side: str, levels: int) -> list[tuple[int, int]]:
        """Top `levels` price levels on `side`, best first, as (price, total_qty)."""
        if levels <= 0:
            return []

        book = self.bids_by_price if side == 'B' else self.asks_by_price
        keys = sorted(book.keys(), reverse=(side == 'B'))
        rv = []; i = 0

        while i < levels and i < len(keys):
            price = keys[i]
            acc = 0
            for order_id in book[price]:
                acc += book[price][order_id].qty
            rv.append((price, acc))
            i += 1
        
        return rv

    def queue(self, side: str, price: int) -> list[int]:
        """Order ids resting at `price` on `side`, in priority order. [] if none."""
        book = self.bids_by_price if side == 'B' else self.asks_by_price

        if not price in book:
            return []
        return [o.idd for o in [book[price][order_id] for order_id in book[price]]]

