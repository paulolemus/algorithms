/*
Difficulty: Easy
*/

use std::cell::RefCell;
use std::mem;
use std::rc::Rc;

impl Solution {
    pub fn invert_tree(root: Option<Rc<RefCell<TreeNode>>>) -> Option<Rc<RefCell<TreeNode>>> {
        if let Some(ref rc) = root {
            dfs_invert_tree(&rc);
        }
        root
    }
}

fn dfs_invert_tree(curr: &Rc<RefCell<TreeNode>>) {
    {
        let mut node_ref_mut = curr.borrow_mut();
        let node = &mut *node_ref_mut;
        mem::swap(&mut node.left, &mut node.right);
    }

    let node_ref = curr.borrow();
    if let Some(ref rc) = node_ref.left {
        dfs_invert_tree(rc);
    }
    if let Some(ref rc) = node_ref.right {
        dfs_invert_tree(rc);
    }
}
