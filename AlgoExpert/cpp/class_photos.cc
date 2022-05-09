/* Notes
Difficulty: Easy
*/

#include <algorithm>
#include <vector>

bool classPhotos(std::vector<int> redShirtHeights,
                 std::vector<int> blueShirtHeights) {
  // Write your code here.
  std::sort(redShirtHeights.begin(), redShirtHeights.end());
  std::sort(blueShirtHeights.begin(), blueShirtHeights.end());
  int red_taller = 0, blue_taller = 0;

  for (size_t idx = 0; idx < redShirtHeights.size(); ++idx) {
    int red = redShirtHeights[idx];
    int blue = blueShirtHeights[idx];

    if (red > blue)
      red_taller += 1;
    else if (blue > red)
      blue_taller += 1;
    else
      return false;

    if (red_taller && blue_taller) return false;
  }
  return true;
}