#include "solution.h"
#include <algorithm>

int depth(TreeNode *node) {
  if (node == nullptr) {
    return 0;
  }

  return 1 + std::max(depth(node->left), depth(node->right));
}

int Solution::maxDepth(TreeNode *root) { return depth(root); }
