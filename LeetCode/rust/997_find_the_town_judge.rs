/*
Difficulty: Easy
*/

use std::collections::{HashMap, HashSet};

impl Solution {
    pub fn find_judge(n: i32, trust: Vec<Vec<i32>>) -> i32 {
        // People who trust at least 1 person.
        let mut fools: HashSet<i32> = HashSet::new();
        // PersonLabel -> number of people who trust PersonLabel.
        let mut trust_counts: HashMap<i32, i32> = HashMap::new();

        for trusters in trust {
            let (truster, trustee) = (trusters[0], trusters[1]);
            fools.insert(truster);
            *trust_counts.entry(trustee).or_default() += 1;
        }

        for person in 1..=n {
            if !fools.contains(&person) {
                if trust_counts.get(&person).copied().unwrap_or(0) == n - 1 {
                    return person;
                }
            }
        }

        // Otherwise no judge.
        -1
    }
}
