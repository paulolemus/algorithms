/* Notes
Difficulty: Easy
*/

#include <string>
#include <unordered_map>

bool generateDocument(std::string characters, std::string document) {
  // Write your code here.
  std::unordered_map<char, int> char_count;
  std::unordered_map<char, int> doc_count;
  for (const char ch : characters) char_count[ch]++;
  for (const char ch : document) doc_count[ch]++;

  for (const auto &[key, value] : doc_count) {
    if (char_count[key] < value) return false;
  }
  return true;
}