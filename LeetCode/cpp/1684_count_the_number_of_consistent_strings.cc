/*
Difficulty: Easy
*/

#include <array>
#include <string>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  /// Time: O(n), n = # chars in words, Space: O(1)
  int countConsistentStrings(const std::string allowed,
                             const std::vector<std::string>& words) {
    std::array<bool, 26> allowedSet{};
    for (const char ch : allowed) {
      allowedSet[ch - 'a'] = true;
    }

    // Remove a consistent for each word with a letter not in the set.
    int consistents = words.size();
    for (const std::string& word : words) {
      for (const char ch : word) {
        if (!allowedSet[ch - 'a']) {
          consistents--;
          break;
        }
      }
    }

    return consistents;
  }
};