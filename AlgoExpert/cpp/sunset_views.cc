/* Notes
Difficulty: Medium
*/

#include <algorithm>
#include <limits>
#include <string>
#include <vector>

std::vector<int> sunsetViews(std::vector<int> buildings,
                             std::string direction) {
  // Write your code here.
  const bool isWest = direction == "WEST";
  int tallest = std::numeric_limits<int>::min();
  std::vector<int> sunsetIndices;

  // Essentially a for loop that picks a direction.
  int i = isWest ? 0 : buildings.size() - 1;
  const int end = isWest ? buildings.size() : -1;
  const int step = isWest ? 1 : -1;

  while (i != end) {
    const int height = buildings[i];
    if (height > tallest) {
      sunsetIndices.push_back(i);
      tallest = height;
    }
    i += step;
  }

  // Flip from descending to ascending.
  if (!isWest) {
    std::reverse(sunsetIndices.begin(), sunsetIndices.end());
  }

  return sunsetIndices;
}