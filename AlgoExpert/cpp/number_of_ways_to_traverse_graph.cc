/* Notes
Difficulty: Medium
*/

/// Find factorial for only positive numbers, no caching.
unsigned long long factorial(int n) {
  // Not correct, but to prevent long loop for accidental negative.
  if (n < 0) n = 0;

  const auto longN = static_cast<unsigned long long>(n);
  unsigned long long product = 1;
  for (unsigned long long val = 2; val <= longN; ++val) {
    product *= val;
  }
  return product;
}

int numberOfWaysToTraverseGraph(const int width, const int height) {
  // Write your code here.
  const int rights = width - 1, downs = height - 1;
  auto ways =
      factorial(rights + downs) / (factorial(rights) * factorial(downs));
  return static_cast<int>(ways);
}