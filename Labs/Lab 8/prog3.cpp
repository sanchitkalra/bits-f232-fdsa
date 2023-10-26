#include <iostream>

using namespace std;

// basic structure of a binary tree node
class binary_tree_node {
 private:
  int data;
  binary_tree_node *leftChild;
  binary_tree_node *rightChild;

 public:
  binary_tree_node(int item) {
    data = item;
    leftChild = rightChild = NULL;
  }
  // getters
  int getData();
  binary_tree_node *getLeftChild();
  binary_tree_node *getRightChild();
  // setters
  void setLeftChild(binary_tree_node *newLeftChild);
  void setRightChild(binary_tree_node *newRightChild);
};

typedef binary_tree_node node;

int node::getData() { return data; }

node *node::getLeftChild() { return leftChild; }

node *node::getRightChild() { return rightChild; }

void node::setLeftChild(node *newLeftChild) { leftChild = newLeftChild; }

void node::setRightChild(node *newRightChild) { rightChild = newRightChild; }

// basic functionalities of a binary tree
class binary_tree {
 private:
  node *root;
  node *insertRecursive(node *root, int item);
  void preorderRecursive(node *root);
  void inorderRecursive(node *root);
  void postorderRecursive(node *root);

 public:
  binary_tree() { root = NULL; }
  void insert(int item);
  bool isEmpty();
  void preorder();
  void inorder();
  void postorder();
};

typedef binary_tree tree;

// inserts the given item into the binary tree.
void tree::insert(int item) { root = insertRecursive(root, item); }

// recursive method to insert the given item into the binary tree
node *tree::insertRecursive(node *root, int item) {
  if (root == NULL) {
    return new node(item);
  }
  if (root->getLeftChild() == NULL) {
    root->setLeftChild(insertRecursive(root->getLeftChild(), item));
  } else if (root->getRightChild() == NULL) {
    root->setRightChild(insertRecursive(root->getRightChild(), item));
  } else {
    // insert in the right-sub-tree
    insertRecursive(root->getRightChild(), item);
  }
  return root;
}

// utility method to check if the tree is empty
bool tree::isEmpty() { return root == NULL; }

// runs a preorder traversal over the binary tree
void tree::preorder() { preorderRecursive(root); }

// recursive preorder traversal over the binary tree
void tree::preorderRecursive(node *root) {
  // code here...
  if (root == NULL) return;
  cout << root->getData() << " ";
  preorderRecursive(root->getLeftChild());
  preorderRecursive(root->getRightChild());
}

// runs an inorder traversal over the binary tree
void tree::inorder() { inorderRecursive(root); }

// recursive inorder traversal over the binary tree
void tree::inorderRecursive(node *root) {
  // base case
  if (root == NULL) {
    return;
  }
  // go to left-sub-tree
  inorderRecursive(root->getLeftChild());
  // display the [root]'s data
  cout << root->getData() << " ";
  // go to right-sub-tree
  inorderRecursive(root->getRightChild());
}

// runs a postorder traversal over the binary tree
void tree::postorder() { postorderRecursive(root); }

// recursive postorder traversal over the binary tree
void tree::postorderRecursive(node *root) {
  // code here...
  if (root == NULL) return;
  postorderRecursive(root->getLeftChild());
  postorderRecursive(root->getRightChild());
  cout << root->getData() << " ";
}

int main(int argc, char **argv) {
  if (argc < 2) {
    cout << "Must pass the items as argument.\n";
    return 1;
  }

  tree tree;

  for (int i = 1; i < argc; i++) {
    const char *str = argv[i];
    int num;
    sscanf(str, "%d", &num);
    tree.insert(num);
  }

  cout << "Preorder Traversal: ";
  tree.preorder();
  cout << endl;

  cout << "Inorder Traversal: ";
  tree.inorder();
  cout << endl;

  cout << "Postorder Traversal: ";
  tree.postorder();
  cout << endl;

  return 0;
}