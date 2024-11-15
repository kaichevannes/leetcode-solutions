#include "01_minimum_size_subarray_sum.h"
#include <climits>

int MinimumSizeSubarraySum::minSubArrayLen(int target, std::vector<int> &nums) {
  int left = 0;
  int right = 0;
  int result = INT_MAX;
  int runningTotal = 0;

  while (right < nums.size()) {
    runningTotal += nums[right++];
    while (runningTotal >= target) {
      runningTotal -= nums[left++];
      if (right - left + 1 < result) {
        result = right - left + 1;
      }
    }
  }

  return result == INT_MAX ? 0 : result;
}
