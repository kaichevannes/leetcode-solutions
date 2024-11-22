#include "../../src/intervals/01_summary_ranges.h"
#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

class SummaryRangesTest : public testing::Test {
protected:
  SummaryRanges summaryRanges;
  std::vector<int> nums;
};

TEST_F(SummaryRangesTest, EmptyNums) {
  nums = {};
  EXPECT_EQ(std::vector<std::string>({}), summaryRanges.summaryRanges(nums));
}

class SummaryRangesTestProperty : public SummaryRangesTest {
protected:
  rc::Gen<std::vector<int>> genUniqueIntVector() {
    return rc::gen::unique<std::vector<int>>(rc::gen::arbitrary<int>());
  }
};

// RC_GTEST_FIXTURE_PROP(SummaryRangesTestProperty, ) {
//
// }
