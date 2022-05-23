/*
Difficulty: Easy
*/

#include <cstddef>
#include <string>

class Solution {
 public:
  /// Time: O(n), Space: O(1)
  std::string replaceDigits(std::string s) {
    for (std::size_t i = 1; i < s.size(); i += 2) {
      const char letter = s[i - 1];
      const char digit = s[i] - '0';
      s[i] = letter + digit;
    }

    return s;
  }
};