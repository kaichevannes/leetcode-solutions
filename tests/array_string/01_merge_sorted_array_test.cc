#include "../../src/array_string/01_merge_sorted_array.h"
#include "rapidcheck/Log.h"
#include "rapidcheck/gen/Arbitrary.h"
#include <algorithm>
#include <functional>
#include <gtest/gtest.h>
#include <numeric>
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

class MergeSortedArrayTestProperty : public MergeSortedArrayTest {
protected:
  const int m = *rc::gen::inRange(0, 200);
  const int n = *rc::gen::inRange(0, 200);
  std::vector<int> nums1 = nonDecreasingVector(m);
  std::vector<int> nums2 = nonDecreasingVector(n);

  bool preConditionsMet() { return m + n >= 1; }

private:
  std::vector<int> nonDecreasingVector(int size) {
    std::vector<int> vec = *rc::gen::container<std::vector<int>>(size, rc::gen::arbitrary<int>());
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
  auto padWithZeros = [=](std::vector<int> &nums) { nums.resize(m + n, 0); };
  std::vector<int> nums1Copy = nums1;
  std::vector<int> nums2Copy = nums2;
  RC_PRE(preConditionsMet());

  padWithZeros(nums1);
  padWithZeros(nums2Copy);

  callMerge(nums1, nums2);
  callMerge(nums2Copy, nums1Copy);

  RC_ASSERT(nums1 == nums2Copy);
}

// R_GTEST_FIXTURE_PROP(MergeSortedArrayTest, NumberOfElementsIsCorrect, ()) {
// }
