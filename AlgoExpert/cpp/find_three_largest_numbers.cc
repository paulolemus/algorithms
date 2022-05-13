/* Notes
Difficulty: Easy
*/

#include <algorithm>
#include <cassert>
#include <limits>
#include <vector>

/// Given a vector of size 3, turn it into a min heap.
void minHeapifyThree(std::vector<int>& heap) {
  assert(heap.size() == 3);
  int smallest = 0;
  const int left = 1, right = 2;

  if (heap[left] < heap[smallest]) smallest = left;
  if (heap[right] < heap[smallest]) smallest = right;
  std::swap(heap[0], heap[smallest]);
}

std::vector<int> findThreeLargestNumbers(const std::vector<int> array) {
  // Write your code here.
  std::vector<int> largest(3, std::numeric_limits<int>::min());

  for (const auto num : array) {
    if (num > largest[0]) {
      largest[0] = num;
      minHeapifyThree(largest);
    }
  }

  std::sort(largest.begin(), largest.end());
  return largest;
}