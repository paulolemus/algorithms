/* Notes
Difficulty: Medium
*/

#include <algorithm>
#include <initializer_list>
#include <utility>
#include <vector>

bool cmpPairByFirst(const std::pair<int, int>& lhs,
                    const std::pair<int, int>& rhs) {
  return lhs.first < rhs.first;
}

std::vector<std::vector<int>> taskAssignment(const int k,
                                             const std::vector<int> tasks) {
  // Write your code here.
  std::vector<std::pair<int, int>> task_indices;
  task_indices.reserve(tasks.size());

  for (int i = 0; i < tasks.size(); ++i) {
    task_indices.emplace_back(tasks[i], i);
  }
  std::sort(task_indices.begin(), task_indices.end(), cmpPairByFirst);

  std::vector<std::vector<int>> assignments;
  assignments.reserve(k);

  for (int left = 0, right = task_indices.size() - 1; left < right;
       ++left, --right) {
    const auto& lhs = task_indices[left];
    const auto& rhs = task_indices[right];
    std::initializer_list<int> list{lhs.second, rhs.second};
    assignments.emplace_back(list);
  }

  return assignments;
}