/*
Difficulty: Easy
*/

#include <unordered_set>
#include <vector>

class Solution {
 public:
  bool containsDuplicate(const std::vector<int>& nums) {
    std::unordered_set<int> seen;
    for (const int num : nums) {
      if (seen.find(num) != seen.cend())
        return true;
      else
        seen.insert(num);
    }

    return false;
  }
};