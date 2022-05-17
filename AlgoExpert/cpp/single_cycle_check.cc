/* Notes
Difficulty: Medium
*/

#include <vector>

/// Wraps index into range 0 .. limit (limit exclusive).
int wrap(const int index, const int limit) {
  return (index % limit + limit) % limit;
}

bool hasSingleCycle(const std::vector<int> array) {
  // Write your code here.
  const int size = array.size();
  const int rootIdx = 0;
  int idx = rootIdx;

  for (int jumps = 0; jumps < size; ++jumps) {
    if (jumps && idx == rootIdx) {
      return false;
    }
    idx = wrap(idx + array[idx], size);
  }

  return idx == rootIdx;
}