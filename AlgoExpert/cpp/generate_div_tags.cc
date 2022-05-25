/*
Difficulty: Hard
*/

#include <cstddef>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

constexpr std::string_view openDiv = "<div>";
constexpr std::string_view closeDiv = "</div>";

/// Returns the size of a string with `numberOfTags` divs.
constexpr std::size_t totalStringDivSize(const int numberOfTags) {
  const std::size_t tags =
      numberOfTags >= 0 ? static_cast<std::size_t>(numberOfTags) : 0;
  return openDiv.size() * tags + closeDiv.size() * tags;
}

void generateDivsRecurse(std::vector<std::string>& out, std::string builder,
                         const int opens, const int closes, const int total) {
  if (opens == total && closes == total) {
    out.push_back(std::move(builder));
    return;
  }

  if (opens < total) {
    std::string newBuilder = builder;
    newBuilder.reserve(totalStringDivSize(total));
    newBuilder += openDiv;
    generateDivsRecurse(out, std::move(newBuilder), opens + 1, closes, total);
  }
  if (closes < opens) {
    std::string newBuilder = builder;
    newBuilder.reserve(totalStringDivSize(total));
    newBuilder += closeDiv;
    generateDivsRecurse(out, std::move(newBuilder), opens, closes + 1, total);
  }
}

std::vector<std::string> generateDivTags(const int numberOfTags) {
  // Write your code here.
  std::vector<std::string> divs;
  generateDivsRecurse(divs, {}, 0, 0, numberOfTags);
  return divs;
}