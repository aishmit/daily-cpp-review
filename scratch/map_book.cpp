// One side of an order book as std::map: price → total qty (orders omitted to keep it short).
// Build: c++ -std=c++20 -Wall -Wextra -Werror -fsanitize=address,undefined -g scratch/map_book.cpp -o build/map_book && ./build/map_book
#include <cstdio>
#include <functional>
#include <map>

int main() {
    std::map<int, int, std::greater<int>> bids;   // greater → highest price first, so begin() is the best bid
    bids[99] = 10;
    bids[98] = 5;
    bids[97] = 2;

    std::printf("best bid: %d\n", bids.begin()->first);       // O(1)

    bids.erase(99);                                            // last order at 99 cancelled → remove the price, O(log n)
    std::printf("after erase(99), best bid: %d\n", bids.begin()->first);

    std::printf("depth, top 2:");
    int n = 0;
    for (auto it = bids.begin(); it != bids.end() && n < 2; ++it, ++n)   // already in order: just walk
        std::printf(" (%d, %d)", it->first, it->second);
    std::printf("\n");
}
