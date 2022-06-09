/*
Difficulty: Very Hard

Strings are three letters, they can be copied with small string optimization.
Inputs represent a potentially disconnected, directed graph.
Each airport except the start without incoming flights requires 1 connection.
Of the airports that cannot be visited from any root airport:
    Treat strongly connected components as single nodes to form a DAG.
    Determine how many roots exist of these "unvisitable" nodes.

Note: This solution passed automated testing, but is not a complete solution.
      Fix coming soon.
*/

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

/// Finding roots: O(r)
/// Finding unvisitable with DFS: O(a + r)
/// Counting circular roots: O(a + r)
/// Time: O(a + r)?
/// Space: O(a + r)
int airportConnections(std::vector<std::string> airports,
                       std::vector<std::vector<std::string>> routes,
                       const std::string startingAirport) {
  // Write your code here.
  // All roots except the starting airport must have a connection.
  std::unordered_set<std::string> roots(airports.cbegin(), airports.cend());
  // All outgoing flights, fromAirport -> toAirports.
  std::unordered_map<std::string, std::unordered_set<std::string>> outgoing;

  for (const auto& route : routes) {
    const std::string& from = route.at(0);
    const std::string& to = route.at(1);
    // Ingore loops.
    if (from != to) {
      roots.erase(to);
      outgoing[from].insert(to);
    }
  }
  roots.insert(startingAirport);

  // Find all nodes that cannot be reached from a root.
  std::unordered_set<std::string> unvisitableFromRoots(airports.cbegin(),
                                                       airports.cend());
  std::unordered_set<std::string> visited;
  for (const auto& root : roots) {
    // Skip nodes previously processed.
    if (visited.find(root) != visited.cend()) continue;

    // DFS from each root.
    std::vector<std::string> stack{root};
    visited.insert(root);
    while (!stack.empty()) {
      std::string currAirport = stack.back();
      stack.pop_back();
      unvisitableFromRoots.erase(currAirport);

      for (const auto& toAirport : outgoing[currAirport]) {
        if (visited.find(toAirport) == visited.cend()) {
          visited.insert(toAirport);
          stack.push_back(toAirport);
        }
      }
    }
  }

  roots.erase(startingAirport);
  // Early end if all nodes have been visited.
  if (unvisitableFromRoots.empty()) return static_cast<int>(roots.size());

  // Run a depth first search from each unvisitable node.
  // A global and local visited list is kept.
  // Nodes in the not in the unvisitable set are skipped.
  // Nodes globally visited are skipped, and a marker is set this is not a new
  // component. Nodes in locallyVisited are skipped. In a traversal, if no nodes
  // are discovered from a previous iteration, then the current component
  // requires 1 flight. Otherwise, we are adding to a component we already
  // considered a flight for.
  int circularRoots = 0;
  visited.clear();
  for (const auto& unvisited : unvisitableFromRoots) {
    // Skip nodes visited in some previous iteration.
    if (visited.find(unvisited) != visited.cend()) continue;

    bool foundPreviouslyCounted = false;
    std::unordered_set<std::string> localVisited{unvisited};
    std::vector<std::string> stack{unvisited};

    while (!stack.empty()) {
      std::string currAirport = stack.back();
      stack.pop_back();

      for (const auto& toAirport : outgoing[currAirport]) {
        // Ignore nodes reachable from any root.
        if (unvisitableFromRoots.find(toAirport) ==
            unvisitableFromRoots.cend()) {
          continue;
        }
        // Skip nodes that have aleady been counted in a component.
        if (visited.find(toAirport) != visited.cend()) {
          foundPreviouslyCounted = true;
          continue;
        }
        // Ignore revisited nodes locally.
        if (localVisited.find(toAirport) != localVisited.cend()) {
          continue;
        }

        localVisited.insert(toAirport);
        stack.push_back(toAirport);
      }
    }

    visited.merge(std::move(localVisited));
    circularRoots += static_cast<int>(!foundPreviouslyCounted);
  }

  return static_cast<int>(roots.size()) + circularRoots;
}