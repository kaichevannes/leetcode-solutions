#include "solution.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

TEST_CASE("[0199] A tree with no elements gives an empty right side view") {
  Solution solution;

  REQUIRE(solution.rightSideView(nullptr) == std::vector<int>{});
}

TEST_CASE("[0199] A tree with one element returns its value") {
  Solution solution;
  TreeNode node1 = TreeNode(1);

  REQUIRE(solution.rightSideView(&node1) == std::vector<int>{1});
}

TEST_CASE("[0199] A tree with two elements returns their values") {
  Solution solution;
  TreeNode node1 = TreeNode(1);
  TreeNode node2 = TreeNode(2);

  node1.right = &node2;

  // 1
  //  2

  REQUIRE(solution.rightSideView(&node1) == std::vector<int>{1, 2});
}

TEST_CASE("[0199] A full tree") {
  SECTION("With three elements has a right side view of nodes 1 and 3") {
    Solution solution;
    TreeNode node1 = TreeNode(1);
    TreeNode node2 = TreeNode(2);
    TreeNode node3 = TreeNode(3);

    //  1
    // 2 3
    node1.left = &node2;
    node1.right = &node3;

    REQUIRE(solution.rightSideView(&node1) == std::vector<int>{1, 3});
  }

  SECTION("With six elements has a right side view of nodes 1, 3 and 6") {
    Solution solution;
    TreeNode node1 = TreeNode(1);
    TreeNode node2 = TreeNode(2);
    TreeNode node3 = TreeNode(3);
    TreeNode node4 = TreeNode(4);
    TreeNode node5 = TreeNode(5);
    TreeNode node6 = TreeNode(6);

    //   1
    //  2 3
    // 4 5 6
    node1.left = &node2;
    node1.right = &node3;
    node2.left = &node4;
    node2.right = &node5;
    node3.left = &node5;
    node3.right = &node6;

    REQUIRE(solution.rightSideView(&node1) == std::vector<int>{1, 3, 6});
  }
}

TEST_CASE("[0199] A left-skewed tree has a right side view of its elements") {
  Solution solution;
  TreeNode node1 = TreeNode(1);
  TreeNode node2 = TreeNode(2);
  TreeNode node3 = TreeNode(3);
  TreeNode node4 = TreeNode(4);
  TreeNode node5 = TreeNode(5);
  TreeNode node6 = TreeNode(6);
  TreeNode node7 = TreeNode(7);

  //       1
  //      2
  //     3
  //    4
  //   5
  //  6
  // 7
  node1.left = &node2;
  node2.left = &node3;
  node3.left = &node4;
  node4.left = &node5;
  node5.left = &node6;
  node6.left = &node7;

  REQUIRE(solution.rightSideView(&node1) ==
          std::vector<int>{1, 2, 3, 4, 5, 6, 7});
}

TEST_CASE("[0199] Example 1") {
  Solution solution;
  TreeNode node1 = TreeNode(1);
  TreeNode node2 = TreeNode(2);
  TreeNode node3 = TreeNode(3);
  TreeNode node4 = TreeNode(4);
  TreeNode node5 = TreeNode(5);

  //   1 <------
  // 2   3 <----
  //  4   5 <---
  node1.left = &node2;
  node2.right = &node4;
  node3.right = &node5;

  REQUIRE(solution.rightSideView(&node1) == std::vector<int>{1, 3, 5});
}
