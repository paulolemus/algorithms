/*
Difficulty: Easy

Runtime: 79 ms (95%)
Memory: 35.6 MB (75%)
*/

#include <algorithm>
#include <cstddef>
#include <limits>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Solution {
 public:
  /// Time: O(n + m), Space: O(min(n, m))
  std::vector<std::string> findRestaurant(std::vector<std::string>& list1,
                                          std::vector<std::string>& list2) {
    std::vector<std::string>& shorter =
        list1.size() < list2.size() ? list1 : list2;
    std::vector<std::string>& longer =
        list1.size() < list2.size() ? list2 : list1;

    std::unordered_map<std::string, std::size_t> restaurantIndices;
    for (std::size_t i = 0; i < shorter.size(); ++i) {
      restaurantIndices.emplace(std::move(shorter[i]), i);
    }

    std::unordered_map<std::string, std::size_t> commonRestaurantSums;
    std::size_t minSum = std::numeric_limits<std::size_t>::max();

    for (std::size_t i = 0; i < longer.size(); ++i) {
      std::string& currRestaurant = longer[i];
      const auto it = restaurantIndices.find(currRestaurant);

      if (it != restaurantIndices.cend()) {
        const std::size_t sumIdx = i + it->second;
        minSum = std::min(minSum, sumIdx);
        commonRestaurantSums.emplace(std::move(currRestaurant), sumIdx);
      }
    }

    std::vector<std::string> bestCommonFavorites;
    for (const auto& [restaurant, sum] : commonRestaurantSums) {
      if (sum == minSum) {
        bestCommonFavorites.push_back(restaurant);
      }
    }

    return bestCommonFavorites;
  }
};