/* Notes
Difficulty: Easy
*/

#include <algorithm>
#include <vector>

int minimumWaitingTime(std::vector<int> queries) {
  // Write your code here.
  std::sort(queries.begin(), queries.end());

  int total_waiting_time = 0;
  int last_waiting_time = 0;
  int last_duration = 0;

  for (const int query : queries) {
    last_waiting_time += last_duration;
    total_waiting_time += last_waiting_time;
    last_duration = query;
  }
  return total_waiting_time;
}