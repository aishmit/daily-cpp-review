# 2958. Length of Longest Subarray With at Most K Frequency — written by Aishmit, Tue Oct 20 (~20 min, 20-min timer, no hints). Saved verbatim.
# Complexity: O(n) time amortized (each index enters and leaves the window at most once), O(n) space.
from typing import List
class Solution:
    def maxSubarrayLength(self, nums: List[int], k: int) -> int:
        left = 0
        right = 0

        curr_state = {}
        curr_good = 0
        max_good = 0

        def good(num):
            if not curr_state.get(num) or curr_state[num] < k:
                return True

            return False


        while right < len(nums):
            if not good(nums[right]):
                curr_state[nums[left]] -= 1
                curr_good -= 1
                left += 1
            else:
                if curr_state.get(nums[right]):
                    curr_state[nums[right]] += 1
                else:
                    curr_state[nums[right]] = 1
                
                curr_good += 1
                right += 1
                if curr_good > max_good:
                    max_good = curr_good

        return max_good
