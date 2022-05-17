/* Notes
Difficulty: Easy
*/

#include <string>
#include <unordered_map>

int firstNonRepeatingCharacter(std::string str) {
  // Write your code here.
  std::unordered_map<char, int> occurrences;

  for (const char ch : str) {
    occurrences[ch]++;
  }
  for (int i = 0; i < str.size(); ++i) {
    if (occurrences[str[i]] == 1) return i;
  }

  return -1;
}