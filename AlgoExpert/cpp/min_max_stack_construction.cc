/*
Difficulty: Medium

push and pop can be done in O(1) time using a vector.
*/

#include <algorithm>
#include <limits>
#include <vector>

struct MinMax {
  int min{std::numeric_limits<int>::max()};
  int max{std::numeric_limits<int>::min()};
};

// Feel free to add new properties and methods to the class.
class MinMaxStack {
  std::vector<int> stack_;
  std::vector<MinMax> minMax_;

 public:
  int peek() const {
    // Write your code here.
    return stack_.back();
  }

  int pop() {
    // Write your code here.
    int value = stack_.back();
    stack_.pop_back();
    minMax_.pop_back();
    return value;
  }

  void push(const int number) {
    // Write your code here.
    MinMax newMinMax;
    if (!minMax_.empty()) newMinMax = minMax_.back();

    newMinMax.min = std::min(newMinMax.min, number);
    newMinMax.max = std::max(newMinMax.max, number);

    minMax_.push_back(newMinMax);
    stack_.push_back(number);
  }

  int getMin() const {
    // Write your code here.
    return minMax_.back().min;
  }

  int getMax() const {
    // Write your code here.
    return minMax_.back().max;
  }
};