/*
Difficulty: Medium
*/

#include <queue>
#include <string>
#include <vector>

// Do not edit the class below except
// for the breadthFirstSearch method.
// Feel free to add new properties
// and methods to the class.
class Node {
 public:
  std::string name;
  std::vector<Node *> children;

  Node(std::string str) { name = str; }

  /// Populating a vec pointer argument and returning by value is a little odd.
  std::vector<std::string> breadthFirstSearch(std::vector<std::string> *array) {
    // Write your code here.
    std::vector<std::string> array_backup;
    std::vector<std::string> &array_ref = (array) ? *array : array_backup;
    std::queue<const Node *> node_queue;
    node_queue.push(this);

    while (!node_queue.empty()) {
      const Node *curr_node = node_queue.front();
      node_queue.pop();
      if (!curr_node) continue;

      array_ref.push_back(curr_node->name);
      for (const Node *child : curr_node->children) {
        node_queue.push(child);
      }
    }

    return array_ref;
  }

  Node *addChild(std::string name) {
    Node *child = new Node(name);
    children.push_back(child);
    return this;
  }
};