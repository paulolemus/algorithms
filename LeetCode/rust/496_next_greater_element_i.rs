/*
Difficulty: Easy
*/

use std::collections::HashMap;

impl Solution {
    /// Time: O(n + m), Space: (m)
    /// n = nums1.len, m = nums2.len
    pub fn next_greater_element(mut nums1: Vec<i32>, nums2: Vec<i32>) -> Vec<i32> {
        // value -> next greater value coming from a greater index.
        let mut next_greater = HashMap::<i32, i32>::new();
        let mut stack = Vec::<i32>::new();

        // Find the next greater number for each number in nums2.
        for curr_num in nums2 {
            while let Some(&most_recent_num) = stack.last() {
                if most_recent_num < curr_num {
                    next_greater.insert(most_recent_num, curr_num);
                    stack.pop();
                } else {
                    break;
                }
            }
            stack.push(curr_num);
        }

        // Replace each value in nums1 with its next greater value in nums2.
        let next_greater = next_greater;
        for num in &mut nums1 {
            *num = next_greater.get(&num).copied().unwrap_or(-1);
        }
        nums1
    }
}
