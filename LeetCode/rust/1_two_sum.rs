/*
Difficulty: Easy
*/

use std::collections::HashMap;

impl Solution {
    pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
        let mut matching_indices = HashMap::<i32, i32>::new();

        for (i, num) in nums.into_iter().enumerate() {
            let (i, pair) = (i as i32, target - num);
            if let Some(&matched_idx) = matching_indices.get(&pair) {
                return vec![i, matched_idx];
            } else {
                matching_indices.insert(num, i);
            }
        }

        vec![0, 0]
    }
}
