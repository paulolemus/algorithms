/*
Difficulty: Easy
*/

#include <cstddef>
#include <unordered_map>
#include <utility>
#include <vector>

class Solution {
 public:
  /// Time: O(n + m), Space: O(n)
  /// n = nums1.size(), m = nums2.size(), n <= m
  std::vector<int> nextGreaterElement(std::vector<int>& nums1,
                                      const std::vector<int>& nums2) {
    // value -> next greater value
    std::unordered_map<int, int> nextGreater;
    for (const int num : nums1) {
      nextGreater[num] = -1;
    }

    std::vector<int> stack;
    for (const int currNum : nums2) {
      while (!stack.empty() && stack.back() < currNum) {
        nextGreater[stack.back()] = currNum;
        stack.pop_back();
      }
      stack.push_back(currNum);
    }

    // Replace values in nums1 with next greatest value from nums2.
    for (std::size_t i = 0; i < nums1.size(); ++i) {
      nums1[i] = nextGreater.at(nums1[i]);
    }

    // Signature does not describe nums1 as const&, so can modify + move it.
    // In normal code, would instead make const& and return a new vector.
    return std::move(nums1);
  }
};