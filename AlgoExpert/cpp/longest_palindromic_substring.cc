/*
Difficulty: Medium
*/

#include <string>
#include <string_view>

/// Returns a view of the largest palindrome centered around left and right.
std::string_view measurePalindrome(const std::string& str, int left,
                                   int right) {
  while (0 <= left && right < str.size() && str[left] == str[right]) {
    left--;
    right++;
  }
  return std::string_view{str}.substr(left + 1, right - left - 1);
}

/// Time: O(n^2), Space: O(n), space only used for returning string allocation.
std::string longestPalindromicSubstring(const std::string str) {
  // Write your code here.
  // Guard empty or 1 sized strings as palindromes.
  if (str.size() <= 1) return str;

  std::string_view longest{""};
  for (int i = 0; i < str.size() - 1; ++i) {
    std::string_view odd = measurePalindrome(str, i - 1, i + 1);
    std::string_view even = measurePalindrome(str, i, i + 1);
    if (odd.size() > longest.size()) longest = odd;
    if (even.size() > longest.size()) longest = even;
  }
  return std::string{longest};
}