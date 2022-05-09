/* Notes
Difficulty: Medium

Sort arrays solution.
If ever find minabsdiff == 0, can return immediately.
*/

#include <algorithm>
#include <limits>
#include <vector>

std::vector<int> smallestDifference(std::vector<int> arrayOne,
                                    std::vector<int> arrayTwo) {
  // Write your code here.
  sort(arrayOne.begin(), arrayOne.end());
  sort(arrayTwo.begin(), arrayTwo.end());

  const int oneSize = arrayOne.size();
  const int twoSize = arrayTwo.size();

  int one = 0, two = 0;
  int minAbsDiff = std::numeric_limits<int>::max();
  int minOne = 0, minTwo = 0;

  while (one < oneSize && two < twoSize) {
    const int oneNum = arrayOne[one];
    const int twoNum = arrayTwo[two];
    const int absDiff = abs(oneNum - twoNum);

    if (absDiff == 0) return {oneNum, twoNum};
    if (absDiff < minAbsDiff) {
      minAbsDiff = absDiff;
      minOne = oneNum;
      minTwo = twoNum;
    }

    if (oneNum < twoNum)
      ++one;
    else
      ++two;
  }

  return {minOne, minTwo};
}