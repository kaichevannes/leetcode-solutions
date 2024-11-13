#include "../../src/Array-String/01_merge_sorted_array.h"
#include <gtest/gtest.h>

class MergeSortedArrayTest : public testing::Test {
protected:
  MergeSortedArray mergeSortedArray;

  void callMerge(std::vector<int>& nums1, std::vector<int>& nums2) {
    mergeSortedArray.merge(nums1, nums1.size(), nums2, nums2.size());
  }
};

TEST_F(MergeSortedArrayTest, setup) {
  std::vector<int> nums1;
  std::vector<int> nums2;

  callMerge(nums1, nums2);

  EXPECT_EQ(nums2, std::vector<int>{1});
}
