#include "../../src/array_string/01_merge_sorted_array.h"
#include "rapidcheck/Log.h"
#include "rapidcheck/gen/Arbitrary.h"
#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

class MergeSortedArrayTest : public testing::Test {
protected:
  MergeSortedArray mergeSortedArray;
  std::vector<int> nums1;
  std::vector<int> nums2;

  void callMerge(std::vector<int> &nums1, std::vector<int> &nums2) {
    mergeSortedArray.merge(nums1, nums1.size() - nums2.size(), nums2,
                           nums2.size());
  }
};

TEST_F(MergeSortedArrayTest, SingleElementInNums1) {
  nums1 = {1};

  callMerge(nums1, nums2);

  EXPECT_EQ(std::vector<int>{1}, nums1);
}

TEST_F(MergeSortedArrayTest, SingleElementInNums2) {
  nums1 = {0};
  nums2 = {1};

  callMerge(nums1, nums2);

  EXPECT_EQ(std::vector<int>{1}, nums1);
}

TEST_F(MergeSortedArrayTest, Nums1FollowedByNums2) {
  nums1 = {1, 2, 3, 0, 0, 0};
  nums2 = {4, 5, 6};

  callMerge(nums1, nums2);

  EXPECT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6}), nums1);
}

TEST_F(MergeSortedArrayTest, Nums2FollowedByNums1) {
  nums1 = {4, 5, 6, 0, 0, 0};
  nums2 = {1, 2, 3};

  callMerge(nums1, nums2);

  EXPECT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6}), nums1);
}

TEST_F(MergeSortedArrayTest, NumsInterleaved) {
  nums1 = {1, 3, 5, 0, 0, 0};
  nums2 = {2, 4, 6};

  callMerge(nums1, nums2);

  EXPECT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6}), nums1);
}

TEST_F(MergeSortedArrayTest, SingleNums1SingleNums2) {
  nums1 = {2, 0};
  nums2 = {1};

  callMerge(nums1, nums2);

  EXPECT_EQ(std::vector<int>({1, 2}), nums1);
}


TEST_F(MergeSortedArrayTest, LeadingZerosInNums2) {
  nums1 = {0, 0, 0};
  nums2 = {0, 0, 1};

  callMerge(nums1, nums2);

  EXPECT_EQ(std::vector<int>({0, 0, 1}), nums1);
}

void logVector(std::string vectorName, std::vector<int> vec) {
  RC_LOG() << vectorName << ": [";
  for (auto i: vec) {
    RC_LOG() << i << ' ';
  }
  RC_LOG() << ']' << std::endl;
}

RC_GTEST_FIXTURE_PROP(MergeSortedArrayTest, Commutativity, ()) {
  const auto m = *rc::gen::inRange(0, 200);
  const auto n = *rc::gen::inRange(0, 200);
  RC_PRE(m + n >= 1);

  auto nums1 =
      *rc::gen::container<std::vector<int>>(m, rc::gen::arbitrary<int>());
  auto nums2 =
      *rc::gen::container<std::vector<int>>(n, rc::gen::arbitrary<int>());
  int firstInputSize = nums1.size() + nums2.size();
  int secondInputSize = nums2.size();
  nums1.resize(firstInputSize);
  callMerge(nums1, nums2);

  auto nums1Copy = nums1;
  auto nums2Copy = nums2;
  nums2Copy.resize(firstInputSize);

  callMerge(nums2Copy, nums1Copy);

  RC_ASSERT(nums1 == nums2Copy);
}

