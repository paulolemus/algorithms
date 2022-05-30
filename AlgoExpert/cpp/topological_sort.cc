/*
Difficulty: Hard

Graph is not guaranteed to be a DAG.
To have a solution, there must not be circular dependencies.
*/
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/// Time: O(n + v), Space: O(n + v)
///  n = number of jobs (nodes), v = number of edges.
std::vector<int> topologicalSort(std::vector<int> jobs,
                                 const std::vector<std::vector<int>> deps) {
  // Write your code here.
  // If there are no dependencies, jobs can be completed in any order.
  if (jobs.empty() || deps.empty()) return jobs;

  // Roots have no prerequisites. Find all roots of directed forest.
  std::unordered_set<int> roots(jobs.cbegin(), jobs.cend());
  for (const auto& dependency : deps) {
    roots.erase(dependency.at(1));
  }

  // map[job] -> dependers of job. aka, look up jobs that depend on key.
  std::unordered_map<int, std::unordered_set<int>> dependers;
  // map[job] -> prerequisites of job. aka, look up prerequisites of key.
  std::unordered_map<int, std::unordered_set<int>> prerequisites;
  for (const auto& dependency : deps) {
    const int prereq = dependency.at(0);
    const int depender = dependency.at(1);
    dependers[prereq].insert(depender);
    prerequisites[depender].insert(prereq);
  }

  // All jobs that are currently free to be processed, prerequisites have been
  // completed.
  std::deque<int> freedJobs(roots.cbegin(), roots.cend());
  std::vector<int> topology;
  topology.reserve(jobs.size());

  // The only jobs added to freedJobs are those with no dependencies.
  // Any node with a circular dependency cannot be added to freedJobs,
  // as its prerequisite list cannot become empty.
  while (!freedJobs.empty()) {
    const int currJob = freedJobs.front();
    freedJobs.pop_front();
    topology.push_back(currJob);

    const auto it = dependers.find(currJob);
    if (it != dependers.cend()) {
      for (const int depender : it->second) {
        std::unordered_set<int>& prereqs = prerequisites[depender];
        prereqs.erase(currJob);
        if (prereqs.empty()) {
          freedJobs.push_back(depender);
        }
      }
    }
  }

  return topology.size() == jobs.size() ? topology : std::vector<int>{};
}