/*
Difficulty: Medium
*/

#include <cstddef>
#include <vector>

/// Time: O(n*d), Space: O(n)
int numberOfWaysToMakeChange(const int n, const std::vector<int> denoms) {
  // Write your code here.
  if (n <= 0) return 1;
  // Ways to make change for 0..=n inclusive.
  // Indexed by change amount.
  std::vector<int> ways(static_cast<std::size_t>(n) + 1, 0);
  ways[0] = 1;

  for (const int denom : denoms) {
    for (std::size_t change = 0; change < ways.size(); ++change) {
      const std::size_t constructibleChange = change + denom;
      if (ways[change] && constructibleChange < ways.size()) {
        ways[constructibleChange] += ways[change];
      }
    }
  }

  return ways.back();
}