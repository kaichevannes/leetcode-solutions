#include "solution.h"
#include <deque>

std::vector<int> Solution::rightSideView(TreeNode *root) {
  std::vector<int> result;
  std::deque<TreeNode *> queue;
  std::deque<TreeNode *> nextLayer;

  if (root) {
    queue.push_back(root);
  }

  while (!queue.empty()) {
    TreeNode *node = queue.front();
    queue.pop_front();

    if (node->left) {
      nextLayer.push_back(node->left);
    }
    if (node->right) {
      nextLayer.push_back(node->right);
    }

    if (queue.empty()) {
      result.push_back(node->val);
      std::swap(queue, nextLayer);
    }
  };

  return result;
}
