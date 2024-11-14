#include "../../src/Array-String/01_merge_sorted_array.h"
#include <gtest/gtest.h>

class MergeSortedArrayTest : public testing::Test {
protected:
  MergeSortedArray mergeSortedArray;
  std::vector<int> nums1;
  std::vector<int> nums2;

  void callMerge(std::vector<int> &nums1, std::vector<int> &nums2) {
    mergeSortedArray.merge(nums1, nums1.size() - nums2.size(), nums2, nums2.size());
  }
};

TEST_F(MergeSortedArrayTest, SingleElementInNums1) {
  nums1 = {1};

  callMerge(nums1, nums2);

  EXPECT_EQ(nums1, std::vector<int>{1});
}

TEST_F(MergeSortedArrayTest, SingleElementInNums2) {
  nums1 = {0};
  nums2 = {1};

  callMerge(nums1, nums2);

  EXPECT_EQ(nums1, std::vector<int>{0});
}

TEST_F(MergeSortedArrayTest, Nums1FollowedByNums2) {
  nums1 = {1, 2, 3, 0, 0, 0};
  nums2 = {4, 5, 6};

  callMerge(nums1, nums2);

  EXPECT_EQ(nums1, std::vector<int>({1, 2, 3, 4, 5, 6}));
}

TEST_F(MergeSortedArrayTest, Nums2FollowedByNums1) {
  nums1 = {4, 5, 6, 0, 0, 0};
  nums2 = {1, 2, 3};

  callMerge(nums1, nums2);

  EXPECT_EQ(nums1, std::vector<int>({1, 2, 3, 4, 5, 6}));
}

TEST_F(MergeSortedArrayTest, NumsInterleaved) {
  nums1 = {1, 3, 5, 0, 0, 0};
  nums2 = {2, 4, 6};

  callMerge(nums1, nums2);

  EXPECT_EQ(nums1, std::vector<int>({1, 2, 3, 4, 5, 6}));
}
