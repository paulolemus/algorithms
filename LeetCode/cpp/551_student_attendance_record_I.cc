/*
Difficulty: Easy
Runtime: 0 ms (100%)
Memory: 6 MB (96%)
*/

#include <string>

class Solution {
 public:
  /// Time: O(n), Space: O(1)
  bool checkRecord(const std::string s) {
    int absents = 0;
    int consecutiveLates = 0;

    for (const char status : s) {
      if (status == 'A') {
        absents++;
        consecutiveLates = 0;
        if (absents >= 2) return false;
      } else if (status == 'L') {
        consecutiveLates++;
        if (consecutiveLates >= 3) return false;
      } else {
        consecutiveLates = 0;
      }
    }

    return true;
  }
};