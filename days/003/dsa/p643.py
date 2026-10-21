# 643. Maximum Average Subarray I — written by Aishmit, Tue Oct 20 (~20 min vs a 10-min timer, no hints). Saved verbatim.
# Complexity: O(n) time, O(1) space (running sum).
class Solution:
    def findMaxAverage(self, nums: list[int], k: int) -> float:
        n = len(nums)
        if k > n:
            k = n

        k = min(n,k)
        max_sum = float('-inf')
        curr_sum = 0

        for j in range(k):
            curr_sum += nums[j]
        
        if curr_sum > max_sum:
            max_sum = curr_sum
                
        for i in range(1,n):
            if i + k > n:
                break
            print(curr_sum)
            
            curr_sum -= nums[i-1]
            curr_sum += nums[i+k-1]

            if curr_sum > max_sum:
                max_sum = curr_sum

        return max_sum/k
