#include <gtest/gtest.h>
#include "../../src/Array-String/01_merge_sorted_array.h"

TEST(MergeSortedArrayTest, setup) {
  std::vector<int> nums1;
  int m = 0;
  std::vector<int> nums2;
  int n = 0;

  MergeSortedArray mergeSortedArray;
  mergeSortedArray.merge(nums1, m, nums2, n);

  std::vector<int> expectedNums2 = {1};
  EXPECT_EQ(nums2, expectedNums2);
}
