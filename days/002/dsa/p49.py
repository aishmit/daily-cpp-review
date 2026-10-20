# 49. Group Anagrams — written by Aishmit, Mon Oct 19 (~9 min, no hints). Saved verbatim.
# Complexity: O(n · k log k), n = number of words, k = max word length.
# Follow-up (discussed): a 26-count tuple key makes it O(n · k).
class Solution:
    def groupAnagrams(self, strs: list[str]) -> list[list[str]]:
        groups = []
        anagram_dict = dict()


        for word in strs:
            anagram_base = "".join(sorted(word))

            if not anagram_base in anagram_dict:
                anagram_dict[anagram_base] = [word]
            else:
                anagram_dict[anagram_base].append(word)
            
        for grouping in anagram_dict.values():
            groups.append(grouping)
        
        return groups
