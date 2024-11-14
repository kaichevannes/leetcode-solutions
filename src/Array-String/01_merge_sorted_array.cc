#include "01_merge_sorted_array.h"

void mergeFromLargestToSmallest(int, int, int, std::vector<int> &, int,
                                std::vector<int> &, int);

/**
 * @brief Merge two non-decreasing arrays.
 *
 * This function takes two non-decreasing arrays nums1, and nums2. The first
 * array must be in the format of {int1, int2, ..., intm, 0, 0, 0} with m
 * integers and n 0s. The sorted array will be mutated in place in nums1.
 *
 * @param[in, out] nums1 The first sorted array, which will contain the result
 * after merging.
 * @param[in] m The number of elements to merge in nums1.
 * @param[in] nums2 The second sorted array. This will be merged into nums1.
 * @param[in] n The number elements to merge in nums2.
 */
void MergeSortedArray::merge(std::vector<int> &nums1, int m,
                             std::vector<int> &nums2, int n) {
  int largestInNums1 = m - 1;
  int largestInNums2 = n - 1;
  int insertIndex = m + n - 1;

  auto moreToMergeIntoNums1 = [&] { return largestInNums2 >= 0; };
  auto nums1NotEmpty = [&] { return largestInNums1 >= 0; };
  auto largerElementInNums1 = [&] {
    return nums1[largestInNums1] > nums2[largestInNums2];
  };

  while (moreToMergeIntoNums1()) {
    if (nums1NotEmpty() && largerElementInNums1()) {
      nums1[insertIndex--] = nums1[largestInNums1--];
    } else {
      nums1[insertIndex--] = nums2[largestInNums2--];
    }
  }
};
