/* Notes
Difficulty: Easy

Approaches:
Iteration
hold an index to the array, and one to the sequence.
Iterate the array using its index, looking for the value in the index of the
sequence.

When a value is found in array, increment sequence index.
At any time, if sequence index is out of bounds, all values have been found and
it is truly a subsequence of array.

Time: O(n), n = size(array)
Space: O(1)
*/
#include <vector>

bool isValidSubsequence(const std::vector<int> array,
                        const std::vector<int> sequence) {
  // Guard impossible sequence.
  if (sequence.size() > array.size()) {
    return false;
  }

  const int seqSize = sequence.size();
  int seqIdx = 0;

  for (const int arrValue : array) {
    if (arrValue == sequence[seqIdx]) {
      if (++seqIdx >= seqSize) return true;
    }
  }
  return seqIdx >= seqSize;
}