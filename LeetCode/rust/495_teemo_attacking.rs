/*
Difficulty: Easy
*/

impl Solution {
    /// Time: O(n), Space: O(1)
    pub fn find_poisoned_duration(time_series: Vec<i32>, duration: i32) -> i32 {
        let mut total_duration = 0;
        let mut curr_range = 0..=0;

        for time in time_series {
            if curr_range.contains(&time) {
                curr_range = *curr_range.start()..=time + duration;
            } else {
                total_duration += *curr_range.end() - *curr_range.start();
                curr_range = time..=time + duration;
            }
        }

        total_duration += *curr_range.end() - *curr_range.start();

        total_duration
    }
}
