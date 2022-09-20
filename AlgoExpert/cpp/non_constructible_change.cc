/*
Difficulty: Easy
*/

#include <algorithm>
#include <vector>

/// Time: O(n*log(n)), Space: O(1)
int nonConstructibleChange(std::vector<int> coins) {
  // Write your code here.
  std::sort(coins.begin(), coins.end());

  int smallestConstructible = 0;
  for (const int coin : coins) {
    if (coin > smallestConstructible + 1) break;
    smallestConstructible += coin;
  }

  return smallestConstructible + 1;
}