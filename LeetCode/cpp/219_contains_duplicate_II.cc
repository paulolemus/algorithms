/*
Difficulty: Easy
*/

#include <cmath>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  bool containsNearbyDuplicate(const std::vector<int>& nums, const int k) {
    // num -> index
    std::unordered_map<int, int> seenIndices;

    for (int i = 0; i < nums.size(); ++i) {
      const int num = nums[i];
      const auto it = seenIndices.find(num);

      if (it != seenIndices.cend() && std::abs(i - it->second) <= k) {
        return true;
      } else {
        seenIndices[num] = i;
      }
    }

    return false;
  }
};