/*
Difficulty: Easy
*/

impl Solution {
    pub fn decode(encoded: Vec<i32>, first: i32) -> Vec<i32> {
        let mut original = Vec::with_capacity(encoded.len() + 1);
        original.push(first);

        let mut curr_original = first;
        for encoded_value in encoded {
            curr_original ^= encoded_value;
            original.push(curr_original);
        }

        original
    }
}
