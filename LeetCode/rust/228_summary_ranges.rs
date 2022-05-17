/*
Difficulty: Easy
*/

use std::ops::RangeInclusive;

impl Solution {
    pub fn summary_ranges(nums: Vec<i32>) -> Vec<String> {
        if (nums.is_empty()) {
            return vec![];
        }
        let mut ranges = Vec::<String>::new();
        let mut start = nums[0];
        let mut end = nums[0];

        for num in nums.into_iter().skip(1) {
            if num != end + 1 {
                ranges.push(range_to_string(start..=end));
                start = num;
            }
            end = num;
        }
        ranges.push(range_to_string(start..=end));

        ranges
    }
}

fn range_to_string(ri: RangeInclusive<i32>) -> String {
    match ri.start() == ri.end() {
        true => format!("{}", ri.start()),
        false => format!("{}->{}", ri.start(), ri.end()),
    }
}
