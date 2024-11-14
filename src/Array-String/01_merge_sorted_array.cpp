#include "01_merge_sorted_array.h"

void MergeSortedArray::merge(std::vector<int> &nums1, int m,
                             std::vector<int> &nums2, int n) {
  int i = m - 1;
  int j = n - 1;
  int k = m + n - 1;

  // if we get to the start of nums1, all of the elements are in the correct
  // place.
  while (j >= 0) {
    if (i >= 0 && nums1[i] > nums2[j]) {
      nums1[k--] = nums1[i--];
    } else {
      nums1[k--] = nums2[j--];
    }
  }
};
