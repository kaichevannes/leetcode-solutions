#include "solution.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

TEST_CASE("A tree with one element has a depth of one") {
  Solution solution;
  TreeNode node1;

  REQUIRE(solution.maxDepth(&node1) == 1);
}

TEST_CASE("A tree with two elements has a depth of two") {
  Solution solution;
  TreeNode node1;
  TreeNode node2;

  node1.right = &node2;

  REQUIRE(solution.maxDepth(&node1) == 2);
}

TEST_CASE("A left-skewed tree with five elements has a depth of five") {
  Solution solution;

  TreeNode node1, node2, node3, node4, node5;

  //     1
  //    2
  //   3
  //  4
  // 5

  node1.left = &node2;
  node2.left = &node3;
  node3.left = &node4;
  node4.left = &node5;

  REQUIRE(solution.maxDepth(&node1) == 5);
}

TEST_CASE("A full tree") {
  SECTION("with three elements has a depth of two") {
    Solution solution;
    TreeNode node1, node2, node3;

    //   1
    // 2   3

    node1.left = &node2;
    node1.right = &node3;

    REQUIRE(solution.maxDepth(&node1) == 2);
  }

  SECTION("with seven elements has a depth of three") {
    Solution solution;
    TreeNode node1, node2, node3, node4, node5, node6, node7;

    //       1
    //   2       3
    // 4   5   6   7

    node1.left = &node2;
    node1.right = &node3;
    node2.left = &node4;
    node2.right = &node5;
    node3.left = &node6;
    node3.right = &node7;

    REQUIRE(solution.maxDepth(&node1) == 3);
  }
}
