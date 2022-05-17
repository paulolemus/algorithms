/*
Difficulty: Easy
*/

impl Solution {
    pub fn min_deletion_size(strs: Vec<String>) -> i32 {
        let len = strs[0].len();
        let mut deletes: i32 = 0;

        for idx in 0..len {
            let mut vertical_bytes = strs
                .iter()
                .map(String::as_bytes)
                .zip(strs.iter().map(String::as_bytes).skip(1));

            deletes += vertical_bytes.any(|(top, bot)| top[idx] > bot[idx]) as i32;
        }

        deletes
    }
}
