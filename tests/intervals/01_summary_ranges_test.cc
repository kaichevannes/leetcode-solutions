#include "../../src/intervals/01_summary_ranges.h"
#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>
#include <string>

class SummaryRangesTest : public testing::Test {
protected:
  SummaryRanges summaryRanges;
  std::vector<int> nums;
};

TEST_F(SummaryRangesTest, ReturnsEmptyListWhenInputIsEmpty) {
  nums = {};
  EXPECT_EQ(std::vector<std::string>({}), summaryRanges.summaryRanges(nums));
}

TEST_F(SummaryRangesTest, GroupsConsecutiveNumbersIntoSingleRange) {
  nums = {0, 1, 2};
  EXPECT_EQ(std::vector<std::string>({"0->2"}),
            summaryRanges.summaryRanges(nums));
}

TEST_F(SummaryRangesTest, ReturnsSingleNumberAsIndividualRange) {
  nums = {0};
  EXPECT_EQ(std::vector<std::string>({"0"}), summaryRanges.summaryRanges(nums));
}

TEST_F(SummaryRangesTest, ReturnsSingleNegativeNumberAsIndividualRange) {
  nums = {-1};
  EXPECT_EQ(std::vector<std::string>({"-1"}),
            summaryRanges.summaryRanges(nums));
}

TEST_F(SummaryRangesTest, GroupsListWithSeparatedNumbersIntoMultipleRanges) {
  nums = {0, 1, 2, 4, 5, 7};
  EXPECT_EQ(std::vector<std::string>({"0->2", "4->5", "7"}),
            summaryRanges.summaryRanges(nums));
}

TEST_F(SummaryRangesTest, HandlesMaximumSizeInput) {
  nums = {-10, -9, -8, -7, -6, -5, -4, -3, -2, -1,
          0,   1,  2,  3,  4,  5,  6,  7,  8,  9};
  EXPECT_EQ(std::vector<std::string>({"-10->9"}),
            summaryRanges.summaryRanges(nums));
}

class SummaryRangesTestProperty : public SummaryRangesTest {
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

RC_GTEST_FIXTURE_PROP(SummaryRangesTestProperty,
                      OutputSizeIsNoGreaterThanInputSize, ()) {
  nums = *genNums();
  RC_ASSERT(summaryRanges.summaryRanges(nums).size() <= nums.size());
}

RC_GTEST_FIXTURE_PROP(SummaryRangesTestProperty, ProducesValidRanges, ()) {
  nums = *genNums();
  std::vector<std::string> ranges = summaryRanges.summaryRanges(nums);

  for (const std::string &range : ranges) {
    if (!isRange(range))
      continue;

    auto [start, end] = parseRange(range);

    RC_ASSERT(start < end);
  }
}

RC_GTEST_FIXTURE_PROP(SummaryRangesTestProperty,
                      AllNumbersWithinOutputRangesBelongToInput, ()) {
  nums = *genNums();
  std::vector<std::string> ranges = summaryRanges.summaryRanges(nums);

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
