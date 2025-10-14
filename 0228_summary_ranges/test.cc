#include "solution.h"
#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>
#include <string>

class Test0228 : public testing::Test {
protected:
  Solution solution;
  std::vector<int> nums;
};

TEST_F(Test0228, ReturnsEmptyListWhenInputIsEmpty) {
  nums = {};
  EXPECT_EQ(std::vector<std::string>({}), solution.summaryRanges(nums));
}

TEST_F(Test0228, GroupsConsecutiveNumbersIntoSingleRange) {
  nums = {0, 1, 2};
  EXPECT_EQ(std::vector<std::string>({"0->2"}), solution.summaryRanges(nums));
}

TEST_F(Test0228, ReturnsSingleNumberAsIndividualRange) {
  nums = {0};
  EXPECT_EQ(std::vector<std::string>({"0"}), solution.summaryRanges(nums));
}

TEST_F(Test0228, ReturnsSingleNegativeNumberAsIndividualRange) {
  nums = {-1};
  EXPECT_EQ(std::vector<std::string>({"-1"}), solution.summaryRanges(nums));
}

TEST_F(Test0228, GroupsListWithSeparatedNumbersIntoMultipleRanges) {
  nums = {0, 1, 2, 4, 5, 7};
  EXPECT_EQ(std::vector<std::string>({"0->2", "4->5", "7"}),
            solution.summaryRanges(nums));
}

TEST_F(Test0228, HandlesMaximumSizeInput) {
  nums = {-10, -9, -8, -7, -6, -5, -4, -3, -2, -1,
          0,   1,  2,  3,  4,  5,  6,  7,  8,  9};
  EXPECT_EQ(std::vector<std::string>({"-10->9"}), solution.summaryRanges(nums));
}

class TestProperty0228 : public Test0228 {
protected:
  rc::Gen<std::vector<int>> genNums() {
    return rc::gen::map(genUniqueIntVector(), [](std::vector<int> nums) {
      std::sort(nums.begin(), nums.end());
      return nums;
    });
  }

  std::pair<int, int> parseRange(std::string range) {
    assert(range.size() > 1);

    auto pos = range.find("->");
    int start = std::stoi(range.substr(0, pos));
    int end = std::stoi(range.substr(pos + 2));

    return {start, end};
  }

  bool isRange(std::string range) {
    return range.find("->") != std::string::npos;
  }

private:
  rc::Gen<std::vector<int>> genUniqueIntVector() {
    return rc::gen::unique<std::vector<int>>(rc::gen::arbitrary<int>());
  }
};

RC_GTEST_FIXTURE_PROP(TestProperty0228, OutputSizeIsNoGreaterThanInputSize,
                      ()) {
  nums = *genNums();
  RC_ASSERT(solution.summaryRanges(nums).size() <= nums.size());
}

RC_GTEST_FIXTURE_PROP(TestProperty0228, ProducesValidRanges, ()) {
  nums = *genNums();
  std::vector<std::string> ranges = solution.summaryRanges(nums);

  for (const std::string &range : ranges) {
    if (!isRange(range))
      continue;

    auto [start, end] = parseRange(range);

    RC_ASSERT(start < end);
  }
}

RC_GTEST_FIXTURE_PROP(TestProperty0228,
                      AllNumbersWithinOutputRangesBelongToInput, ()) {
  nums = *genNums();
  std::vector<std::string> ranges = solution.summaryRanges(nums);

  for (std::string range : ranges) {
    if (!isRange(range)) {
      RC_ASSERT(std::find(nums.begin(), nums.end(), std::stoi(range)) !=
                nums.end());
    } else {
      auto [start, end] = parseRange(range);

      for (int i = start; i <= end; i++) {
        RC_ASSERT(std::find(nums.begin(), nums.end(), i) != nums.end());
      }
    }
  }
}
