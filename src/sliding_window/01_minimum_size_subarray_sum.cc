#include "01_minimum_size_subarray_sum.h"

int MinimumSizeSubarraySum::minSubArrayLen(int target, std::vector<int> &nums) {
  int left = 0;
  int right = 0;
  int result = nums.size() + 1;
  int runningTotal = 0;

  while (right < nums.size()) {
    while (right < nums.size() && runningTotal < target) {
      runningTotal += nums[right++];
    }
    while (left < nums.size() && runningTotal >= target) {
      runningTotal -= nums[left++];
    }
    if (right - left + 1 < result) {
      result = right - left + 1;
    }
  }

  return result > nums.size() ? 0 : result;
}
