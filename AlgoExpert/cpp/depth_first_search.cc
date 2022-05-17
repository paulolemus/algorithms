/* Notes
Difficulty: Easy
*/

#include <string>
#include <vector>

// Do not edit the class below except
// for the depthFirstSearch method.
// Feel free to add new properties
// and methods to the class.
class Node {
  void dfsGetNames(std::vector<std::string> &out) const {
    out.push_back(this->name);
    for (const Node *child : this->children) {
      if (child) {
        child->dfsGetNames(out);
      }
    }
  }

 public:
  std::string name;
  std::vector<Node *> children;

  Node(std::string str) { name = str; }

  std::vector<std::string> depthFirstSearch(
      std::vector<std::string> *const array) const {
    // Write your code here.
    // Accepting a vector by pointer and returning a copy of it is pretty weird.
    std::vector<std::string> backup;
    std::vector<std::string> &validArray = (array != nullptr) ? *array : backup;
    this->dfsGetNames(validArray);
    return validArray;
  }

  Node *addChild(std::string name) {
    Node *child = new Node(name);
    children.push_back(child);
    return this;
  }
};