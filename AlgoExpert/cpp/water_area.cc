/*
Difficulty: Hard
*/

#include <algorithm>
#include <cstddef>
#include <vector>

/// Time: O(n), Space: O(1)
int waterArea2(const std::vector<int>& heights) {
  // Write your code here.
  if (heights.empty()) return 0;

  int leftIdx = 0;
  int rightIdx = static_cast<int>(heights.size()) - 1;
  int leftMaxHeight = heights[leftIdx];
  int rightMaxHeight = heights[rightIdx];
  int water = 0;

  while (leftIdx <= rightIdx) {
    leftMaxHeight = std::max(leftMaxHeight, heights[leftIdx]);
    rightMaxHeight = std::max(rightMaxHeight, heights[rightIdx]);
    const int waterLevel = std::min(leftMaxHeight, rightMaxHeight);

    if (heights[leftIdx] <= heights[rightIdx]) {
      water += std::max(0, waterLevel - heights[leftIdx]);
      leftIdx++;
    } else {
      water += std::max(0, waterLevel - heights[rightIdx]);
      rightIdx--;
    }
  }

  return water;
}

// Time: O(n), Space: O(n)
int waterArea(const std::vector<int>& heights) {
  // Write your code here.
  // Greatest heights to left and right of each index
  std::vector<int> greatestHeightToLeft(heights.size(), 0);
  std::vector<int> greatestHeightToRight(heights.size(), 0);

  // Find greatest lefts
  int maxHeight = 0;
  for (std::size_t i = 0; i < heights.size(); ++i) {
    maxHeight = std::max(maxHeight, heights[i]);
    greatestHeightToLeft[i] = maxHeight;
  }

  // Find greatest rights
  maxHeight = 0;
  for (int i = heights.size() - 1; 0 <= i; --i) {
    maxHeight = std::max(maxHeight, heights[i]);
    greatestHeightToRight[i] = maxHeight;
  }

  int water = 0;
  for (std::size_t i = 0; i < heights.size(); ++i) {
    const int min = std::min(greatestHeightToLeft[i], greatestHeightToRight[i]);
    water += min - heights[i];
  }

  return water;
}