/*
Difficulty: Easy
*/

#include <any>
#include <typeinfo>
#include <vector>

int recurseProductSum(const std::vector<std::any>& array, const int depth = 1) {
  int curr_sum = 0;

  for (const std::any& item : array) {
    if (item.type() == typeid(std::vector<std::any>)) {
      const auto& list = std::any_cast<const std::vector<std::any>&>(item);
      curr_sum += recurseProductSum(list, depth + 1);
    } else {
      curr_sum += std::any_cast<int>(item);
    }
  }

  return curr_sum * depth;
}

// Tip: You can use el.type() == typeid(vector<any>) to check whether an item is
// a list or an integer.
// If you know an element of the array is vector<any> you can cast it using:
//     any_cast<vector<any>>(element)
// If you know an element of the array is an int you can cast it using:
//     any_cast<int>(element)

/// Time: O(n), Space: O(d), n = number of ints, d = greatest depth of nesting
int productSum(std::vector<std::any> array) {
  // Write your code here.
  return recurseProductSum(array);
}