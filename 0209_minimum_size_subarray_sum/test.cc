#include "solution.h"
#include <algorithm>
#include <climits>
#include <gtest/gtest.h>
#include <numeric>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

class Test0209 : public testing::Test {
protected:
  Solution solution;
  int target;
  std::vector<int> nums;
};

TEST_F(Test0209, SubArrayMatchesTarget) {
  target = 2;
  nums = {2};
  EXPECT_EQ(1, solution.minSubArrayLen(target, nums));
}

TEST_F(Test0209, NoSuchSubArray) {
  target = 100;
  nums = {1, 2, 3, 4, 5};
  EXPECT_EQ(0, solution.minSubArrayLen(target, nums));
}

TEST_F(Test0209, SpreadOutSubArray) {
  target = 7;
  nums = {1, 1, 3, 4, 1};
  EXPECT_EQ(2, solution.minSubArrayLen(target, nums));
}

TEST_F(Test0209, DuplicateInSubArray) {
  target = 4;
  nums = {1, 4, 4};
  EXPECT_EQ(1, solution.minSubArrayLen(target, nums));
}

TEST_F(Test0209, LongSubArray) {
  target = 10;
  nums = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  EXPECT_EQ(10, solution.minSubArrayLen(target, nums));
}

TEST_F(Test0209, ContiguousSubArray) {
  target = 7;
  nums = {3, 1, 4};
  EXPECT_EQ(3, solution.minSubArrayLen(target, nums));
}

class TestProperty0209 : public Test0209 {
protected:
  int defaultTarget() { return *rc::gen::inRange(1, 100000); }

  std::vector<int> defaultNums() {
    return *rc::gen::suchThat(
        rc::gen::container<std::vector<int>>(rc::gen::inRange(1, 10000)),
        [](std::vector<int> vec) { return vec.size() > 0; });
  }
};

RC_GTEST_FIXTURE_PROP(TestProperty0209, ReturnsZeroWhenTargetIsMaximumInteger,
                      ()) {
  target = INT_MAX;
  nums = defaultNums();
  RC_ASSERT(solution.minSubArrayLen(target, nums) == 0);
}

RC_GTEST_FIXTURE_PROP(TestProperty0209,
                      SolutionExistsWhenArraySizeExceedsTarget, ()) {
  target = *rc::gen::inRange(1, 50);
  std::vector<int> nums =
      *rc::gen::mapcat(rc::gen::inRange<int>(target, 100), [](int size) {
        return rc::gen::container<std::vector<int>>(size,
                                                    rc::gen::positive<int>());
      });
  RC_ASSERT(solution.minSubArrayLen(target, nums) != 0);
}

RC_GTEST_FIXTURE_PROP(TestProperty0209,
                      PreservesSolutionWhenArrayElementsAreIncremented, ()) {
  target = defaultTarget();
  nums = defaultNums();
  RC_PRE(solution.minSubArrayLen(target, nums) != 0);

  std::transform(nums.begin(), nums.end(), nums.begin(),
                 [](int val) { return val + 1; });
  RC_ASSERT(solution.minSubArrayLen(target, nums) != 0);
}

RC_GTEST_FIXTURE_PROP(TestProperty0209, ResultEqualsTargetWhenAllElementsAreOne,
                      ()) {
  target = *rc::gen::inRange(1, 100);
  nums = *rc::gen::container<std::vector<int>>(rc::gen::just<int>(1));
  RC_PRE(nums.size() >= target);

  RC_ASSERT(solution.minSubArrayLen(target, nums) == target);
}

RC_GTEST_FIXTURE_PROP(TestProperty0209,
                      EnsuresArraySumExceedsTargetForValidSolution, ()) {
  target = defaultTarget();
  nums = defaultNums();
  RC_PRE(solution.minSubArrayLen(target, nums) != 0);

  long long sum = std::accumulate(nums.begin(), nums.end(), 0LL);
  RC_ASSERT(sum >= target);
}

RC_GTEST_FIXTURE_PROP(TestProperty0209, ReturnsOneWhenTargetIsOne, ()) {
  target = 1;
  nums = defaultNums();
  RC_ASSERT(solution.minSubArrayLen(target, nums) == 1);
}

RC_GTEST_FIXTURE_PROP(TestProperty0209, ReturnsOneWhenElementExceedsTarget,
                      ()) {
  target = defaultTarget();
  nums = defaultNums();
  nums.push_back(target + 1);
  RC_ASSERT(solution.minSubArrayLen(target, nums) == 1);
}
