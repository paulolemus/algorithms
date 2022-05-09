/* Notes
Difficulty: Medium

How to tell if two words are anagrams?
They have the same length, and they have the same frequency for each letter in
the word.

Groups of words are grouped by anagram.
Would like to be able to identify and look up correct anagram group for any
word.
*/

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::vector<std::string>> groupAnagrams(
    std::vector<std::string> words) {
  // Write your code here.
  using std::string;
  using std::unordered_map;
  using std::vector;
  unordered_map<string, vector<string>> anagramGroups;

  for (string& word : words) {
    string sortedWord = word;
    sort(sortedWord.begin(), sortedWord.end());
    anagramGroups[sortedWord].emplace_back(move(word));
  }

  vector<vector<string>> listGroups;
  for (auto& [anagram, groups] : anagramGroups) {
    listGroups.push_back(move(groups));
  }

  return listGroups;
}