/*
Difficulty: Easy
*/

/// Returns true if first three values in window are unique.
fn distinctWindowThree(window: &&[u8]) -> bool {
    window[0] != window[1] && window[0] != window[2] && window[1] != window[2]
}

impl Solution {
    /// Time: O(n), n = s.len(), Space: O(1)
    pub fn count_good_substrings(s: String) -> i32 {
        s.as_bytes().windows(3).filter(distinctWindowThree).count() as i32
    }
}
