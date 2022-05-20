/*
Difficulty: Medium
*/

#include <string>
#include <unordered_map>
#include <vector>

/// Generates all mnemonics for a given phoneNumber and char-to-vocabulary
/// mapping. Stores them in vector out. Requires initial condition of:
/// buf.size() == phoneNumber.size()
void generateMnemonics(std::vector<std::string>& out,
                       const std::unordered_map<char, std::string>& map,
                       const std::string& phoneNumber, const int idx,
                       std::string& buf) {
  // Consider raising error or manually resizing.
  if (buf.size() != phoneNumber.size()) return;

  if (idx >= phoneNumber.size()) {
    out.push_back(buf);
    return;
  }

  const std::string& alternatives = map.at(phoneNumber[idx]);
  for (const char ch : alternatives) {
    buf[idx] = ch;
    generateMnemonics(out, map, phoneNumber, idx + 1, buf);
  }
}

std::vector<std::string> phoneNumberMnemonics(std::string phoneNumber) {
  // Write your code here.
  if (phoneNumber.empty()) return {};

  const std::unordered_map<char, std::string> numberLetters = {
      {'0', "0"},   {'1', "1"},   {'2', "abc"},  {'3', "def"}, {'4', "ghi"},
      {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};
  std::vector<std::string> mnemonics;
  std::string buffer(phoneNumber.size(), '0');

  generateMnemonics(mnemonics, numberLetters, phoneNumber, 0, buffer);
  return mnemonics;
}