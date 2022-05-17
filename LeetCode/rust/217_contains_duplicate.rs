/*
Difficulty: Easy
*/

use std::collections::HashSet;

impl Solution {
    pub fn contains_duplicate(nums: Vec<i32>) -> bool {
        let mut seen = HashSet::new();

        for num in nums {
            match seen.contains(&num) {
                true => return true,
                false => seen.insert(num),
            };
        }
        return false;
    }
}
