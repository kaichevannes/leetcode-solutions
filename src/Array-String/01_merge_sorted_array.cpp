#include "01_merge_sorted_array.h"

void MergeSortedArray::merge(std::vector<int> &nums1, int m,
                             std::vector<int> &nums2, int n) {
  std::vector<int> output;
  int i = 0; // Pointer to next unsorted element in nums1
  int j = 0; // Pointer to next unsorted element in nums2

  auto moreElementsToMerge = [&] { return i + j < m + n; };
  auto lowestElementInNums1 = [&] { return nums1[i] < nums2[j]; };
  auto nums1HasElements = [&] { return i < m; };
  auto nums2HasElements = [&] { return j < n; };

  while (moreElementsToMerge()) {
    if (nums1HasElements() && nums2HasElements()) {
      if (lowestElementInNums1()) {
        output.push_back(nums1[i++]);
      } else {
        output.push_back(nums2[j++]);
      }
    } else if (nums1HasElements()) {
      output.push_back(nums1[i++]);
    } else if (nums2HasElements()) {
      output.push_back(nums2[j++]);
    }
  }

  nums1 = output;
};
