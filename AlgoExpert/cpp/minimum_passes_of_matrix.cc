/*
Difficulty: Medium
*/

#include <algorithm>
#include <array>
#include <cstddef>
#include <deque>
#include <unordered_set>
#include <vector>

struct Pos {
  int row{0};
  int col{0};
  constexpr Pos(const int row_, const int col_) : row(row_), col(col_) {}

  bool isLegal(const int rows, const int cols) const {
    return 0 <= row && row < rows && 0 <= col && col < cols;
  }

  std::vector<Pos> neighbors(const int rows, const int cols) const {
    constexpr std::array<Pos, 4> deltas = {{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};
    std::vector<Pos> adj;

    for (const auto [rowDelta, colDelta] : deltas) {
      const Pos neighbor{row + rowDelta, col + colDelta};
      if (neighbor.isLegal(rows, cols)) {
        adj.push_back(neighbor);
      }
    }
    return adj;
  }
};

bool operator==(const Pos& lhs, const Pos& rhs) {
  return lhs.row == rhs.row && lhs.col == rhs.col;
}

struct PosHash {
  std::size_t operator()(const Pos& p) const {
    constexpr int goldenRatio = 0x9e3779b9;
    const int rowHash = std::hash<int>{}(p.row);
    const int colHash = std::hash<int>{}(p.col);
    return (goldenRatio * rowHash) ^ colHash;
  }
};

bool isPositive(const int value) { return value > 0; }

bool isNegative(const int value) { return value < 0; }

/// Time: O(w * h), Space: O(w * h), w = width of matrix, h = height of matrix
int minimumPassesOfMatrix(const std::vector<std::vector<int>> matrix) {
  // Write your code here.
  if (!matrix.size() || !matrix[0].size()) return -1;

  const int rows = static_cast<int>(matrix.size());
  const int cols = static_cast<int>(matrix[0].size());
  std::unordered_set<Pos, PosHash> negatives;
  std::deque<Pos> converted;

  const auto& crmat = matrix;
  const auto posPositive = [crmat](const Pos& p) {
    return isPositive(crmat[p.row][p.col]);
  };

  // Add all negative numbers to `converted` if they are adjacent to a positive,
  // otherwise add them to negatives.
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      const auto neighbors = Pos{row, col}.neighbors(rows, cols);

      if (isNegative(matrix[row][col])) {
        if (std::any_of(neighbors.cbegin(), neighbors.cend(), posPositive)) {
          converted.emplace_back(row, col);
        } else {
          negatives.emplace(row, col);
        }
      }
    }
  }

  // BFS on converted queue, with each depth equal to one pass.
  std::size_t breadth = converted.size();
  int passes = 0;
  while (!converted.empty()) {
    for (std::size_t _ = 0; _ < breadth; ++_) {
      const Pos curr = converted.front();
      converted.pop_front();
      negatives.erase(curr);

      for (const Pos& neighbor : curr.neighbors(rows, cols)) {
        if (negatives.count(neighbor)) {
          negatives.erase(neighbor);
          converted.push_back(neighbor);
        }
      }
    }
    passes++;
    breadth = converted.size();
  }

  return negatives.empty() ? passes : -1;
}