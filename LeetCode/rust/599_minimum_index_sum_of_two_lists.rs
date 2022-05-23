/*
Difficulty: Easy
*/

use std::cmp;
use std::collections::HashMap;

impl Solution {
    pub fn find_restaurant(list1: Vec<String>, list2: Vec<String>) -> Vec<String> {
        let (shorter, longer) = match list1.len() < list2.len() {
            true => (list1, list2),
            false => (list2, list1),
        };
        let restaurant_indices: HashMap<String, usize> = shorter
            .into_iter()
            .enumerate()
            .map(|(i, restaurant)| (restaurant, i))
            .collect();

        let mut min_sum = usize::MAX;
        let mut common_restaurant_sums = HashMap::<String, usize>::new();

        for (i, restaurant) in longer.into_iter().enumerate() {
            if let Some(&pair_idx) = restaurant_indices.get(&restaurant) {
                let idx_sum = i + pair_idx;
                min_sum = cmp::min(min_sum, idx_sum);
                common_restaurant_sums.insert(restaurant, idx_sum);
            }
        }

        common_restaurant_sums
            .into_iter()
            .filter(|(_, sum)| *sum == min_sum)
            .map(|(restaurant, _)| restaurant)
            .collect()
    }
}
