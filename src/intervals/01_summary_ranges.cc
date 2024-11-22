#include "01_summary_ranges.h"
#include <algorithm>
#include <format>
#include <iterator>

struct Range {
  int start;
  int end;
};

std::vector<Range> buildRanges(const std::vector<int> &nums) {
  std::vector<Range> ranges;

  auto isConsecutiveWithCurrentRange = [&](int num) -> bool {
    return num == ranges.back().end + 1;
  };
  auto extendCurrentRange = [&](int num) { ranges.back().end += 1; };
  auto startNewRange = [&](int num) { ranges.emplace_back(Range{num, num}); };

  for (int num : nums) {
    if (!ranges.empty() && isConsecutiveWithCurrentRange(num)) {
      extendCurrentRange(num);
    } else {
      startNewRange(num);
    }
  }

  return ranges;
}

std::vector<std::string>
convertRangesToStrings(const std::vector<Range> &ranges) {
  auto rangeToString = [](const Range &range) {
    if (range.start == range.end) {
      return std::format("{}", range.start);
    }
    return std::format("{}->{}", range.start, range.end);
  };

  std::vector<std::string> result;
  std::ranges::transform(ranges, std::back_inserter(result), rangeToString);
  return result;
}

std::vector<std::string> SummaryRanges::summaryRanges(std::vector<int> &nums) {
  if (nums.empty())
    return {};
  std::vector<Range> ranges = buildRanges(nums);
  return convertRangesToStrings(ranges);
}
