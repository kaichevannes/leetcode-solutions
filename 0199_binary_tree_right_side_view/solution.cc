#include "solution.h"

void recurse(TreeNode *node, std::vector<int> &result) {
  // base
  if (node == nullptr) {
    return;
  }

  // pre
  result.push_back(node->val);

  // recurse
  if (node->right) {
    recurse(node->right, result);
  } else {
    recurse(node->left, result);
  }

  // post
}

std::vector<int> Solution::rightSideView(TreeNode *root) {
  std::vector<int> result = std::vector<int>{};
  recurse(root, result);
  return result;
}
