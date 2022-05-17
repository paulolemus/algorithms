/* Notes
Difficulty: Easy
*/

#include <string>

constexpr char encryptChar(const char ch, const int key) {
  constexpr char base = 'a', end = 'z';
  constexpr char maxTarget = end - base + 1;
  const char newKey = static_cast<char>(key % static_cast<int>(maxTarget));
  return (ch - base + newKey) % maxTarget + base;
}

std::string caesarCypherEncryptor(const std::string str, const int key) {
  // Write your code here.
  std::string encrypted = str;
  for (int i = 0; i < encrypted.size(); ++i) {
    encrypted[i] = encryptChar(encrypted[i], key);
  }
  return encrypted;
}