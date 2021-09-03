#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <unordered_set>
#include <cmath>

struct Node {
  const char ch;
  Node *left = nullptr;
  Node *right = nullptr;

  explicit Node(const char other) : ch(other) {}
};

std::bitset<26> DFS(Node *node, std::unordered_set<std::bitset<26>> &string_set, std::bitset<26> &result) {
  if (node == nullptr || result.any()) {
    return 0x0;
  }
  std::bitset<26> bitset(0);
  bitset |= DFS(node->left, string_set, result);
  bitset |= DFS(node->right, string_set, result);
  bitset |= 1 << (node->ch - 'A');

  if (string_set.count(bitset) && result.none()) {
    result = bitset;
  }
  if (bitset.any()) {
    string_set.insert(bitset);
  }
  return bitset;
}

class BinaryTree {
public:
  explicit BinaryTree(std::string &str) {
    root = nullptr;
    int cur_h = 0;
    int h = floor(log2(str.size())) + 1;
    int i = 0;
    root = GrowBinaryTree(str, i, cur_h, h);
  }

  Node *root;
private:
  Node *GrowBinaryTree(std::string s, int &i, int &cur_h, int h) {
    if (i == s.size() || cur_h == h) {
      --cur_h;
      return nullptr;
    }
    if (s[i] == '0') {
      i++;
      --cur_h;
      return nullptr;
    }
    Node *node = new Node(s[i++]);
    node->left = GrowBinaryTree(s, i, ++cur_h, h);
    node->right = GrowBinaryTree(s, i, ++cur_h, h);
    --cur_h;
    return node;
  }
};

int main() {
  std::string s;
  std::cin >> s;
  BinaryTree tree(s);
  std::bitset<26> result;
  std::unordered_set<std::bitset<26>> set;
  DFS(tree.root, set, result);

  if (result.none()) {
    std::cout << "None\n";
    return 0;
  }

  for (int i = 0; i < 26; ++i) {
    std::bitset<26> ch;
    ch.set(i);
    if (result.test(i)) {
      std::cout << char('A' + i);
    }
  }

}
