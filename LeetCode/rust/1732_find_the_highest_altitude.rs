/*
Difficulty: Easy
*/

use std::cmp;

impl Solution {
    pub fn largest_altitude(gain: Vec<i32>) -> i32 {
        let mut curr_altitude = 0;
        let mut max_altitude = 0;

        for delta in gain {
            curr_altitude += delta;
            max_altitude = cmp::max(max_altitude, curr_altitude);
        }

        max_altitude
    }
}
