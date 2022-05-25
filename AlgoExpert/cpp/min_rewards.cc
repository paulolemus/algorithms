/*
Difficulty: Hard

Reward for any local valley (min) is 1.
*/

#include <algorithm>
#include <cstddef>
#include <limits>
#include <numeric>
#include <unordered_set>
#include <vector>

std::unordered_set<std::size_t> findLocalMinimaIdx(
    const std::vector<int>& scores) {
  constexpr int intMax = std::numeric_limits<int>::max();
  std::unordered_set<std::size_t> extrema;

  for (std::size_t i = 0; i < scores.size(); ++i) {
    const std::size_t iLeft = i - 1, iRight = i + 1;
    const int leftValue = iLeft < scores.size() ? scores[iLeft] : intMax;
    const int rightValue = iRight < scores.size() ? scores[iRight] : intMax;
    if (leftValue > scores[i] && scores[i] < rightValue) {
      extrema.insert(i);
    }
  }
  return extrema;
}

std::unordered_set<std::size_t> findLocalMaximaIdx(
    const std::vector<int>& scores) {
  constexpr int intMin = std::numeric_limits<int>::min();
  std::unordered_set<std::size_t> extrema;

  for (std::size_t i = 0; i < scores.size(); ++i) {
    const std::size_t iLeft = i - 1, iRight = i + 1;
    const int leftValue = iLeft < scores.size() ? scores[iLeft] : intMin;
    const int rightValue = iRight < scores.size() ? scores[iRight] : intMin;
    if (leftValue < scores[i] && scores[i] > rightValue) {
      extrema.insert(i);
    }
  }
  return extrema;
}

/// Time: O(n), Space: O(n)
/// Solution comes from adapting my Longest Peak solution.
int minRewardsSlower(const std::vector<int> scores) {
  // Write your code here.
  const auto localMinimaIdx = findLocalMinimaIdx(scores);
  const auto localMaximaIdx = findLocalMaximaIdx(scores);
  std::vector<int> rewards(scores.size(), 0);

  for (const std::size_t iMinima : localMinimaIdx) {
    int currReward = 1;
    for (std::size_t i = iMinima; i < rewards.size(); ++i, ++currReward) {
      if (localMaximaIdx.find(i) != localMaximaIdx.cend()) {
        rewards[i] = std::max(rewards[i], currReward);
        break;
      } else {
        rewards[i] = currReward;
      }
    }

    currReward = 1;
    for (std::size_t iPlus = iMinima + 1; iPlus > 0; --iPlus, ++currReward) {
      const std::size_t i = iPlus - 1;
      if (localMaximaIdx.find(i) != localMaximaIdx.cend()) {
        rewards[i] = std::max(rewards[i], currReward);
        break;
      } else {
        rewards[i] = currReward;
      }
    }
  }

  return std::accumulate(rewards.begin(), rewards.end(), 0);
}

/// Time: O(n), Space: O(n)
int minRewards(const std::vector<int> scores) {
  // Write your code here.
  std::vector<int> rewards(scores.size(), 1);

  for (std::size_t i = 1; i < rewards.size(); ++i) {
    const std::size_t iPrev = i - 1;
    if (scores[iPrev] < scores[i]) {
      rewards[i] = rewards[iPrev] + 1;
    }
  }

  for (int i = static_cast<int>(rewards.size()) - 2; i >= 0; --i) {
    const std::size_t iNext = static_cast<std::size_t>(i) + 1;
    if (scores[i] > scores[iNext]) {
      rewards[i] = std::max(rewards[i], rewards[iNext] + 1);
    }
  }

  return std::accumulate(rewards.cbegin(), rewards.cend(), 0);
}