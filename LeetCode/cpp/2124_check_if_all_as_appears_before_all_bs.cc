/*
Difficulty: Easy
Runtime: 0 ms (100%)
*/

#include <string>

class Solution {
 public:
  /// Time: O(n), Space: O(1)
  bool checkString(const std::string s) {
    bool foundB = false;
    for (const char ch : s) {
      if (ch == 'b') foundB = true;
      if (foundB && ch == 'a') return false;
    }

    return true;
  }
};