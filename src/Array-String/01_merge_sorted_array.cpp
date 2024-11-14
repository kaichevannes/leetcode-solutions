#include "01_merge_sorted_array.h"

void MergeSortedArray::merge(std::vector<int> &nums1, int m,
                             std::vector<int> &nums2, int n) {
  int i = m - 1; // the current largest element of nums1
  int j = n - 1; // the current largest element of nums2
  int k =
      m + n -
      1; // the current index in nums1, updating from the end back to the start

  auto reachedNums1 = [=](int j) { return j >= 0; };
  // if we get to the start of nums1, all of the elements are in the correct
  // place.
  while (reachedNums1(j)) {
    if (i >= 0 && nums1[i] > nums2[j]) {
      nums1[k--] = nums1[i--];
    } else {
      nums1[k--] = nums2[j--];
    }
  }
};
