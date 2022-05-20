/*
Difficulty: Hard
*/

#include <algorithm>
#include <cmath>
#include <functional>
#include <queue>

template <typename T>
T absDiff(T lhs, T rhs) {
  return std::max(lhs, rhs) - std::min(lhs, rhs);
}

// Do not edit the class below except for
// the insert method. Feel free to add new
// properties and methods to the class.
class ContinuousMedianHandler {
  /// Balance min and max heaps to have the same number of elements.
  /// If the total number of elements is odd, maxHeap will have the extra value.
  void balanceStorage() {
    // Shift heaps until the difference in their sizes is at most 1.
    while (absDiff(minHeap.size(), maxHeap.size()) > 1) {
      if (minHeap.size() > maxHeap.size()) {
        maxHeap.push(minHeap.top());
        minHeap.pop();
      } else {
        minHeap.push(maxHeap.top());
        maxHeap.pop();
      }
    }

    // For odd counts, ensure maxHeap holds the extra number.
    if (maxHeap.size() < minHeap.size()) {
      maxHeap.push(minHeap.top());
      minHeap.pop();
    }
  }

  /// Sets the median with the assumption that the two heaps are balanced
  /// around the logical center of all the inserted numbers sorted.
  void updateMedian() {
    const int isEvenSize = (minHeap.size() + maxHeap.size()) % 2 == 0;

    if (isEvenSize) {
      median = static_cast<double>(minHeap.top() + maxHeap.top()) / 2.;
    } else {
      median = maxHeap.top();
    }
  }

 public:
  double median;
  /// Storage for left half of all inserted numbers logically sorted.
  std::priority_queue<int> maxHeap;
  /// Storage for right half of all inserted numbers logically sorted.
  std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

  /// Time: O(log n), Space: O(n)
  void insert(const int number) {
    // Write your code here.
    if (maxHeap.empty() || number <= maxHeap.top()) {
      maxHeap.push(number);
    } else {
      minHeap.push(number);
    }

    this->balanceStorage();
    this->updateMedian();
  }

  double getMedian() const { return median; }
};