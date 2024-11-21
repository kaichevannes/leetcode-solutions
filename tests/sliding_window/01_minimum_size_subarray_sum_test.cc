#include "../../src/sliding_window/01_minimum_size_subarray_sum.h"
#include <algorithm>
#include <climits>
#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

class MinimumSizeSubArraySumTest : public testing::Test {
protected:
  MinimumSizeSubArraySum minimumSizeSubArraySum;
  int target;
  std::vector<int> nums;
};

TEST_F(MinimumSizeSubArraySumTest, SubArrayMatchesTarget) {
  target = 2;
  nums = {2};
  EXPECT_EQ(1, minimumSizeSubArraySum.minSubArrayLen(target, nums));
}

TEST_F(MinimumSizeSubArraySumTest, NoSuchSubArray) {
  target = 100;
  nums = {1, 2, 3, 4, 5};
  EXPECT_EQ(0, minimumSizeSubArraySum.minSubArrayLen(target, nums));
}

TEST_F(MinimumSizeSubArraySumTest, SpreadOutSubArray) {
  target = 7;
  nums = {1, 1, 3, 4, 1};
  EXPECT_EQ(2, minimumSizeSubArraySum.minSubArrayLen(target, nums));
}

TEST_F(MinimumSizeSubArraySumTest, DuplicateInSubArray) {
  target = 4;
  nums = {1, 4, 4};
  EXPECT_EQ(1, minimumSizeSubArraySum.minSubArrayLen(target, nums));
}

TEST_F(MinimumSizeSubArraySumTest, LongSubArray) {
  target = 10;
  nums = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  EXPECT_EQ(10, minimumSizeSubArraySum.minSubArrayLen(target, nums));
}

TEST_F(MinimumSizeSubArraySumTest, ContiguousSubArray) {
  target = 7;
  nums = {3, 1, 4};
  EXPECT_EQ(3, minimumSizeSubArraySum.minSubArrayLen(target, nums));
}

class MinimumSizeSubArraySumTestProperty : public MinimumSizeSubArraySumTest {
protected:
  int target = *rc::gen::positive<int>();
  std::vector<int> nums = *rc::gen::positive<std::vector<int>>();
};

RC_GTEST_FIXTURE_PROP(MinimumSizeSubArraySumTestProperty, MaxIntTargetAlwaysReturnsZero, ()) {
  target = INT_MAX;
  RC_ASSERT(minimumSizeSubArraySum.minSubArrayLen(target, nums) == 0); 
}
