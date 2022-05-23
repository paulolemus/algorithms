/*
Difficulty: Easy
*/

impl Solution {
    /// Time: O(n), n = # chars in words, Space: O(1)
    pub fn count_consistent_strings(allowed: String, words: Vec<String>) -> i32 {
        let mut allowed_set: [bool; 26] = [false; 26];
        for &ch in allowed.as_bytes() {
            allowed_set[(ch - b'a') as usize] = true;
        }

        let mut consistents = words.len() as i32;
        for word in words {
            for &ch in word.as_bytes() {
                if !allowed_set[(ch - b'a') as usize] {
                    consistents -= 1;
                    break;
                }
            }
        }

        consistents
    }
}
