/*
Difficulty: Easy
*/

/// Nth begins at 1, ex:
///     getNthFib(1) == F0 == 0
///     getNthFib(2) == F1 == 1
/// Time: O(n), Space: O(1)
int getNthFib(const int n) {
  // Write your code here.
  if (n <= 2) return n == 2;

  // Calculate any fib starting at 3rd.
  int prevFib = 0;
  int fib = 1;
  for (int _ = 2; _ < n; ++_) {
    const int nextFib = fib + prevFib;
    prevFib = fib;
    fib = nextFib;
  }
  return fib;
}