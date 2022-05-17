/*
Difficulty: Easy
*/

use std::cmp::Ordering;
use std::collections::HashMap;

impl Solution {
    pub fn is_alien_sorted(words: Vec<String>, order: String) -> bool {
        let ordering: HashMap<char, usize> =
            order.chars().enumerate().map(|(i, ch)| (ch, i)).collect();

        words
            .iter()
            .zip(words.iter().skip(1))
            .all(|(l, r)| is_sorted(l, r, &ordering))
    }
}

/// Lexically compare two strs given an alphabet ordering.
fn is_sorted(lhs: &str, rhs: &str, ordering: &HashMap<char, usize>) -> bool {
    let char_pairs = lhs.chars().zip(rhs.chars());

    for (l, r) in char_pairs {
        match ordering[&l].cmp(&ordering[&r]) {
            Ordering::Less => return true,
            Ordering::Greater => return false,
            Ordering::Equal => {}
        }
    }
    lhs.len() <= rhs.len()
}
