#include "solution.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

class SolutionTest : public testing::Test {
protected:
  Solution solution;
  std::vector<int> nums1;
  std::vector<int> nums2;

  void callMerge(std::vector<int> &nums1, std::vector<int> &nums2) {
    solution.merge(nums1, nums1.size() - nums2.size(), nums2, nums2.size());
  }
};

TEST_F(SolutionTest, SingleElementInNums1) {
  nums1 = {1};

  callMerge(nums1, nums2);

  EXPECT_EQ(std::vector<int>{1}, nums1);
}

TEST_F(SolutionTest, SingleElementInNums2) {
  nums1 = {0};
  nums2 = {1};

  callMerge(nums1, nums2);

  EXPECT_EQ(std::vector<int>{1}, nums1);
}

TEST_F(SolutionTest, Nums1FollowedByNums2) {
  nums1 = {1, 2, 3, 0, 0, 0};
  nums2 = {4, 5, 6};

  callMerge(nums1, nums2);

  EXPECT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6}), nums1);
}

TEST_F(SolutionTest, Nums2FollowedByNums1) {
  nums1 = {4, 5, 6, 0, 0, 0};
  nums2 = {1, 2, 3};

  callMerge(nums1, nums2);

  EXPECT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6}), nums1);
}

TEST_F(SolutionTest, NumsInterleaved) {
  nums1 = {1, 3, 5, 0, 0, 0};
  nums2 = {2, 4, 6};

  callMerge(nums1, nums2);

  EXPECT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6}), nums1);
}

TEST_F(SolutionTest, SingleNums1SingleNums2) {
  nums1 = {2, 0};
  nums2 = {1};

  callMerge(nums1, nums2);

  EXPECT_EQ(std::vector<int>({1, 2}), nums1);
}

TEST_F(SolutionTest, LeadingZerosInNums2) {
  nums1 = {0, 0, 0};
  nums2 = {0, 0, 1};

  callMerge(nums1, nums2);

  EXPECT_EQ(std::vector<int>({0, 0, 1}), nums1);
}

class MergeSortedArrayTestProperty : public SolutionTest {
protected:
  int m = *rc::gen::inRange(0, 200);
  int n = *rc::gen::inRange(0, 200);
  std::vector<int> nums1 = nonDecreasingVector(m);
  std::vector<int> nums2 = nonDecreasingVector(n);

  bool preConditionsMet() { return m + n >= 1; }

  void padWithZeros(std::vector<int> &nums) { nums.resize(m + n, 0); }

private:
  std::vector<int> nonDecreasingVector(int size) {
    std::vector<int> vec =
        *rc::gen::container<std::vector<int>>(size, rc::gen::arbitrary<int>());
    std::sort(vec.begin(), vec.end());
    return vec;
  }
};

void logVector(std::string vectorName, std::vector<int> vec) {
  std::cerr << vectorName << ": [";
  for (auto i : vec) {
    std::cerr << i << ' ';
  }
  std::cerr << ']' << std::endl;
}

RC_GTEST_FIXTURE_PROP(MergeSortedArrayTestProperty, Commutativity, ()) {
  RC_PRE(preConditionsMet());
  std::vector<int> nums1Copy = nums1;
  std::vector<int> nums2Copy = nums2;

  padWithZeros(nums1);
  padWithZeros(nums2Copy);

  callMerge(nums1, nums2);
  callMerge(nums2Copy, nums1Copy);

  RC_ASSERT(nums1 == nums2Copy);
}

RC_GTEST_FIXTURE_PROP(MergeSortedArrayTestProperty, HasCorrectElements, ()) {
  RC_PRE(preConditionsMet());

  std::vector<int> elements;
  elements.reserve(m + n);
  elements.insert(elements.end(), nums1.begin(), nums1.end());
  elements.insert(elements.end(), nums2.begin(), nums2.end());

  padWithZeros(nums1);
  callMerge(nums1, nums2);

  RC_ASSERT(std::is_permutation(nums1.begin(), nums1.end(), elements.begin()));
}

RC_GTEST_FIXTURE_PROP(MergeSortedArrayTestProperty, Nums1MergedWithEmptyIsNums1,
                      ()) {
  n = 0;
  nums2 = {};
  RC_PRE(preConditionsMet());

  std::vector<int> nums1Before = nums1;
  padWithZeros(nums1);
  callMerge(nums1, nums2);

  RC_ASSERT(nums1Before == nums1);
}

RC_GTEST_FIXTURE_PROP(MergeSortedArrayTestProperty, EmptyMergedWithNums2IsNums2,
                      ()) {
  m = 0;
  nums1 = {};
  RC_PRE(preConditionsMet());

  std::vector<int> nums2Before = nums2;
  padWithZeros(nums1);
  callMerge(nums1, nums2);

  RC_ASSERT(nums2Before == nums2);
}

RC_GTEST_FIXTURE_PROP(MergeSortedArrayTestProperty, NonDecreasingOrder, ()) {
  RC_PRE(preConditionsMet());

  padWithZeros(nums1);
  callMerge(nums1, nums2);

  RC_ASSERT(std::is_sorted(nums1.begin(), nums1.end()));
}
