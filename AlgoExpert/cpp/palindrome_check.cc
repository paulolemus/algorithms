/* Notes
Difficulty: Easy
*/

#include <string>

bool isPalindrome(std::string str) {
  // Write your code here.
  if (str.size() <= 1) return true;
  int left = 0, right = str.size() - 1;

  while (left <= right) {
    if (str[left++] != str[right--]) return false;
  }
  return true;
}