/* Notes
Difficulty: Easy
*/

#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>

std::string tournamentWinner(std::vector<std::vector<std::string>> competitions,
                             std::vector<int> results) {
  assert(competitions.size() == results.size());

  std::unordered_map<std::string, int> scores;
  std::string tournament_winners = "";
  int max_score = 0;

  for (size_t idx = 0; idx < results.size(); ++idx) {
    const int result = results[idx];
    const auto& home = competitions[idx][0];
    const auto& away = competitions[idx][1];
    const auto& winners = (result == 1) ? home : away;
    const int score = ++scores[winners];

    if (score > max_score) {
      max_score = score;
      tournament_winners = winners;
    }
  }
  return tournament_winners;
}