#include <gtest/gtest.h>
#include "../../src/sliding_window/01_minimum_size_subarray_sum.h"

class MinimumSizeSubarraySumTest : public testing::Test {
protected:
  MinimumSizeSubarraySum minimumSizeSubArraySum;
  int target;
  std::vector<int> nums;
};

TEST_F(MinimumSizeSubarraySumTest, Unit_SubarrayMatchesTarget) {
  target = 2;
  nums = {2};
  EXPECT_EQ(1, minimumSizeSubArraySum.minSubArrayLen(target, nums));
}

TEST_F(MinimumSizeSubarraySumTest, Unit_NoSuchSubarray) {
  target = 100;
  nums = {1,2,3,4,5};
  EXPECT_EQ(0, minimumSizeSubArraySum.minSubArrayLen(target, nums));
}

TEST_F(MinimumSizeSubarraySumTest, Unit_SpreadOutSubarray) {
  target = 7;
  nums = {1, 1, 3, 4, 1};
  EXPECT_EQ(2, minimumSizeSubArraySum.minSubArrayLen(target, nums));
}

TEST_F(MinimumSizeSubarraySumTest, Unit_DuplicateInSubarray) {
  target = 4;
  nums = {1, 4, 4};
  EXPECT_EQ(1, minimumSizeSubArraySum.minSubArrayLen(target, nums));
}

TEST_F(MinimumSizeSubarraySumTest, Unit_LongSubarray) {
  target = 10;
  nums = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  EXPECT_EQ(10, minimumSizeSubArraySum.minSubArrayLen(target, nums));
}

TEST_F(MinimumSizeSubarraySumTest, Unit_ContiguousSubarray) {
  target = 7;
  nums = {3, 1, 4};
  EXPECT_EQ(3, minimumSizeSubArraySum.minSubArrayLen(target, nums));
}
