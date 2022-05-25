/*
Difficulty: Easy
Runtime: 0 ms (100%)
*/

impl Solution {
    /// Time: O(n), Space: O(1)
    /// Would rather take s as &str.
    pub fn check_string(s: String) -> bool {
        let mut found_b = false;
        for &ch in s.as_bytes() {
            if ch == b'b' {
                found_b = true;
            }
            if found_b && ch == b'a' {
                return false;
            }
        }

        true
    }
}
