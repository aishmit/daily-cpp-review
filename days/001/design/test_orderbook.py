from orderbook import OrderBook


def book_with_spread():
    b = OrderBook()
    assert b.add(1, "B", 99, 10)
    assert b.add(2, "B", 98, 5)
    assert b.add(3, "S", 101, 7)
    assert b.add(4, "S", 102, 3)
    return b


def test_empty_book():
    b = OrderBook()
    assert b.best_bid() is None
    assert b.best_ask() is None
    assert b.depth("B", 5) == []
    assert b.queue("S", 100) == []


def test_best_prices_and_depth():
    b = book_with_spread()
    assert b.best_bid() == 99
    assert b.best_ask() == 101
    assert b.depth("B", 5) == [(99, 10), (98, 5)]
    assert b.depth("S", 1) == [(101, 7)]


def test_levels_aggregate_quantity():
    b = book_with_spread()
    assert b.add(5, "B", 99, 4)
    assert b.depth("B", 1) == [(99, 14)]


def test_time_priority_within_level():
    b = book_with_spread()
    b.add(5, "B", 99, 1)
    b.add(6, "B", 99, 1)
    assert b.queue("B", 99) == [1, 5, 6]


def test_rejects_invalid_orders():
    b = book_with_spread()
    assert not b.add(1, "B", 97, 1)      # duplicate id
    assert not b.add(10, "B", 97, 0)     # qty
    assert not b.add(11, "B", 0, 1)      # price
    assert not b.add(12, "X", 97, 1)     # side
    assert b.depth("B", 5) == [(99, 10), (98, 5)]


def test_post_only_rejects_crossing():
    b = book_with_spread()
    assert not b.add(20, "B", 101, 1)    # bid at best ask crosses
    assert not b.add(21, "S", 99, 1)     # ask at best bid crosses
    assert b.add(22, "B", 100, 1)        # improves the bid, doesn't cross
    assert b.best_bid() == 100


def test_cancel_removes_and_cleans_level():
    b = book_with_spread()
    assert b.cancel(3)
    assert not b.cancel(3)               # already gone
    assert not b.cancel(999)             # unknown
    assert b.best_ask() == 102           # empty level 101 disappeared
    assert b.depth("S", 5) == [(102, 3)]


def test_cancel_frees_order_id_for_reuse():
    b = book_with_spread()
    b.cancel(1)
    assert b.add(1, "B", 97, 2)          # id no longer resting → allowed
    assert b.depth("B", 5) == [(98, 5), (97, 2)]


def test_modify_down_keeps_priority():
    b = book_with_spread()
    b.add(5, "B", 99, 1)
    assert b.modify(1, 4)
    assert b.queue("B", 99) == [1, 5]
    assert b.depth("B", 1) == [(99, 5)]


def test_modify_up_loses_priority():
    b = book_with_spread()
    b.add(5, "B", 99, 1)
    assert b.modify(1, 20)
    assert b.queue("B", 99) == [5, 1]
    assert b.depth("B", 1) == [(99, 21)]


def test_modify_edge_cases():
    b = book_with_spread()
    assert b.modify(1, 10)               # same qty: no-op
    assert b.queue("B", 99) == [1]
    assert not b.modify(1, 0)            # use cancel instead
    assert not b.modify(999, 5)          # unknown
    assert b.depth("B", 1) == [(99, 10)]


def test_many_levels_sorted():
    b = OrderBook()
    for i, p in enumerate([95, 90, 97, 92, 99, 91]):
        b.add(i, "B", p, 1)
    for i, p in enumerate([110, 105, 108, 101]):
        b.add(100 + i, "S", p, 1)
    assert [p for p, _ in b.depth("B", 3)] == [99, 97, 95]
    assert [p for p, _ in b.depth("S", 3)] == [101, 105, 108]
