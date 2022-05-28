/*
Difficulty: Easy
*/

#include <vector>

class Solution {
 public:
  std::vector<int> decode(const std::vector<int>& encoded, const int first) {
    std::vector<int> original;
    original.reserve(encoded.size() + 1);
    original.push_back(first);

    int currDecoded = first;
    for (const int codedValue : encoded) {
      currDecoded ^= codedValue;
      original.push_back(currDecoded);
    }

    return original;
  }
};