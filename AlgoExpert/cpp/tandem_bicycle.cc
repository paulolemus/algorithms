/* Notes
Difficulty: Easy
*/

#include <algorithm>
#include <vector>

int tandemBicycle(std::vector<int> redShirtSpeeds,
                  std::vector<int> blueShirtSpeeds, bool fastest) {
  // Write your code here.
  std::sort(redShirtSpeeds.begin(), redShirtSpeeds.end());
  if (fastest) {
    std::sort(blueShirtSpeeds.rbegin(), blueShirtSpeeds.rend());
  } else {
    std::sort(blueShirtSpeeds.begin(), blueShirtSpeeds.end());
  }

  int total_speed = 0;
  for (size_t idx = 0; idx < redShirtSpeeds.size(); ++idx) {
    total_speed += std::max(redShirtSpeeds[idx], blueShirtSpeeds[idx]);
  }

  return total_speed;
}