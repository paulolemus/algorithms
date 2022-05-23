/*
Difficulty: Easy
Runtime: 0 ms (100%)
*/

impl Solution {
    /// Time: O(n), Space: O(1)
    pub fn check_record(s: String) -> bool {
        let mut absents = 0;
        let mut consecutive_lates = 0;

        for &ch in s.as_bytes() {
            if ch == b'A' {
                absents += 1;
                consecutive_lates = 0;
                if absents >= 2 {
                    return false;
                }
            } else if ch == b'L' {
                consecutive_lates += 1;
                if consecutive_lates >= 3 {
                    return false;
                }
            } else {
                consecutive_lates = 0;
            }
        }

        true
    }
}
