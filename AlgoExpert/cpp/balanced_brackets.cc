/* Notes
Difficulty: Medium
*/

#include <stdexcept>
#include <string>
#include <vector>

bool isOpen(const char bracket) {
  return bracket == '{' || bracket == '(' || bracket == '[';
}

bool isClose(const char bracket) {
  return bracket == '}' || bracket == ')' || bracket == ']';
}

char getMatching(const char openBracket) {
  switch (openBracket) {
    case '{':
      return '}';
    case '[':
      return ']';
    case '(':
      return ')';
  }
  throw std::invalid_argument("illegal open bracket character");
}

bool balancedBrackets(const std::string str) {
  // Write your code here.
  std::vector<char> matchingClose;

  for (const char bracket : str) {
    if (isOpen(bracket)) {
      matchingClose.push_back(getMatching(bracket));
    } else if (isClose(bracket)) {
      if (matchingClose.empty() || bracket != matchingClose.back()) {
        return false;
      }
      matchingClose.pop_back();
    }
  }

  return matchingClose.empty();
}