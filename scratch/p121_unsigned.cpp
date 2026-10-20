#include <cstddef>
#include <cstdio>
#include <vector>
using std::vector;

// His code, verbatim logic (printing trimmed), to show the warning and the conversion.
int maxProfit(vector<int>& prices) {
    size_t cheapest_price = prices[0];
    size_t profit = 0;
    for (size_t i = 0; i < prices.size(); i++) {
        int todayProfit = prices[i] - cheapest_price;
        if (todayProfit > profit) profit = todayProfit;
        if (prices[i] < cheapest_price) cheapest_price = prices[i];
    }
    return profit;
}

int main() {
    vector<int> p{7, 1, 5, 3, 6, 4};
    std::printf("returned %d (expected 5)\n", maxProfit(p));
    std::printf("-6 converted to size_t = %zu\n", static_cast<size_t>(-6));
}
