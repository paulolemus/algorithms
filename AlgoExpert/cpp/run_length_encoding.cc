/* Notes
Difficulty: Easy
*/

#include <string>

/// Append to `str` the encoding corresponding to a run length of `count` of the
/// character `ch`.
void appendEncoding(std::string& str, int count, const char ch) {
  const int num_nines = count / 9;
  count -= num_nines * 9;
  for (int _ = 0; _ < num_nines; ++_) {
    str.push_back('9');
    str.push_back(ch);
  }

  if (count) {
    str.append(std::to_string(count));
    str.push_back(ch);
  }
}

std::string runLengthEncoding(const std::string str) {
  // Guard empty string.
  if (str.size() < 1) return {};

  std::string encoded;
  char prev = str[0];
  int runLen = 1;

  for (int i = 1; i < str.size(); ++i) {
    const char ch = str[i];
    if (ch == prev) {
      runLen++;
    } else {
      appendEncoding(encoded, runLen, prev);
      runLen = 1;
      prev = ch;
    }
  }

  if (runLen) {
    appendEncoding(encoded, runLen, prev);
  }
  return encoded;
}