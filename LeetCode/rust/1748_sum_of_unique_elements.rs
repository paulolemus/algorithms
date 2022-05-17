/*
Difficulty: Easy
*/

use std::collections::HashSet;

impl Solution {
    pub fn sum_of_unique(nums: Vec<i32>) -> i32 {
        let mut dup = HashSet::new();
        let mut unique = HashSet::new();

        for num in nums {
            if dup.contains(&num) || unique.contains(&num) {
                dup.insert(num);
                unique.remove(&num);
            } else {
                unique.insert(num);
            }
        }

        unique.into_iter().sum()
    }
}
