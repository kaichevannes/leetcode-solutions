#include "01_minimum_size_subarray_sum.h"
#include <climits>

int MinimumSizeSubarraySum::minSubArrayLen(int target, std::vector<int> &nums) {
  int left = 0;
  int right = 0;
  int smallestSubArray = INT_MAX;
  int runningTotal = 0;

  auto canIncreaseSlidingWindow = [&] { return right < nums.size(); };
  auto canDecreaseSlidingWindow = [&] { return runningTotal >= target; };
  auto sizeOfSlidingWindow = [&] { return right - left + 1; };

  while (canIncreaseSlidingWindow()) {
    runningTotal += nums[right++];
    while (canDecreaseSlidingWindow()) {
      runningTotal -= nums[left++];
      smallestSubArray = std::min(smallestSubArray, sizeOfSlidingWindow());
    }
  }

  auto noSolutionFound = [&] { return smallestSubArray == INT_MAX; };
  return noSolutionFound() ? 0 : smallestSubArray;
}
