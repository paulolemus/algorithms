/* Notes
Difficulty: Medium
*/

#include <vector>

int staircaseTraversal(const int height, const int maxSteps) {
  // Write your code here.
  // Guard trivial / invalid parameters.
  if (height <= 0 || maxSteps <= 0) return 0;

  // Ground floor + each step of height.
  std::vector<int> ways(height + 1, 0);
  ways[0] = 1;
  int currWays = 0;

  // Ways to current step is sum of window from currHeight - 1 to currHeight -
  // maxSteps. Instead of summing entire window, add the right most of current
  // window to sum, and remove count that just left the window to sum.
  for (int currHeight = 1; currHeight < ways.size(); ++currHeight) {
    const int windowIn = currHeight - 1;
    const int windowOut = currHeight - 1 - maxSteps;

    currWays += ways[windowIn];
    if (windowOut >= 0) {
      currWays -= ways[windowOut];
    }
    ways[currHeight] = currWays;
  }

  return currWays;
}