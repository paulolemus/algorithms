/*
Difficulty: Easy
*/

use std::collections::HashMap;

impl Solution {
    pub fn contains_nearby_duplicate(nums: Vec<i32>, k: i32) -> bool {
        if k < 0 {
            return false;
        }

        let mut seen_indices = HashMap::<i32, i32>::new();
        for (i, num) in nums.into_iter().enumerate() {
            let i = i as i32;
            if let Some(&matched_idx) = seen_indices.get(&num) {
                if (i - matched_idx).abs() <= k {
                    return true;
                }
            }
            seen_indices.insert(num, i);
        }

        false
    }
}
