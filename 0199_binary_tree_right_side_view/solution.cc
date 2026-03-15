#include "solution.h"
#include <queue>

std::vector<int> Solution::rightSideView(TreeNode *root) {
  std::vector<int> result;
  std::queue<TreeNode *> queue;

  if (root) {
    queue.push(root);
  }

  while (!queue.empty()) {
    int nodesInLayer = queue.size();

    for (int i = 0; i < nodesInLayer; i++) {
      TreeNode *node = queue.front();
      queue.pop();

      if (node->left) {
        queue.push(node->left);
      }
      if (node->right) {
        queue.push(node->right);
      }

      bool atLastNodeInLayer = (i == nodesInLayer - 1);
      if (atLastNodeInLayer) {
        result.push_back(node->val);
      }
    }
  }

  return result;
}
