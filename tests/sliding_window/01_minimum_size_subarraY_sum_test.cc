#include <gtest/gtest.h>
#include "../../src/sliding_window/01_minimum_size_subarray_sum.h"

class MinimumSizeSubarraySumTest : public testing::Test {
protected:
  MinimumSizeSubarraySum minimumSizeSubArraySum;
  int target;
  std::vector<int> nums;
};

TEST_F(MinimumSizeSubarraySumTest, SubarrayMatchesTarget) {
  target = 2;
  nums = {2};
  EXPECT_EQ(2, minimumSizeSubArraySum.minSubArrayLen(2, nums));
}
