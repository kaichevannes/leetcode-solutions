#include "solution.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("A tree with one element has a depth of one") {
  Solution solution;
  TreeNode root;

  REQUIRE(solution.maxDepth(&root) == 1);
}
