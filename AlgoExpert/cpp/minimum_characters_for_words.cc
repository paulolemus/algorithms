/* Notes
Difficulty: Medium
*/

#include <algorithm>
#include <unordered_map>
#include <vector>

std::vector<char> minimumCharactersForWords(
    const std::vector<std::string> words) {
  std::unordered_map<char, int> maxCharCounts;

  for (const std::string& word : words) {
    std::unordered_map<char, int> localCharCounts;
    for (const char& ch : word) {
      localCharCounts[ch]++;
    }

    for (const auto& [ch, count] : localCharCounts) {
      maxCharCounts[ch] = std::max(maxCharCounts[ch], count);
    }
  }

  std::vector<char> minimums;

  for (const auto& [ch, count] : maxCharCounts) {
    for (int i = 0; i < count; ++i) {
      minimums.push_back(ch);
    }
  }

  return minimums;
}