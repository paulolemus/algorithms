/* Notes
Difficulty: Medium
*/

#include <vector>

std::vector<int> nextGreaterElement(const std::vector<int> array) {
  // Write your code here.
  std::vector<int> out(array.size(), -1);
  std::vector<int> idxStack;

  // Iterate list twice to emulate circular vector.
  // Both for loops have base combined time of O(2*n) -> O(n).
  for (int _ = 0; _ < 2; ++_) {
    for (int i = 0; i < array.size(); ++i) {
      const int num = array[i];

      // This runs n times in total (n=array.size()).
      while (!idxStack.empty() && array[idxStack.back()] < num) {
        const int idxSolved = idxStack.back();
        idxStack.pop_back();
        out[idxSolved] = num;
      }

      // Special value given by problem.
      // Indicates greater value for idx i not found.
      if (out[i] == -1) {
        idxStack.push_back(i);
      }
    }
  }

  return out;
}