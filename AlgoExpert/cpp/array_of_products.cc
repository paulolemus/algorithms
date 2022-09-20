/*
Difficulty: Medium
*/

#include <cstddef>
#include <vector>

/// Solved without division.
/// Time: O(n), Space: O(n)
std::vector<int> arrayOfProducts(const std::vector<int> array) {
  // Write your code here.
  std::vector<int> products(array.size(), 1);

  int leftProduct = 1;
  for (std::size_t i = 0; i < array.size(); ++i) {
    products[i] = leftProduct;
    leftProduct *= array[i];
  }

  int rightProduct = 1;
  for (int i = static_cast<int>(array.size()) - 1; i >= 0; --i) {
    products[i] *= rightProduct;
    rightProduct *= array[i];
  }

  return products;
}