/*
Difficulty: Medium
*/

#include <cstddef>
#include <limits>
#include <vector>

/// Time: O(n * d), Space: O(n)
int minNumberOfCoinsForChange(const int n, const std::vector<int> denoms) {
  // Write your code here.
  if (n < 0) return -1;
  std::vector<int> minCoins(n + 1, std::numeric_limits<int>::max());
  std::vector<bool> canConstruct(minCoins.size(), false);
  minCoins[0] = 0;
  canConstruct[0] = true;

  for (const int denom : denoms) {
    for (std::size_t change = 0; change < minCoins.size(); ++change) {
      const std::size_t constructibleChange = change + denom;
      // Break this denom early if current change is outside target solution
      // range.
      if (constructibleChange >= minCoins.size()) break;

      if (canConstruct[change]) {
        canConstruct[constructibleChange] = true;
        minCoins[constructibleChange] =
            std::min(minCoins[constructibleChange], minCoins[change] + 1);
      }
    }
  }

  return canConstruct.back() ? minCoins.back() : -1;
}